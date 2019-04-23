/******************************************************************************

 @File         DrawLoadDemo.cpp

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  Particle animation system. Requires the PVRShell.

******************************************************************************/

#include "ParticleSystemCPU.h"

#include "MGLPVRShell.h"
#include "OGLES2Tools.h"
#import <MoltenGL/mglext.h>

/******************************************************************************
 Content file names
******************************************************************************/

// Asset files

#ifndef MGL_DEMO_POLY_SIZE
#	define MGL_DEMO_POLY_SIZE	80
#endif

#if (MGL_DEMO_POLY_SIZE == 1280)
const char c_szSphereModelFile[] = "isosphere-1280-tris.pod";
#endif
#if (MGL_DEMO_POLY_SIZE == 320)
const char c_szSphereModelFile[] = "isosphere-320-tris.pod";
#endif
#if (MGL_DEMO_POLY_SIZE == 80)
const char c_szSphereModelFile[] = "isosphere-80-tris.pod";
#endif

// Source and binary shaders
const char c_szFragShaderSrcFile[]	= "FragShader.fsh";
const char c_szVertShaderSrcFile[]	= "VertShader.vsh";

/******************************************************************************
 Defines
******************************************************************************/

// Maximum number of m_Particles
const unsigned int g_ui32MinNoParticles = 1 << 9;
const unsigned int g_ui32MaxNoParticles = 1 << 16;
const unsigned int g_ui32InitialNoParticles = 1 << 10;
const float g_fCameraNear = 1.0f;
const float g_fCameraFar = 100.0f;

const PVRTVec3 g_caLightPosition(0.0f, 10.0f, 0.0f);

// Index to bind the attributes to vertex shaders
#define POSITION_ARRAY	0
#define LIFESPAN_ARRAY	1

#define VERTEX_ARRAY	0
#define NORMAL_ARRAY	1

/******************************************************************************
 Structure definitions
******************************************************************************/

const Sphere g_caSpheres[] = 
{
	{ { -20.0f,  6.0f,   0.0f },  4.0f },
	{ {   0.0f,  6.0f,  20.0f },  4.0f },
	{ {  27.0f,  6.0f,   0.0f },  5.0f },
	{ {   0.0f,  6.0f, -18.0f },  4.0f },	

	{ { -10.0f,  3.0f, -11.0f },  2.0f },
	{ { -11.0f,  3.0f,  10.0f },  1.5f },
	{ {  10.0f,  5.0f,  11.0f },  3.0f },
	{ {  10.0f,  4.0f, -10.0f },  2.0f },	

};
const unsigned int g_cuiNumSpheres = sizeof(g_caSpheres) / sizeof(g_caSpheres[0]);

/*!****************************************************************************
 Class implementing the PVRShell functions.
******************************************************************************/
class DrawLoadDemo : public MGLPVRShell
{
public:

	// Shader ids
	GLuint m_uiSimpleVertShader;
	GLuint m_uiSimpleFragShader;

	CPVRTModelPOD m_Scene;
	Mesh m_SphereMesh;
	GLuint m_uiVbo;
	GLuint m_uiIbo;
	bool m_isPaused;
	double m_numParticles;	// As double for precision on increases and decreases

	// View matrix
	PVRTMat4 m_mView, m_mProjection, m_mViewProjection;

	ParticleSystemCPU* m_pParticleSystem;

	struct
	{
		GLuint uiId;
		GLint iModelViewMatrixLoc;
		GLint iModelViewITMatrixLoc;
		GLint iModelViewProjectionMatrixLoc;
		GLint iLightPosition;
		GLint iColorLoc;
	}
	m_SimpleShaderProgram;

public:
	
	virtual bool InitApplication();
	virtual bool InitView();
	virtual bool ReleaseView();
	virtual bool QuitApplication();
	virtual bool RenderScene();
	
	bool LoadVbos(CPVRTString* const pErrorStr);
	bool LoadShaders(CPVRTString* const pErrorStr);
	float UpdateFramerateCounter();

	void HandleInput();
	
	void RenderFloor();
	void RenderSphere(PVRTVec3 position, float radius);
	void RenderParticles();

	void UpdateParticles();
};

/*!****************************************************************************
 @Function		LoadVbos
 @Description	Loads the mesh data required for this training course into
				vertex buffer objects
******************************************************************************/
bool DrawLoadDemo::LoadVbos(CPVRTString* const pErrorStr)
{
	glGenBuffers(1, &m_uiVbo);
	
	// Load vertex data into buffer object
	SPODMesh& Mesh = m_Scene.pMesh[0];
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh.nNumVertex * Mesh.sVertex.nStride, Mesh.pInterleaved, GL_STATIC_DRAW);

	PVRShellOutputDebug("Sphere mesh contains %d vertices and %d faces.\n", Mesh.nNumVertex, Mesh.nNumFaces);

	// Load index data into buffer object
	glGenBuffers(1, &m_uiIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, PVRTModelPODCountIndices(Mesh) * sizeof(GLshort), Mesh.sFaces.pData, GL_STATIC_DRAW);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Cache the mesh info for a sphere mesh
	m_SphereMesh.pMesh = &Mesh;
	m_SphereMesh.vtxBuff = m_uiVbo;
	m_SphereMesh.idxBuff = m_uiIbo;



	return true;
}

/*!****************************************************************************
 @Function		LoadShaders
 @Output		pErrorStr		A string describing the error on failure
 @Return		bool			true if no error occured
 @Description	Loads and compiles the shaders and links the shader programs
				required for this training course
******************************************************************************/
bool DrawLoadDemo::LoadShaders(CPVRTString* const pErrorStr)
{
	/*
	 *  Simple Shader
	 */
	const char* aszSimpleAttribs[] = { "inVertex", "inNormal" };
	const unsigned int numSimpleAttribs = sizeof(aszSimpleAttribs) / sizeof(aszSimpleAttribs[0]);

	if (PVRTShaderLoadFromFile(NULL, c_szVertShaderSrcFile, GL_VERTEX_SHADER, GL_SGX_BINARY_IMG, &m_uiSimpleVertShader, pErrorStr) != PVR_SUCCESS)
		return false;

	if (PVRTShaderLoadFromFile(NULL, c_szFragShaderSrcFile, GL_FRAGMENT_SHADER, GL_SGX_BINARY_IMG, &m_uiSimpleFragShader, pErrorStr) != PVR_SUCCESS)
		return false;

	if (PVRTCreateProgram(&m_SimpleShaderProgram.uiId, m_uiSimpleVertShader, m_uiSimpleFragShader, aszSimpleAttribs, numSimpleAttribs, pErrorStr) != PVR_SUCCESS)
		return false;

	m_SimpleShaderProgram.iModelViewMatrixLoc = glGetUniformLocation(m_SimpleShaderProgram.uiId, "uModelViewMatrix");
	m_SimpleShaderProgram.iModelViewITMatrixLoc = glGetUniformLocation(m_SimpleShaderProgram.uiId, "uModelViewITMatrix");
	m_SimpleShaderProgram.iModelViewProjectionMatrixLoc	= glGetUniformLocation(m_SimpleShaderProgram.uiId, "uModelViewProjectionMatrix");
	m_SimpleShaderProgram.iLightPosition = glGetUniformLocation(m_SimpleShaderProgram.uiId, "uLightPosition");
	m_SimpleShaderProgram.iColorLoc = glGetUniformLocation(m_SimpleShaderProgram.uiId, "uColor");

	return true;
}

/*!****************************************************************************
 @Function		InitApplication
 @Return		bool		true if no error occured
 @Description	Code in InitApplication() will be called by PVRShell once per
				run, before the rendering context is created.
				Used to initialize variables that are not dependant on it
				(e.g. external modules, loading meshes, etc.)
				If the rendering context is lost, InitApplication() will
				not be called again.
******************************************************************************/
bool DrawLoadDemo::InitApplication()
{
	m_isPaused = false;
	m_pParticleSystem = 0;

	// Get and set the read path for content files
	CPVRTResourceFile::SetReadPath((char*)PVRShellGet(prefReadPath));

	// Get and set the load/release functions for loading external files.
	// In the majority of cases the PVRShell will return NULL function pointers implying that
	// nothing special is required to load external files.
	CPVRTResourceFile::SetLoadReleaseFunctions(PVRShellGet(prefLoadFileFunc), PVRShellGet(prefReleaseFileFunc));

	// Load the scene
	if(m_Scene.ReadFromFile(c_szSphereModelFile) != PVR_SUCCESS)
	{
		PVRShellSet(prefExitMessage, "ERROR: Couldn't load the sphere.pod file\n");
		return false;
	}
	
	srand((unsigned int) PVRShellGetTime());

	PVRShellSet(prefSwapInterval, 0);

	return true;
}

/*!****************************************************************************
 @Function		QuitApplication
 @Return		bool		true if no error occured
 @Description	Code in QuitApplication() will be called by PVRShell once per
				run, just before exiting the program.
				If the rendering context is lost, QuitApplication() will
				not be called.
******************************************************************************/
bool DrawLoadDemo::QuitApplication()
{
	if (m_pParticleSystem) delete m_pParticleSystem;
	m_Scene.Destroy();

	return true;
}

/*!****************************************************************************
 @Function		InitView
 @Return		bool		true if no error occured
 @Description	Code in InitView() will be called by PVRShell upon
				initialization or after a change in the rendering context.
				Used to initialize variables that are dependant on the rendering
				context (e.g. textures, vertex buffers, etc.)
******************************************************************************/
bool DrawLoadDemo::InitView()
{

//	glDisable(GL_DEFERRED_DRAWABLE_MGL);

	CPVRTString ErrorStr;
	bool bRotate = PVRShellGet(prefIsRotated) && PVRShellGet(prefFullScreen);

	// Initialize Print3D textures
	if(m_Print3D.SetTextures(0, PVRShellGet(prefWidth), PVRShellGet(prefHeight), bRotate) != PVR_SUCCESS)
	{
		PVRShellSet(prefExitMessage, "ERROR: Cannot initialise Print3D\n");
		return false;
	}

	//	Load and compile the shaders & link programs
	if (!LoadVbos(&ErrorStr))
	{
		PVRShellSet(prefExitMessage, ErrorStr.c_str());
		return false;
	}

	//	Load and compile the shaders & link programs
	if (!LoadShaders(&ErrorStr))
	{
		PVRShellSet(prefExitMessage, ErrorStr.c_str());
		return false;
	}

	// Creates the projection matrix.
	m_mProjection = PVRTMat4::PerspectiveFovRH(PVRT_PI / 3.0f, (float)PVRShellGet(prefWidth)/(float)PVRShellGet(prefHeight), g_fCameraNear, g_fCameraFar, PVRTMat4::OGL, bRotate);
			
	m_pParticleSystem = new ParticleSystemCPU();
	if (!m_pParticleSystem->Init(&ErrorStr))
	{
		PVRShellSet(prefExitMessage, ErrorStr.c_str());
		return false;
	}

	m_pParticleSystem->SetParticleMesh(&m_SphereMesh);
	m_pParticleSystem->SetCollisionSpheres(g_caSpheres, g_cuiNumSpheres);

	m_numParticles = g_ui32InitialNoParticles;
	m_pParticleSystem->SetNumberOfParticles(m_numParticles);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Enable culling
	glEnable(GL_CULL_FACE);
	return true;
}

/*!****************************************************************************
 @Function		ReleaseView
 @Return		bool		true if no error occured
 @Description	Code in ReleaseView() will be called by PVRShell when the
				application quits or before a change in the rendering context.
******************************************************************************/
bool DrawLoadDemo::ReleaseView()
{
	// Release shaders
	glDeleteShader(m_uiSimpleFragShader);
	glDeleteShader(m_uiSimpleVertShader);

	glDeleteProgram(m_SimpleShaderProgram.uiId);

	// Release buffers
	glDeleteBuffers(1, &m_uiVbo);
	glDeleteBuffers(1, &m_uiIbo);
	
	// Release Print3D Textures
	m_Print3D.ReleaseTextures();
	return true;
}

/*!****************************************************************************
 @Function		RenderScene
 @Return		bool		true if no error occured
 @Description	Main rendering loop function of the program. The shell will
				call this function every frame.
				eglSwapBuffers() will be performed by PVRShell automatically.
				PVRShell will also manage important OS events.
				Will also manage relevent OS events. The user has access to
				these events through an abstraction layer provided by PVRShell.
******************************************************************************/
bool DrawLoadDemo::RenderScene()
{
	MGLPVRShellUpdateFPS();
	HandleInput();
	UpdateParticles();

	float time_delta = PVRShellGetTime() / 10000.0f;
	PVRTVec3 vFrom = PVRTVec3((float) sin(time_delta) * 50.0f, 30.0f, (float) cos(time_delta) * 50.0f);
	m_mView = PVRTMat4::LookAtRH(vFrom, PVRTVec3(0.0f, 5.0f, 0.0f), PVRTVec3(0.0f, 1.0f, 0.0f));
	m_mViewProjection = m_mProjection * m_mView;

	// Clear colour and depth buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enables depth testing
	glEnable(GL_DEPTH_TEST);

	// Render floor
	RenderFloor();

	for (unsigned int i=0; i < g_cuiNumSpheres; i++) {
		RenderSphere(g_caSpheres[i].aPosition, g_caSpheres[i].fRadius);
	}

	// Render particles
	RenderParticles();

	// Display info text.
	unsigned int numDrawCalls = m_pParticleSystem->GetNumberOfParticles() + g_cuiNumSpheres + 1;
	DisplayTitle("DrawLoad");
	m_Print3D.Print3D(2.0f, 90.0f, 0.5f, 0xFFFFFFFF, "Draws: %d | Triangles per: %d | Triangles total: %d | FPS: %d",
					  numDrawCalls, MGL_DEMO_POLY_SIZE, (MGL_DEMO_POLY_SIZE * numDrawCalls), m_fps);
	m_Print3D.Flush();
	
	return true;
}

/*!****************************************************************************
 @Function		RenderSphere
 @Description	Renders a sphere at the specified position.
 ******************************************************************************/
void DrawLoadDemo::RenderSphere(PVRTVec3 position, float radius)
{
	glUseProgram(m_SimpleShaderProgram.uiId);

	PVRTMat4 mModel = PVRTMat4::Translation(position) * PVRTMat4::Scale(radius, radius, radius);
	PVRTMat4 mModelView = m_mView * mModel;
	PVRTMat4 mModelViewProj = m_mProjection * mModelView;
	PVRTMat3 mModelViewIT(mModelView.inverse().transpose());
	glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewProjectionMatrixLoc, 1, GL_FALSE, mModelViewProj.f);
	glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewMatrixLoc, 1, GL_FALSE, mModelView.f);
	glUniformMatrix3fv(m_SimpleShaderProgram.iModelViewITMatrixLoc, 1, GL_FALSE, mModelViewIT.f);

	PVRTVec3 vLightPosition = m_mView * PVRTVec4(g_caLightPosition, 1.0f);
	glUniform3fv(m_SimpleShaderProgram.iLightPosition, 1, &vLightPosition.x);

	PVRTVec4 color = PVRTVec4(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(m_SimpleShaderProgram.iColorLoc, 1, &color.x);

	// Enable vertex arributes
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIbo);

	SPODMesh* pMesh = &m_Scene.pMesh[0];
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sVertex.nStride, pMesh->sVertex.pData);
	glVertexAttribPointer(NORMAL_ARRAY, 3, GL_FLOAT, GL_FALSE, pMesh->sNormals.nStride, pMesh->sNormals.pData);

	// Indexed Triangle list
	glDrawElements(GL_TRIANGLES, pMesh->nNumFaces*3, GL_UNSIGNED_SHORT, 0);

	// Safely disable the vertex attribute arrays
	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*!****************************************************************************
 @Function		RenderFloor
 @Description	Renders the floor as a quad.
******************************************************************************/
void DrawLoadDemo::RenderFloor()
{
	glUseProgram(m_SimpleShaderProgram.uiId);

	PVRTMat3 mViewIT(m_mView.inverse().transpose());
	glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewProjectionMatrixLoc, 1, GL_FALSE, m_mViewProjection.f);
	glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewMatrixLoc, 1, GL_FALSE, m_mView.f);
	glUniformMatrix3fv(m_SimpleShaderProgram.iModelViewITMatrixLoc, 1, GL_FALSE, mViewIT.f);

	PVRTVec3 vLightPosition = m_mView * PVRTVec4(g_caLightPosition, 1.0f);
	glUniform3fv(m_SimpleShaderProgram.iLightPosition, 1, &vLightPosition.x);

	PVRTVec4 color = PVRTVec4(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(m_SimpleShaderProgram.iColorLoc, 1, &color.x);

	// Enable vertex arributes
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(NORMAL_ARRAY);

	PVRTVec2 minCorner(-100.0f, -100.0f);
	PVRTVec2 maxCorner( 100.0f,  100.0f);

	const float afVertexData[] = { minCorner.x, 0.0f, minCorner.y, minCorner.x, 0.0f, maxCorner.y,  
		                           maxCorner.x, 0.0f, minCorner.y, maxCorner.x, 0.0f, maxCorner.y };
	const float afNormalData[] = { 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f };

	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, afVertexData);
	glVertexAttribPointer(NORMAL_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, afNormalData);

	// Draw the quad
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Safely disable the vertex attribute arrays
	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(NORMAL_ARRAY);	
}


/*!****************************************************************************
 @Function		RenderParticles
 @Description	Renders the particles.
******************************************************************************/
void DrawLoadDemo::RenderParticles()
{	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		
	glUseProgram(m_SimpleShaderProgram.uiId);
	
	const Particle *particles = m_pParticleSystem->GetParticleArray();
	const unsigned int partCnt = m_pParticleSystem->GetNumberOfParticles();

	for (unsigned int partIdx = 0; partIdx < partCnt; partIdx++) {
		const Particle* pPart = &particles[partIdx];

		PVRTMat4 mModel = PVRTMat4::Translation(pPart->position) * PVRTMat4::Scale(pPart->radius);
		PVRTMat4 mModelView = m_mView * mModel;
		PVRTMat4 mModelViewProj = m_mProjection * mModelView;
		PVRTMat3 mModelViewIT(mModelView.inverse().transpose());
		glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewProjectionMatrixLoc, 1, GL_FALSE, mModelViewProj.f);
		glUniformMatrix4fv(m_SimpleShaderProgram.iModelViewMatrixLoc, 1, GL_FALSE, mModelView.f);
		glUniformMatrix3fv(m_SimpleShaderProgram.iModelViewITMatrixLoc, 1, GL_FALSE, mModelViewIT.f);

		PVRTVec3 vLightPosition = m_mView * PVRTVec4(g_caLightPosition, 1.0f);
		glUniform3fv(m_SimpleShaderProgram.iLightPosition, 1, &vLightPosition.x);

		glUniform4fv(m_SimpleShaderProgram.iColorLoc, 1, &pPart->color.x);

		Mesh* pMesh = pPart->pMesh;

		// Enable vertex arributes
		glEnableVertexAttribArray(VERTEX_ARRAY);
		glEnableVertexAttribArray(NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, pMesh->vtxBuff);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->idxBuff);

		SPODMesh* pSPODMesh = pMesh->pMesh;
		glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, pSPODMesh->sVertex.nStride, pSPODMesh->sVertex.pData);
		glVertexAttribPointer(NORMAL_ARRAY, 3, GL_FLOAT, GL_FALSE, pSPODMesh->sNormals.nStride, pSPODMesh->sNormals.pData);

		// Indexed Triangle list
		glDrawElements(GL_TRIANGLES, pSPODMesh->nNumFaces*3, GL_UNSIGNED_SHORT, 0);

		// Safely disable the vertex attribute arrays
		glDisableVertexAttribArray(VERTEX_ARRAY);
		glDisableVertexAttribArray(NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisable(GL_BLEND);
	}
}

/*!****************************************************************************
 @Function		UpdateParticles
 @Description	Updates particle positions and attributes, e.g. lifespan.
******************************************************************************/
void DrawLoadDemo::UpdateParticles()
{
	if (m_isPaused) { return; }

	static long lastTime = PVRShellGetTime();
	long nowTime = PVRShellGetTime();
	long elapsedTime = nowTime - lastTime;
	float step = elapsedTime / 140.0f;
	lastTime = nowTime;
		
	static float rot_angle = 0.0f;
	rot_angle += step / 2.0f;		
	float el_angle = ((float) sin(rot_angle / 4.0f) + 1.0f) * 0.2f + 0.2f;

	PVRTMat4 rot = PVRTMat4::RotationY(rot_angle);
	PVRTMat4 skew = PVRTMat4::RotationZ(el_angle);
	
	Emitter sEmitter;
	sEmitter.mTransformation = rot * skew;
	sEmitter.fHeight = 2.0f;
	sEmitter.fRadius = 0.35f;

	m_pParticleSystem->SetEmitter(sEmitter);
	m_pParticleSystem->Update(step);
}


/*!****************************************************************************
 @Function		HandleInput
 @Description	Handles user input and updates live variables accordingly.
******************************************************************************/
void DrawLoadDemo::HandleInput()
{
	if (PVRShellIsKeyPressed(PVRShellKeyNameLEFT))
	{
		m_numParticles = m_numParticles / M_SQRT2;
		if (m_numParticles < g_ui32MinNoParticles) { m_numParticles = g_ui32MinNoParticles; }
		m_pParticleSystem->SetNumberOfParticles(m_numParticles);
	}

	if (PVRShellIsKeyPressed(PVRShellKeyNameRIGHT))
	{
		m_numParticles = m_numParticles * M_SQRT2;
		if (m_numParticles > g_ui32MaxNoParticles) { m_numParticles = g_ui32MaxNoParticles; }
		m_pParticleSystem->SetNumberOfParticles(m_numParticles);
	}

	if (PVRShellIsKeyPressed(PVRShellKeyNameACTION1) || PVRShellIsKeyPressed(PVRShellKeyNameACTION2))
	{
		m_isPaused = !m_isPaused;
	}
}

/*!****************************************************************************
 @Function		NewDemo
 @Return		PVRShell*		The demo supplied by the user
 @Description	This function must be implemented by the user of the shell.
				The user should return its PVRShell object defining the
				behaviour of the application.
******************************************************************************/
PVRShell* NewDemo()
{
	return new DrawLoadDemo();
}

/******************************************************************************
 End of file (DrawLoadDemo.cpp)
******************************************************************************/


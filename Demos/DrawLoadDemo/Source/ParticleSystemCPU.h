/*!****************************************************************************
 @File          ParticleSystemCPU.h

 @Title         ParticleSystemCPU

 @Copyright     Copyright (C) by Imagination Technologies Limited.

 @Platform      Independant

 @Description   Particle system implemented using the CPU.
******************************************************************************/

#ifndef _PARTICLESYSTEMCPU__H_
#define _PARTICLESYSTEMCPU__H_

#include "OGLES2Tools.h"

struct Mesh
{
	SPODMesh* pMesh;
	GLuint vtxBuff;
	GLuint idxBuff;
};

struct Emitter
{
	PVRTMat4 mTransformation;
	float fHeight;
	float fRadius;
};

struct Particle
{
	PVRTVec3 position;
	PVRTVec3 velocity;
	float lifespan;
	float radius;
	PVRTVec4 color;
	Mesh* pMesh;
};

struct Sphere
{
	float aPosition[3];
	float fRadius;
};

class ParticleSystemCPU
{
public:

	ParticleSystemCPU();
	virtual ~ParticleSystemCPU();

	bool Init(CPVRTString *pErrorStr) { return true; }

	bool Update(float step);

	bool SetEmitter(const Emitter &emitter);
	bool SetCollisionSpheres(const Sphere *pSpheres, unsigned int uiNumSpheres);
	bool SetNumberOfParticles(unsigned int numParticles);	
	bool SetParticleMesh(Mesh* particleMesh);

	unsigned int GetNumberOfParticles() const { return m_aParticles.GetSize(); }
	const Particle* GetParticleArray(void){ return &(m_aParticles[0]); }
	
protected:
	
	Emitter					m_sEmitter;
	CPVRTArray<Sphere>		m_aSpheres;
	CPVRTArray<float>		m_aSquaredRadii;
	CPVRTArray<Particle>	m_aParticles;
	Mesh*					m_ParticleMesh;
};

#endif // _PARTICLESYSTEMCPU__H_

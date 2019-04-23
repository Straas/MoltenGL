<a class="site-logo" href="http://moltengl.com/" title="MoltenGL">
	<img src="images/MoltenGL-Logo-Banner.png" alt="MoltenGL Home" style="width:256px;height:auto">
</a>

MoltenGL Runtime User Guide
===========================

Copyright (c) 2014-2019 [The Brenwill Workshop Ltd.](http://www.brenwill.com) All rights reserved.

*This document is written in [Markdown](http://en.wikipedia.org/wiki/Markdown) format. 
For best results, use a Markdown reader.*



Table of Contents
-----------------

- [**MoltenGL** License Agreement](#license)
- [About **MoltenGL**](#about)
- [Running the **MoltenGL** Demo Applications](#demos)
- [Installing **MoltenGL** in Your *OpenGL ES 2.0* Application](#install)
- [Adding Support for Native *OpenGL ES 2.0* in *macOS*](#ogles-macos)
- [Activating Your **MoltenGL** License](#licensing)
- [**MoltenGL** Product Support](#support)
- [Supported *OpenGL ES 2.0* Extensions](#extensions)
- [Device Platforms and *OpenGL* System Classes](#platforms)
	- [Modifying the Scenarios](#modifying_scenarios)
	- [EAGL and GLKit System Classes](#system_classes)
- [Interacting with the **MoltenGL** Runtime](#interaction)
- [*Metal* Shaders](#shaders)
	- [*Metal* Shader Texture Coordinates](#shader_tex_coords)
- [MoltenGLShaderConverter Shader Converter Tool](#shader_converter_tool)
- [Troubleshooting Shader Conversion](#glsl_vs_msl)
	- [*GLSL* Preprocessor Directives](#shader_preproc)
	- [Using Texture Arrays in Shaders](#shader_tex_arrays)
	- [Sampling Depth Textures in Shaders](#shader_depth_tex)
- [Performance Considerations](#performance)
	- [Call Latency](#call_latency)
	- [Shader Loading Time](#shader_load_time)
	- [Xcode Configuration](#xcode_config)
	- [Metal System Trace Tool](#trace_tool)
- [Known **MoltenGL** Limitations](#limitations)



<a name="license"></a>

**MoltenGL** License Agreement
------------------------------

**CAREFULLY READ THE *[MoltenGL LICENSE AGREEMENT](MoltenGL_LICENSE.md)*, FOUND IN THIS MoltenGL
DISTRIBUTION PACKAGE. BY INSTALLING OR OTHERWISE USING THIS MoltenGL DISTRIBUTION PACKAGE, YOU
ACCEPT AND AGREE TO BE BOUND BY THE TERMS AND CONDITIONS OF THE *MoltenGL LICENSE AGREEMENT*.
IF YOU DO NOT ACCEPT THE TERMS AND CONDITIONS OF THE *MoltenGL LICENSE AGREEMENT*, DO NOT 
INSTALL OR USE THIS MoltenGL DISTRIBUTION PACKAGE.**



<a name="about"></a>

About **MoltenGL**
------------------

**MoltenGL** is an implementation of the [*OpenGL ES 2.0*](https://www.khronos.org/opengles/2_X/) 
API, that runs on Apple's [*Metal*](https://developer.apple.com/metal/) graphics framework on both
*iOS* and *macOS*.

**MoltenGL** provides the performance benefits and added [debugging and tracing capabilities](#trace_tool)
of the *Metal* framework, while maintaining compliance with the proven *OpenGL ES 2.0* API. 
Applications built on *OpenGL ES 2.0*, can use **MoltenGL** to provide additional graphic 
performance and development capabilities, without having to abandon the familiar 
*OpenGL ES 2.0* API, or rewrite rendering logic and shaders for different platforms.

**MoltenGL** runs on either *iOS* or *macOS*, and provides a fast implementation of *OpenGL ES 2.0*
on both platforms. In addition to improving performance on each platform, **MoltenGL** allows you 
to easily transfer your *OpenGL ES 2.0* application from *iOS* to *macOS* without having to rewrite
your application in desktop *OpenGL* for use on *macOS*. On both platforms, your *OpenGL ES 2.0*
application will benefit from the speed and additional debugging and tracing capabilities of *Metal*.

**MoltenGL** automatically detects whether the device your application is running on supports
*Metal*, and will use the *Metal* framework where available. When running on a device that
does not support *Metal*, **MoltenGL** will automatically downshift, and transparently make
use of the native *OpenGL ES 2.0* rendering engine (see the 
[Adding Support for Native *OpenGL ES 2.0* in *macOS*](#ogles-macos) section below for how
to arrange this on the *macOS* platform).

*Metal* uses a different shading language, the *Metal Shading Language (MSL)*, than 
*OpenGL ES 2.0*, which uses the *OpenGL Shading Language (GLSL)*. However, fear not, 
as **MoltenGL** will automatically convert your *GLSL* shaders to their *MSL* equivalents. 
This can be performed transparently at run time, using the **Runtime Shader Conversion**
feature of **MoltenGL**, or at development time using the 
[**MoltenGLShaderConverter**](#shader_converter_tool) tool provided with **MoltenGL**.



<a name="demos"></a>

Running the **MoltenGL** Demo Applications
------------------------------------------

You can explore the range of performance improvements and additional debugging and tracing
capabilities that **MoltenGL** can bring to your *OpenGL ES* applications by reviewing and 
running the demo applications that come with **MoltenGL**.

The **MoltenGL** sample apps are located in the `MoltenGL/Demos` folder within the **MoltenGL**
distribution package. Each demo app is available as an *Xcode* project. To allow you to 
compare performance, each app project can be built to render using either *MoltenGL*, or the 
native *OpenGL ES* engine.

To review and run all of the available demo apps, open the `MoltenGL/Demos/Demos.xcworkspace` 
workspace in *Xcode*.

Please read the [Demos/README.md](../Demos/README.md) document for a description of each demo app, 
and instructions on running the demo apps. In particular, run the *DrawLoad* sample app, to 
explore the conditions under which *Metal* performs better than *OpenGL*



<a name="install"></a>

Installing **MoltenGL** in Your *OpenGL ES 2.0* Application
----------------------------------------------------------

Installation of **MoltenGL** is straightforward and easy! To add **MoltenGL** to your 
*OpenGL ES 2.0* application, follow the steps in this section. If you're new to **MoltenGL**, 
it is recommended that you start with a smaller project to help you understand the transition,
and to reduce the possibility of needing to make modifications to your [shaders](#shaders) to 
ensure their compatibility with the *Metal* environment. 

1. Open your application in *Xcode* and select your application's project in the 
   *Project Navigator* panel.

2. **MoltenGL** intercepts and redirects your application's *OpenGL API* calls to functionality 
   within **MoltenGL**. To enable this, you need to make a few changes to the *Build Settings* 
   in your *Xcode*  project, as follows:

	1. In the *Project Navigator* panel, select your application's project, and open the 
	   *Build Settings* tab.
	2. Set the **Always Search User Paths** (aka `ALWAYS_SEARCH_USER_PATHS`) setting to `YES`.
	3. In the **User Header Search Paths** (aka `USER_HEADER_SEARCH_PATHS`) setting, add an 
	   entry that points to the `MoltenGL/RedirectHeaders/include` folder, found in the 
	   **MoltenGL** distribution package, and mark it as `recursive`. Be sure that you have 
	   ***not*** included the `MoltenGL/RedirectHeaders/orig` folder.   
	4. In the **Framework Search Paths** (aka `FRAMEWORK_SEARCH_PATHS`) build setting, add 
	   entries that point to the `MoltenGL/iOS` and `MoltenGLShaderConverter/iOS` folders 
	   in the **MoltenGL** distribution package (or the `MoltenGL/macOS`  and 
	   `MoltenGLShaderConverter/macOS` folders if building a *macOS* app).
	5. Set the **Enable Modules (C and Objective-C)** (aka `CLANG_ENABLE_MODULES`) setting 
	   to `NO`. Modules interfere with the ability to redirect the *OpenGL* API references.

	(Alternately, you can make the above changes to the *Xcode* project targets that 
	reference *OpenGL* API or *EAGL* header files). 
	
3. Repeat the previous step for any *Xcode* **sub-projects** that also reference *OpenGL* 
   API or *EAGL* header files. 

4. Within *Xcode*, add the **MoltenGL** framework to your application as follows:

	1. In the *Project Navigator* panel, select your application's project, select the 
	   *Build Phases* tab, and open the *Link Binary With Libraries* list.
	2. Click the **+** button, and in the dialog window that opens, click the 
	   *Add Other...* button. Locate `MoltenGL/iOS/MoltenGL.framework` in the **MoltenGL** 
	   distribution package (or locate `MoltenGL/macOS/MoltenGL.framework` if building an 
	   *macOS* app), and click the *Open* button.
	3. In the *Link Binary With Libraries* list, click the **+** button again, and 
	   (selecting from the list of system frameworks) add `Metal.framework` and 
	   `libc++.tbd` (or `libc++.dylib` in *Xcode 6* and earlier).
	4. Because of the need to set the **Enable Modules (C and Objective-C)** 
	   (aka `CLANG_ENABLE_MODULES`) build setting to `NO` (see above), the 
	   **Link Frameworks Automatically** (aka `CLANG_MODULES_AUTOLINK`) build setting 
	   will no longer have any effect. If you have not already done so, in the 
	   *Link Binary With Libraries* list, ensure that you have added any other system frameworks
	   that your application uses (e.g. `OpenGLES`, `UIKit`, `GLKit`, `QuartzCore`, etc.).
	
5. If you are just starting out, and want to make use of **Runtime Shader Conversion** to 
   transparently convert your *OpenGL* shaders to *Metal* shaders at runtime, you can add
   the **MoltenGL Shader Converter** framework to your application as follows. If you already 
   have *Metal* versions of your shaders, you can skip this step.

	1. In the *Project Navigator* panel, select your application's project, select the 
	   *Build Phases* tab, and open the *Link Binary With Libraries* list.
	2. Click the **+** button, and in the dialog window that opens, click the *Add Other...* 
	   button. Locate `MoltenGLShaderConverter/iOS/MoltenGLShaderConverter.framework` 
	   in the **MoltenGL** distribution package (or locate 
	   `MoltenGLShaderConverter/macOS/MoltenGLShaderConverter.framework` if building an 
	   *macOS* app), and click the *Open* button.
	3. In the *Build Settings* tab, ensure that the **Other Linker Flags** (aka `OTHER_LDFLAGS`)
	   setting includes an entry for `-ObjC`. Since the shader converter framework is optional
	   and weakly-linked, this entry ensures *Xcode* will add the `MoltenGLShaderConverter.framework` 
	   to the application during the link phase. 

6. If you are building an *iOS* application, skip this step. If you are building an *macOS* application, 
   drag the four files: `gl.m`, `glext.m`, `egl.m`, and `EAGL.m` from the `MoltenGL/macOS` folder in the 
   **MoltenGL** distribution package to your application project in the *Xcode Project Navigator* panel. 
   In the dialog that opens, add the files to your application's *macOS* target.
   
   These files provide a non-functional "native" *OpenGL ES 2.0* stub API for *macOS*, to satisfy 
   the linker. If you will only be running your *macOS* application on devices that support *Metal*,
   this is sufficient. If you will be running your *macOS* application on legacy devices and versions
   of *macOS* that don't support *Metal*, you can add a full "native" implementation of *OpenGL ES 2.0*
   for *macOS* by following the steps in the [Adding Support for Native *OpenGL ES 2.0* in *macOS*](#ogles-macos) 
   section below.

7. When a *Metal* app is running from *Xcode*, the default ***Scheme*** settings reduce
   performance. To improve performance and gain the benefits of *Metal*, perform the 
   following in *Xcode*:
   
	1. Open the ***Scheme Editor*** for building your main application. You can do 
	   this by selecting ***Edit Scheme...*** from the ***Scheme*** drop-down menu, or select 
	   ***Product -> Scheme -> Edit Scheme...*** from the main menu.
	2. On the ***Info*** tab, set the ***Build Configuration*** to ***Release***, and disable the 
	   ***Debug executable*** check-box.
	3. On the ***Options*** tab, disable both the ***Metal API Validation*** and ***GPU Frame Capture***
	   options. For optimal performance, you may also consider disabling the other simulation
	   and debugging options on this tab. For further information, see the 
	   [Xcode Scheme Settings and Performance](https://developer.apple.com/library/ios/documentation/Miscellaneous/Conceptual/MetalProgrammingGuide/Dev-Technique/Dev-Technique.html#//apple_ref/doc/uid/TP40014221-CH8-SW3) 
	   section of Apple's *Metal Programming Guide* documentation.

8. Build and run your application. 

You can tell whether your application is now using *Metal* by checking the logs for an entries 
similar to the following:

	[mgl-info] OpenGL functionality using Metal provided by MoltenGL 0.XX.X (build X).
	...
	[mgl-info] Establishing MoltenGL EAGLContext.
	
The first message indicates that the device you are running on supports Metal and MoltenGL,
and the second message indicates that your call to create an EAGLContext was successfully handled
by MoltenGL instead of the native OpenGL ES driver.

You can also verify that your application is now using *Metal* by Using *Xcode* to 
[capture a GPU frame](https://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/ToolsOverview/ToolsOverview.html#//apple_ref/doc/uid/TP40008793-A2-SW1).

If you find that your application is not running *Metal*, the first thing you should do is 
verify that the device supports *Metal*. *Metal* requires *iOS 8* running on a device with 
at least a 64-bit `A7` processor, or a *Mac* running *macOS 10.11*. Then check that the path to the 
`MoltenGL/RedirectHeaders/include` folder that you configured in the **User Header Search Paths** 
(aka `USER_HEADER_SEARCH_PATHS`) build setting is correct, and has been marked `recursive`. 
If it is not accurate, redirection of the *OpenGL* API calls into **MoltenGL** functionality 
will not occur, and your application will continue to use the native *OpenGL ES* libraries.



<a name="ogles-macos"></a>

Adding Support for Native *OpenGL ES 2.0* in *macOS*
----------------------------------------------------

When using **MoltenGL** on *macOS*, on a device or version of *macOS* that does ***not*** support 
*Metal*, your *OpenGL ES 2.0* app needs to be able to access a "native" *OpenGL ES 2.0* 
implementation. *macOS* supports desktop *OpenGL* by default, and so an *OpenGL ES 2.0* 
implementation must be provided for use on *macOS* if *Metal* is not available.

You do not need to install a native *OpenGL ES 2.0* implementation if your app will only run on an
*macOS* device that supports *Metal*, or when running your app on *iOS*, as *iOS* already provides 
a native *OpenGL ES 2.0* implementation.

You can use any "native" *OpenGL ES* implementation for *macOS* you prefer. If you do not already 
have a preference, you can [download a free implementation here](https://moltengl.com/downloads/#ogles-osx).
This implementation contains both *OpenGL ES 2.0* and *EGL* libraries, and converts *OpenGL ES 2.0* 
calls to the desktop *OpenGL* calls available on *macOS*.

Follow these steps to add a native *OpenGL ES 2.0* implementation for *macOS* to your application
(or follow similar steps if you already have a preferred implementation of *OpenGL ES* for *macOS*):

1. Download the [*OpenGL ES 2.0* for *macOS* implementation](https://moltengl.com/downloads/#ogles-osx)
   and unzip the contents.
   
2. Open your application in *Xcode*.

3. In the *Project Navigator* panel, remove the `gl.m` and `egl.m` files that you added during
   the [installation steps](#install) above, from your project. Leave the `glext.m` and `EAGL.m` 
   files in your project.
   
4. Drag the `libGLESv2.dylib` and `libEGL.dylib` files to the *Frameworks* group in the 
   *Xcode Project Navigator* panel. In the dialog that opens, add the files to your application's
   **_macOS_** target.

5. Select your application's project in the *Project Navigator* panel, select the *macOS* target,
   and select the *Build Phases* tab. Drag the `libGLESv2.dylib` and `libEGL.dylib` files from
   the *Frameworks* group in the *Xcode Project Navigator* panel to the *Copy Files* list in the 
   *Build Phases* tab. If a *Copy Files* list does not exist, you can add it as a new phase by
   clicking the `+` button in the *Build Phases* tab.
   
   > **Hint:** If you find it difficult to select both files in the *Frameworks* group without 
   switching away from the *Build Phases* tab of the project target, use the `Command` key on 
   your keyboard when selecting each of the files, or try dragging the files one by one from 
   the *Frameworks* group to the *Copy Files* list in the *Build Phases* tab.



<a name="licensing"></a>

Activating Your **MoltenGL** License
------------------------------------

**MoltenGL** is provided under a commercial paid license. You must purchase licenses covering 
the **MoltenGL** features you are using before releasing **MoltenGL** as part of a production 
game or application.

During evaluation, you can run **MoltenGL** without purchasing a license. The same **MoltenGL** 
distribution package can be used for both evaluation and production games and applications, 
and the features and performance are identical in both modes. During evaluation, you will 
see the **MoltenGL** logo displayed as a watermark overlay on your *OpenGL* scene. Once valid 
licenses have been purchased and activated to cover the **MoltenGL** features you are using,
this watermark will disappear.

Licenses can be purchased for one or more **MoltenGL** feature sets. Depending on whether you
purchased a single license that covers all the features you are using, or purchased individual
licenses for each features set, you may need to activate one or more licenses within **MoltenGL**.

Each license consists of a null-terminated string containing the license type, a null-terminated 
string containing the ID under which the license was purchased, the date the license was purchased,
the license quantity purchased, and a null-terminated string containing the license key assigned to 
the purchased license. All of these are provided to you when you purchase the license.

There are two ways to activate a license within **MoltenGL**:

1. The preferred method is to enter your license type, ID, date, and key as compiler build settings 
   in your development environment, and call the `glActivateMoltenGLLicensesMGL()` function to 
   activate them:

		MGL_LICENSE_TYPE
		MGL_LICENSE_ID
		MGL_LICENSE_YEAR
		MGL_LICENSE_MONTH
		MGL_LICENSE_DAY
		MGL_LICENSE_KEY

   Each element is defined as a build setting, and should not include quote marks.
   For example, you might configure the following build settings:

 		MGL_LICENSE_TYPE="Indie"
		MGL_LICENSE_ID=john.doe@example.com
		MGL_LICENSE_YEAR=2019
		MGL_LICENSE_MONTH=4
		MGL_LICENSE_DAY=12
		MGL_LICENSE_KEY=NOVOT3NGHDZ6OQSCXX4VYNXGI3QLI6Z6
   
   In addition to the license purchase information, for any license activation to take place,
   you must also set the following build setting to indicate that you accept the terms and
   conditions of the MoltenGL license agreement:

		MGL_LICENSE_ACCEPT_TERMS_AND_CONDITIONS=1

   You can call the `glActivateMoltenGLLicensesMGL()` function at any time, but typically
   you will call it during application startup.

2. If you are unable to use build settings to enter license information, you can call the

		`glActivateMoltenGLLicenseMGL(licenseType,
										 licenseID, 
										 licenseYear, 
										 licenseMonth, 
										 licenseDay, 
										 licenseKey, 
										 acceptLicenseTermsAndConditions)`

   function from within your application, passing the license information directly.

   You can call this function at any time, before or after the OpenGL context is created,
   but typically you will call this function during application startup. Until a valid license 
   is applied covering each feature set used by your application,
   **MoltenGL** will operate in evaluation mode.
   
You must also verify the user count with your license purchaser or administrator.

Once you have activated one or more licenses to cover the **MoltenGL** features you are using,
an information message will appear in the console logs for each activated feature set: 

	[mgl-info] Activated MoltenGL OpenGL ES 2.0 GLES-Indie*2 license as part of a 
	license pack purchased by 'john.doe@example.com'. Please verify the user count 
	with your license purchaser or administrator.

and the **MoltenGL** logo watermark will no longer be displayed on top of your *OpenGL* scene.


<a name="support"></a>

**MoltenGL** Product Support
---------------------------

Support for **MoltenGL** is readily available through the 
[MoltenGL Support Forum](http://www.moltengl.com/forum/product-support/). This forum 
is actively and professionally managed by the staff at **MoltenGL**, as well as the 
community of **MoltenGL** users like you. For more advanced support requirements, 
you can [contact us](mailto:sales@moltengl.com) to learn more about professional
services available to help you integrate **MoltenGL** into your application.



<a name="extensions"></a>

Supported *OpenGL ES 2.0* Extensions
------------------------------------

This version of **MoltenGL** provides support for the following *OpenGL ES 2.0* extensions:

```
APPLE_color_buffer_packed_float
APPLE_rgb_422
APPLE_texture_format_BGRA8888
APPLE_texture_packed_float
EXT_color_buffer_half_float
EXT_debug_label
EXT_debug_marker
EXT_discard_framebuffer
EXT_pvrtc_sRGB
EXT_read_format_bgra
EXT_shadow_samplers
EXT_sRGB
EXT_texture_filter_anisotropic
EXT_texture_rg
IMG_read_format
IMG_texture_compression_pvrtc
NV_generate_mipmap_sRGB
OES_depth24
OES_depth_texture
OES_element_index_uint
OES_mapbuffer
OES_packed_depth_stencil
OES_rgb8_rgba8
OES_texture_float
OES_texture_half_float
OES_texture_half_float_linear
OES_vertex_array_object
```

This list can also be retrieved at runtime via the standard `glGetString(GL_EXTENSIONS)`
function call.



<a name="platforms"></a>

Device Platforms and *OpenGL* System Classes
--------------------------------------------

There are several typical platform configuration scenarios under which your application might
be running **MoltenGL**:

1. **_iOS 8_ (or above) on a device with an `A7` processor (or above), or _macOS 10.11_ (or above) on a _Mac_:**
   
   These devices use a CPU and GPU that support *Metal*. Under this scenario, *Metal* is available. 
   **MoltenGL** will automatically intercept all *OpenGL ES 2.0* calls and redirect them to the 
   **MoltenGL** libraries, where all *OpenGL ES 2.0* functionality will be implemented using *Metal*.

2. **_iOS 7_ (or earlier) on a device with an `A7` processor (or above), or _macOS 10.10_ (or earlier) on a _Mac_:**
   
   Although these devices use a CPU and GPU that support *Metal*, the *Metal* framework is only 
   available with *iOS 8* and *macOS 10.11*, or above. Under this scenario, *Metal* is currently
   unavailable, but it will be available in the future when the user upgrades to the OS. **MoltenGL** 
   will automatically intercept all *OpenGL ES 2.0* calls and direct them to the native *OpenGL ES 2.0*
   implementation. When the user upgrades to a compatible version of *iOS* or *macOS*, **MoltenGL** 
   will then follow *Scenario 1* above and redirect all *OpenGL ES 2.0* calls to the **MoltenGL** 
   libraries, where all *OpenGL ES 2.0* functionality will be implemented using *Metal*.

   When running under this scenario under *macOS*, your *OpenGL ES 2.0* app needs to be able to 
   access a "native" *OpenGL ES 2.0* implementation. *macOS* supports *OpenGL* by default, and so 
   an *OpenGL ES 2.0* implementation must be provided for use on *macOS* if *Metal* is not available.
   Follow this instructions in the [Adding Support for Native *OpenGL ES 2.0* in *macOS*](#ogles-macos)
   section above to add this capability.

3. **Any _iOS_ version on a device with an `A6` processor (or earlier):** 

   These devices use the `arm7` processor, and have a GPU that cannot support *Metal*. 
   Under this scenario, *Metal* will never be available. When building for an `arm7` architecture,
   all *OpenGL ES 2.0* calls will be directed to the native *OpenGL* implementation directly, 
   without first passing through the **MoltenGL** framework. In this scenario, your *OpenGL* 
   application runs exactly as it does without **MoltenGL**.

_You do not need to do anything to support these various scenarios. **MoltenGL** handles them all
automatically._


<a name="modifying_scenarios"></a>

###Modifying the Scenarios

If needed, you can programmatically modify the scenario configurations above. For example, because
*Scenario 3* completely bypasses **MoltenGL**, it does not support the combined *GLSL+MSL* shaders 
described in the [*Metal* Shaders](#shaders) section below, so you may want to run a device that would 
normally operate in *Scenario 3* as if it was operating in *Scenario 2* instead. Or during development, 
you may want to test your application under both *Scenario 2* or *Scenario 3* on a device that normally
supports *Scenario 1*.

- On a device configured for *Scenario 3*, setting the value of the `MGL_SUPPORT_OPENGL_ON_METAL` 
  compiler build setting to `1` in all projects and sub-projects that you configured to use **MoltenGL** 
  during [installation](#install) will cause **MoltenGL** to operate as if it was in *Scenario 2*.
  **MoltenGL** will automatically intercept all *OpenGL ES 2.0* calls and direct them to the native
  *OpenGL* implementation. The `MGL_SUPPORT_OPENGL_ON_METAL` build setting is defined and documented
  in the `MoltenGL/RedirectHeaders/include/MoltenGL/mglEnv.h` file.
  
  There are several situations where it makes sense to intercept all *OpenGL* calls that are directed 
  to the native *OpenGL* implementation, including:

	- To gain support for combined *GLSL+MSL* shaders as described in the [*Metal* Shaders](#shaders)
	  section below.

	- To gracefully handle those *OpenGL* enumerations that are used by **MoltenGL** but not
	  *OpenGL*, in functions such as `glEnable()` and `glDisable()`. These enumerations are defined
	  in the file `MoltenGL/RedirectHeaders/include/MoltenGL/mglEnv.h`.
	
	- To use *Metal* in an application that needs to run in 32-bit mode on a 64-bit processor.
	  If there is some reason why you cannot distribute a binary containing a 64-bit component,
	  then as long as the device has a 64-bit processor and is running *iOS 8* or above, *Metal* can
	  still be used, because the processor supports it, even though the binary was compiled for the
	  32-bit `arm7` processor.
  
- Conversely, setting the value of the `MGL_SUPPORT_OPENGL_ON_METAL` compiler build setting to `0` in 
  all projects and sub-projects that you configured to use **MoltenGL** during [installation](#install)
  will cause **MoltenGL** to operate as if it was in *Scenario 3*. All *OpenGL ES 2.0* calls will
  be directed to the native *OpenGL* implementation directly, without first passing through the
  **MoltenGL** framework. You might do this during application development to test *Scenario 3* on
  a device that normally supports *Scenario 1* or *Scenario 2*.
  
- On a device configured for *Scenario 1*, calling `glDisable(GL_OPENGL_USE_METAL_MGL)`, before your
  application has made any *OpenGL* calls, or created an *OpenGL* context, will cause **MoltenGL** to 
  operate as if it was in *Scenario 2*. **MoltenGL** will automatically intercept all *OpenGL ES 2.0* 
  calls and direct them to the native *OpenGL* implementation. You must call
  `glDisable(GL_OPENGL_USE_METAL_MGL)` before your application has made any *OpenGL* calls or created 
  an *OpenGL* context, for example, during application startup.
  
- Not surprisingly, you *cannot* programmatically change a device that normally operates in 
  *Scenario 2* or *Scenario 3* to have it operate in *Scenario 1*, because *Scenario 1* requires
  that both the device and OS version support *Metal*.


<a name="system_classes"></a>

###EAGL and GLKit System Classes

In order to correctly intercept *OpenGL* behaviour, under _Scenario 1 (iOS & macOS)_ and 
_Scenario 2 (iOS)_ above, **MoltenGL** automatically replaces the *OpenGL* system classes 
`EAGLContext`, `EAGLSharegroup`, `CAEAGLLayer` and `GLKView` with classes that operate the
same way, but implement their behaviour using *Metal* instead of *OpenGL*. 

Under _Scenario 1_, (running _Metal_) these classes are available in _macOS_ as well.

In most cases, this replacement is completely transparent to your application under all three 
scenarios above. However, in order for your application to operate as expected in *Scenario 2* 
on _iOS_, you should avoid adding [custom categories](https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/CustomizingExistingClasses/CustomizingExistingClasses.html#//apple_ref/doc/uid/TP40011210-CH6-SW2) 
to either of the classes `GLKView` or `CAEAGLLayer`. Any custom categories you add to `GLKView` 
or `CAEAGLLayer`will be ignored in *Scenario 2*. If you want to add custom functionality to `GLKView`,
you should do so be creating and using a custom subclass, instead of adding a custom category to
`GLKView` itself. Your custom subclass will operate correctly in all three of the scenarios above.

On _iOS_, you can use `GLKView` and `GLKViewController` in an *Xcode Storyboard*, by declaring a subclass 
of `GLKView` (e.g. `MyGLKitView`) and using it in your *Storyboard*. You must declare and use a subclass
of `GLKit` so that **MoltenGL** can automatically replace the `GLKView` superclass with a version that
is compatible with *Metal*, when the class is dynamically loaded as part of the *Storyboard*. 

On _macOS_ under _Scenario 1_, you can do the same with `GLKView`, but you must subclass your view 
controller from `NSViewController` instead of `GLKViewController`.

On _macOS_ under _Scenario 2_, `GLKView` is not available.

Support for `GLKView` is provided as a convenience for *OpenGL* applications that use `GLKView` in 
*Storyboards*, or simply as an easy way to create a view that is compatible with *OpenGL* rendering.
Be aware that **MoltenGL** does ***not*** yet support other `GLKit` features and components, such as 
effects or the texture loader.



<a name="interaction"></a>

Interacting with the **MoltenGL** Runtime
----------------------------------------

You programmatically configure and interact with the **MoltenGL** runtime through function 
calls, enumeration values, and capabilities, in exactly the same way you do with *OpenGL*. 
The `MoltenGL/RedirectHeaders/include/MoltenGL` folder contains several header files that define 
access to **MoltenGL** configuration, capabilities, behaviour, and components:

- `mglext.h` - ***This is your primary interface for configuring the MoltenGL environment.*** 
  This file contains standard *OpenGL* enumerations, capabilities, and `gl...MGL()` extension 
  functions to configure and access **MoltenGL** capabilities and behaviour in exactly the same
  way you interact with *OpenGL*. In particular, you can use the capability enumerations defined
  in this file with the standard *OpenGL*  `glEnable()` and `glDisable()` functions to enable or
  disable runtime and debugging capabilities within **MoltenGL**. Be sure to familiarize yourself 
  with the functionality provided by the enumerations, capabilities, and functions in this file.

- `mglMetalState.h` - Contains functions for accessing some of the *Metal* components used
  by **MoltenGL**. By accessing these Metal components, you can augment the *OpenGL* behaviour
  with certain *Metal* behaviour directly, opening up the option of creating a hybrid
  *OpenGL-Metal* application.
  
- `mglDataTypes.h` - Contains helpful functions for converting between *OpenGL* and *Metal* data types.
  
- `mglGLKDataTypes.h` - Contains helpful functions for converting between *GLKit* and *Metal* data types.

- `mln_env.h` - Contains foundational environmental configuration, including the version of 
  **MoltenGL**, and build directives that automatically tell your application how to interact 
  with **MoltenGL** in various [platform scenarios](#platforms). You generally don't use this
  file directly; it is imported by the automatic redirection headers.



<a name="shaders"></a>

*Metal* Shaders
---------------

*Metal* uses a different shader language than *OpenGL*. *OpenGL* uses the well-known
*OpenGL Shading Language (GLSL)*, whereas *Metal* uses the new *Metal Shading Language (MSL)*.

**MoltenGL** provides several options for creating and running *MSL* versions of your 
existing *GLSL* shaders. The following options are presented in order of increasing 
sophistication and difficulty:

- You can use the **Runtime Shader Conversion** feature of **MoltenGL** to automatically and
  transparently convert your *GLSL* shaders to *MSL* at runtime, by simply loading your *GLSL*
  shaders as you always have, using the standard *OpenGL* `glShaderSource()` function. When 
  running on *Metal*, **MoltenGL** will detect that the *GLSL* shaders need to be converted to
  *MSL*, and will convert them automatically. When running on a device that does not support
  *Metal*, **MoltenGL** will simply pass the *GLSL* source code to the native *OpenGL* engine.

  To make use of this feature, you must have added the `MoltenGLShaderConverter.framework` 
  to your application as described in the [installation](#install) section above.

- You can create shader source files that contain ***both*** *GLSL* source code and *MSL* 
  source code, and load them using the standard *OpenGL* `glShaderSource()` function. 
  **MoltenGL** will separate the two versions of the shader source code, and automatically 
  use either the *MSL* version or the *GLSL* version, depending on whether the device 
  supports *Metal* or not.

  This option can be quite useful if you encounter an error when using **Runtime Shader 
  Conversion** to automatically convert a specific *GLSL* shader as described in the previous
  option. You can convert the *GLSL* source code for that shader to *MSL* offline, and include
  both versions when loading that shader.
	
  This option does ***not*** require the `MoltenGLShaderConverter.framework` be added 
  to your application.
  
  This option *does* require that **MoltenGL** is intercepting *OpenGL* calls, 
  as it does when operating in either *Scenario 1* or *Scenario 2*, as described in the 
  [Device Platforms and OpenGL System Classes](#platforms) section above.

  To identify which section of your combined shader source contains *GLSL* or *MSL*, 
  you can use the following `pragma` directives within your combined shader source code:
	
		#pragma MoltenGL language GLSL
		...
		#pragma MoltenGL language METAL		// or #pragma MoltenGL language MSL
		...
		#pragma MoltenGL language ALL
		...

  In each case, any code following one of these directives will be taken to be either *GLSL*
  or *MSL* source code, or in the case of the *ALL* directive, will be taken to be usable by
  both *GLSL* and *MSL* source code. You can flip back and forth between *GLSL* and *MSL* code
  within your shader by including any number of these directives. The `pragma` directives
  `MSL` and `METAL` are synonymous.
  
  Source code following the `ALL` directive will be accepted as both *GLSL* and *MSL* code.
  The `ALL` directive can be useful for demarcating statements like the `#ifdef` conditional
  compilation statement, where you want the `#ifdef` statement to be included in both the
  GLSL and MSL versions of the source code. For example, you might have a complex shader that
  includes something like the following:
  
		#pragma MoltenGL language ALL
		#ifdef USE_LIGHTING

		#pragma MoltenGL language GLSL
		...some GLSL lighting code...

		#pragma MoltenGL language MSL
		...some MSL lighting code...

		#pragma MoltenGL language ALL
		#endif
  
- You can use the standard *OpenGL* `glShaderSource()` function to provide your own *MSL* 
  shader source code when you know your application is using *Metal*. To do so, call
  `glShaderSourceLanguageMGL(GL_SHADER_SOURCE_LANG_METAL)` to indicate that source code you submit
  to the `glShaderSource()` function contains only *MSL* source code. Alternately, you can identify
  the shader source as *MSL* using the pragma directive at the top of your *MSL* source code:

		 #pragma MoltenGL language METAL
		 ...
	
  This option does ***not*** require the `MoltenGLShaderConverter.framework` be added 
  to your application.
  
  This option *does* require that your application is aware of whether *Metal* is being used, 
  and is therefore aware of whether it should submit *GLSL* or *MSL* shader source code.
  You can call `glIsEnabled(GL_OPENGL_USE_METAL_MGL)` to determine if *Metal* is being used.

- As with other *Metal* applications, you can create your own *MSL* shader source code as 
  `.metal` files, and compile it offline using *Xcode*. Using a pre-compiled shader provides
  for much faster shader creation at run time. You can use one of two mechanisms to associate
  the pre-compiled *Metal* shader functions with a particular shader:
  
	- You can use the `glShaderFunctionMGL()` function to identify the name of the *Metal* 
	  shader function to load into a particular shader.  This option requires you to modify 
	  your application code to call the `glShaderFunctionMGL()` function either *after*, 
	  or (even better) *instead of*, calling the `glShaderSource()` and `glCompileShader()`
	  functions. 

	  Although it is safe to call the `glShaderFunctionMGL()` function in addition to calling 
	  the `glShaderSource()` and `glCompileShader()` functions, to avoid wasting effort possibly
	  converting and compiling shader code you won't use, you should either avoid calling the
	  `glShaderSource()` and `glCompileShader()` functions, or cause the source code to be 
	  ignored by calling `glShaderSourceLanguageMGL(GL_SHADER_SOURCE_LANG_IGNORE)` at least
	  once prior to any `glShaderSource()` function calls.
	
	  This option does ***not*** require the `MoltenGLShaderConverter.framework` be added 
	  to your application.

	- You can also use the standard `glShaderSource()` function to identify the name of the
	  *Metal* shader function to load into a particular shader. In this case, the strings that 
	  you submit to the `glShaderSource()` function do ***not*** contain shader source code, 
	  but simply contain the *name* of a pre-compiled *Metal* shader function:
	  
			glShaderSourceLanguageMGL(GL_SHADER_SOURCE_LANG_METAL_FUNC);
			...
			...
			const GLchar* shSrc = "// This source code just contains the name of \n"
			                      "// a Metal function precompiled by Xcode \n"
			                      "myPrecompiledVertexFunction  \n";
			glShaderSource(shaderID, 1, &shSrc, NULL);
			glCompileShader(shaderID);

	  In this example, the shader source contains only the *name* of a *Metal* shader function 
	  (`myPrecompiledVertexFunction`) that has been pre-compiled by *Xcode*. You may also 
	  include optional comments and whitespace. As illustrated in this example, you must call
	  `glShaderSourceLanguageMGL(GL_SHADER_SOURCE_LANG_METAL_FUNC)` at least once sometime before
	  submitting *Metal* function names this way, so that **MoltenGL** knows that shader source code
	  you submit with subsequent `glShaderSource` calls will contain just a *Metal* function name.
	  
	  You might choose to use `glShaderSource()` to submit the names of pre-compiled *Metal* 
	  functions in those cases where you don't have access to call the `glShaderFunctionMGL()`
	  function, but you *do* have the ability to set the content of the shader source code strings.
	  Typically this might happen if you are using a third-party library to manage your *OpenGL* 
	  environment.
	
	  This option does ***not*** require the `MoltenGLShaderConverter.framework` be added 
	  to your application.

	  This option *does* require that your application is aware of whether *Metal* is being used, 
	  and is therefore aware of whether to submit only *Metal* function names as shader source code.
	  You can call `glIsEnabled(GL_OPENGL_USE_METAL_MGL)` to determine if *Metal* is being used.

You can mix and match these options in your application. For example, a simple approach is 
to use **Runtime Shader Conversion** for most *GLSL* shaders, and provide combined *GLSL+MSL* 
shader source code for the odd *GLSL* shader that prove problematic for runtime conversion.


<a name="shader_tex_coords"></a>

###*Metal* Shader Texture Coordinates

One key difference between *MSL* and *GLSL* is the orientation of the texture coordinate system.
In *OpenGL* (and *GLSL*), texture coordinates start at the *lower-left* corner of the texture
and increase towards the *upper-right* corner.
In *Metal* (and *MSL*), texture coordinates start at the *upper-left* corner of the texture
and increase towards the *lower-right* corner.

In effect, you can think of the Y-axis of the texture coordinates of *Metal* as being "flipped",
or "inverted", relative to the Y-axis of *OpenGL*. To compensate for this, when writing an *MSL* 
shader, you should use `(1.0 - y)` wherever you need to specify the Y-value of a texture coordinate.
As an example, in an *MSL* shader, you should sample a texture as follows:

	half4 texColor = myTex.sample(mySampler, float2(v_texCoord.x, (1.0 - v_texCoord.y)));

When using **Runtime Shader Conversion** or the `MoltenGLShaderConverter` 
[Shader Converter Tool](#shader_converter_tool), this is handled for you automatically. However,
if you need to write your own *MSL* shaders  (or hand-tweak the automatically converted *GLSL* 
shaders), be sure to invert the Y-value when using texture coordinates in *MSL*.

Further considerations regarding differences between *MSL* and *GLSL* are discussed in the
[Troubleshooting Shader Conversion](#glsl_vs_msl) section below.



<a name="shader_converter_tool"></a>

MoltenGLShaderConverter Shader Converter Tool
--------------------------------------------

The **MoltenGL** distribution package includes the `MoltenGLShaderConverter` command line tool,
located in the `MoltenGLShaderConverter/Tools` folder within the **MoltenGL** distribution package.
This tool allows you to convert your *GLSL* shader source code to *MSL* at development time, and 
then supply the *MSL* code to **MoltenGL** using one of the methods describe in the 
[*Metal* Shaders](#shaders) section above.

The `MoltenGLShaderConverter` tool uses the same conversion technology as the **Runtime Shader
Conversion** feature of **MoltenGL**.

The `MoltenGLShaderConverter` tool has a number of options available from the command line:

- The tool can be used to convert a single *GLSL* file, or an entire directory tree of shader files. 

- The resulting *MSL* code can be saved to its own file, or can be appended to the *GLSL* code
  to create a combined *GLSL+MSL* source code file, as described in the [*Metal* Shaders](#shaders)
  section above.

- The tool can parse a combined *GLSL+MSL* shader file, and re-convert the *GLSL* component.

- The name of the resulting *MSL* shader function can be supplied or auto-generated.

- The *MSL* source code can be output to `.metal` files, to be compiled by *Xcode* into a 
  default *Metal* shader library, whose functions can be accessed from within your application
  using the `glShaderFunctionMGL()` function.

To see a complete list of options, run the `MoltenGLShaderConverter` tool from the command 
line with no arguments.



<a name="glsl_vs_msl"></a>

Troubleshooting Shader Conversion
---------------------------------

The shader converter technology in **MoltenGL** is quite robust, and most *GLSL* shaders can
be converted to *MSL* without any problems. In the case where a conversion issue arises, 
you can address the issue as follows:

- Errors encountered during **Runtime Shader Conversion** are appended to the 
  information log of the shader. You can retrieve this log using the standard 
  *OpenGL* `glGetShaderInfoLog()` function.

- To help understand conversion issues during **Runtime Shader Conversion**, you can enable
  the logging of the *GLSL* and *MSL* shader source code during conversion as follows:
  
		glEnable(GL_LOG_SHADER_CONVERSION_SOURCE_CODE_MGL);

  You can call this function any time after the *OpenGL* context has been created, 
  and prior to any shader conversion activity.

- For minor issues, you may be able to adjust your *GLSL* code so that it behaves the same 
  under *OpenGL*, but is easier to automatically convert to *MSL*.
  
- For more significant issues, you can use the `MoltenGLShaderConverter` tool to convert the
  shaders at development time, adjust the *MSL* code manually so that it compiles correctly, 
  and create a combined *GLSL+MSL* shader code that can be loaded without changes to 
  your application code.
  
- You can use the `MoltenGLShaderConverter` tool to convert the shaders to `.metal` files 
  at development time, fix any issues with the *MSL* code, and compile the *MSL* shaders 
  into a default *Metal* shader library, whose functions can be accessed from within your 
  application using the `glShaderFunctionMGL()` function.

The following sub-sections describe a few rare situations where the design features of the
respective shading languages make automatic shader conversion difficult, and describe what
you can do to correct it.


<a name="shader_preproc"></a>

###*GLSL* Preprocessor Directives
  
Shader conversion (via either **Runtime Shader Conversion** or the `MoltenGLShaderConverter`
tool) resolves all *GLSL* preprocessor directives (eg- `#define` and `#ifdef...#endif`) prior
to conversion to *MSL*. This can sometimes be problematic, particularly for offline shader 
conversion, if you depend on the directives being dynamically set prior to compilation.


<a name="shader_tex_arrays"></a>

###Using Texture Arrays in Shaders

*GLSL* permits uniforms of type `sampler2D` and `samplerCube` to be declared and used as arrays. 
For example, the following could be used to declare a two-element array of texture samplers in *GLSL*:

	uniform sampler2D myTextures[2];

On the other hand, *MSL* requires that all textures (and their associated samplers) be declared
individually, as part of the *Metal* shader function argument list. For example, the following
could be used to declare the same two texture samplers in *MSL*:

	fragment FragOutStruct myFragmentShader(FragInStruct fragIn [[stage_in]],
		texture2d<half> myTextureA [[texture(1)]], sampler mySampler0 [[sampler(1)]]
		texture2d<half> myTextureB [[texture(2)]], sampler mySampler1 [[sampler(2)]])

A potential problem arises therefore, if the *OpenGL* application using the shaders expects 
to set the value of the texture sampler uniform as an array using a single call to the *OpenGL*
function `glUniform1iv`.

With **MoltenGL**, if your *OpenGL* application uses an array of texture samplers, 
you have a couple of ways around this issue:

- You can modify your application, and your *GLSL* fragment shader code, to use individual
  texture samplers, as follows:

		uniform sampler2D myTextureA;
		uniform sampler2D myTextureB;

  and pass the value of each sampler uniform in a separate call to `glUniform1i` or `glUniform1iv`.
  This option mimics the calling form of the *MSL* shaders, and allows you to write your shaders
  once in *GLSL* and then seamlessly convert them to *MSL* using either **Runtime Shader 
  Conversion** or the `MoltenGLShaderConverter` [Shader Converter Tool](#shader_converter_tool).

- If you are not able to (or simply don't want to) modify the way your *OpenGL* application
  passes an array of texture samplers to the `glUniform1iv` function, **MoltenGL** allows you
  to modify your *MSL* code instead, to declare the individual *MSL* textures so that 
  **MoltenGL** will treat them as elements in an array, and will reference those individual
  texture arguments when your *OpenGL* application calls the `glUniform1iv` function with 
  an array of texture samplers.

  To allow this, in your *MSL* code, declare each of your texture arguments with a special 
  suffix that indicates the index of the element in the texture sampler array:

		fragment FragOutStruct myFragmentShader(FragInStruct fragIn [[stage_in]],
			texture2d<half> myTextures_0_ [[texture(1)]], sampler mySampler0 [[sampler(1)]]
			texture2d<half> myTextures_1_ [[texture(2)]], sampler mySampler1 [[sampler(2)]])

  Notice the suffix in the form `_N_` attached to the names of each of the `texture2d` arguments
  (and notice also that you do *not* need to do this for the associated `sampler` arguments). 
  This special suffix indicates to **MoltenGL** that these two `texture2d` arguments should be
  treated as a single *GLSL* uniform declared as an array of type `texture2D`, of length `2`,
  and named `myTextures`. This last point, the uniform name, is important to keep in mind when
  requesting the location of the uniform using the `glGetUniformLocation` function.
	
  The numbers you assign in the suffixes must be consecutive and start at zero. And notice
  from the above example that the numbers do ***not*** have to agree with the *Metal* texture 
  indexes you assign (eg- `[[texture(2)]]`). This means that you can combine a texture 
  array with other discrete texture declarations in your *MSL* code.
	
  To reference these variables within your *MSL* code, use the names as they are declared 
  in the *MSL* function declaration (`myTextures_0_`, `myTextures_1_`). 
	
  Since this option requires you to modify your *MSL* code, you cannot make use of **Runtime
  Shader Conversion**, but you can use one of the other techniques [listed above](#shaders), 
  to load the *MSL* code into your application when it is running *Metal*.
	
  The `MoltenGLShaderConverter` [Shader Converter Tool](#shader_converter_tool) can help you
  create the *MSL* code in the form needed by this option. Create a copy of your *GLSL* shader,
  and modify the declaration of the `myTextures` uniform from:
	
		uniform sampler2D myTextures[2];

  to:

		uniform sampler2D myTextures_0_;
		uniform sampler2D myTextures_1_;

  and change all references to the array elements from:
	
		...texture2D(myTextures[1], texCoords)...

  to:
	
		...texture2D(myTextures_1_, texCoords)...

  When you run the `MoltenGLShaderConverter` tool, it will populate the *Metal* shader function
  arguments as described above for use as array elements. Finally, remember that, when running
  under *OpenGL*, do not use the *GLSL* code that you modified here for this special conversion.
  You should use the original unmodified *GLSL* code to allow it to continue to accept the 
  texture samplers as an array.


<a name="shader_depth_tex"></a>

###Sampling Depth Textures in Shaders

Most of the time, your textures contain visible content. However, there are certain multi-pass
situations, such as shadow-mapping, where you will want to sample from a texture that contains 
depth information. Whereas *GLSL* does not always distinguish between sampling visible or depth
texture content, *MSL* requires you to declare a different type of texture when using depth content.

If you are explicitly using a shadow sampler in your *GLSL* code to compare depth content held
in a texture:

	#extension GL_EXT_shadow_samplers : require
	varying vec3			v_shadowCoords;
	uniform sampler2DShadow	s_ShadowTex;
	...
	float luma = shadow2DEXT(s_ShadowTex, v_shadowCoords);
	...

**MoltenGL** will automatically convert this *GLSL* shadow sampler and texture to the 
cooresponding *MSL* representations. Note that you must explicitly require the 
`EXT_shadow_samplers` extension in your *GLSL* shader code.

However, if your *GLSL* code is simply treating the depth texture as a regular texture, you
must treat the texture differently in the corresponding *MSL* code. For example, during 
normal shader conversion, a *GLSL* texture sampler declared as follows:

	uniform sampler2D myTexture;
	
will typically be automatically converted to this `texture2d` *MSL* shader declaration:

	fragment FragOutStruct myFragmentShader(FragInStruct fragIn [[stage_in]],
		texture2d<half> myTexture [[texture(1)]], sampler mySampler [[sampler(1)]])

However, under *MSL*, when sampling a depth texture, the equivalent texture declaration must be `depth2d`:

	fragment FragOutStruct myFragmentShader(FragInStruct fragIn [[stage_in]],
		depth2d<float> myTexture [[texture(1)]], sampler mySampler [[sampler(1)]])

Unless you are explicitly using shader samplers (as described above), automatic shader conversion 
has no way of knowing that you intend to put depth content into the texture, and you will need
to manually edit the resulting *MSL* shader source code to change the texture declaration to 
indicate depth content. Because you must modify your *MSL* code, you cannot make use of **Runtime 
Shader Conversion**, but you can use one of the other techniques [listed above](#shaders), 
to load the *MSL* code into your application when it is running *Metal*.



<a name="performance"></a>

Performance Considerations
--------------------------

This section discusses how **MoltenGL** helps improve your game or application performance, 
and what results you should expect to see.


<a name="call_latency"></a>

###Call Latency

*Metal* has a much thinner API layer than *OpenGL*, providing lower latency for each draw call. 
In addition, *Metal* enforces a strict organization to how you construct the graphics context 
state used by each draw call, effectively forcing you to pre-configure your graphics context 
states. This is in contrast to the wildly free-form state construction available in *OpenGL*,
which offers flexibility but, like any dynamic system, is less efficient than a fixed alternative.
  
Taken together, when compared with *OpenGL*, the CPU load for each draw call is much less 
with *Metal*, meaning that you can make many more draw calls within a given frame time. 
The result is the ability to render much more content per frame.

*MoltenGL* provides a comprehensive, lightweight, and highly-optimized bridge between the 
free-form state construction of *OpenGL* and the strict state management of *Metal*, while 
retaining much of the call latency improvements available through *Metal*. With *MoltenGL* 
you can perform over **three times** the number of *OpenGL* draw calls, compared with native 
*OpenGL ES 2.0*, effectively tripling the amount of content you can draw in each frame.

Keep in mind that *MoltenGL* can only help you reduce the time spent making *OpenGL* calls.
It cannot help you reduce the time your app spends *outside* the *OpenGL* calls. An effective
performance improvement strategy should involve an effort to streamline your application logic
so that *OpenGL* calls are the blocking factor to further improvements, at which point 
**MoltenGL** will help you take your *OpenGL* game or application performance to the next level.


<a name="shader_load_time"></a>

###Shader Loading Time

*Metal* supports pre-compiled shaders, which can improve shader loading and set-up performance,
allowing you to reduce your scene loading time. See the [*Metal* Shaders](#shaders) and
`MoltenGLShaderConverter` [Shader Converter Tool](#shader_converter_tool) sections above for 
more information about how to use the `MoltenGLShaderConverter` *Shader Converter Tool* to
create and load pre-compiled *Metal* shaders into **MoltenGL**.


<a name="xcode_config"></a>

###Xcode Configuration

When a *Metal* app is running from *Xcode*, the default ***Scheme*** settings reduce performance. 
Be sure to follow the instructions for configuring your application's ***Scheme*** within *Xcode*,
found in the  in the [installation](#install) section above.


<a name="trace_tool"></a>

###Metal System Trace Tool

To help you get the best performance from your graphics app, in addition to the *GPU Driver* 
template, starting with *Xcode 7* and *iOS 9*, the *Instruments* profiling tool includes the
*Metal System Trace* template. This template can be used to provide detailed tracing of the
CPU and GPU behaviour of your application, allowing you unprecedented performance measurement
and tuning capabilities for apps using *Metal*.

This enhanced performance tuning functionality is not available for native *OpenGL ES* applications,
but **_is_** available for *OpenGL ES* applications running through **MoltenGL**.



<a name="limitations"></a>

Known **MoltenGL** Limitations
-----------------------------

The following is a list of known limitations in this version of **MoltenGL**:

- Multi-sampling has not yet been implemented.

- Vertex attributes of type `GL_BYTE`, `GL_UNSIGNED_BYTE`, `GL_SHORT`, or `GL_UNSIGNED_SHORT` 
  that have only a single element per vertex cannot be the last component of a vertex, unless
  there is room at the end of the vertex structure for a duplicate element of that type. 
  This is because *Metal* does not support those vertex attribute types as single elements, 
  and the vertex content must be read as a two-element format. For example, a vertex attribute
  that is defined as a single `GL_SHORT` will be read as two `GL_SHORT` values, and the value
  of the second element will be ignored in the shader. This does not cause any problems if
  that attribute is positioned in the middle of the vertex structure. However, if that
  attribute is positioned at the end of the vertex structure, it is possible that reading
  the attribute will cause the vertex stride to be breached, and an error will occur. 
  Try to arrange that any single-element vertex attributes of these types are not positioned 
  at the end of your vertex content, or pad your vertex stride accordingly (for example, with
  4-byte alignment).

- Shader conversion (via either **Runtime Shader Conversion** or the `MoltenGLShaderConverter`
  tool) fails to convert *GLSL* shaders that use multiple textures passed as an array, or to
  distinguish textures that sample depth content. See the [section above](#glsl_vs_msl) for 
  assistance with handling texture arrays and depth content in shaders.

- When using shadow samplers, values submitted to the `glTexParameterX()` function calls,
  with a *pname* parameter of `GL_TEXTURE_COMPARE_MODE_EXT` or `GL_TEXTURE_COMPARE_FUNC_EXT`
  will be accepted, and can be retrieved using the `glGetTexParameterX()` function. However,
  the submitted values will have no effect on the operation of shadow samplers. This is 
  because *Metal* does not currently support configuring the `compare_func` parameter of a 
  sampler via the API. *Metal* currently requires that any sampler that uses the `compare_func` 
  parameter *must* be created and configured within the *MSL* shader code itself. 
  To accommodate this, when converting *GLSL* shader code that uses shadow samplers, 
  **MoltenGL** configures a default shadow sampler within the converted *MSL* code. 
  If you need to modify the configuration of this shadow sampler, you will need to modify 
  the converted *MSL* code. Because you must modify your *MSL* code, you cannot make use of
  **Runtime Shader Conversion**, but you can use one of the other techniques 
  [listed above](#shaders), to load the *MSL* code into your application when it is running *Metal*.

- **MoltenGL** supports `GLKView` and `GLKController`, but does not provide support for other
`GLKit` components such as effects and the texture loader.

- If you need to run **MoltenGL** on a 64-bit device with *iOS 7* or earlier, you should avoid 
  adding custom categories to either of the system classes `GLKView` or `CAEAGLLayer`. See the 
  [Device Platforms and OpenGL System Classes](#platforms)  section above for more information.


---------------

**MoltenGL** uses technology from the open-source [GLSL optimizer](https://github.com/aras-p/glsl-optimizer) 
and [Mesa](http://mesa3d.org) projects to perform *GLSL* to *MSL* shader conversion during
**Runtime Shader Conversion** and in the `MoltenGLShaderConverter` tool.

**MoltenGL** uses technology from the open-source [PVRTCCompressor](https://bitbucket.org/jthlim/pvrtccompressor) 
project to help manage compressed *PVRTC* textures.

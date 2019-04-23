<a class="site-logo" href="http://www.moltengl.com/" title="MoltenGL">
<img src="images/MoltenGL-Logo-Banner.png" alt="MoltenGL Home" style="width:256px;height:auto">
</a>

#What's New in MoltenGL

Copyright (c) 2014-2019 [The Brenwill Workshop Ltd.](http://www.brenwill.com) All rights reserved.

*This document is written in [Markdown](http://en.wikipedia.org/wiki/Markdown) format. 
For best results, use a Markdown reader.*



MoltenGL 0.22.2
---------------

Released 2019/04/13

- MSL: Remove half precision casts to avoid half-precision varyings.
- Suport Xcode 10.2.



MoltenGL 0.22.1
---------------

Released 2019/03/17

- MSL: Fix half precision casts.
- MoltenGLShaderConverter add -l command line logging option.



MoltenGL 0.22.0
---------------

Released 2019/03/10

- Add mglTexGetMTLTexture() and mglTexSetMTLTexture() functions to support 
  getting and setting the MTLTexture underlying an OpenGL texture.
- MSL: Fix inversion of cube map Y-axis texture coordinate.



MoltenGL 0.21.1
---------------

Released 2019/02/21

- Fix GLKView render issue when GLKViewController not used.



MoltenGL 0.21.0
---------------

Released 2019/02/04

- Fix crash when EAGLContext is destroyed.
- Update to latest glsl-optimizer.
- Minor fixes to documentation.
- Update copyrights to 2019.



MoltenGL 0.20.0
---------------

Released 2018/11/06

- Remove MoltenVK code
- Support new MoltenGL license levels
- Fix shader texture sampling issue introduced by iOS 12



Molten 0.19.0
-------------

Released 2017/11/06


- Fix name of directory `GLKIt` to `GLKit`.



Molten 0.13.3
-------------

Released 2016/10/13


- Improved handling of retrieval of `CAMetalDrawable` from `CAMetalLayer`.



Molten 0.13.1
-------------

Released 2016/08/31

- MSL only use half precision for GLSL low precision, and never for scalar floats.
- Support larger textures for GPUs and OS versions that support them.
- Replace GL_FORCE_RENDERABLE_TEXTURES_MGL capability with GL_OPTIMIZE_SAMPLE_ONLY_TEXTURES_MGL.



MoltenGL 0.11.0
---------------

Released 2016/04/05

- MetalGL renamed to MoltenGL



MetalGL 0.10.0
--------------

Released 2015/09/21

- Add support for running *OpenGL ES 2.0* applications under OS X
- Add `DrawLoadDemo` sample project to demonstrate **MoltenGL** vs *OpenGL* 
  performance characteristics.
- Fix setting properties on iOS `MGLGLKView` via *Interface Builder*.
- Fixed issues related to several changes in *Metal* API under *iOS 9*
- Allow an *OpenGL* shader to be deleted immediately after being attached to an *OpenGL* program.
- Added support for *Xcode 7*
- `MetalGL_LICENSE.md` updated to clarify API license usage.



MetalGL 0.9.1
-------------

Released 2015/08/04

- Add support for *OpenGL ES 2.0* `EXT_shadow_samplers` extension
- Add support for *OpenGL ES 2.0* `EXT_texture_filter_anisotropic` extension
- Add sample demo *Xcode* projects in `SampleProjects` folder
- Add `ParticlesDemo` sample project
- Add support for rendering to depth-only framebuffer
- Convert empty *GLSL* shaders to *MSL*
- Trim whitespace from ends of *GLSL* & *MSL* source and shader info logs
- Rename `README.md` to `README-UserGuide.md`
- Add list of supported *OpenGL ES* extensions to `README-UserGuide.md`
- Add description of sample *Xcode* projects to `README-UserGuide.md`
- Add `SampleProjects/README-SampleProjects.md` to describe sample apps.
- Add `Whats_New.md` file to log changes delivered with each **MoltenGL** version



MetalGL 0.9.0
-------------

Released 2015/06/01

Initial public release.


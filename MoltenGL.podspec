Pod::Spec.new do |s|

  s.name                = "MoltenGL"
  s.version             = "0.22.2"
  s.summary             = "MoltenVK will run your OpenGL ES 2.0 application or game on iOS or macOS using Metal — and faster!"
  s.description         = "MoltenGL is an implementation of the OpenGL ES 2.0 API that runs on Apple's Metal graphics framework. MoltenGL provides many of the performance benefits of the Metal framework, while maintaining compliance with the proven OpenGL ES 2.0 API. And MoltenGL will continue to run your OpenGL ES application or game on future versions of iOS and macOS, should Apple remove OpenGL ES in the future."
  s.homepage            = "https://moltengl.com/"
  s.license = { :type => 'custom', :file => 'LICENSE.md' }
  s.author              = "MoltenGL"
  s.platform            = :ios, "8.0"
  s.source              = { :git => "https://github.com/allenlinli/moltengl.git", :tag => "0.22.2" }
  s.ios.source_files    = ["MoltenGL/iOS/**/*.{h,m}", "MoltenGLShaderConverter/iOS/**/*.{h,m}", "MoltenGL/RedirectHeaders/include/**/*.h"]
  s.swift_version       = "4.2"
  s.pod_target_xcconfig = {
      'OTHER_LDFLAGS' => '-lObjC',
      'CLANG_ENABLE_MODULES' => 'NO',
      'ALWAYS_SEARCH_USER_PATHS' => 'YES',
      'USER_HEADER_SEARCH_PATHS' => 'MoltenGL/RedirectHeaders/include/**/*',
      'FRAMEWORK_SEARCH_PATHS' => ['MoltenGL/iOS', 'MoltenGLShaderConverter/iOS'],
      'VALID_ARCHS' => 'arm64 armv7',
      'VALID_ARCHS[sdk=iphonesimulator*]' => '', # https://github.com/CocoaPods/CocoaPods/issues/5854
      'ARCHS' => 'arm64 armv7',
      'ONLY_ACTIVE_ARCH' => 'YES',
      'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
      'CLANG_CXX_LIBRARY' => 'libc++'
  }
  s.public_header_files = "MoltenGL/RedirectHeaders/include/**/*.h"
  s.ios.deployment_target  = '8.0'
  s.ios.frameworks = ['Metal', 'OpenGLES', 'UIKit', 'GLKit', 'QuartzCore']
  s.ios.library = 'c++'
  s.ios.vendored_frameworks = ['MoltenGL/iOS/MoltenGL.framework', 'MoltenGLShaderConverter/iOS/MoltenGLShaderConverter.framework']
  s.user_target_xcconfig = { 'VALID_ARCHS' => 'arm64 armv7' }
end
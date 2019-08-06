# MoltenGL

MoltenGL pod is a pod which uses `MoltenGL`, a commercial SDK that adopt to Metal without rewriting your projects uses OpenGL.

# Installing MoltenGL Using Cocoapods

If you would like to install MoltenGL with Cocoapods, you can use setup the podfile and do the following commands. For more information of Cocoapods, you can go to the [MoltenGL officail website](https://moltengl.com/).

```
//Pofile
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '9.0'

target 'GPUImage' do
  use_frameworks!
  pod 'MoltenGL'
end

target 'GPUImageFramework' do
  use_frameworks!
  pod 'MoltenGL'
end
```

Then, run the following command:
```
pod install
```

This is a Cocoapod that wrap the commercial framework MoltenGL. If you like to use full features, you would need to purchase the appropriate MoltenGL license from the official website.

For versions, the minor version of this pod will match the original MoltenGL framework, but the patch version will be for the pod's patches.

This cocoapod is provided by [StraaS](https://straas.io/) under [iKala](https://ikala.tv/). If you have questions about using this pod, you can contact allen.lin[at]ikala.tv.

# Import Headers

You will need to import the corresponding MoltenGL headers below the OpenGL headers. For example:

```
#import <OpenGLES/ES2/gl.h>
#import <MoltenGL/MoltenGL.h>
#import <MoltenGL/EAGL.h>
#import <MoltenGL/GLKView.h>
#import <MoltenGL/gl.h>
```

There is an example `TryMoltenGL` under the `Demos` folder, you can take it as a reference.

//
//  ViewController.m
//  TryMoltenGL
//
//  Created by Allen and Kim on 2019/5/16.
//  Copyright © 2019 ikala. All rights reserved.
//

#import "ViewController.h"

#import <OpenGLES/ES2/gl.h>
#import <MoltenGL/MoltenGL.h>
#import <MoltenGL/EAGL.h>
#import <MoltenGL/GLKView.h>
#import <MoltenGL/gl.h>

@interface ViewController () <GLKViewDelegate>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2]; // 1
    GLKView *view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]]; // 2
    view.context = context; // 3
    view.delegate = self; // 4
    [self.view addSubview:view]; // 5

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    // will got errors if uncomment the following lines
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}


@end

//
//  ViewController.m
//  TryMoltenGL
//
//  Created by Allen and Kim on 2019/5/16.
//  Copyright © 2019 ikala. All rights reserved.
//

#import "ViewController.h"

// MARK: You will need to import the MoltenGL headers below the OpenGL headers
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
    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    GLKView *view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    view.context = context;
    view.delegate = self;
    [self.view addSubview:view];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}


@end

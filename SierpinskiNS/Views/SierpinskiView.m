//
//  SierpinskiView.m
//  SierpinskiNS
//
//  Created by Josh Lynn on 8/22/14.
//  Copyright (c) 2014 Josh Lynn. All rights reserved.
//

#import "SierpinskiView.h"
#import "SierpinskiMain.h"
#import <OpenGL/gl3.h> 

@implementation SierpinskiView

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        [self setupOpenGL4];
    }
    return self;
}

-(void)awakeFromNib {
    [self setupOpenGL4];
    return;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Call the function to draw stuff to the screen....
    SierpinskiDisplay(); 
    
}

-(void)prepareOpenGL {
    SierpinskiInit();
}

-(void)setupOpenGL4 {
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core, 0
    };
    
    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    
    if (!format) {
        NSLog(@"No OpenGL pixel format");
    }
    
    NSOpenGLContext *context = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
    
    [self setPixelFormat:format];
    [self setOpenGLContext:context];
}

@end

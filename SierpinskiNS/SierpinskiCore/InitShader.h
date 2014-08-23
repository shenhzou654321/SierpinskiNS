//
//  InitShader.h
//  SierpinskiNS
//
//  Created by Josh Lynn on 8/22/14.
//  Copyright (c) 2014 Josh Lynn. All rights reserved.
//

#ifndef __SierpinskiNS__InitShader__
#define __SierpinskiNS__InitShader__

#include <iostream>
#include <OpenGL/gl3.h>

struct Shader {
    const char *filename;
    GLenum type;
    GLchar *source;
};

GLuint InitShader(const char*, const char*);

#endif /* defined(__SierpinskiNS__InitShader__) */

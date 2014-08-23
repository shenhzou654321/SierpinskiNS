//
//  InitShader.cpp
//  SierpinskiNS
//
//  Created by Josh Lynn on 8/22/14.
//  Copyright (c) 2014 Josh Lynn. All rights reserved.
//

#include "InitShader.h"

#include <iostream>
#include <fstream> 
#include <string>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static char* readShaderSource(const char*);
void processShader(Shader&, GLuint&);
void logLinkerError(GLuint&);
void logShaderError(GLuint&);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
GLuint InitShader(const char* vertexShaderFile, const char *fragmentShaderFile) {
    Shader vertexShader = {vertexShaderFile, GL_VERTEX_SHADER, NULL};
    Shader fragmentShader = {fragmentShaderFile, GL_FRAGMENT_SHADER, NULL};

    GLuint program = glCreateProgram();
    
    processShader(vertexShader, program);
    processShader(fragmentShader, program);
    
    glLinkProgram(program);
    
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        cerr << "Shader program failed to link" << endl;
        logLinkerError(program);
        exit(EXIT_FAILURE);
    }
    
    glUseProgram(program);
    return program;
    
    return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void processShader(Shader &inShader, GLuint &program) {
    inShader.source = readShaderSource(inShader.filename);
    if (inShader.source == NULL) {
        cerr << "Failed to read " << inShader.filename << endl;
        exit(EXIT_FAILURE);
    }
    
    GLuint shader = glCreateShader(inShader.type);
    glShaderSource(shader, 1, &inShader.source, NULL);
    glCompileShader(shader);
    
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        cerr << inShader.filename << " failed to compile!" << endl;
        logShaderError(shader);
        exit(EXIT_FAILURE);
    }
    delete [] inShader.source;
    glAttachShader(program, shader);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static char* readShaderSource(const char* shaderFile) {
    FILE *fp = fopen(shaderFile, "r");
    if (fp == NULL) return NULL;
    
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    
    fseek(fp, 0L, SEEK_SET);
    char *buffer = new char[size + 1];
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    fclose(fp);
    return buffer;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void logLinkerError(GLuint &program) {
    cerr << "Inside log linker error" << endl;
    GLint logSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    char *logMsg = new char[logSize];
    glGetProgramInfoLog(program, logSize, NULL, logMsg);
    cerr << "log msg: " << logMsg << "log len " << logSize << endl;
    delete [] logMsg;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void logShaderError(GLuint &shader) {
    cerr << "Inside log shader error" << endl;
    GLint logSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    char *logMsg = new char[logSize];
    glGetShaderInfoLog(shader, logSize, &logSize, logMsg);
    cerr << "log msg: " << logMsg << endl;
    delete [] logMsg;
}
//
//  main.cpp
//  SierpinskiNS
//
//  Created by Josh Lynn on 8/22/14.
//  Copyright (c) 2014 Josh Lynn. All rights reserved.
//

#include "SierpinskiMain.h"
#include "InitShader.h"

#include <openGL/gl3.h> 
#include <glm/glm.hpp>
#include <iostream> 
#include <fstream>
#include <string>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const int NumPoints = 500000;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SierpinskiInit() {
    glm::vec2 points[NumPoints];
    
    glm::vec2 vertices[3] = {
        glm::vec2(-1.0, -1.0),
        glm::vec2(0.0, 1.0),
        glm::vec2(1.0, -1.0)
    };
    
    points[0] = glm::vec2(0.25, 0.50);
    
    for(int k = 1; k < NumPoints; k++) {
        int j = rand() % 3;
        
        points[k].x = (points[k-1].x + vertices[j].x) / 2.0;
        points[k].y = (points[k-1].y + vertices[j].y) / 2.0;
        
    }
    
    GLuint program = InitShader("shaders/shader.vertsh", "shaders/shader.fragsh");
    glUseProgram(program);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SierpinskiDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, NumPoints);
    glFlush();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int SierpinskiMain() {
    return 0; 
}

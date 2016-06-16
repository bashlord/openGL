//
//  Node.h
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef Node_h
#define Node_h
# pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace glm;
class Node {
public:
    Node();
    virtual ~Node();
    virtual void draw(mat4 C) = 0;
    virtual void update(mat4 C) = 0;
    char* getId(){ return id;}
    void setID(char* id){ this->id = id;}
    void SetModelScale ( vec3 s ) { modelScale = s ;}
    void SetTransform ( const mat4 & matrix ) { transform = matrix ;}
    glm::mat4 toWorld,MVP;
protected:
    char* id;
    Node* parent;
    mat4 worldTransform ;
    mat4 transform ;
    vec3 modelScale ;
    vec4 colour ;

    };

#endif /* Node_h */

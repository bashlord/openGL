//
//  Light.hpp
//  CSE167-Starter-Code-2
//
//  Created by John Jin Woong Kim on 4/15/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <ostream>
#include <cerrno>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <limits>
#pragma once


class Light {
protected:
    
public:
    Light(int, float*, float*, float*);
    glm::vec4 diffuse;
   glm::vec4 specular;
    glm::vec4 ambient;
    
    GLenum glLight;
    int lightNum;
    
    glm::vec3 axis;
    
    bool visible;
    virtual ~Light();

    
};

class PointLight : public Light {
private:
   
public:
    PointLight(int, float*, float*, float*, float*);
    float angle;
    glm::vec4 pos;
    virtual ~PointLight();

};

class SpotLight : public Light {
private:
    
public:
    
    SpotLight(int, float*, float*, float*, float*, float*, float, float);
    glm::vec4 pos;
    glm::vec3 dir;
    float exp, cutoff;
    float angle;
    virtual ~SpotLight();

};

//
//  Geode.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#pragma once
#include "Node.h"
#include <stdio.h>
#include <string>


using namespace glm;


class Geode : public Node {
public:
    std::vector<unsigned int> indices,indices1;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> cps;
    

    
    GLuint VBO, VAO, EBO, CBO, shaderProgram;
    
    bool updateOn;
      bool orbitOn;
    
    vec3 cam_pos;		// e  | Position of camera
    vec3 cam_look_at;	// d  | This is where the camera looks at
    vec3 cam_up;
    Geode(char* name);
    Geode();
    virtual ~Geode();
    
    void draw(mat4);
     void draw_quads(mat4);
     void draw(GLuint shader, mat4 mvp,mat4 tmat);
    void update(mat4);
    void render();
    //void setCam(vec3 pos, vec3 look, vec3 up);
    
};


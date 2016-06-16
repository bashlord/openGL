//
//  Geode.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "Geode.h"
#include "Shader.h"
#include "shader1.h"
static glm::vec3 cam_pos(0.0f, 0.0f, -3.0f);		// e  | Position of camera
static glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
static glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

Geode::Geode(char* name) {
    this->id = name;
     shaderProgram =LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.frag");
   
    toWorld = glm::mat4(1.0f);
    printf("SHADER ORIGRAM IS CALED HERE");
}

Geode::Geode() {
    this->id = "";
     shaderProgram =LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.frag");
    
    printf("SHADER ORIGRAM IS CALED HERE");
}


Geode::~Geode() {
}

void Geode::draw(glm::mat4 C) {

}

void Geode::draw(GLuint shader, mat4 mvp, mat4 tmat) {
    //Window::P * Window::V * toWorld;
    // We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    
    GLuint MatrixID = glGetUniformLocation(shader, "MVP");
    GLuint modelID = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &tmat[0][0]);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}






void Geode::update(glm::mat4 C) {
        this->toWorld = C;

}

void Geode::render() {
  
}
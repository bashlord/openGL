//
//  SMObject.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/29/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "SMObject.h"
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
#include "Window.h"
#include <limits>
#include <FreeImage.h>
#include "SOIL.h"
using namespace std;
static float pointsize = 1.0f;
static GLuint cubemapTexture;
static GLuint loadText;

static GLfloat skyboxVertices[] = {
    // Positions
    -500.0f,  500.0f, -500.0f,
    -500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    
    -500.0f, -500.0f,  500.0f,
    -500.0f, -500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f,  500.0f,
    -500.0f, -500.0f,  500.0f,
    
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    
    -500.0f, -500.0f,  500.0f,
    -500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f, -500.0f,  500.0f,
    -500.0f, -500.0f,  500.0f,
    
    -500.0f,  500.0f, -500.0f,
    500.0f,  500.0f, -500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    -500.0f,  500.0f,  500.0f,
    -500.0f,  500.0f, -500.0f,
    
    -500.0f, -500.0f, -500.0f,
    -500.0f, -500.0f,  500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    -500.0f, -500.0f,  500.0f,
    500.0f, -500.0f,  500.0f
};


SMObject::SMObject() {
    this->parse();

}

SMObject::SMObject(const char *filepath)
{
    toWorld = glm::mat4(1.0f);
    resetWorld = glm::mat4(1.0f);
    parse(filepath);

}

GLuint SMObject::loadCubemap()
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width,height;
    unsigned char* image;
    
    
    for(GLuint i = 0; i < this->faces.size(); i++)
    {
        image = SOIL_load_image(this->faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    //printf("wtf is this fukin value %d", textureID);
    this->id = textureID;
    return textureID;
    
}

void SMObject::parse(const char *filepath)
{
   
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_rt.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_lf.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_up.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_dn.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_bk.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_ft.JPG");
    
    
}
void SMObject::parse()
{
    
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_rt.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_lf.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_up.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_dn.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_bk.JPG");
    this->faces.push_back("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/skymap/borg_ft.JPG");
    
    
}

void SMObject::draw(GLuint shaderProgram, int flag)
{
   
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width,height;
    unsigned char* image;
    
    
    for(GLuint i = 0; i < this->faces.size(); i++)
    {
        image = SOIL_load_image(this->faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    //printf("wtf is this fukin value %d", textureID);
    this->id = textureID;

    
   // printf("cube map texture %d\n", this->id);
    
    
    
    
    glDepthFunc(GL_LEQUAL);
    
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
  
    
    glm::mat4 MVP = Window::P * Window::V * toWorld;
    // We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));	// Remove any translation component of the view matrix
    glm::mat4 projection = glm::perspective(45.0f, (float)640/(float)480, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "skybox"), 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Use clamp to edge to hide skybox edges:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    
}




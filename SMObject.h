//
//  SMObject.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/29/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef SMObject_h
#define SMObject_h

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>



class SMObject
{
private:
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<const GLchar*> faces;
    std::vector<unsigned int> reset_indices;
    std::vector<glm::vec3> reset_vertices;
    std::vector<glm::vec3> reset_normals;
    
    
public:
    GLuint id;
    
    SMObject();
    SMObject(const char* filepath);
    glm::mat4 toWorld;
    GLuint VBO, VAO, EBO, CBO;
    float angle;
    glm::mat4 resetWorld;

    void parse(const char* filepath);
    void parse();
    void draw(GLuint shaderProgram, int flag);
    GLuint loadCubemap();
   

};

#endif
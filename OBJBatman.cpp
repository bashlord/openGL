//
//  OBJBatman.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 5/27/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "OBJBatman.h"
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
using namespace std;
static float pointsize = 1.0f;

static int numOfParts = 0;



OBJBatman::OBJBatman() {
    // Populate the face indices, vertices, and normals vectors with the OBJ Object data
    int c1,c2;
    
    
    char vn;
    char v;
    FILE* fp;
    // position coordinates
    float posX = 0.0, posY = 0.0, posZ = 0.0;
    // normal coordinates
    float normX = 0.0, normY = 0.0, normZ = 0.0;
    float normX1 = 0.0, normY1 = 0.0, normZ1 = 0.0;
    
    // open file for reading
    fp = fopen("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Batman/Batman.obj", "r");
    
    if (fp == NULL) {
        cerr << "error loading file" << endl;
        
        exit(-1);
    }  // just in case the file can't be found or is corrupt
    
    
    int a = 0;
    int vcount = 0;
    int vncount = 0;
    string str;
    c1 = fgetc(fp);
    while(c1 != '#') c1 = fgetc(fp);
    c2 = fgetc(fp);
    int counter = 0;
    //while(c1 != EOF || c2 != EOF){
    while(counter < 103){
        // printf("fuck these c1 %c c2 %c\n", c1,c2);
        
        
        
        if(c1 == '#'){
            if( fscanf(fp, "%d %s\n", &a, &str) ){
                counter ++;
            }
        }
        else if((c1 == 'v' && c2 == ' ')){
            
            fscanf(fp, "%f %f %f\n", &posX, &posY, &posZ);
            vertices.push_back(glm::vec3(posX, posY, posZ));
            
            
            a++;
            vcount++;
        }
        else if(c1 == 'v' && c2 == 'n'){
            fscanf(fp, " %f %f %f\n", &normX, &normY, &normZ);
            glm::vec3 norm = glm::normalize(glm::vec3(normX, normY, normZ));
            normals.push_back(norm);
            
            a++;
            vncount++;
        }else if(c1 == 'f' && c2 == ' '){
            uint v1, n1, v2, n2, v3, n3, v4,n4;
            //if(fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3) != 0){
            if( fscanf(fp, "%u//%u %u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3, &v4,&n4) != 0 ){
            indices.push_back((v1));
            //indices.push_back((n1));
            
            indices.push_back((v2));
            //indices.push_back((n2));
            
            indices.push_back((v3));
                indices1.push_back((v4));

            //indices.push_back((n3));
            //printf("pushed back %u, %u, %u", v1,v2,v3);
            }else if(fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3) != 0){
            
                indices1.push_back((v1));
                //indices.push_back((n1));
                
                indices1.push_back((v2));
                //indices.push_back((n2));
                
                indices1.push_back((v3));
                //indices.push_back((n3));
                            }
            
            
        }else if(c2 == 'f'){
            uint v1, n1, v2, n2, v3, n3,v4,n4;
            if(fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3) != 0){
                indices.push_back((v1));
                //indices.push_back((n1));
                
                indices.push_back((v2));
                //indices.push_back((n2));
                
                indices.push_back((v3));
                //indices.push_back((n3));
                //printf("pushed back %u, %u, %u", v1,v2,v3);
            }else if( fscanf(fp, "%u//%u %u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3, &v4,&n4) != 0 ){
                
                indices1.push_back((v1));
                //indices.push_back((n1));
                
                indices1.push_back((v2));
                //indices.push_back((n2));
                
                indices1.push_back((v3));
                //indices.push_back((n3));
                indices1.push_back((v4));
            }
            
            
        }
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        
        
    }
    fclose(fp);
    printf("batman sizes %d %d %d %d\n", vertices.size(), normals.size(),indices.size(), indices1.size());
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &CBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3) ), &vertices[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, (normals.size() * sizeof(glm::vec3) ), &normals[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(
                          1,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    char* i = "pod";
    setID(i);
    
    
}

OBJBatman::OBJBatman(const OBJBatman &obj){
    updateOn = true;
    indices = obj.indices;
    vertices = obj.vertices;
    normals = obj.normals;
    
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &CBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3) ), &vertices[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, (normals.size() * sizeof(glm::vec3) ), &normals[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(
                          1,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    char* i = "cyl";
    setID(i);
    
}



OBJBatman::~OBJBatman() {
    
    
}

void OBJBatman::parse(const char *filepath)
{
    //TODO parse the OBJ file
    // Populate the face indices, vertices, and normals vectors with the OBJ Object data
    int c1,c2;
    
    
    char vn;
    char v;
    FILE* fp;
    // position coordinates
    float posX = 0.0, posY = 0.0, posZ = 0.0;
    // normal coordinates
    float normX = 0.0, normY = 0.0, normZ = 0.0;
    float normX1 = 0.0, normY1 = 0.0, normZ1 = 0.0;
    
    // open file for reading
    fp = fopen("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/pod.obj", "r");
    
    if (fp == NULL) {
        cerr << "error loading file" << endl;
        cerr << filepath << endl;
        exit(-1);
    }  // just in case the file can't be found or is corrupt
    
    
    int a = 0;
    int vcount = 0;
    int vncount = 0;
    c1 = fgetc(fp);
    c2 = fgetc(fp);
    
    while(c1 != EOF || c2 != EOF){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if(c1 == '#'){
            
        }
        else if((c1 == 'v' && c2 == ' ')){
            fscanf(fp, "%f %f %f %f %f %f", &posX, &posY, &posZ, &normX1, &normY1, &normZ1);
            vertices.push_back(glm::vec3(posX, posY, posZ));
            
            
            a++;
            vcount++;
        }
        else if(c1 == 'v' && c2 == 'n'){
            fscanf(fp, " %f %f %f", &normX, &normY, &normZ);
            glm::vec3 norm = glm::normalize(glm::vec3(normX, normY, normZ));
            normals.push_back(norm);
            
            a++;
            vncount++;
        }else if(c1 == 'f' && c2 == ' '){
            uint v1, n1, v2, n2, v3, n3;
            fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3);
            indices.push_back((v1-1));
            indices.push_back((v2-1));
            indices.push_back((v3-1));
            //printf("pushed back %u, %u, %u", v1,v2,v3);
            
            
        }else if(c2 == 'f'){
            uint v1, n1, v2, n2, v3, n3;
            fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3);
            indices.push_back((v1-1));
            indices.push_back((v2-1));
            indices.push_back((v3-1));
        }
        
        
    }
    fclose(fp);
    
    
    
    
    
    size_t normals_buffer_size =0;
    size_t vertex_buffer_size = 0;
    size_t index_buffer_size = 0;
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &CBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3) ), &vertices[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, (normals.size() * sizeof(glm::vec3) ), &normals[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(
                          1,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}



void OBJBatman::render()
{
    //TODO parse the OBJ file
    // Populate the face indices, vertices, and normals vectors with the OBJ Object data
    int c1,c2;
    
    
    char vn;
    char v;
    FILE* fp;
    // position coordinates
    float posX = 0.0, posY = 0.0, posZ = 0.0;
    // normal coordinates
    float normX = 0.0, normY = 0.0, normZ = 0.0;
    float normX1 = 0.0, normY1 = 0.0, normZ1 = 0.0;
    
    // open file for reading
    fp = fopen("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/cylinder.obj", "r");
    
    if (fp == NULL) {
        cerr << "error loading file" << endl;
        exit(-1);
    }  // just in case the file can't be found or is corrupt
    
    
    int a = 0;
    int vcount = 0;
    int vncount = 0;
    c1 = fgetc(fp);
    c2 = fgetc(fp);
    
    while(c1 != EOF || c2 != EOF){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if(c1 == '#'){
            
        }
        else if((c1 == 'v' && c2 == ' ')){
            fscanf(fp, "%f %f %f %f %f %f", &posX, &posY, &posZ, &normX1, &normY1, &normZ1);
            vertices.push_back(glm::vec3(posX, posY, posZ));
            
            
            a++;
            vcount++;
        }
        else if(c1 == 'v' && c2 == 'n'){
            fscanf(fp, " %f %f %f", &normX, &normY, &normZ);
            glm::vec3 norm = glm::normalize(glm::vec3(normX, normY, normZ));
            normals.push_back(norm);
            
            a++;
            vncount++;
        }else if(c1 == 'f' && c2 == ' '){
            uint v1, n1, v2, n2, v3, n3;
            fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3);
            indices.push_back((v1-1));
            indices.push_back((v2-1));
            indices.push_back((v3-1));
            //printf("pushed back %u, %u, %u", v1,v2,v3);
            
            
        }else if(c2 == 'f'){
            uint v1, n1, v2, n2, v3, n3;
            fscanf(fp, "%u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3);
            indices.push_back((v1-1));
            indices.push_back((v2-1));
            indices.push_back((v3-1));
        }
        
        
    }
    fclose(fp);
    
    
    
    
    
    size_t normals_buffer_size =0;
    size_t vertex_buffer_size = 0;
    size_t index_buffer_size = 0;
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &CBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3) ), &vertices[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, (normals.size() * sizeof(glm::vec3) ), &normals[0], GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
    
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(
                          1,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          sizeof(glm::vec3),                  // stride
                          (void*)0            // array buffer offset
                          );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}



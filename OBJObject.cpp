#include "OBJObject.h"
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
using namespace std;
static float pointsize = 1.0f;
OBJObject::OBJObject() {
    this->drawFlag = false;
    this->visableFlag = false;
    
}

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
    resetWorld = glm::mat4(1.0f);
	parse(filepath);
    this->size = 5.0f;
    this->angle = 0.0f;
    this->drawFlag = false;
    this->visableFlag = false;
    this->direction = -1;
    this->orbitPos = 0;
}

void OBJObject::parse(const char *filepath) 
{
	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
    int c1,c2;
    this->maxX = std::numeric_limits<float>::infinity();
    this->maxY = std::numeric_limits<float>::infinity();
    this->minX = -std::numeric_limits<float>::infinity();
    this->minY = -std::numeric_limits<float>::infinity();
    this->maxZ = std::numeric_limits<float>::infinity();
    this->minZ = -std::numeric_limits<float>::infinity();
    
    char vn;
    char v;
    FILE* fp;
    // position coordinates
    float posX = 0.0, posY = 0.0, posZ = 0.0;
    // normal coordinates
    float normX = 0.0, normY = 0.0, normZ = 0.0;
    float normX1 = 0.0, normY1 = 0.0, normZ1 = 0.0;
    
    // open file for reading
    fp = fopen(filepath, "r");

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

        //cerr << c1 << endl;
        //cerr << c2 << endl;
        while(c1 != EOF || c2 != EOF){
            c1 = fgetc(fp);
            c2 = fgetc(fp);
            if(c1 == '#'){
                //char buffer[100];
                //fgets(buffer,100, fp);
                //c1 = fgetc(fp);
                //c2 = fgetc(fp);

            }
            else if((c1 == 'v' && c2 == ' ')){
                fscanf(fp, "%f %f %f %f %f %f", &posX, &posY, &posZ, &normX1, &normY1, &normZ1);
                vertices.push_back(glm::vec3(posX, posY, posZ));
                reset_vertices.push_back(glm::vec3(posX, posY, posZ));
                
                if(this->maxX > posX){
                    this->maxX = posX;
                }
                if(this->minX < posX){
                    this->minX = posX;
                }
                
                if(this->maxY > posY){
                    this->maxY = posY;
                }
                if(this->minY < posY){
                    this->minY = posY;
                }
                if(this->maxZ > posZ){
                    this->maxZ = posZ;
                }
                if(this->minZ < posZ){
                    this->minZ = posZ;
                }
                //glColor3f(normX, normY, normZ);
                //normals.push_back(glm::vec3(posX,posY, posZ));
                a++;
                vcount++;
            }
            else if(c1 == 'v' && c2 == 'n'){
                fscanf(fp, " %f %f %f", &normX, &normY, &normZ);
                //vertices.push_back(glm::vec3((double)normX, (double)normY, (double)normZ));
                //glm::vec3 norm = glm::vec3(glm::normalize(normX), glm::normalize(normY), glm::normalize(normZ));
                //glm::vec3 norm = glm::vec3(glm::normalize(normX), glm::normalize(normY), glm::normalize(normZ));
                glm::vec3 norm = glm::normalize(glm::vec3(normX, normY, normZ));
                normals.push_back(norm);
                reset_normals.push_back(norm);
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
    float avgX = (minX+maxX)/2;
    float avgY = (minY+maxY)/2;
    float avgZ = (minZ+maxZ)/2;
    float aaa = 0.0;
    
    if(minX > minY){
        aaa= minX;
    }else{
        aaa= minY;
    }
    
    if(minZ > aaa){
        aaa = minZ;
    }
        
        
    printf("max %f %f %f\n", minX, minY, minZ);
    printf("min %f %f %f\n", maxX, maxY, maxZ);
    printf("%f %f %f\n", avgX, avgY, avgZ);
    
    
    if(aaa == 1){
        aaa+= .5;
    }
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].x = vertices[i].x/aaa;
        vertices[i].y = vertices[i].y/aaa;

        vertices[i].z = vertices[i].z/aaa;
        
        //vertices[i] = glm::scale(vertices[i], aaa);

        
    }
    
    printf("normals %d verticies %d indicies %d\n\n", normals.size(), vertices.size(), indices.size());
    this->angle = 0.0f;
    
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
    
    
    // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    

}

void OBJObject::draw(GLuint shaderProgram, int flag)
{
    glm::mat4 MVP = Window::P * Window::V * toWorld;
    // We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    GLuint uniform_mv = glGetUniformLocation(shaderProgram, "M");
    GLuint uniform_v = glGetUniformLocation(shaderProgram, "V");
     GLuint uniform_p = glGetUniformLocation(shaderProgram, "camerapos");
    GLuint flag1 = glGetUniformLocation(shaderProgram, "flag");
    GLuint expon = glGetUniformLocation(shaderProgram, "expon");
    GLuint cutoff = glGetUniformLocation(shaderProgram, "cutoff");
    GLuint colorflag = glGetUniformLocation(shaderProgram, "colorflag");
    
    GLuint mdc = glGetUniformLocation(shaderProgram, "mdc");

    
    GLuint uniform_lightPosition = glGetUniformLocation(shaderProgram, "lightPosition");
    GLuint uniform_normalMatrix = glGetUniformLocation(shaderProgram, "normalMatrix");
    
    
    glm::vec3 camera = glm::vec3(0,0,1);
    glUniform1f(expon,  Main::spotLight->exp);
    glUniform1f(cutoff,  Main::spotLight->cutoff);
    glUniform1i(colorflag,  Main::colorflag);
    glUniform1i(flag1,  flag);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE,  &MVP[0][0]);
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE,  &this->toWorld[0][0]);
    glUniformMatrix4fv(uniform_v, 1, GL_FALSE,  &Window::V[0][0]);
    
    
    //printf(" spotlight dir %f %f %f\n", Main::spotLight->dir[0], Main::spotLight->dir[1], Main::spotLight->dir[2]);
    
    if(flag == 1){
        
        glUniform3fv(uniform_p, 1, &Main::dirLight->dir[0] );
        glUniform4fv(mdc, 1, &Main::dirLight->pos[0]);
    }else if(flag == 2){
         glUniform4fv(mdc, 1, &Main::pointLight->pos[0]);
    }else if(flag == 3){
        glUniform3fv(uniform_p, 1, &Main::spotLight->dir[0] );
        glUniform4fv(mdc, 1, &Main::spotLight->pos[0]);
    }

    //glUniformMatrix3fv(uniform_normalMatrix, 1, GL_FALSE,   );
    glUniform3fv(uniform_lightPosition, 1, &camera[0]);
    //glUniform3fv(uniform_lightPosition, 1, glm::value_ptr(glm::vec3(glm::vec4(cam.cameraPosition, 1.0f) * cam.calculateMVP())));

    //glUniform3fv(uniform_lightPosition, 1, glm::value_ptr(cam.cameraPosition));
    
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    
    glDrawElements(GL_TRIANGLES, indices.size() * sizeof(uint), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

	//glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
 
}

void OBJObject::update()
{
    spin(1.0f);
    //1000, 600 needs to change back to width and eight
    //orbit(500, 300, 1.0f);
    //orbit(1.0f);
    //toLeft();
}

void OBJObject::orbitUpdate(float width, float height)
{
    //spin(1.0f);
    //orbit(width, -height, 1.0f);
    //toLeft();
}


void OBJObject::spin(float deg)
{
    this->angle = deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    //this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //needs to rotate at the center axis of where it is, even if it is moved
    this->toWorld = glm::rotate(
                                this->toWorld, this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void OBJObject::orbit(float w, float h, float deg)
{
    this->angle = deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    //this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //this->toWorld = Projection * this->toWorld * tw;
    
    this->toWorld = glm::rotate(
                                glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f)) * this->toWorld;

    
}


void OBJObject::orbit1(float w, float h, float deg)
{
    this->angle = deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    //this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //this->toWorld = Projection * this->toWorld * tw;
    
    this->toWorld = glm::rotate(
                                glm::mat4(1.0f), -(this->angle / 180.0f * glm::pi<float>()), glm::vec3(0.0f, 0.0f, 1.0f)) * this->toWorld;
    
    
}

void OBJObject::mouseRotate(glm::mat4 mat, glm::vec3 vec, float deg){
    //this->toWorld = mat * this->toWorld;
    //this->toWorld *= mat;
    this->angle = deg;
    //this->toWorld = glm::rotate(glm::mat4(1.0f), deg, glm::normalize(vec)) * this->toWorld;
    this->toWorld = glm::rotate(this->toWorld, deg, glm::normalize(vec));
}

void OBJObject::mouseDrag(glm::mat4 mat, glm::vec3 vec, float deg){
    //this->toWorld *= mat;
    //this->toWorld *= glm::translate(glm::mat4(1.0f), vec);
    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3( -vec.x/5,vec.y/5,vec.z ) )* this->toWorld;
   // this->toWorld = glm::translate(this->toWorld, glm::normalize(vec));
}

void OBJObject::toLeft(){
    
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * this->toWorld;
    //glm::(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

}

void OBJObject::toRight(){
    
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    //glm::mat4(1.0f)
    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * this->toWorld;
    //glm::(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void OBJObject::toUp(){
    
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    //cerr << "Previous Matrix coords: ";
    //cerr << myMatrix[0] << endl;
    
    
    
    //this->toWorld = glm::translate(myMatrix, glm::vec3(0.0f, 1.0f, 0.0f)) * this->toWorld;
    //glm::mat4(1.0f)
    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * this->toWorld;
    //glm::(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void OBJObject::toDown(){
    
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;

    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * this->toWorld;
    //glm::(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void OBJObject::zoom(){
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    //cerr << "Previous Matrix coords: ";
    //cerr << myMatrix[0] << endl;
    
     this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * this->toWorld;


}

void OBJObject::scale(){
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    

    this->toWorld = glm::scale(this->toWorld, glm::vec3(0.5f, 0.5f, 0.5f));
    
}

void OBJObject::zoom1(){
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    //cerr << "Previous Matrix coords: ";
    //cerr << myMatrix[0] << endl;
    
    this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f)) * this->toWorld;
    
    
}

void OBJObject::scale1(){
    glm::vec4 myVector(0.0f, 1.0f, 0.0f, 0.0f);
    glm::mat4 myMatrix = this->toWorld;
    
    
    this->toWorld = glm::scale(this->toWorld, glm::vec3(1.5f, 1.5f, 1.5f));
    
}

glm::vec3 OBJObject::norm(int i){
    return this->normals[i];
    
}

void OBJObject::pointUp(){
    if(pointsize < 20) pointsize++;
    
}

void OBJObject::pointDown(){
    if(pointsize >= 2.0f) pointsize--;
    
}

float OBJObject::pointsizer(){
    return pointsize;
}

void OBJObject::reset(){
    //return this->normals[i];
    this->vertices.clear();

    this->vertices = this->reset_vertices;
    this->normals.clear();
    this->normals = this->normals;

    this->toWorld = glm::mat4(1.0f);
    pointsize = 1.0f;
    
    
}

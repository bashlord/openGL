#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>



class OBJObject
{
private:
std::vector<unsigned int> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
    
std::vector<unsigned int> reset_indices;
std::vector<glm::vec3> reset_vertices;
std::vector<glm::vec3> reset_normals;


public:
    OBJObject();
	OBJObject(const char* filepath);
    glm::mat4 toWorld;
    GLuint VBO, VAO, EBO, CBO;
    float angle;
    glm::mat4 resetWorld;
    
    float minX;
    float minY;
    float maxX;
    float maxY;
    float maxZ;
    float minZ;
    
    int normalLen(){ return (int)normals.size(); }
    int vertexLen(){ return (int)vertices.size(); }
    
    glm::vec3 vert( int i ){return vertices[i]; }
    glm::vec3 norm(int i);
    float size;

    float orbitPos;
    
	void parse(const char* filepath);
	void draw(GLuint shaderProgram, int flag);
    
    void update();
    void spin(float);
    
    void orbit(float w, float h, float def);
    void orbit1(float w, float h, float def);
    
    bool drawFlag;
    bool visableFlag;
    
    void toLeft();
    void toRight();
    void toUp();
    void toDown();
    
    void zoom();
    
    void scale();
    void zoom1();
    
    void scale1();
    
    void orbitUpdate(float width, float height);
    
    void reset();
    
    void pointUp();
    void pointDown();
    
    void mouseRotate(glm::mat4 mat, glm::vec3 vec, float deg);
    void mouseDrag(glm::mat4 mat, glm::vec3 vec, float deg);
    
    float pointsizer();
    //1 = up
    //2 = down
    //3 = left
    //4 = right
    int direction;
};

#endif
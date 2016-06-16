#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <vector>
#include "Window.h"

class Park
{
public:
	GLuint VAO, VBO;
	GLuint texture;
	std::vector<glm::vec3> debug_grid;
	Park();

	void draw(GLuint shader);
    void draw(GLuint shader, mat4 mvp, mat4 tmat);

	unsigned char* LoadPPM(const char* filename, int& width, int& height);
	void LoadTexture();
};


#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <vector>
#include "Window.h"

using namespace glm;

class Building
{
public:
	GLuint
		VAO0, VBO0, VBO0N, VBO0T,
		VAO1, VBO1, VBO1N, VBO1T,
		VAO2, VBO2, VBO2N, VBO2T,
		VAOD, VBOD;

	Building();
	~Building();

	void Draw(GLuint shader);
    void Draw(GLuint shader, mat4 mvp);

    void Draw(GLuint shader, mat4 mvp, mat4 tmat);

    void GenerateNew();
	void GenerateTier();
	void GenerateMult();
	void MakeTexture();
	unsigned char* LoadPPM(const char* filename, int& width, int& height);
	void LoadTexture();
	void CalcNormAndText();
};

#endif


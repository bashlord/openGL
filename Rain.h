#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <vector>
#include "Cube.h"
#include "Window.h"



typedef struct {
	//Particle Color
	float r, g, b;

	// Gravity
	float gravity;

	//Lifespan
	float lifeSpan;
	float fadeAmount;
	bool shouldDraw;

	//Velocity in y-direction
	float vel;

	//Position
	float x;
	float y;
	float z;

}particle;

class Rain
{
public:
	//Controls how quickly the raindrops fall
	float velocity;
	float deccel;

	//Controls how high the raindrops begin
	float y_start;

	// The raindrops are spawned on a grid, this is essentially how many rows/cols that grid has
	int gridSize;
	int offset;

	//Controls how long the raindrops last until they disappear
	float lifeSpan;

	Rain();
	void draw(GLuint shader);

private:

	GLuint VAO, VBO;
	int numParticles;
	std::vector<particle> rain_particles;
	std::vector<glm::vec3> rain_particles_pos;

	void initParticle(int i);
};


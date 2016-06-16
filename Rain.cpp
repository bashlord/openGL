#include "Rain.h"
#include <glm/gtc/type_ptr.hpp>


Rain::Rain()
{
	//Variables
	velocity = -100.0f;
	deccel = 2.5f;

	numParticles = 1000;
	y_start = 250.0;
	lifeSpan = 3.0f;
	gridSize = 1000;
	offset = 500;

	//Initialize particles
	for (int i = 0; i < numParticles; i++) {

		particle toAdd;
		glm::vec3 toAddPos;

		//Initialize particle information
		toAdd.shouldDraw = true;
		toAdd.lifeSpan = lifeSpan;
		toAdd.fadeAmount = 0.0001f * (float)(rand()%100);//assign a random value to the fade

		toAdd.x = (float)(rand() % gridSize) - offset;
		toAdd.y = y_start;
		toAdd.z = (float)(rand() % gridSize) - offset;

		toAdd.r = 0.5;
		toAdd.g = 0.5;
		toAdd.b = 1.0;

		toAdd.vel = velocity;
		toAdd.gravity = -0.8;

		//Set position vector which is used to draw VAO/VBO
		toAddPos.x = toAdd.x;
		toAddPos.y = toAdd.y;
		toAddPos.z = toAdd.z;

		//Add to vectors
		rain_particles.push_back(toAdd);
		rain_particles_pos.push_back(toAddPos);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, rain_particles_pos.size() * sizeof(glm::vec3), &(rain_particles_pos.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);
}

void Rain::draw(GLuint shader) {
	for (int i = 0; i < numParticles; i++) {

		if (rain_particles[i].shouldDraw == true) {

			//Make the raindrops fall down
			rain_particles[i].y += rain_particles[i].vel / (deccel * 10);
			rain_particles[i].vel += rain_particles[i].gravity;

			//Update position vector
			rain_particles_pos[i].y = rain_particles[i].y;

			//Decrease their lifespan as they fall
			rain_particles[i].lifeSpan -= rain_particles[i].fadeAmount;

			//If the raindrops fall too far down, reset them
			if (rain_particles[i].y <= -15) {
				//rain_particles[i].lifeSpan = -1.0;
			}

			//Reset a particle if it has died
			if (rain_particles[i].lifeSpan < 0.0) {
				initParticle(i);
			}
		}
	}

	//PlaySound(TEXT("water_droplet.wav"), NULL, SND_FILENAME | SND_ASYNC);

	glUseProgram(shader);

	//Rebind the buffers so the position updates
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, rain_particles_pos.size() * sizeof(glm::vec3), &(rain_particles_pos.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);

	//Draw the array
	glPointSize(3.0f);

	glUseProgram(shader);
	glm::mat4 MVP = Window::P * Window::V * glm::mat4(1.0f);
	GLuint MatrixID = glGetUniformLocation(shader, "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(glGetUniformLocation(shader, "which"), 99);

	glLineWidth(3.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, rain_particles_pos.size());
	glBindVertexArray(0);
}

//Reset a particle to its starting values
void Rain::initParticle(int i) {
	rain_particles[i].shouldDraw = true;
	rain_particles[i].lifeSpan = 1.0;
	rain_particles[i].fadeAmount = 0.0001f * (float)(rand() % 100);

	rain_particles[i].x = (float)(rand() % gridSize) - offset;
	rain_particles[i].y = y_start;
	rain_particles[i].z = (float)(rand() % gridSize) - offset;

	rain_particles[i].r = 0.5;
	rain_particles[i].g = 0.5;
	rain_particles[i].b = 1.0;

	rain_particles[i].vel = velocity;
	rain_particles[i].gravity = -0.8;

	rain_particles_pos[i].x = rain_particles[i].x;
	rain_particles_pos[i].y = rain_particles[i].y;
	rain_particles_pos[i].z = rain_particles[i].z;
}

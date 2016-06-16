#include "Park.h"

#define MAX_X 4
#define MAX_Z 4

using namespace glm;

Park::Park()
{
    LoadTexture();
	// debug grid
	debug_grid.push_back(vec3(MAX_X, 0, MAX_Z));
	debug_grid.push_back(vec3(MAX_X, 0, -MAX_Z));
	debug_grid.push_back(vec3(-MAX_X, 0, -MAX_Z));

	debug_grid.push_back(vec3(MAX_X, 0, MAX_Z));
	debug_grid.push_back(vec3(-MAX_X, 0, MAX_Z));
	debug_grid.push_back(vec3(-MAX_X, 0, -MAX_Z));
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, debug_grid.size() * sizeof(vec3), &(debug_grid.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);
}


void Park::draw(GLuint shader) {
	glUseProgram(shader);

	//Draw the array
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, debug_grid.size());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Park::draw(GLuint shader, mat4 mvp, mat4 tmat) {
    //glUseProgram(shader);
    printf("PARK DRAW \n");
    //Draw the array
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "P"), 1, GL_FALSE, &tmat[0][0]);
    GLuint texID = glGetUniformLocation(shader, "texcoord");
    glUniform3fv(glGetUniformLocation(shader, "batSignalDir"), 1, &Window::batSignalDir[0]);
    glUniform3fv(glGetUniformLocation(shader, "batSignalPos"), 1, &Window::batSignalPos[0]);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE2);	// Activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "tex"), 2);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, debug_grid.size());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

unsigned char* Park::LoadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

void Park::LoadTexture()
{
	int width, height;   // texture width/height [pixels]

	unsigned char * image;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture);
	image = LoadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/grass.ppm", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
    
    printf("PARK LOAD TEXTURE \n");

}
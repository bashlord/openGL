#include "Building.h"

#define TEXTURE_WIDTH 524
#define TEXTURE_HEIGHT 524

#define MAX_X 4
#define MAX_TIER_Y 10
#define MAX_MULT_Y 10
#define MAX_Z 4
#define MAX_VARIANCE 16
#define TIER_BIAS 2
#define TIER_SCALING 2/3

GLubyte MatrixTexture[TEXTURE_HEIGHT][TEXTURE_WIDTH][3];

std::vector<vec3> part0;
std::vector<GLfloat> part0_t;
std::vector<vec3> part_norm;
std::vector<vec3> part1;
std::vector<GLfloat> part1_t;
std::vector<vec3> part2;
std::vector<GLfloat> part2_t;
std::vector<vec3> debug_grid;

GLuint texture;
GLuint textureSidewalk;

bool is_tier;

GLfloat textureVertices[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

Building::Building()
{
	CalcNormAndText();
	LoadTexture();
	GenerateNew();


	for (int i = 0; i < 8; ++i)
	{
		part0_t.push_back(textureVertices[0]);
	}
	for (int i = 0; i < 8; ++i)
	{
		part1_t.push_back(textureVertices[0]);
	}
	for (int i = 0; i < 8; ++i)
	{
		part2_t.push_back(textureVertices[0]);
	}


	// debug grid
	debug_grid.push_back(vec3(MAX_X, 0, MAX_Z));
	debug_grid.push_back(vec3(MAX_X, 0, -MAX_Z));
	debug_grid.push_back(vec3(-MAX_X, 0, -MAX_Z));
    
	debug_grid.push_back(vec3(MAX_X, 0, MAX_Z));
    debug_grid.push_back(vec3(-MAX_X, 0, MAX_Z));
    debug_grid.push_back(vec3(-MAX_X, 0, -MAX_Z));
	//debug_grid.push_back(vec3(MAX_X, 0, MAX_Z));

	glGenVertexArrays(1, &VAOD);
	glGenBuffers(1, &VBOD);

	glBindVertexArray(VAOD);

	glBindBuffer(GL_ARRAY_BUFFER, VBOD);
	glBufferData(GL_ARRAY_BUFFER, debug_grid.size() * sizeof(vec3), &(debug_grid.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOD);
	glBindVertexArray(0);

}

void Building::CalcNormAndText()
{
	vec3 defaultCubeVertices[] = {
		// Front vertices
		vec3(-1, 0,  1), // bottom-left 0
		vec3(1, 0,  1), // bottom-right 1
		vec3(1, 1,  1), // top-right 2
		vec3(-1, 1,  1), // top-left 3
		// Back vertices
		vec3(-1, 0, -1), // bottom-left 4
		vec3(1, 0, -1), // bottom-right 5
		vec3(1, 1, -1), // top-right 6 
		vec3(-1, 1, -1) // top-left 7
	};

	for (int i = 0; i < 4; ++i)
	{
		part0_t.push_back(textureVertices[0]);
		part0_t.push_back(textureVertices[1]);
		part0_t.push_back(textureVertices[2]);
		part0_t.push_back(textureVertices[3]);
		part0_t.push_back(textureVertices[4]);
		part0_t.push_back(textureVertices[5]);
        part0_t.push_back(textureVertices[0]);
        part0_t.push_back(textureVertices[1]);
        part0_t.push_back(textureVertices[4]);
        part0_t.push_back(textureVertices[5]);
		part0_t.push_back(textureVertices[6]);
		part0_t.push_back(textureVertices[7]);
	}

	vec3 tmp_dir0 = defaultCubeVertices[0] - defaultCubeVertices[1];
	vec3 tmp_dir1 = defaultCubeVertices[0] - defaultCubeVertices[3];
	for (int i = 0; i < 6; ++i)
	{
		part_norm.push_back(glm::cross(tmp_dir0, tmp_dir1));
	}

	tmp_dir0 = defaultCubeVertices[1] - defaultCubeVertices[5];
	tmp_dir1 = defaultCubeVertices[1] - defaultCubeVertices[2];
	for (int i = 0; i < 6; ++i)
	{
		part_norm.push_back(glm::cross(tmp_dir0, tmp_dir1));
	}

	tmp_dir0 = defaultCubeVertices[4] - defaultCubeVertices[5];
	tmp_dir1 = defaultCubeVertices[4] - defaultCubeVertices[7];
	for (int i = 0; i < 6; ++i)
	{
		part_norm.push_back(glm::cross(tmp_dir0, tmp_dir1));
	}

	tmp_dir0 = defaultCubeVertices[0] - defaultCubeVertices[4];
	tmp_dir1 = defaultCubeVertices[0] - defaultCubeVertices[3];
	for (int i = 0; i < 6; ++i)
	{
		part_norm.push_back(-glm::cross(tmp_dir0, tmp_dir1));
	}

	tmp_dir0 = defaultCubeVertices[3] - defaultCubeVertices[2];
	tmp_dir1 = defaultCubeVertices[3] - defaultCubeVertices[7];
	for (int i = 0; i < 6; ++i)
	{
		part_norm.push_back(-glm::cross(tmp_dir0, tmp_dir1));
	}
}

Building::~Building()
{
	glDeleteVertexArrays(1, &VAO0);
	glDeleteBuffers(1, &VBO0);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteVertexArrays(1, &VAOD);
	glDeleteBuffers(1, &VBOD);
}

void Building::Draw(GLuint shader)
{
	glm::mat4 MVP = Window::P * Window::V;
	

	GLuint texID = glGetUniformLocation(shader, "texcoord");
    
    
    if (true)
    {
        //glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 0.0f);
        
        glBindVertexArray(VAOD);
        glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, textureSidewalk);
        glUniform1i(glGetUniformLocation(shader, "tex"), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, debug_grid.size());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    
	// part0
	GLuint colorID = glGetUniformLocation(shader, "color_in");
	glUniform4f(colorID, 0.0f, 1.0f, 0.0f, 0.0f);

	glBindVertexArray(VAO0);
	glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);
    glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
	glBindVertexArray(0);
    
    // part1
    glUniform4f(colorID, 1.0f, 1.0f, 0.0f, 0.0f);
    
    glBindVertexArray(VAO1);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
     glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    // part2
    glUniform4f(colorID, 1.0f, 1.0f, 1.0f, 0.0f);
    
    glBindVertexArray(VAO2);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
     glDisableVertexAttribArray(0);
    glBindVertexArray(0);



    //printf("building %d %d %d\n", part0.size(), part1.size(),part2.size());
	
}

void Building::Draw(GLuint shader, mat4 mvp)
{
    glm::mat4 MVP = Window::P * Window::V;
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &mvp[0][0]);
    GLuint texID = glGetUniformLocation(shader, "texcoord");
    glUniform3fv(glGetUniformLocation(shader, "batSignalDir"), 1, &Window::batSignalDir[0]);
    glUniform3fv(glGetUniformLocation(shader, "batSignalPos"), 1, &Window::batSignalPos[0]);
    
    // part0
    GLuint colorID = glGetUniformLocation(shader, "color_in");
    glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 0.0f);
    
    
    if (true)
    {
        //glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 0.0f);
        
        glBindVertexArray(VAOD);
        glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, textureSidewalk);
        glUniform1i(glGetUniformLocation(shader, "tex"), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, debug_grid.size());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    
    glBindVertexArray(VAO0);
    glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "tex"), 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glUniform4f(colorID, 1.0f, 0.271f, 0.0f, 0.0f);
    
    glBindVertexArray(VAO1);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    // part2
    glUniform4f(colorID, 1.0f, 1.0f, 1.0f, 0.0f);
    
    glBindVertexArray(VAO2);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    

}

void Building::Draw(GLuint shader, mat4 mvp,mat4 tmat)
{
    glm::mat4 MVP = Window::P * Window::V;
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &mvp[0][0]);
     glUniformMatrix4fv(glGetUniformLocation(shader, "P"), 1, GL_FALSE, &tmat[0][0]);
    GLuint texID = glGetUniformLocation(shader, "texcoord");
    glUniform3fv(glGetUniformLocation(shader, "batSignalDir"), 1, &Window::batSignalDir[0]);
    glUniform3fv(glGetUniformLocation(shader, "batSignalPos"), 1, &Window::batSignalPos[0]);
    
    // part0
    GLuint colorID = glGetUniformLocation(shader, "color_in");
    glUniform4f(colorID, 1.0f, 1.0f, 1.0f, 0.0f);
    
    if (true)
    {
        //glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 0.0f);
        
        glBindVertexArray(VAOD);
        glActiveTexture(GL_TEXTURE1);	// Activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, textureSidewalk);
        glUniform1i(glGetUniformLocation(shader, "tex"), 1);
        
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, debug_grid.size());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
     glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 0.0f);
    glBindVertexArray(VAO0);
    glActiveTexture(GL_TEXTURE0);	// Activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "tex"), 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glUniform4f(colorID, 1.0f, 0.271f, 0.0f, 0.0f);
    
    glBindVertexArray(VAO1);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    // part2
    glUniform4f(colorID, 1.0f, 1.0f, 1.0f, 0.0f);
    
    glBindVertexArray(VAO2);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    

}



void Building::GenerateNew()
{
	part0.clear();
	part1.clear();
	part2.clear();
	if (rand() % TIER_BIAS == 0)
	{
         printf("building generateMult");
		GenerateMult();
		is_tier = false;
	}
	else
	{
         printf("building generateTier");
		GenerateTier();
		is_tier = true;
	}

	// part0
	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);
	glGenBuffers(1, &VBO0N);
	glGenBuffers(1, &VBO0T);

	glBindVertexArray(VAO0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, part0.size() * sizeof(vec3), &(part0.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0N);
	glBufferData(GL_ARRAY_BUFFER, part_norm.size() * sizeof(vec3), &(part_norm.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0T);
	glBufferData(GL_ARRAY_BUFFER, part0_t.size() * sizeof(GLfloat), &(part0_t.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0N);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0T);
	glBindVertexArray(0);

	// part1
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO1N);
	glGenBuffers(1, &VBO1T);

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, part1.size() * sizeof(vec3), &(part1.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1N);
	glBufferData(GL_ARRAY_BUFFER, part_norm.size() * sizeof(vec3), &(part_norm.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1T);
	glBufferData(GL_ARRAY_BUFFER, part0_t.size() * sizeof(GLfloat), &(part0_t.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1N);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1T);
	glBindVertexArray(0);

	// part2
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &VBO2N);
	glGenBuffers(1, &VBO2T);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, part2.size() * sizeof(vec3), &(part2.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2N);
	glBufferData(GL_ARRAY_BUFFER, part_norm.size() * sizeof(vec3), &(part_norm.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2T);
	glBufferData(GL_ARRAY_BUFFER, part0_t.size() * sizeof(GLfloat), &(part0_t.front()), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2N);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2T);
	glBindVertexArray(0);
}

void Building::GenerateTier()
{
	vec3 cubeVertices[] = {
		// Front vertices
		vec3(-1, 0,  1), // bottom-left 0
		vec3(1, 0,  1), // bottom-right 1
		vec3(1, 1,  1), // top-right 2
		vec3(-1, 1,  1), // top-left 3
		// Back vertices
		vec3(-1, 0, -1), // bottom-left 4
		vec3(1, 0, -1), // bottom-right 5
		vec3(1, 1, -1), // top-right 6 
		vec3(-1, 1, -1) // top-left 7
	};

	float base_x = rand() % MAX_VARIANCE;
	base_x = (base_x / MAX_VARIANCE) * MAX_X;
	base_x = base_x < 3 ? 3 : base_x;
	float base_y = rand() % MAX_VARIANCE;
	base_y = (base_y / MAX_VARIANCE) * MAX_TIER_Y;
	base_y = base_y < 3 ? 3 : base_y;

	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x *= base_x;
		cubeVertices[i].y *= base_y;
		cubeVertices[i].z *= base_x;
	}
	part0.push_back(cubeVertices[0]);//0
	part0.push_back(cubeVertices[1]);//1
	part0.push_back(cubeVertices[2]);//2
	part0.push_back(cubeVertices[0]);//0
    part0.push_back(cubeVertices[2]);//3
    part0.push_back(cubeVertices[3]);//2

	part0.push_back(cubeVertices[1]);//0
	part0.push_back(cubeVertices[5]);//1
	part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[1]);//2
    part0.push_back(cubeVertices[6]);//1
	part0.push_back(cubeVertices[2]);//3

	part0.push_back(cubeVertices[4]);//0
	part0.push_back(cubeVertices[5]);//1
	part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[4]);//2
    part0.push_back(cubeVertices[6]);//1
	part0.push_back(cubeVertices[7]);//3

	part0.push_back(cubeVertices[4]);//0
	part0.push_back(cubeVertices[7]);//1
	part0.push_back(cubeVertices[3]);//2
    part0.push_back(cubeVertices[4]);//2
    part0.push_back(cubeVertices[3]);//1
	part0.push_back(cubeVertices[0]);//3

	part0.push_back(cubeVertices[3]);//0
	part0.push_back(cubeVertices[2]);//1
	part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[3]);//1
	part0.push_back(cubeVertices[7]);//3



	float highest_y = cubeVertices[2].y;
	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x = cubeVertices[i].x * TIER_SCALING;
		if (i == 2 || i == 3 || i == 6 || i == 7)
			cubeVertices[i].y = highest_y + (base_y * TIER_SCALING);
		else
			cubeVertices[i].y = highest_y;
		cubeVertices[i].z = cubeVertices[i].z * TIER_SCALING;
	}

    part1.push_back(cubeVertices[0]);//0
    part1.push_back(cubeVertices[1]);//1
    part1.push_back(cubeVertices[2]);//2
    part1.push_back(cubeVertices[0]);//0
    part1.push_back(cubeVertices[2]);//3
    part1.push_back(cubeVertices[3]);//2
    
    part1.push_back(cubeVertices[1]);//0
    part1.push_back(cubeVertices[5]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[1]);//2
    part1.push_back(cubeVertices[6]);//1
    part1.push_back(cubeVertices[2]);//3
    
    part1.push_back(cubeVertices[4]);//0
    part1.push_back(cubeVertices[5]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[4]);//2
    part1.push_back(cubeVertices[6]);//1
    part1.push_back(cubeVertices[7]);//3
    
    part1.push_back(cubeVertices[4]);//0
    part1.push_back(cubeVertices[7]);//1
    part1.push_back(cubeVertices[3]);//2
    part1.push_back(cubeVertices[4]);//2
    part1.push_back(cubeVertices[3]);//1
    part1.push_back(cubeVertices[0]);//3
    
    part1.push_back(cubeVertices[3]);//0
    part1.push_back(cubeVertices[2]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[3]);//1
    part1.push_back(cubeVertices[7]);//3


	highest_y = cubeVertices[2].y;
	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x = cubeVertices[i].x * TIER_SCALING;
		if (i == 2 || i == 3 || i == 6 || i == 7)
			cubeVertices[i].y = highest_y + (base_y * TIER_SCALING);
		else
			cubeVertices[i].y = highest_y;
		cubeVertices[i].z = cubeVertices[i].z * TIER_SCALING;
	}

    part2.push_back(cubeVertices[0]);//0
    part2.push_back(cubeVertices[1]);//1
    part2.push_back(cubeVertices[2]);//2
    part2.push_back(cubeVertices[0]);//0
    part2.push_back(cubeVertices[2]);//3
    part2.push_back(cubeVertices[3]);//2
    
    part2.push_back(cubeVertices[1]);//0
    part2.push_back(cubeVertices[5]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[1]);//2
    part2.push_back(cubeVertices[6]);//1
    part2.push_back(cubeVertices[2]);//3
    
    part2.push_back(cubeVertices[4]);//0
    part2.push_back(cubeVertices[5]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[4]);//2
    part2.push_back(cubeVertices[6]);//1
    part2.push_back(cubeVertices[7]);//3
    
    part2.push_back(cubeVertices[4]);//0
    part2.push_back(cubeVertices[7]);//1
    part2.push_back(cubeVertices[3]);//2
    part2.push_back(cubeVertices[4]);//2
    part2.push_back(cubeVertices[3]);//1
    part2.push_back(cubeVertices[0]);//3
    
    part2.push_back(cubeVertices[3]);//0
    part2.push_back(cubeVertices[2]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[3]);//1
    part2.push_back(cubeVertices[7]);//3
    
}

void Building::GenerateMult()
{
	vec3 defaultCubeVertices[] = {
		// Front vertices
		vec3(-1, 0,  1), // bottom-left 0
		vec3(1, 0,  1), // bottom-right 1
		vec3(1, 1,  1), // top-right 2
		vec3(-1, 1,  1), // top-left 3
		// Back vertices
		vec3(-1, 0, -1), // bottom-left 4
		vec3(1, 0, -1), // bottom-right 5
		vec3(1, 1, -1), // top-right 6 
		vec3(-1, 1, -1) // top-left 7
	};

	vec3 cubeVertices[8];

	float base_x = rand() % MAX_VARIANCE;
	base_x = (base_x / MAX_VARIANCE) * MAX_X;
	base_x = base_x < 3 ? 3 : base_x;
	float base_y = rand() % MAX_VARIANCE;
	base_y = (base_y / MAX_VARIANCE) * MAX_MULT_Y;
	base_y = base_y < 3 ? 3 : base_y;
	float base_z = rand() % MAX_VARIANCE;
	base_z = (base_z / MAX_VARIANCE) * MAX_Z;
	base_z = base_z < 3 ? 3 : base_z;
	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x = defaultCubeVertices[i].x * base_x;
		cubeVertices[i].y = defaultCubeVertices[i].y * base_y;
		cubeVertices[i].z = defaultCubeVertices[i].z * base_z;
	}

    part0.push_back(cubeVertices[0]);//0
    part0.push_back(cubeVertices[1]);//1
    part0.push_back(cubeVertices[2]);//2
    part0.push_back(cubeVertices[0]);//0
    part0.push_back(cubeVertices[2]);//3
    part0.push_back(cubeVertices[3]);//2
    
    part0.push_back(cubeVertices[1]);//0
    part0.push_back(cubeVertices[5]);//1
    part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[1]);//2
    part0.push_back(cubeVertices[6]);//1
    part0.push_back(cubeVertices[2]);//3
    
    part0.push_back(cubeVertices[4]);//0
    part0.push_back(cubeVertices[5]);//1
    part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[4]);//2
    part0.push_back(cubeVertices[6]);//1
    part0.push_back(cubeVertices[7]);//3
    
    part0.push_back(cubeVertices[4]);//0
    part0.push_back(cubeVertices[7]);//1
    part0.push_back(cubeVertices[3]);//2
    part0.push_back(cubeVertices[4]);//2
    part0.push_back(cubeVertices[3]);//1
    part0.push_back(cubeVertices[0]);//3
    
    part0.push_back(cubeVertices[3]);//0
    part0.push_back(cubeVertices[2]);//1
    part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[6]);//2
    part0.push_back(cubeVertices[3]);//1
    part0.push_back(cubeVertices[7]);//3


	base_x = rand() % MAX_VARIANCE;
	base_x = (base_x / MAX_VARIANCE) * MAX_X;
	base_x = base_x < 1 ? 1 : base_x;
	base_y = rand() % MAX_VARIANCE;
	base_y = (base_y / MAX_VARIANCE) * MAX_MULT_Y;
	base_y = base_y < 1 ? 1 : base_y;
	base_z = rand() % MAX_VARIANCE;
	base_z = (base_z / MAX_VARIANCE) * MAX_Z;
	base_z = base_z < 1 ? 1 : base_z;
	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x = defaultCubeVertices[i].x * base_x + .0025f;
		cubeVertices[i].y = defaultCubeVertices[i].y * base_y + .0025f;
		cubeVertices[i].z = defaultCubeVertices[i].z * base_z + .0025f;
	}

    part1.push_back(cubeVertices[0]);//0
    part1.push_back(cubeVertices[1]);//1
    part1.push_back(cubeVertices[2]);//2
    part1.push_back(cubeVertices[0]);//0
    part1.push_back(cubeVertices[2]);//3
    part1.push_back(cubeVertices[3]);//2
    
    part1.push_back(cubeVertices[1]);//0
    part1.push_back(cubeVertices[5]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[1]);//2
    part1.push_back(cubeVertices[6]);//1
    part1.push_back(cubeVertices[2]);//3
    
    part1.push_back(cubeVertices[4]);//0
    part1.push_back(cubeVertices[5]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[4]);//2
    part1.push_back(cubeVertices[6]);//1
    part1.push_back(cubeVertices[7]);//3
    
    part1.push_back(cubeVertices[4]);//0
    part1.push_back(cubeVertices[7]);//1
    part1.push_back(cubeVertices[3]);//2
    part1.push_back(cubeVertices[4]);//2
    part1.push_back(cubeVertices[3]);//1
    part1.push_back(cubeVertices[0]);//3
    
    part1.push_back(cubeVertices[3]);//0
    part1.push_back(cubeVertices[2]);//1
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[6]);//2
    part1.push_back(cubeVertices[3]);//1
    part1.push_back(cubeVertices[7]);//3
    
	base_x = rand() % MAX_VARIANCE;
	base_x = (base_x / MAX_VARIANCE) * MAX_X;
	base_x = base_x < 1 ? 1 : base_x;
	base_y = rand() % MAX_VARIANCE;
	base_y = (base_y / MAX_VARIANCE) * MAX_MULT_Y;
	base_y = base_y < 1 ? 1 : base_y;
	base_z = rand() % MAX_VARIANCE;
	base_z = (base_z / MAX_VARIANCE) * MAX_Z;
	base_z = base_z < 1 ? 1 : base_z;
	for (int i = 0; i < 8; ++i)
	{
		cubeVertices[i].x = defaultCubeVertices[i].x * base_x + .005f;
		cubeVertices[i].y = defaultCubeVertices[i].y * base_y + .005f;
		cubeVertices[i].z = defaultCubeVertices[i].z * base_z + .005f;
	}

    part2.push_back(cubeVertices[0]);//0
    part2.push_back(cubeVertices[1]);//1
    part2.push_back(cubeVertices[2]);//2
    part2.push_back(cubeVertices[0]);//0
    part2.push_back(cubeVertices[2]);//3
    part2.push_back(cubeVertices[3]);//2
    
    part2.push_back(cubeVertices[1]);//0
    part2.push_back(cubeVertices[5]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[1]);//2
    part2.push_back(cubeVertices[6]);//1
    part2.push_back(cubeVertices[2]);//3
    
    part2.push_back(cubeVertices[4]);//0
    part2.push_back(cubeVertices[5]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[4]);//2
    part2.push_back(cubeVertices[6]);//1
    part2.push_back(cubeVertices[7]);//3
    
    part2.push_back(cubeVertices[4]);//0
    part2.push_back(cubeVertices[7]);//1
    part2.push_back(cubeVertices[3]);//2
    part2.push_back(cubeVertices[4]);//2
    part2.push_back(cubeVertices[3]);//1
    part2.push_back(cubeVertices[0]);//3
    
    part2.push_back(cubeVertices[3]);//0
    part2.push_back(cubeVertices[2]);//1
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[6]);//2
    part2.push_back(cubeVertices[3]);//1
    part2.push_back(cubeVertices[7]);//3

}

void Building::MakeTexture()
{
	int x, y;

}

unsigned char* Building::LoadPPM(const char* filename, int& width, int& height)
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

void Building::LoadTexture()
{
	int width, height;   // texture width/height [pixels]

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	unsigned char * image;
	image = LoadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Building-Lights.ppm", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
    
    
    
    glGenTextures(1, &textureSidewalk);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureSidewalk);
    image = LoadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/sidewalk.ppm", width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
}
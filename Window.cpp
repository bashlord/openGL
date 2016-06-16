#include "window.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <ostream>
#include <cerrno>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <math.h>
#include "shader1.h"
#include "Shader.h"
#include "Model.h"
#include "Building.h"
#include "Rain.h"
#include "AudioManager.h"
#include "CityGen.h"

AudioManager *AudioManager::_instance = 0;
CityGen *cityGen;

static OBJPod* puddle;
static float watertime = 0;

static Shader batShader;
static Model batModel;
static Model capeModel;
static Model jokerModel;
static Shader buildingShader;

static Model water;
static Shader waterShade;

const char* window_title = "GLFW Starter Project";
GLint shaderProgram;
GLuint shaderProgramBeizer;
GLuint envmapshader;

float macmode = true;
GLint shaderProgramSC;
GLint shaderProgramObj;
GLint shader;
static bool batflag = true;
// Default camera parameters
static glm::vec3 cam_pos(0.0f, 0.0f, 3.0f);		// e  | Position of camera
static glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
static glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

static Rain* rain;
GLint rainShader;

static glm::vec3 moon(0,0,0);
 glm::vec3 Window::batSignalPos(0,8,0);
 glm::vec3 Window::batSignalDir(-0.3,1,0);

bool Window::debug_building = false;
Building *building;
Building *building1;
Building *building2;
Building *building3;
Building *building4;
Building *building5;
Building *building6;
Building *building7;


static glm::vec3 bear_cam_pos(0.0f, 0.0f, 3.0f);		// e  | Position of camera
static glm::vec3 bear_cam_look_at(0.0f, 0.0f, 0.0f);
int Window::width;
int Window::height;
static glm::mat4 Bear_V;
static GLuint text1;//top

static float movementSpeed = 9.0f;
static float mouseSpeed = 0.005f;

static std::vector<glm::vec3> controls, controllers;
std::vector<vec3> cps;

glm::mat4 Window::P;
glm::mat4 Window::V;

static double x_coord, y_coord;
static double x_drag, y_drag;
static bool leftB, rightB, motionB;

static int control_point_flag = -1;

static GLuint skyboxVAO, skyboxVBO;
static GLuint streetVAO, streetVBO;
static GLuint buildVAO, buildVBO;

static GLfloat skyboxVertices[] = {
    // Positions
    -500.0f,  500.0f, -500.0f,
    -500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    
    -500.0f, -500.0f,  500.0f,
    -500.0f, -500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f, -500.0f,
    -500.0f,  500.0f,  500.0f,
    -500.0f, -500.0f,  500.0f,
    
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    
    -500.0f, -500.0f,  500.0f,
    -500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f, -500.0f,  500.0f,
    -500.0f, -500.0f,  500.0f,
    
    -500.0f,  500.0f, -500.0f,
    500.0f,  500.0f, -500.0f,
    500.0f,  500.0f,  500.0f,
    500.0f,  500.0f,  500.0f,
    -500.0f,  500.0f,  500.0f,
    -500.0f,  500.0f, -500.0f,
    
    -500.0f, -500.0f, -500.0f,
    -500.0f, -500.0f,  500.0f,
    500.0f, -500.0f, -500.0f,
    500.0f, -500.0f, -500.0f,
    -500.0f, -500.0f,  500.0f,
    500.0f, -500.0f,  500.0f
};

static GLfloat street[] = {
    -500.0f, -0.1f, -500.0f,//0
    -500.0f, -0.1f,  500.0f,//1
    500.0f, -0.1f, -500.0f,//2
    
    500.0f, -0.1f, -500.0f,//2
    -500.0f, -0.1f,  500.0f,//1
    500.0f, -0.1f,  500.0f//3
};

vec3 streetBlock[] = {
    // Front vertices
    vec3(-1, 0,  -1), // bottom-left 0
    vec3(-1, 0,  1), // bottom-right 1
    vec3(1, 0,  -1), // top-right 2
    // Back vertices
    vec3(1, 0, -1), // bottom-left 4
    vec3(-1, 0, 1), // bottom-right 5
    vec3(1, 0, 1) // top-right 6
};


unsigned char* loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    if ( (fp=fopen(filename, "rb")) == NULL)
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
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
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

// load image file into texture object
void loadTexture()
{
    GLuint texture[1];     // storage for one texture
    int twidth, theight;   // texture width/height [pixels]
    unsigned char* tdata;  // texture pixel data
    
    // Load image file
    tdata = loadPPM("image.ppm", twidth, theight);
    if (tdata==NULL) return;
    
    // Create ID for texture
    glGenTextures(1, &texture[0]);
    
    // Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
    
    // Set bi-linear filtering for both minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Window::initialize_objects()
{
    puddle = new OBJPod::OBJPod();
    building = new Building();
    building1 = new Building();
    building2 = new Building();
    building3 = new Building();
    building4 = new Building();
    building5 = new Building();
    building6 = new Building();
    building7 = new Building();
    cityGen = new CityGen();
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float shininess[] = { 100.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    batShader.initShader("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Bat.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Bat.frag" );
     waterShade.initShader("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/envmap.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/envmap.frag" );
    //buildingShader.initShader("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shader1.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shader1.frag" );
    batModel.initModel("/Users/JJK/Desktop/Batman/BatmanArmoured.obj");
     jokerModel.initModel("/Users/JJK/Desktop/Joker/Joker.obj");
    capeModel.initModel("/Users/JJK/Desktop/Batman/Cape.obj");
    water.initModel("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/cylinder_flat.obj");

    unsigned char * image;
    int width, height;
    glGenTextures(6, &text1);
     glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, text1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glLineWidth(100);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Use clamp to edge to hide skybox edges:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_up_tga.ppm",width ,height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_up.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width,width, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    
    //glGenTextures(1, &text2);
    //glBindTexture(GL_TEXTURE_2D, text2);
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_dn_tga.ppm",width , height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_dn.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, width, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    //glGenTextures(1, &text3);
    //glBindTexture(GL_TEXTURE_2D, text3);//bk
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_bk_tga.ppm",width , height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_bk.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    //glGenTextures(1, &text4);
    //glBindTexture(GL_TEXTURE_2D, text4);
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_ft_tga.ppm",width , height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_ft.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    //glGenTextures(1, &text5);
    //glBindTexture(GL_TEXTURE_2D, text5);
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_rt_tga.ppm",width , height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_rt.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    //glGenTextures(1, &text6);
    //glBindTexture(GL_TEXTURE_2D, text6);
    image = loadPPM("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/crim/darkcity_lf_tga.ppm",width , height);
    //image = loadPPM("/Users/JJK/Desktop/mp_us/urbansp_lf.ppm",width ,height);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    
    glGenVertexArrays(1, &streetVAO);
    glGenBuffers(1, &streetVBO);
    glBindVertexArray(streetVAO);
    glBindBuffer(GL_ARRAY_BUFFER, streetVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(street), &street, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
    
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
    //MAIN 3
    
    rain = new Rain();
    
	// Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
	shaderProgram = LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shader.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shader.frag");
    shaderProgramSC =LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderSM.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderSM.frag");
     shaderProgramObj =LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shaderObj.frag");
    shader =LoadShaders("/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shader.vert", "/Users/JJK/Desktop/167hw3/CSE167_3/CSE167_3/shader.frag");
#else // Not windows

    shaderProgramSC =LoadShaders("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shaderSM.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shaderSM.frag");
   shaderProgramObj =LoadShaders("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shaderObj.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shaderObj.frag");
    shader =LoadShaders("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shader1.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/shader1.frag");
    rainShader =LoadShaders("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/rainshader.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/rainshader.frag");
    envmapshader =LoadShaders("/Users/JJK/Desktop/CSE167_3 4/CSE167_3/envmap.vert", "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/envmap.frag");

    

#endif
}
void Window::clean_up()
{

	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
    
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
   AudioManager::Instance()->Update();

}

void Window::display_callback(GLFWwindow* window)
{
    int flag = 0;
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     glDepthMask(GL_FALSE);
    glUseProgram(shaderProgramSC);

    glBindVertexArray(skyboxVAO);
    glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramSC, "view"), 1, GL_FALSE, &V[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramSC, "projection"), 1, GL_FALSE, &P[0][0]);
    glUniform1i(glGetUniformLocation(shaderProgramSC, "flag"), flag);
    // skybox cube
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, text1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Select GL_MODULATE to mix texture with polygon color for shading:
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Use clamp to edge to hide skybox edges:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    
    mat4 puddle1, p1, p2, p3, p4, p5, p6, p7, p8, p9,p10;
    puddle1 = glm::scale(puddle1, vec3(0.4,0.4,0.4));
    waterShade.Use();
    glBindTexture(GL_TEXTURE_CUBE_MAP, text1);
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "MVP"), 1, GL_FALSE,
                       &(P * V )[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(puddle1)[0][0]);
    glUniform3f(glGetUniformLocation(waterShade.Program, "cameraPos"), cam_pos.x, cam_pos.y, cam_pos.z);
    watertime+= 0.25;
    if (watertime >= 360)
        watertime = 0;
    glUniform1f(glGetUniformLocation(waterShade.Program, "time"), watertime);
    water.Draw(waterShade);
    
    p1 =glm::translate(puddle1, glm::vec3(-150.0f, 0.0f, 150.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p1)[0][0]);
    water.Draw(waterShade);
     p2 =glm::translate(puddle1, glm::vec3(-350.0f, 0.0f, 177.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p2)[0][0]);
    water.Draw(waterShade);
     p3 =glm::translate(puddle1, glm::vec3(222.0f, 0.0f, 322.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p3)[0][0]);
    water.Draw(waterShade);
     p4 =glm::translate(puddle1, glm::vec3(-100.0f, 0.0f, -150.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p4)[0][0]);
    water.Draw(waterShade);
     p5 =glm::translate(puddle1, glm::vec3(76.0f, 0.0f, 333.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p5)[0][0]);
    water.Draw(waterShade);
     p6 =glm::translate(puddle1, glm::vec3(-2.0f, 0.0f, -300.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p6)[0][0]);
    water.Draw(waterShade);
     p7 =glm::translate(puddle1, glm::vec3(210.0f, 0.0f, -34.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p7)[0][0]);
    water.Draw(waterShade);
     p8 =glm::translate(puddle1, glm::vec3(-180.0f, 0.0f, 90.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p8)[0][0]);
    water.Draw(waterShade);
     p9 =glm::translate(puddle1, glm::vec3(450.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p9)[0][0]);
    water.Draw(waterShade);
     p10 =glm::translate(puddle1, glm::vec3(0.0f, 0.0f, -329.0f));
    glUniformMatrix4fv(glGetUniformLocation(waterShade.Program, "model"), 1, GL_FALSE,
                       &(p10)[0][0]);
    water.Draw(waterShade);
    
    glUseProgram(shaderProgramObj);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramObj, "M"), 1, GL_FALSE, &V[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramObj, "MVP"), 1, GL_FALSE, &P[0][0]);
    glUniform3fv(glGetUniformLocation(shaderProgramObj, "batSignalDir"), 1, &batSignalDir[0]);
    glUniform3fv(glGetUniformLocation(shaderProgramObj, "batSignalPos"), 1, &batSignalPos[0]);
    flag = 1;
    glBindVertexArray(streetVAO);
    glUniform1i(glGetUniformLocation(shaderProgramObj, "flag"), flag);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0,6);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    flag = 0;
    
    glUseProgram(rainShader);
    rain->draw(rainShader);
    
    glUseProgram(shader);
    mat4 tmat;
    mat4 tmat1,tmat2,tmat3,tmat4,tmat5,tmat6,tmat7;
    tmat = glm::scale(tmat, glm::vec3(10.0f, 10.0f, 10.0f));
    tmat7 =glm::translate(tmat, glm::vec3(-5.0f, 0.0f, 0.0f));

    tmat = glm::translate(tmat, glm::vec3(5.0f, 0.0f, 0.0f));
    building->Draw(shader, P*V,tmat);
    building7->Draw(shader, P*V,tmat7);
    cityGen->draw(shader, P*V);
   
    batShader.Use();   // <-- Don't forget this one!
    // Transformation matrices
    glUniformMatrix4fv(glGetUniformLocation(batShader.Program, "projection"), 1, GL_FALSE, &P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(batShader.Program, "view"), 1, GL_FALSE, &V[0][0]);
    glUniform3fv(glGetUniformLocation(batShader.Program, "batSignalDir"), 1, &batSignalDir[0]);
    glUniform3fv(glGetUniformLocation(batShader.Program, "batSignalPos"), 1, &batSignalPos[0]);
    
    // Draw the loaded model
    glm::mat4 model;

    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
    
    glm::mat4 bat;
    bat =glm::translate(model, glm::vec3(-500.0f, 1895.0f, -40.0f));
     glUniformMatrix4fv(glGetUniformLocation(batShader.Program, "model"), 1, GL_FALSE,&bat[0][0]);
    batModel.Draw(batShader);
    capeModel.Draw(batShader);
    
    mat4 model1;
    model1= glm::rotate( model, 180.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    model1= glm::rotate( model1, 90.0f / 180.0f * glm::pi<float>(), glm::vec3(-1.0f, 0.0f, 0.0f));
    
    glm::mat4 joker;
    joker=glm::translate(model1, glm::vec3(500.0f, 40.0f, 1895.0f));
     glUniformMatrix4fv(glGetUniformLocation(batShader.Program, "model"), 1, GL_FALSE,&joker[0][0]);
     jokerModel.Draw(batShader);
   
    
    // Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}


void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //scroll not used
}


void Window::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        //printf("left");
        glfwGetCursorPos(window, &x_coord, &y_coord);
        motionB = true;
    }else if (button == GLFW_MOUSE_BUTTON_MIDDLE && !(action == GLFW_PRESS)){
        motionB = false;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        printf("left");
        glfwGetCursorPos(window, &x_coord, &y_coord);
        leftB = true;
        unsigned char res[4];
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        if(macmode)
            glReadPixels(x_coord*2,  viewport[3]-y_coord*2, 1,1,GL_RGBA, GL_UNSIGNED_BYTE, &res);
        else
            glReadPixels(x_coord,  viewport[3]-y_coord, 1,1,GL_RGBA, GL_UNSIGNED_BYTE, &res);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        //printf("left");
        //glfwGetCursorPos(window, &x_coord, &y_coord);
        leftB = false;
        control_point_flag = -1;
    }
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        glfwGetCursorPos(window, &x_drag, &y_drag);
        rightB = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        //glfwGetCursorPos(window, &x_coord, &y_coord);
        rightB = false;
    }
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    //glfwGetCursorPos(window, &xpos, &ypos);
    if(motionB){
        float horizontalAngle = 3.14f;
        // vertical angle : 0, look at the horizon
        float verticalAngle = 0.0f;
        
        horizontalAngle += mouseSpeed  * float(640/2 - xpos);
        verticalAngle   += mouseSpeed  * float( 480/2 - ypos );
        glm::vec3 direction =  glm::vec3(
                                         cos(verticalAngle) * sin(horizontalAngle),
                                         sin(verticalAngle),
                                         cos(verticalAngle) * cos(horizontalAngle)
                                         );

        cam_look_at = cam_pos + direction;
        glm::vec3 right = glm::vec3(
                                    sin(horizontalAngle - 3.14f/2.0f),
                                    0,
                                    cos(horizontalAngle - 3.14f/2.0f)
                                    );
       glm::vec3 up = glm::cross( right, direction );
        cam_up = up;

    }
    
    // controls ARE THE POINTS
    // controllers ARE THE LINES
    if(leftB){
        
    
    }
    else if(rightB){
        
    }
}


void Window::dragTrackball(int w, int h, int startX, int startY, int endX, int endY) {

}

void Window::rotateLight(int w, int h, int startX, int startY, int endX, int endY) {
    glm::vec3 x_vec, x_vec2; // mouse drag positions
    
    float x_vector = (float)(2.0 * startX - w) / (float)w;
    float y_vector = (float)(h - 2.0 * startY) / (float)h;
    float x_vector2 = (float)(2.0 * endX - w) / (float)w;
    float x_vec2y = (float)(h - 2.0 * endY) / (float)h;

    
    float length = sqrt(x_vector*x_vector + y_vector*y_vector);
    length = length < 1.0 ? length : 1.0;
    float z_vector = sqrtf(1.001 - length * length);
    
        length = sqrt(x_vector2*x_vector2 + x_vec2y*x_vec2y);
    length = length < 1.0 ? length : 1.0;
    float z_vector2 = sqrtf(1.001 - length * length);
    
    x_vec = glm::vec3(x_vector, y_vector, z_vector);
    x_vec2 = glm::vec3(x_vector2, x_vec2y, z_vector2);

    glm::normalize(x_vec);
    glm::normalize(x_vec2);
    
    // rotation angle (in degrees)
    double rotationAngle = (acos(x_vec2[0] * x_vec.x + x_vec2[1] * x_vec.y + x_vec2[2] * x_vec.z / (x_vec2.length() * x_vec.length()))) * 180.0 / glm::pi<float>();
    //x_vec2.angleFrom(x_vec);
    
    // rotation tmat_vec
    glm::vec3 tmat_vec= glm::cross(x_vec, x_vec2);
    
    glm::mat4 inverse = P*V;
    glm::vec4 v3 = inverse * glm::vec4(tmat_vec[0], tmat_vec[1], tmat_vec[2], 0.0);
    tmat_vec = glm::vec3(v3[0], v3[1], v3[2]);
    //tmat_vec.normalize();
    tmat_vec = glm::normalize(tmat_vec);
    
    double cosAngle = cos(rotationAngle);
    double sinAngle = sin(rotationAngle);
    glm::mat4 rm = glm::mat4(
                             (tmat_vec.x*tmat_vec.x)*(1 - cosAngle) + cosAngle, (tmat_vec.x*tmat_vec.y)*(1 -cosAngle) - (tmat_vec.z*sinAngle), (tmat_vec.x*tmat_vec.z)*(1 -cosAngle) + (tmat_vec.y*sinAngle), 0.0,
                             (tmat_vec.x*tmat_vec.y)*(1 -cosAngle) + (tmat_vec.z*sinAngle), (tmat_vec.y*tmat_vec.y)*(1 -cosAngle) +cosAngle, (tmat_vec.y*tmat_vec.z)*(1 -cosAngle) - (tmat_vec.x*sinAngle), 0.0,
                             (tmat_vec.x*tmat_vec.z)*(1 -cosAngle) - (tmat_vec.y*sinAngle), (tmat_vec.y*tmat_vec.z)*(1 -cosAngle) + (tmat_vec.x*sinAngle), (tmat_vec.z*tmat_vec.z)*(1 -cosAngle) +cosAngle, 0.0,
                             0.0, 0.0, 0.0, 1.0);
     //glm::mat4 rm = glm::mat4();
    
    if(batflag){
        
        //Main::spotLight->setDir( vec3( rm * vec4(Main::spotLight->dir,0.0)));
        batSignalDir = glm::vec3( rm * glm::vec4(batSignalDir,0.0));
        
    }

}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printf("key: %d", key);
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if(key == 67){
            Main::colorflag = (Main::colorflag+1)%12;
        }
        glm::vec3 forwardVector = cam_look_at - cam_pos;
        forwardVector = glm::vec3(glm::normalize(forwardVector));
        if(key == GLFW_KEY_W){
            
            cam_pos += (forwardVector * movementSpeed);
            cam_look_at += (forwardVector * movementSpeed);
        }
        if(key == GLFW_KEY_S){
            cam_pos -= (forwardVector * movementSpeed);
            cam_look_at -= (forwardVector * movementSpeed);
        }
        if(key == GLFW_KEY_A){
            glm::vec3 leftVector = glm::cross(cam_up,forwardVector);
            cam_pos += leftVector * movementSpeed;
            cam_look_at += leftVector * movementSpeed;
        }
        if(key == GLFW_KEY_D){
            glm::vec3 rightVector = glm::cross(forwardVector, cam_up);
            cam_pos += rightVector * movementSpeed;
            cam_look_at += rightVector * movementSpeed;
            
        }if(key == GLFW_KEY_UP){
            if(batflag){
                printf("Right B\n");
                printf("New batsignal Dir %f %f %f\n ", batSignalDir.x, batSignalDir.y, batSignalDir.z);

                /*
                
                float horizontalAngle = 3.14f;
                // vertical angle : 0, look at the horizon
                float verticalAngle = 0.0f;
                
                horizontalAngle += mouseSpeed  * float(640/2 - xpos);
                verticalAngle   += mouseSpeed  * float( 480/2 - ypos );
                glm::vec3 direction =  glm::vec3(
                                                 cos(verticalAngle) * sin(horizontalAngle),
                                                 sin(verticalAngle),
                                                 cos(verticalAngle) * cos(horizontalAngle)
                                                 );
                
                cam_look_at = cam_pos + direction;
                glm::vec3 right = glm::vec3(
                                            sin(horizontalAngle - 3.14f/2.0f),
                                            0,
                                            cos(horizontalAngle - 3.14f/2.0f)
                                            );
                glm::vec3 up = glm::cross( right, direction );
                cam_up = up;
                */
                batSignalDir = batSignalPos + (batSignalDir +vec3(0.25,0.0,0));
                
                
                
                printf("New batsignal Dir %f %f %f\n\n ", batSignalDir.x, batSignalDir.y, batSignalDir.z);
            }
        }if(key == GLFW_KEY_DOWN){
            if(batflag){
                printf("Right B\n");
                printf("New batsignal Dir %f %f %f\n ", batSignalDir.x, batSignalDir.y, batSignalDir.z);
                
                //batSignalDir +=vec3(-0.25,0,0);
                batSignalDir = normalize( batSignalPos +( batSignalDir -vec3(0.25,0.0,0)));
                printf("New batsignal Dir %f %f %f\n\n ", batSignalDir.x, batSignalDir.y, batSignalDir.z);
            }
        }
        if(key == GLFW_KEY_SPACE){
            //building->GenerateNew();
            building1->GenerateNew();
            building2->GenerateNew();
            building3->GenerateNew();
            building4->GenerateNew();
            building5->GenerateNew();
            building6->GenerateNew();
        
        }
        if( key == GLFW_KEY_H){
            AudioManager::Instance()->Laugh();
        }
        if( key == GLFW_KEY_J){
            cityGen->recalc();
        }
    }
}






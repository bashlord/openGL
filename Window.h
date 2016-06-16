#ifndef _WINDOW_H_
#define _WINDOW_H_
#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OBJObject.h"
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "main.h"
#include <list>
#include "Node.h"




class Window
{
public:
	static int width;
	static int height;
	static glm::mat4 P;
	static glm::mat4 V;
    static bool debug_building;
    static vec3 batSignalPos,batSignalDir;
    
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void rotateTrackball(int w, int h, int startX, int startY, int endX, int endY);
    static void dragTrackball(int w, int h, int startX, int startY, int endX, int endY);
    static void rotateLight(int w, int h, int startX, int startY, int endX, int endY);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    
   };

#endif

#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <vector>
#include "Window.h"
#include "/Users/JJK/Desktop/FMOD-Programmers-API/api/lowlevel/inc/fmod.hpp"
#include "/Users/JJK/Desktop/FMOD-Programmers-API/api/lowlevel/inc/fmod_errors.h"

using namespace glm;

class AudioManager
{
private:
	static AudioManager *_instance;
	
	AudioManager();
	void FmodErrorCheck(FMOD_RESULT result);
public:
	static AudioManager *Instance();

	~AudioManager();
	void Update();
	void Laugh();
};

#endif


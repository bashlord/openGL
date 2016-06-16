#ifndef _MAIN_H_
#define _MAIN_H_
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Window.h"
#include "Light.h"
#include "Group.h"
#include "OBJCyl.h"
#include "OBJPod.h"
#include "OBJBatman.h"
#include "OBJBear.h"
#include "MatrixTransform.h"

namespace Main {
    extern OBJObject bunny;//("/Users/JJK/Desktop/CSE167-Starter-Code-master/CSE167_1/CSE167_1/bunny.obj");
    extern OBJObject dragon;//("/Users/JJK/Desktop/CSE167-Starter-Code-master/CSE167_1/CSE167_1/dragon.obj");
    extern OBJObject bear;
    //extern Camera* camera;
    //extern PointLight* pl;
    extern SpotLight *spotLight;
     extern SpotLight *dirLight;
    extern PointLight  *pointLight;
    extern int colorflag;
    
    extern Group* cake;
     extern Group* cake1;
     extern MatrixTransform* theCake;
}

#endif
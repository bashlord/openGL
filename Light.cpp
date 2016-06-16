//
//  Light.cpp
//  CSE167-Starter-Code-2
//
//  Created by John Jin Woong Kim on 4/15/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "Light.h"


Light::Light(int l, float* d, float* s, float* a) : lightNum(l) {
    // set GL_LIGHT
    
    for (int i = 0; i < 4; ++i) {
        diffuse[i] = d[i];
        specular[i] = s[i];
        ambient[i] = a[i];
    }
    
}


Light::~Light() {
}



PointLight::PointLight(int i, float* d, float *s, float *a, float* p) : Light(i, d, s, a) {
    for (int i = 0; i < 4; ++i) {
        pos[i] = p[i];
    }
    
}
PointLight::~PointLight() {
    
}

SpotLight::SpotLight(int i, float* d, float *s, float *a, float *p, float *di, float e, float c) : Light(i, d, s, a) {
    for (int i = 0; i < 4; ++i) {
        pos[i] = p[i];
    }

    dir = glm::vec3(di[0],di[1],di[2]);
    exp = e;
    cutoff = c;

}

SpotLight::~SpotLight() {
    
}


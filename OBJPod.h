//
//  OBJPod.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef OBJPod_h
#define OBJPod_h
#pragma once
#include <stdio.h>
#include "Geode.h"


class OBJPod : public Geode{

    
public:
    OBJPod();
    OBJPod(const OBJPod &obj);
    ~OBJPod();

    void parse(const char *filepath);
    void render();
    
};


#endif /* OBJPod_hpp */

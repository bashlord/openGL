//
//  OBJBear.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 5/6/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef OBJBear_h
#define OBJBear_h

#pragma once
#include <stdio.h>
#include "Geode.h"


class OBJBear : public Geode{
    
    
public:
    OBJBear();
    OBJBear(const OBJBear &obj);
    ~OBJBear();
    
    void parse(const char *filepath);
    void render();
    
};


#endif /* OBJPod_hpp */

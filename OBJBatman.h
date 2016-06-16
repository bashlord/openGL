//
//  OBJBatman.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 5/27/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef OBJBatman_hpp
#define OBJBatman_hpp

#pragma once
#include <stdio.h>
#include "Geode.h"


class OBJBatman : public Geode{
    
    
public:
    OBJBatman();
    OBJBatman(const OBJBatman &obj);
    ~OBJBatman();
    
    void parse(const char *filepath);
    void render();
    
};


#endif /* OBJPod_hpp */

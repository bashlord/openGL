//
//  OBJCyl.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef OBJCyl_h
#define OBJCyl_h

#pragma once
#include <stdio.h>
#include "Geode.h"


class OBJCyl : public Geode{
    
public:
    OBJCyl();
    OBJCyl(const OBJCyl &obj);
    OBJCyl(const OBJCyl &obj, int i);
    ~OBJCyl();
    void parse(const char *filepath);
    void render();
    
    
private:

    
    
};


#endif /* OBJPod_hpp */


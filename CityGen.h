//
//  CityGen.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 6/6/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef CityGen_h
#define CityGen_h

#include <stdio.h>
#include <random>
#include "Building.h"
#include "Park.h"
class CityGen
{
public:

    int xLimit,zLimit;//this is the max/min we are going to be using, z has a max/min of 10/5 streets
                                                                //x has a max/min of 8/4 streets
    CityGen();
    void draw(GLuint shader);
    void draw(GLuint shader, mat4 mvp);
    void regen();
    void recalc();
    
private:
    Building *building1;
    Building *building2;
    Building *building3;
    Building *building4;
    Building *building5;
    Building *building6;
    Building *building7;
    
    Building *building8;
    Building *building9;
    Building *building10;
    Building *building11;
    Building *building12;
    Building *building13;
    Building *building14;
    Park* park1;
    Park* park2;
    Park* park3;
    
    std::vector<Building*> buildings;
    std::vector<Park*> parks;

};

#endif /* CityGen_hpp */

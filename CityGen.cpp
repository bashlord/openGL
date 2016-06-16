//
//  CityGen.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 6/6/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "CityGen.h"

std::default_random_engine generator;
std::uniform_int_distribution<int> distributionZ(5,10);
std::uniform_int_distribution<int> distributionX(4,8);

float zoffset, xoffset;
float zpos,xpos;

static float xstep = 5;
static float zstep = 5;

CityGen::CityGen(){
    zLimit = distributionZ(generator);//range of 5-10
    xLimit = distributionX(generator);//range of 4-8
    
    building1 = new Building();
    building2 = new Building();
    building3 = new Building();
    building4 = new Building();
    building5 = new Building();
    building6 = new Building();
    building7 = new Building();
    building8 = new Building();
    building9 = new Building();
    building10 = new Building();
    building11 = new Building();
    building12 = new Building();
    building13 = new Building();
    building14 = new Building();
    
    park1 = new Park();
    park2 = new Park();
    park3 = new Park();
    
    parks.push_back(park1);
    parks.push_back(park2);
    parks.push_back(park3);

    buildings.push_back(building1);
    buildings.push_back(building2);
    buildings.push_back(building3);
    buildings.push_back(building4);
    buildings.push_back(building5);
    buildings.push_back(building6);
    buildings.push_back(building7);
    buildings.push_back(building8);
    buildings.push_back(building9);
    buildings.push_back(building10);
    buildings.push_back(building11);
    buildings.push_back(building12);
    buildings.push_back(building13);
    buildings.push_back(building14);
}

void CityGen::draw(GLuint shader){

}

void CityGen::draw(GLuint shader, mat4 mvp){

    //lets just have z and x limit preset for base case reasons
    
    //if(zLimit == 10) zoffset = 2;//these offsets are by 5.0f, meaning offset of 1 means no space between streets
    //else if(zLimit == 9) zoffset = ;
    //if(xLimit == 8) xoffset = 2;//^^^^
    zoffset = zLimit /3;
    xoffset = xLimit/3;
    int bcount = 0;
    int pcount = 0;
    xpos = -45.0f;
    zpos = -45.0f;
    
    mat4 tmat;
    tmat = glm::scale(tmat, glm::vec3(10.0f, 10.0f, 10.0f));
    mat4 tmat1,tmat2,tmat3,tmat4,tmat5,tmat6,tmat7;
    if(zLimit < 7) zLimit *= 2;
    if(xLimit < 7) xLimit *= 2;

    //printf("xlim %d zlim %d\n", xLimit, zLimit);
    for( int i = 0; i < zLimit; i++){//z INDEX
        xpos = -45.0;
        for(int j = 0; j < xLimit; j++){//x INDEX
            if( (j < 7 && j > 3 && i == 2)){
                tmat1 =glm::translate(tmat, glm::vec3(xpos, 0.0f, zpos));
                parks.at(pcount++%2)->draw(shader, mvp, tmat1);
                xpos += xstep*xoffset;
            }else{
                tmat1 =glm::translate(tmat, glm::vec3(xpos, 0.0f, zpos));
                buildings.at(bcount++%13)->Draw(shader, mvp, tmat1);
                xpos += xstep*xoffset;
            }
        }
        zpos += zstep*zoffset;
    }
}

void CityGen::recalc(){
    zLimit = distributionZ(generator);//range of 5-10
    xLimit = distributionX(generator);//range of 4-8

}

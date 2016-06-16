//
//  MatrixTransform.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef MatrixTransform_h
#define MatrixTransform_h
#pragma once

#include "Group.h"
using namespace glm;

class MatrixTransform : public Group {
protected:
    mat4 M; // Transformation matrix
public:
    MatrixTransform();
    MatrixTransform(mat4 m);
    ~MatrixTransform();
    

    void draw(mat4);
    void update(mat4);
    
    void setM(mat4 M) { this->M = M; }
    mat4 getM() { return M; }
};

#endif /* MatrixTransform_hpp */

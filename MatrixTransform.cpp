//
//  MatrixTransform.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "MatrixTransform.h"

MatrixTransform::MatrixTransform() {
   
}

MatrixTransform::MatrixTransform(mat4 m) {
    M = m;
    MVP = m;
    
}
MatrixTransform::~MatrixTransform() {

}



void MatrixTransform::draw(mat4 C) {
    mat4 tm = C * MVP;

    for (Node* child : *children) {
        child->draw(tm);
    }
}


void MatrixTransform::update(mat4 C){
    mat4 tm = C * MVP;
    for (Node* child : *children) {
        child->update(tm);
    }
}
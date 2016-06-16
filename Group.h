//
//  Group.hpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#ifndef Group_h
#define Group_h
#pragma once
#include <stdio.h>
#include "Node.h"
#include <list>

using namespace glm;

class Group : public Node {
protected:
    std::list<Node*> *children;
    
public:
    Group(char* n = "");
    Group(const Group&);
    virtual ~Group();
    
    void addChild(Node*); // Add child
    bool removeChild(Node*); // Remove child
    bool removeChild(char* nodeName); // Remove child by name
    bool removeChild(int i); // Remove child by index
    
    void setParent(Node& p) { *this->parent = p; }
    
    virtual void draw(mat4) = 0;
    virtual void update(mat4 C) = 0;
};

#endif /* Group_hpp */

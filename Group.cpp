//
//  Group.cpp
//  CSE167_3
//
//  Created by John Jin Woong Kim on 4/30/16.
//  Copyright © 2016 John Jin Woong Kim. All rights reserved.
//

#include "Group.h"
Group::Group(char* n) {
    this->id = n;
    children = new std::list<Node*>();
}

Group::Group(const Group& other) {
    children = new std::list<Node*>();
}

Group::~Group() {
    for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++) {
        delete *it;
    }
    delete children;
}

void Group::addChild(Node* child) {
    children->push_back(child);
}

bool Group::removeChild(Node* child) {
    for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++) {
        if (*it == child) {
            children->erase(it);
            return true;
        }
    }
    return false;
}

bool Group::removeChild(char* childName) {
    for (Node* child : *children) {
        if (strcmp(childName, child->getId())) {
            children->remove(child);
            return true;
        }
    }
    return false;
}

bool Group::removeChild(int index) {
    std::list<Node*>::iterator it = children->begin();
    std::advance(it, index);
    children->erase(it);
    return true;
}
/*
void Group::draw(mat4 C) {
    for (Node* child : *children) {
        child->draw(C);
        // draw(C);
    }
}

void Group::update(){
    
    for (Node* child : *children) {
        child->update();
    }
}
*/
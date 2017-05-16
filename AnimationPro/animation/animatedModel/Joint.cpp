//
//  Joint.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Joint.hpp"


Joint::Joint() { }

Joint::Joint(int index, string name, glm::mat4 bindLocalTransform) {
    this->index = index;
    this->name = name;
    this->localBindTransform = bindLocalTransform;
}

void Joint::addChild(Joint child) {
    this->children.push_back(child);
}

glm::mat4 Joint::getAnimatedTransform() {
    return this->animatedTransform;
}

void Joint::setAnimatedTransform(glm::mat4 transform) {
    this->animatedTransform = transform;
}

glm::mat4 Joint::getInvBindTransform() {
    return this->invBindTransform;
}

int Joint::getIndex() {
    return this->index;
}

vector<Joint> Joint::getChildren() {
    return this->children;
}

string Joint::getName() {
    return this->name;
}

void Joint::calcInvBindTransform(glm::mat4 parentBindTransform) {
    glm::mat4 bindTransform = parentBindTransform * this->localBindTransform;
    this->invBindTransform = glm::inverse(bindTransform);
    
    for (Joint child : this->children) {
        child.calcInvBindTransform(bindTransform);
    }
}

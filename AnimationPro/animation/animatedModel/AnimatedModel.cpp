//
//  AnimatedModel.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "AnimatedModel.hpp"


AnimatedModel::AnimatedModel() { }

AnimatedModel::AnimatedModel(TextureModel model, Joint rootJoint, int jointCount) {
    this->textureModel = model;
    this->rootJoint = rootJoint;
    this->jointCount = jointCount;
}

TextureModel AnimatedModel::getTextureModel() {
    return this->textureModel;
}

Joint AnimatedModel::getRootJoint() {
    return this->rootJoint;
}

glm::mat4* AnimatedModel::getJointTransforms() {
    glm::mat4 *mats = new glm::mat4[this->jointCount];
    
    addJointToArray(this->rootJoint, mats);
    return mats;
}

void AnimatedModel::clean() {
    
}

void AnimatedModel::update() {
    
}

void AnimatedModel::addJointToArray(Joint headJoint, glm::mat4 *jointMats) {
    jointMats[headJoint.getIndex()] = headJoint.getAnimatedTransform();
    for (Joint joint : headJoint.getChildren()) {
        addJointToArray(joint, jointMats);
    }
}

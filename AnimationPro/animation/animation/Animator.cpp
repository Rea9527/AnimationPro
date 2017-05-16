//
//  Animator.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Animator.hpp"


Animator::Animator() {
    this->animationTime = 0.0f;
}

Animator::Animator(AnimatedModel entity) {
    this->animationTime = 0.0f;
    this->entity = entity;
}

void Animator::runAnimation(Animation animation) {
    this->animationTime = 0.0f;
    this->currentAnimation = animation;
}

void Animator::update() {
    if (0) return;
    
    this->increaseAnimationTime();
    map<string, glm::mat4> currentPos = calcCurrentAnimationPos();
    applyPoseToJoints(currentPos, entity.getRootJoint(), glm::mat4());
}

void Animator::increaseAnimationTime() {
    // animation time shou sync with sys time???
    this->animationTime += 1.0f / 60.0f;
    
    if (animationTime > currentAnimation.getLength()) {
        this->animationTime = fmod(this->animationTime, this->currentAnimation.getLength());
    }
}

map<string, glm::mat4> Animator::calcCurrentAnimationPos() {
    vector<KeyFrame> frames = getPreviousAndNextFrame();
    float progression = calcProgression(frames[0], frames[1]);
    return interpolatePoses(frames[0], frames[1], progression);
}

void Animator::applyPoseToJoints(map<string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform) {
    glm::mat4 currentLocalTransform = currentPose[joint.getName()];
    glm::mat4 currentTransform = parentTransform * currentLocalTransform;
    
    for (Joint childJoint : joint.getChildren()) {
        applyPoseToJoints(currentPose, childJoint, currentTransform);
    }
    
    currentTransform = currentTransform * joint.getInvBindTransform();
    joint.setAnimatedTransform(currentTransform);
}

vector<KeyFrame> Animator::getPreviousAndNextFrame() {
    vector<KeyFrame> allFrames = this->currentAnimation.getKeyFrames();
    KeyFrame previousFrame = allFrames[0];
    KeyFrame nextFrame = allFrames[0];
    
    for (int i = 1; i < allFrames.size(); i++) {
        nextFrame = allFrames[i];
        if (nextFrame.getTimeStamp() > this->animationTime) {
            break;
        }
        previousFrame = allFrames[i];
    }
    
    vector<KeyFrame> frames;
    frames.push_back(previousFrame);
    frames.push_back(nextFrame);
    return frames;
}

float Animator::calcProgression(KeyFrame previousFrame, KeyFrame nextFrame) {
    float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
    float currentTime = animationTime - previousFrame.getTimeStamp();
    return currentTime / totalTime;
}

map<string, glm::mat4> Animator::interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression) {
    map<string, glm::mat4> currentPose;
    
    for (map<string, glm::mat4>::iterator it = currentPose.begin(); it != currentPose.end(); it++) {
        JointTransform previousTransform = previousFrame.getJointKeyFrames()[it->first];
        JointTransform nextTransform = nextFrame.getJointKeyFrames()[it->first];
        JointTransform currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
        currentPose.insert(make_pair(it->first, currentTransform.getLocalTransform()));
    }
    
    return currentPose;
}

//
//  KeyFrame.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "KeyFrame.hpp"


KeyFrame::KeyFrame() { }

KeyFrame::KeyFrame(float timeStamp, map<string, JointTransform> jointKeyFrames) {
    this->timeStamp = timeStamp;
    this->pose = jointKeyFrames;
}

float KeyFrame::getTimeStamp() {
    return this->timeStamp;
}

map<string, JointTransform> KeyFrame::getJointKeyFrames() {
    return this->pose;
}

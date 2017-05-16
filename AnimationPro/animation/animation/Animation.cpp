//
//  Animation.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Animation.hpp"


Animation::Animation() { }

Animation::Animation(float lengthInSeconds, vector<KeyFrame> keyFrames) {
    this->length = lengthInSeconds;
    this->keyFrames = keyFrames;
}

float Animation::getLength() {
    return this->length;
}

vector<KeyFrame> Animation::getKeyFrames() {
    return this->keyFrames;
}

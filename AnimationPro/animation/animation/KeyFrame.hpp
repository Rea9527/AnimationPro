//
//  KeyFrame.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef KeyFrame_hpp
#define KeyFrame_hpp

#include <iostream>
#include <map>

#include "JointTransform.hpp"

using namespace std;


class KeyFrame {
    
public:
    KeyFrame();
    KeyFrame(float timeStamp, map<string, JointTransform> jointKeyFrames);
    
    float getTimeStamp();
    
    map<string, JointTransform> getJointKeyFrames();
    
private:
    float timeStamp;
    
    map<string, JointTransform> pose;
};

#endif /* KeyFrame_hpp */

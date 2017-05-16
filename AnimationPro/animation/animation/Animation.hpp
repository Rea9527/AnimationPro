//
//  Animation.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <iostream>
#include <vector>

#include "KeyFrame.hpp"

using namespace std;

class Animation {
    
public:
    Animation();
    Animation(float lengthInSeconds, vector<KeyFrame> keyFrames);
    
    float getLength();
    vector<KeyFrame> getKeyFrames();
    
private:
    float length;
    
    vector<KeyFrame> keyFrames;
};

#endif /* Animation_hpp */

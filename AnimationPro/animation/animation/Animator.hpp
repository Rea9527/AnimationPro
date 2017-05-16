//
//  Animator.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#include <iostream>
#include <vector>
#include <map>

#include "KeyFrame.hpp"
#include "Animation.hpp"
#include "../animatedModel/AnimatedModel.hpp"


class Animator {
public:
    Animator();
    Animator(AnimatedModel entity);
    
    void runAnimation(Animation animation);
    
    void update();
    
private:
    void increaseAnimationTime();
    
    map<string, glm::mat4> calcCurrentAnimationPos();
    
    void applyPoseToJoints(map<string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform);
    
    vector<KeyFrame> getPreviousAndNextFrame();
    
    float calcProgression(KeyFrame previousFrame, KeyFrame nextFrame);
    
    map<string, glm::mat4> interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression);
    
    AnimatedModel entity;
    
    Animation currentAnimation;
    float animationTime;
    
};

#endif /* Animator_hpp */

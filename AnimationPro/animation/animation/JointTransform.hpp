//
//  JointTransform.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef JointTransform_hpp
#define JointTransform_hpp

#include <iostream>

#include "Quaternion.hpp"



class JointTransform {
    
public:
    JointTransform();
    JointTransform(glm::vec3 position, Quaternion rotation);
    
    static JointTransform interpolate(JointTransform frameA, JointTransform frameB, float progression);
    
    glm::mat4 getLocalTransform();
    
private:
    static glm::vec3 interpolate(glm::vec3 start, glm::vec3 end, float progression);
    
    glm::vec3 position;
    Quaternion rotation;
};

#endif /* JointTransform_hpp */

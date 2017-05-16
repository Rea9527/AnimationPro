//
//  AnimatedModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef AnimatedModel_hpp
#define AnimatedModel_hpp

#include <iostream>

#include "../../models/TextureModel.hpp"
#include "Joint.hpp"
#include "../animation/Animation.hpp"

class AnimatedModel {
    
public:
    AnimatedModel();
    AnimatedModel(TextureModel model, Joint rootJoint, int jointCount);
    
    TextureModel getTextureModel();
    
    Joint getRootJoint();
    
    glm::mat4* getJointTransforms();
    
    void clean();
    void update();
    
private:
    void addJointToArray(Joint headJoint, glm::mat4 jointMats[]);
    
    TextureModel textureModel;
    
    Joint rootJoint;
    int jointCount;

};

#endif /* AnimatedModel_hpp */


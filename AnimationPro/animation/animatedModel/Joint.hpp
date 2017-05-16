//
//  Joint.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Joint_hpp
#define Joint_hpp

#include <iostream>
#include <string>
#include <vector>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


class Joint {
    
public:
    Joint();
    Joint(int index, string name, glm::mat4 bindLocalTransform);
    
    void addChild(Joint child);
    
    glm::mat4 getAnimatedTransform();
    void setAnimatedTransform(glm::mat4 transform);
    
    glm::mat4 getInvBindTransform();
    
    void calcInvBindTransform(glm::mat4 parentBindTransform);
    
    int getIndex();
    vector<Joint> getChildren();
    string getName();
    
private:
    int index;
    string name;
    vector<Joint> children;
    
    glm::mat4 animatedTransform;
    
    glm::mat4 localBindTransform;
    glm::mat4 invBindTransform;
    
};

#endif /* Joint_hpp */

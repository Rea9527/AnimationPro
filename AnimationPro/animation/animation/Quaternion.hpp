//
//  Quaternion.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include <iostream>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Quaternion {
    
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    
    void normalize();
    glm::mat4 toRotationMatrix();
    
    static Quaternion fromMatrix(glm::mat4 mat);
    
    static Quaternion interpolate(Quaternion a, Quaternion b, float blend);
    
private:
    float x;
    float y;
    float z;
    float w;
};

#endif /* Quaternion_hpp */

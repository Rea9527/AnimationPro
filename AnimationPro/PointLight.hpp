//
//  PointLight.hpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include "Light.hpp"

class PointLight : public Light {
public:
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos, GLfloat constant, GLfloat linear, GLfloat quadratic);
    
    glm::vec3 getPos();
    GLfloat getConstant();
    GLfloat getLinear();
    GLfloat getQuadratic();
    
    
private:
    glm::vec3 Pos;
    
    GLfloat Constant;
    GLfloat Linear;
    GLfloat Quadratic;
};

#endif /* PointLight_hpp */

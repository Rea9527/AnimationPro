//
//  PointLight.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "PointLight.hpp"



PointLight::PointLight(glm::vec3 ambient,glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos,
                       GLfloat constant = 1.0f, GLfloat linear = 0.9f, GLfloat quadratic = 0.032f) : Light(ambient, diffuse, specular) {
    
    this->Pos = pos;
    this->Constant = constant;
    this->Linear = linear;
    this->Quadratic = quadratic;
}

glm::vec3 PointLight::getPos() {
    return this->Pos;
}

GLfloat PointLight::getConstant() {
    return this->Constant;
}

GLfloat PointLight::getLinear() {
    return this->Linear;
}

GLfloat PointLight::getQuadratic() {
    return this->Quadratic;
}

//
//  DirectionalLight.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "DirectionalLight.hpp"



DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                                   glm::vec3 direction) : Light(ambient, diffuse, specular) {
    this->Direction = direction;
}

glm::vec3 DirectionalLight::getDirection() {
    return this->Direction;
}

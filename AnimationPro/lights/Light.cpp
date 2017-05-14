//
//  Light.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Light.hpp"



Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->Ambient = ambient;
    this->Diffuse = diffuse;
    this->Specular = specular;
}

glm::vec3 Light::getAmbient() {
    return this->Ambient;
}

glm::vec3 Light::getDiffuse() {
    return this->Diffuse;
}

glm::vec3 Light::getSpecular() {
    return this->Specular;
}

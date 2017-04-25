//
//  Light.hpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>


class Light {
    
public:
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    
private:
    
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};

#endif /* Light_hpp */

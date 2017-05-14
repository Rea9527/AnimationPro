//
//  DirectionalLight.hpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include "Light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
    
    glm::vec3 getDirection();
    
private:
    glm::vec3 Direction;
};

#endif /* DirectionalLight_hpp */

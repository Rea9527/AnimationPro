//
//  Entity.hpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <iostream>
#include "../models/TextureModel.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
    
public:
    Entity();
    Entity(TextureModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    TextureModel getModel();
    
private:
    TextureModel model;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
};

#endif /* Entity_hpp */

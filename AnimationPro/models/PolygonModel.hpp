//
//  PolygonModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 25/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef PolygonModel_hpp
#define PolygonModel_hpp

#include <iostream>

#include "RawModel.hpp"
#include "../loader/Loader.hpp"

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class PolygonModel {
    
public:
    PolygonModel();
    
    void load();
    void draw();
    
    RawModel getModel();
    
    // transformation
    glm::mat4 modelMatrix;
    glm::mat4 projectionViewMatrix;
    
private:
    RawModel rawModel;
    Loader loader;
    
};

#endif /* PolygonModel_hpp */

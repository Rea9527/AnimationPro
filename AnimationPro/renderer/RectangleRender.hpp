//
//  RectangleRender.hpp
//  AnimationPro
//
//  Created by 陈主润 on 02/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef RectangleRender_hpp
#define RectangleRender_hpp

#include <iostream>

#include "../camera/Camera.hpp"
#include "../shaders/StaticShader.hpp"
#include "../shaders/ModelShader.hpp"
#include "../models/RectangleModel.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RectangleRender {
    
public:
    RectangleRender(StaticShader shader);
    RectangleRender(ModelShader shader);
    void render(RectangleModel cube, glm::mat4 projectionView, glm::mat4 model, Camera camera);
    
    void addLight(PointLight pointLight, DirectionalLight directionalLight);
    
    void unbind();
    
private:
    StaticShader staticShader;
    ModelShader modelShader;
    
    bool isLighting;
};

#endif /* RectangleRender_hpp */

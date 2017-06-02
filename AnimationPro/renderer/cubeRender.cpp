//
//  cubeRender.cpp
//  AnimationPro
//
//  Created by 陈主润 on 25/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "cubeRender.hpp"


CubeRender::CubeRender(StaticShader shader) {
    this->Shader = shader;
}

void CubeRender::render(PolygonModel cube, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
    this->Shader.Use();
    this->Shader.getAllUniformLocations();
    this->Shader.loadProjectionMat(glm::value_ptr(projection));
    this->Shader.loadViewMat(glm::value_ptr(view));
    this->Shader.loadModelMat(glm::value_ptr(model));
    
    cube.draw();
    
    this->Shader.Stop();
}

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

void CubeRender::render(PolygonModel cube, glm::mat4 projectionView, glm::mat4 model) {
    this->Shader.Use();
    this->Shader.getAllUniformLocations();
    this->Shader.loadProjectionViewMatrix(projectionView);
    this->Shader.loadModelMat(model);
    
    cube.draw();
    
    this->Shader.Stop();
}

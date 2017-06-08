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

void CubeRender::render(PolygonModel cube) {
    this->Shader.Use();
    this->Shader.getAllUniformLocations();
    this->Shader.loadProjectionViewMatrix(cube.projectionViewMatrix);
    this->Shader.loadModelMat(cube.modelMatrix);
    
    cube.draw();
    
    this->Shader.Stop();
}

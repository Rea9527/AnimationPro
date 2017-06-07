//
//  SkeletalRender.cpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "SkeletalRender.hpp"


SkeletalRender::SkeletalRender(ModelShader shader) {
    this->Shader = shader;
    this->Shader.Use();
    this->Shader.getAllUniformLocations();
    this->Shader.Stop();
}

void SkeletalRender::render(SkeletalModel &skeletalModel, glm::mat4 projectionView, glm::mat4 model, Camera camera) {
    glStencilMask(0x00);
    
    this->Shader.Use();
    this->Shader.loadViewPos(camera.Pos.x, camera.Pos.y, camera.Pos.z);
    this->Shader.loadProjectionViewMatrix(projectionView);
    this->Shader.loadModelMat(model);
    
    skeletalModel.Draw(this->Shader);
    
    this->Shader.Stop();
}

void SkeletalRender::addLight(PointLight pointLight, DirectionalLight directionalLight) {
    this->Shader.Use();
    this->Shader.addPointLight(pointLight);
    this->Shader.addDirectionalLight(directionalLight);
    this->Shader.Stop();
}

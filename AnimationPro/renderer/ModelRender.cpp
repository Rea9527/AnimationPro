//
//  ModelRender.cpp
//  AnimationPro
//
//  Created by 陈主润 on 25/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ModelRender.hpp"


ModelRender::ModelRender(ModelShader shader) {
    this->Shader = shader;
}

void ModelRender::render(ObjModel objModel, Camera camera) {
    
    this->prepare();
    this->Shader.loadViewPos(camera.Pos.x, camera.Pos.y, camera.Pos.z);
    this->Shader.loadProjectionViewMatrix(objModel.projectionViewMatrix);
    this->Shader.loadModelMat(objModel.modelMatrix);
    
    objModel.Draw(this->Shader);
    this->Shader.Stop();
}

void ModelRender::addLight(PointLight pointLight, DirectionalLight directionalLight) {
    this->Shader.Use();
    this->Shader.addPointLight(pointLight);
    this->Shader.addDirectionalLight(directionalLight);
    this->Shader.Stop();
}

void ModelRender::prepare() {
    this->Shader.Use();
    this->Shader.getAllUniformLocations();

}

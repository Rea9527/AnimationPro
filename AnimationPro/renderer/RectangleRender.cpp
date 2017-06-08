//
//  RectangleRender.cpp
//  AnimationPro
//
//  Created by 陈主润 on 02/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "RectangleRender.hpp"


RectangleRender::RectangleRender(StaticShader shader) {
    this->staticShader = shader;
    this->isLighting = false;
}

RectangleRender::RectangleRender(ModelShader shader) {
    this->modelShader = shader;
    this->isLighting = true;
}

void RectangleRender::render(RectangleModel rectangle, Camera camera) {
    if (isLighting) {
        this->modelShader.Use();
        this->modelShader.getAllUniformLocations();
        this->modelShader.loadViewPos(camera.Pos.x, camera.Pos.y, camera.Pos.z);
        this->modelShader.loadProjectionViewMatrix(rectangle.projectionViewMatrix);
        this->modelShader.loadModelMat(rectangle.modelMatrix);
        
        rectangle.draw();
        
        this->modelShader.Stop();
    } else {
        this->staticShader.Use();
        this->staticShader.getAllUniformLocations();
        this->staticShader.loadProjectionViewMatrix(rectangle.projectionViewMatrix);
        this->staticShader.loadModelMat(rectangle.modelMatrix);
        
        rectangle.draw();
        
        this->staticShader.Stop();
    }
    
}

void RectangleRender::addLight(PointLight pointLight, DirectionalLight directionalLight) {
    this->modelShader.Use();
    this->modelShader.addPointLight(pointLight);
    this->modelShader.addDirectionalLight(directionalLight);
    this->modelShader.Stop();
}

//
//  StaticShader.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "StaticShader.hpp"



StaticShader::StaticShader() { }

StaticShader::StaticShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) { }


void StaticShader::getAllUniformLocations() {
    this->modelLoc = this->getUniformLocation("model");
    this->projectionViewLoc = this->getUniformLocation("projectionView");
}

void StaticShader::loadModelMat(glm::mat4 model) {
    this->setMat4(this->modelLoc, model);
}

void StaticShader::loadProjectionViewMatrix(glm::mat4 projectionViewMat) {
    this->setMat4(this->projectionViewLoc, projectionViewMat);
}

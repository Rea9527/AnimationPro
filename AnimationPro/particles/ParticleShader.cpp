//
//  ParticleShader.cpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ParticleShader.hpp"


ParticleShader::ParticleShader() : Shader() { }

ParticleShader::ParticleShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) { }

void ParticleShader::getAllUniformLocations() {
    this->mvp_loc = this->getUniformLocation("MVP");
    this->modelLoc = this->getUniformLocation("model");
    this->projectionViewLoc = this->getUniformLocation("projectionView");
}

void ParticleShader::loadMVP(glm::mat4 mvp) {
    glUniformMatrix4fv(this->mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
}

void ParticleShader::loadModelMat(glm::mat4 model) {
    this->setMat4(this->modelLoc, model);
}

void ParticleShader::loadProjectionViewMatrix(glm::mat4 projectionViewMat) {
    this->setMat4(this->projectionViewLoc, projectionViewMat);
}

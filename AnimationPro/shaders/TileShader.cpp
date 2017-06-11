//
//  TileShader.cpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TileShader.hpp"


TileShader::TileShader() {}

TileShader::TileShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) {}


void TileShader::loadViewPos(GLfloat x, GLfloat y, GLfloat z) {
    this->viewPosLoc = this->getUniformLocation("viewPos");
    glUniform3f(this->viewPosLoc, x, y, z);
}

void TileShader::getAllUniformLocations() {
    this->modelLoc = this->getUniformLocation("model");
    this->modelViewLoc = this->getUniformLocation("modelView");
    this->projectionViewLoc = this->getUniformLocation("projectionView");
    this->shadowMapMatrixLoc = this->getUniformLocation("toShadowMapSpace");
    this->shadowMapLoc = this->getUniformLocation("shadowMap");
    this->textureLoc = this->getUniformLocation("tex");
}

void TileShader::addDirLight(DirectionalLight light) {
    glUniform3f(this->getUniformLocation("dirLight.direction"), light.getDirection().x, light.getDirection().y, light.getDirection().z);
    glUniform3f(this->getUniformLocation("dirLight.ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z);
    glUniform3f(this->getUniformLocation("dirLight.diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z);
    glUniform3f(this->getUniformLocation("dirLight.specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z);
    
    glUniform1f(this->getUniformLocation("shininess"), 8.0f);
}


void TileShader::loadTextureLoc() {
    
}

void TileShader::connectTexture() {
    this->setInt(this->textureLoc, 0);
    this->setInt(this->shadowMapLoc, 1);
}

void TileShader::loadShadowMapMatrix(glm::mat4 shadowMapMatrix) {
    this->setMat4(this->shadowMapMatrixLoc, shadowMapMatrix);
}

void TileShader::loadModelMat(glm::mat4 model) {
    this->setMat4(this->modelLoc, model);
}

void TileShader::loadProjectionViewMatrix(glm::mat4 projectionViewMat) {
    this->setMat4(this->projectionViewLoc, projectionViewMat);
}

void TileShader::loadModelViewMatrix(glm::mat4 modelViewMat) {
    this->setMat4(this->modelViewLoc, modelViewMat);
}

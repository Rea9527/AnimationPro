//
//  TerrainShader.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TerrainShader.hpp"


TerrainShader::TerrainShader() {}

TerrainShader::TerrainShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) {}


void TerrainShader::loadViewPos(GLfloat x, GLfloat y, GLfloat z) {
    this->viewPosLoc = this->getUniformLocation("viewPos");
    glUniform3f(this->viewPosLoc, x, y, z);
}

void TerrainShader::getAllUniformLocations() {
    this->modelLoc = this->getUniformLocation("model");
    this->projectionViewLoc = this->getUniformLocation("projectionView");
    this->bgTextureLoc = this->getUniformLocation("bgTexture");
    this->rTextureLoc = this->getUniformLocation("rTexture");
    this->gTextureLoc = this->getUniformLocation("gTexture");
    this->bTextureLoc = this->getUniformLocation("bTexture");
    this->blendMapLoc = this->getUniformLocation("blendMap");
    this->shadowMapMatrixLoc = this->getUniformLocation("toShadowMapMatrix");
    this->shadowMapLoc = this->getUniformLocation("shadowMap");
}

void TerrainShader::addDirLight(DirectionalLight light) {
    glUniform3f(this->getUniformLocation("dirLight.direction"), light.getDirection().x, light.getDirection().y, light.getDirection().z);
    glUniform3f(this->getUniformLocation("dirLight.ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z);
    glUniform3f(this->getUniformLocation("dirLight.diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z);
    glUniform3f(this->getUniformLocation("dirLight.specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z);
    
    glUniform1f(this->getUniformLocation("shininess"), 16.0f);
}


void TerrainShader::loadTextureLoc() {

}

void TerrainShader::connectTexture() {
    this->setInt(this->bgTextureLoc, 0);
    this->setInt(this->rTextureLoc, 1);
    this->setInt(this->gTextureLoc, 2);
    this->setInt(this->bTextureLoc, 3);
    this->setInt(this->blendMapLoc, 4);
    this->setInt(this->shadowMapLoc, 5);
}

void TerrainShader::loadShadowMapMatrix(glm::mat4 shadowMapMatrix) {
    this->setMat4(this->shadowMapMatrixLoc, shadowMapMatrix);
}

void TerrainShader::loadModelMat(glm::mat4 model) {
    this->setMat4(this->modelLoc, model);
}

void TerrainShader::loadProjectionViewMatrix(glm::mat4 projectionViewMat) {
    this->setMat4(this->projectionViewLoc, projectionViewMat);
}



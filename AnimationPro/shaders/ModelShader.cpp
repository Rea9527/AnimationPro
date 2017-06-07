//
//  StaticShader.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ModelShader.hpp"


ModelShader::ModelShader() {}

ModelShader::ModelShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) {
    
}

//LIGHT
void ModelShader::loadViewPos(GLfloat x, GLfloat y, GLfloat z) {
    this->viewPosLoc = glGetUniformLocation(this->Program, "viewPos");
    glUniform3f(this->viewPosLoc, x, y, z);
}

void ModelShader::getAllUniformLocations() {
    this->modelLoc = this->getUniformLocation("model");
    this->projectionViewLoc = this->getUniformLocation("projectionView");
}

void ModelShader::loadModelMat(glm::mat4 model) {
    this->setMat4(this->modelLoc, model);
}

void ModelShader::loadProjectionViewMatrix(glm::mat4 projectionViewMat) {
    this->setMat4(this->projectionViewLoc, projectionViewMat);
}

void ModelShader::addPointLight(PointLight light) {
    this->pointLights.push_back(light);
    
    glUniform3f(glGetUniformLocation(this->Program, "pointLights[0].pos"), light.getPos().x, light.getPos().y, light.getPos().z);
    glUniform3f(glGetUniformLocation(this->Program, "pointLights[0].ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z);
    glUniform3f(glGetUniformLocation(this->Program, "pointLights[0].diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z);
    glUniform3f(glGetUniformLocation(this->Program, "pointLights[0].specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z);
    glUniform1f(glGetUniformLocation(this->Program, "pointLights[0].constant"),  light.getConstant());
    glUniform1f(glGetUniformLocation(this->Program, "pointLights[0].linear"),    light.getLinear());
    glUniform1f(glGetUniformLocation(this->Program, "pointLights[0].quadratic"), light.getQuadratic());
}

void ModelShader::addDirectionalLight(DirectionalLight light) {
    this->directionalLights.push_back(light);
    
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.direction"), light.getDirection().x, light.getDirection().y, light.getDirection().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z);
}

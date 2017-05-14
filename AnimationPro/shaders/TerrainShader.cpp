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
    this->viewPosLoc = glGetUniformLocation(this->Program, "viewPos");
    glUniform3f(this->viewPosLoc, x, y, z);
}

void TerrainShader::addDirLight(DirectionalLight light) {
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.direction"), light.getDirection().x, light.getDirection().y, light.getDirection().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z);
    glUniform3f(glGetUniformLocation(this->Program, "dirLight.specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z);
    
    glUniform1f(glGetUniformLocation(this->Program, "shininess"), 16.0f);
}


void TerrainShader::loadTextureLoc() {
    this->bgTextureLoc = glGetUniformLocation(this->Program, "bgTexture");
    this->rTextureLoc = glGetUniformLocation(this->Program, "rTexture");
    this->gTextureLoc = glGetUniformLocation(this->Program, "gTexture");
    this->bTextureLoc = glGetUniformLocation(this->Program, "bTexture");
    this->blendMapLoc = glGetUniformLocation(this->Program, "blendMap");
}

void TerrainShader::connectTexture() {
    glUniform1i(this->bgTextureLoc, 0);
    glUniform1i(this->rTextureLoc, 1);
    glUniform1i(this->gTextureLoc, 2);
    glUniform1i(this->bTextureLoc, 3);
    glUniform1i(this->blendMapLoc, 4);
}

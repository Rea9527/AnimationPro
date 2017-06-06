//
//  ShadowMapRenderer.cpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ShadowMapRenderer.hpp"

ShadowMapRenderer::ShadowMapRenderer() {
    this->SHADOW_MAP_SIZE = 1024;
}

ShadowMapRenderer::ShadowMapRenderer(Camera camera) {
    this->shader = ShadowShader("shadows/shadow.vs", "shadows/shadow.frag");
    this->shadowBox = ShadowBox(this->lightViewMatrix, camera);
    this->shadowFBO = ShadowFrameBuffer(this->SHADOW_MAP_SIZE, this->SHADOW_MAP_SIZE);
}

void ShadowMapRenderer::render(ObjModel model, DirectionalLight light) {
    
}

glm::mat4 ShadowMapRenderer::getToShadowMapMatrix() {
    return this->offset * this->projectionViewMatrix;
}

void ShadowMapRenderer::cleanUp() {
    this->shadowFBO.cleanUp();
}

GLuint ShadowMapRenderer::getShadowMap() {
    return this->shadowFBO.getShadowMap();
}

glm::mat4 ShadowMapRenderer::getLightSpaceTransform() {
    return this->lightViewMatrix;
}

void ShadowMapRenderer::prepare(glm::vec3 lightDirection) {
    this->updateOrthoProjectionMatrix(this->shadowBox.getWidth(), this->shadowBox.getHeight(), this->shadowBox.getLength());
    this->updateLightViewMatrix(lightDirection, this->shadowBox.getCenter());
    this->projectionViewMatrix = this->projectionMatrix * this->lightViewMatrix;
    this->shadowFBO.bindFrameBuffer();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    this->shader.Use();
}

void ShadowMapRenderer::finish() {
    this->shader.Stop();
    this->shadowFBO.unbindFrameBuffer();
}

void ShadowMapRenderer::updateLightViewMatrix(glm::vec3 lightDirection, glm::vec3 center) {
    glm::vec3 direction = glm::normalize(lightDirection);
    glm::vec3 cent = -center;
    this->lightViewMatrix = glm::mat4(1.0f);
    
    float pitch = (float) acos(glm::vec2(direction.x, direction.z).length());
    this->lightViewMatrix = glm::rotate(lightViewMatrix, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    float yaw = (float) glm::degrees(((float) atan(direction.x / direction.z)));
    yaw = direction.z > 0 ? yaw - 180 : yaw;
    this->lightViewMatrix = glm::rotate(lightViewMatrix, glm::radians(yaw), glm::vec3(0, 1.0f, 0));
    this->lightViewMatrix = glm::translate(lightViewMatrix, cent);
    
    //use glm lookat
//    this->lightViewMatrix = glm::lookAt((center - direction) * 10000.0f, center, glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void ShadowMapRenderer::updateOrthoProjectionMatrix(float width, float height, float length) {
    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix[0][0] = 2.0f / width;
    projectionMatrix[1][1] = 2.0f / height;
    projectionMatrix[2][2] = -2.0f / length;
    projectionMatrix[3][3] = 1;
}

glm::mat4 ShadowMapRenderer::createOffset() {
    offset = glm::mat4();
    offset = glm::translate(offset, glm::vec3(0.5f, 0.5f, 0.5f));
    offset = glm::scale(offset, glm::vec3(0.5f, 0.5f, 0.5f));
    return offset;
}


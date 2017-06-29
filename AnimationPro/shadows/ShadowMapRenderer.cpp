//
//  ShadowMapRenderer.cpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ShadowMapRenderer.hpp"

ShadowMapRenderer::ShadowMapRenderer() {
    this->SHADOW_MAP_SIZE = 4096;
    
    this->projectionMatrix = glm::mat4(1.0f);
    this->projectionViewMatrix = glm::mat4(1.0f);
    this->lightViewMatrix = glm::mat4(1.0f);
    this->offset = createOffset();

}

ShadowMapRenderer::ShadowMapRenderer(Camera camera) : ShadowMapRenderer() {
    
    this->shader = ShadowShader("shadows/shadow.vs", "shadows/shadow.frag");
    this->skeletalShader = ShadowShader("shadows/skeletalShadow.vs", "shadows/skeletalShadow.frag");
    this->instanceShader = ShadowShader("shadows/instanceShadow.vs", "shadows/instanceShadow.frag");
    this->shadowBox = ShadowBox(this->lightViewMatrix, camera);
    this->shadowFBO = ShadowFrameBuffer(this->SHADOW_MAP_SIZE, this->SHADOW_MAP_SIZE);
}

void ShadowMapRenderer::render(ObjModel model) {
    
    this->shader.Use();
    this->shader.getAllUniformLocations();
    
    this->loadMvp(this->shader, model.modelMatrix);
    model.Draw(this->shader);
    
    this->shader.Stop();

}

void ShadowMapRenderer::render(SkeletalModel model) {
    this->skeletalShader.Use();
    this->skeletalShader.getAllUniformLocations();
    
    this->loadMvp(this->skeletalShader, model.modelMatrix);
    if (model.isAnimated) model.isAnimated = false;
    model.Draw(this->skeletalShader);
    
    this->skeletalShader.Stop();
}

void ShadowMapRenderer::renderInstance(ObjModel model, int count) {
    this->instanceShader.Use();
    this->instanceShader.getAllUniformLocations();
    
    this->instanceShader.loadProjectionViewMatrix(this->projectionViewMatrix);
    model.DrawInstance(this->instanceShader, count);
    
    this->instanceShader.Stop();
    
    
}

// get the matrix: map object's pos to shadow map coordinate 
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

void ShadowMapRenderer::prepare(DirectionalLight light, Camera camera) {
    this->shadowBox.update(camera);
    glm::vec3 lightDirection = -light.getDirection();
    this->updateOrthoProjectionMatrix(this->shadowBox.getWidth(), this->shadowBox.getHeight(), this->shadowBox.getLength());
    this->updateLightViewMatrix(lightDirection, this->shadowBox.getCenter());
    this->projectionViewMatrix = this->projectionMatrix * this->lightViewMatrix;

    this->shadowFBO.bindFrameBuffer();
////    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
}

void ShadowMapRenderer::loadMvp(ShadowShader shader, glm::mat4 modelMatrix) {
    glm::mat4 mvp = this->projectionViewMatrix * modelMatrix;
    shader.loadMVP(mvp);
}

void ShadowMapRenderer::finish() {
    this->shadowFBO.unbindFrameBuffer();
}

void ShadowMapRenderer::updateLightViewMatrix(glm::vec3 lightDirection, glm::vec3 center) {
    glm::vec3 direction = glm::normalize(lightDirection);
    glm::vec3 cent = -center;
    this->lightViewMatrix = glm::mat4(1.0f);
    
    float pitch = (float) acos(sqrt(direction.x * direction.x + direction.z * direction.z));
    this->lightViewMatrix = glm::rotate(lightViewMatrix, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    float yaw = (float) glm::degrees(((float) atan(direction.x / direction.z)));
    yaw = direction.z > 0 ? yaw - 180 : yaw;
    this->lightViewMatrix = glm::rotate(lightViewMatrix, glm::radians(yaw), glm::vec3(0, 1.0f, 0));
    this->lightViewMatrix = glm::translate(lightViewMatrix, cent);
    
    //use glm lookat
//    this->lightViewMatrix = glm::lookAt((direction) * 10000.0f, center, glm::vec3(0.0f, 1.0f, 0.0f));
    
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


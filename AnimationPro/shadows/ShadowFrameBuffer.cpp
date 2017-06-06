//
//  ShadowFrameBuffer.cpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ShadowFrameBuffer.hpp"


ShadowFrameBuffer::ShadowFrameBuffer() {
    this->HEIGHT = 1024;
    this->WIDTH = 1024;
    this->initialFrameBuffer();
}

ShadowFrameBuffer::ShadowFrameBuffer(int width, int height) {
    this->HEIGHT = height;
    this->WIDTH = width;
    
    this->initialFrameBuffer();
}

void ShadowFrameBuffer::bindFrameBuffer() {
    this->bindFrameBuffer(this->FBO, this->WIDTH, this->HEIGHT);
}

void ShadowFrameBuffer::unbindFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Utils::WIN_WIDTH, Utils::WIN_HEIGHT);
}

void ShadowFrameBuffer::bindFrameBuffer(GLuint fbo, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

GLuint ShadowFrameBuffer::getShadowMap() {
    return this->shadowMap;
}

void ShadowFrameBuffer::initialFrameBuffer() {
    this->FBO = this->createFrameBuffer();
    this->shadowMap = this->createDepthBufferAttachment();
    this->unbindFrameBuffer();
}

GLuint ShadowFrameBuffer::createFrameBuffer() {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    return fbo;
}

GLuint ShadowFrameBuffer::createDepthBufferAttachment() {
    GLuint depthMap;
    
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16,
                 this->WIDTH, this->HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    
    return depthMap;
}

void ShadowFrameBuffer::cleanUp() {
    glDeleteFramebuffers(1, &this->FBO);
    glDeleteTextures(1, &this->shadowMap);
    
}

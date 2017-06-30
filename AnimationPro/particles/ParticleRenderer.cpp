//
//  ParticleRenderer.cpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ParticleRenderer.hpp"


ParticleRenderer::ParticleRenderer(ParticleShader shader) {
    this->shader = shader;
    this->shader.Use();
    this->shader.setInt("sprite", 0);
    this->shader.Stop();
}

void ParticleRenderer::render(ParticleGenerator particles, glm::mat4 projectionMatrix, float dt) {
    
    this->shader.Use();
    this->shader.setMat4("projection", projectionMatrix);
    particles.Update(dt, glm::vec3(1460, 10.0f, 1390), 2);
    particles.Draw();
    
    this->shader.Stop();
}

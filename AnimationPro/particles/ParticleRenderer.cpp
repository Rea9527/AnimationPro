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

void ParticleRenderer::render(ParticleGenerator *particles, glm::mat4 projectionViewMatrix, glm::mat4 modelMatrix, float dt) {
    
    this->shader.Use();
    this->shader.setMat4("projectionView", projectionViewMatrix);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(modelMatrix, glm::vec3(1.05f, 1.05f, 1.05f));
    this->shader.setMat4("model", model);
    particles->Update(dt, 1);
    particles->Draw();
    
    this->shader.Stop();
}

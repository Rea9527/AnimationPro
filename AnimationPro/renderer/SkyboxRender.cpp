//
//  SkyboxRender.cpp
//  AnimationPro
//
//  Created by 陈主润 on 05/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "SkyboxRender.hpp"


SkyboxRender::SkyboxRender() { }

SkyboxRender::SkyboxRender(StaticShader shader) {
    this->Shader = shader;
    this->Shader.Use();
    this->Shader.getAllUniformLocations();
    this->Shader.Stop();
}

void SkyboxRender::render(Skybox skybox) {
    glStencilMask(0x00);
    
    this->Shader.Use();
    this->Shader.loadProjectionViewMatrix(skybox.projectionViewMatrix);

    
    glBindVertexArray(skybox.getModel().getVAO());
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(this->Shader.Program, "skybox"), 0);
    ModelTexture texture = skybox.getTexture();
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getId());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    this->Shader.Stop();
    
}



//
//  TileRenderer.cpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TileRenderer.hpp"


TileRenderer::TileRenderer(TileShader shader) {
    this->shader = shader;
    this->shader.Use();
    this->shader.getAllUniformLocations();
    this->shader.connectTexture();
    this->shader.Stop();
}

void TileRenderer::render(RectangleModel tile, glm::mat4 toShadowMapMatrix, GLuint shadowMap, Camera camera) {
    glStencilMask(0x00);
    
    this->shader.Use();
    
    this->shader.loadShadowMapMatrix(toShadowMapMatrix);
    this->shader.loadViewPos(camera.getPos().x, camera.getPos().y, camera.getPos().z);
    this->shader.loadProjectionViewMatrix(tile.projectionViewMatrix);
    this->shader.loadModelMat(tile.modelMatrix);
    
    this->bindTexture(tile, shadowMap);
    tile.draw();
    
    this->shader.Stop();
}



void TileRenderer::bindTexture(RectangleModel tile, GLuint shadowMap) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tile.getTexture().getId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    
    
}

void TileRenderer::addDirLight(DirectionalLight dirLight) {
    this->shader.Use();
    this->shader.addDirLight(dirLight);
    this->shader.Stop();
}

void TileRenderer::unbindTextureModel() {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

}

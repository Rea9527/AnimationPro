//
//  TerrainRender.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TerrainRender.hpp"


TerrainRender::TerrainRender(TerrainShader shader) {
    this->shader = shader;
    this->shader.Use();
    this->shader.getAllUniformLocations();
    this->shader.loadTextureLoc();
    this->shader.connectTexture();
    this->shader.Stop();
}

void TerrainRender::render(vector<Terrain> terrains, glm::mat4 projection, glm::mat4 view, Camera camera) {
    this->shader.Use();

    this->shader.loadViewPos(camera.getPos().x, camera.getPos().y, camera.getPos().z);
    this->shader.loadViewMat(glm::value_ptr(view));
    this->shader.loadProjectionMat(glm::value_ptr(projection));
    for (Terrain terrain : terrains) {
        loadModelMat(terrain);
        prepareTerrain(terrain);
        glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTextureModel();
    }
    
    this->shader.Stop();
}

void TerrainRender::prepareTerrain(Terrain terrain) {
    RawModel model = terrain.getModel();

    this->bindTexture(terrain);
    glBindVertexArray(model.getVAO());
}

void TerrainRender::bindTexture(Terrain terrain) {
    TerrainTexturePack texturePack = terrain.getTexturePack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePack.getBgTerrain().getTextureId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texturePack.getRTerrain().getTextureId());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texturePack.getGTerrain().getTextureId());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texturePack.getBTerrain().getTextureId());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain.getBlendMap().getTextureId());
    

}

void TerrainRender::addDirLight(DirectionalLight dirLight) {
    this->shader.Use();
    this->shader.addDirLight(dirLight);
    this->shader.Stop();
}

void TerrainRender::unbindTextureModel() {
    glBindVertexArray(0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TerrainRender::loadModelMat(Terrain terrain) {
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0, -0.3f, 0));
    shader.loadModelMat(glm::value_ptr(model));
}



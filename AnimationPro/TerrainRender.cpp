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

//    this->shader.Stop();
}

void TerrainRender::render(vector<Terrain> terrains, glm::mat4 projection, glm::mat4 view) {
    this->shader.Use();
    this->shader.getAllUniformLocations();
    this->shader.loadViewMat(glm::value_ptr(view));
    this->shader.loadProjectionMat(glm::value_ptr(projection));
    for (Terrain terrain : terrains) {
        loadModelMat(terrain);
        prepareTerrain(terrain);
        glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTextureModel();
    }
}

void TerrainRender::prepareTerrain(Terrain terrain) {
    RawModel model = terrain.getModel();
    
    ModelTexture texture = terrain.getTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glBindVertexArray(model.getVAO());
    
}

void TerrainRender::loadModelMat(Terrain terrain) {
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0, 0, 0));
    shader.loadModelMat(glm::value_ptr(model));
}

void TerrainRender::unbindTextureModel() {
    glBindVertexArray(0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


//
//  RectangleModel.cpp
//  AnimationPro
//
//  Created by 陈主润 on 02/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "RectangleModel.hpp"


RectangleModel::RectangleModel() { }

void RectangleModel::load(string path) {
    
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.0f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, 0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.0f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    this->model = this->loader.loadToVAO(vertices, sizeof(vertices), indices, sizeof(indices));
    
    this->texture = ModelTexture(this->loader.loadTexture(path));
}

void RectangleModel::draw() {
    glBindTexture(GL_TEXTURE_2D, this->texture.getId());
    
    glBindVertexArray(this->model.getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

RawModel RectangleModel::getModel() {
    return this->model;
}

ModelTexture RectangleModel::getTexture() {
    return this->texture;
}


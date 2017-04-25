//
//  Terrain.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Terrain.hpp"


Terrain::Terrain() {
    this->SIZE = 800;
    this->VERTEX_COUNT = 128;
}

Terrain::Terrain(int gridX, int gridZ, Loader loader, ModelTexture texture) {
    
    this->SIZE = 800;
    this->VERTEX_COUNT = 128;
    
    this->Texture = texture;
    this->x = gridX * SIZE;
    this->z = gridZ * SIZE;
    this->Model = generateTerrain(loader);
    
}


RawModel Terrain::generateTerrain(Loader loader) {
    
    GLfloat vertices[8*128*128];
    GLuint indices[6*127*127];
    
    int vertexPointer = 0;
    for (int i = 0;i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            int k = vertexPointer*8;
            vertices[k] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            vertices[k+1] = 0;
            vertices[k+2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
            vertices[k+3] = 0;
            vertices[k+4] = 1;
            vertices[k+5] = 0;
            vertices[k+6] = (float)j / ((float)VERTEX_COUNT - 1);
            vertices[k+7] = (float)i / ((float)VERTEX_COUNT - 1);
            vertexPointer++;
            
        }
    }
    
    
    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT-1; gz++){
        for (int gx = 0; gx < VERTEX_COUNT-1; gx++){
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    
//    std::cout << "from: " << vertices[15000] << " " << vertices[15001] << " " << vertices[15002] << " " << vertices[15003] <<std::endl;
    return loader.loadToVAO(vertices, sizeof(vertices), indices, sizeof(indices));
}

RawModel Terrain::getModel() {
    return this->Model;
}

ModelTexture Terrain::getTexture() {
    return this->Texture;
}

GLfloat Terrain::getX() {
    return this->x;
}

GLfloat Terrain::getZ() {
    return this->z;
}


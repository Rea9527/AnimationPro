//
//  Terrain.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Terrain.hpp"


Terrain::Terrain() {
    this->SIZE = 1600;
    this->MAX_HEIGHT = 100;
    this->MAX_PIXEL_COLOR = 256 * 256 * 256;
}

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, string heightMap) {
    
    this->SIZE = 1600;
    this->MAX_HEIGHT = 100;
    this->MAX_PIXEL_COLOR = 256 * 256 * 256;
    this->TexturePack = texturePack;
    this->BlendMap = blendMap;
    this->x = gridX * SIZE;
    this->z = gridZ * SIZE;
    this->Model = generateTerrain(loader, heightMap);
    
}


RawModel Terrain::generateTerrain(Loader loader, string heightMap) {
    std::cout << 1 << endl;
    int width, height, channel;
    unsigned char* image = SOIL_load_image(heightMap.c_str(), &width, &height, &channel, SOIL_LOAD_RGB);
    this->VERTEX_COUNT = height;
    unsigned char (*pixels)[300][3] = (unsigned char (*)[300][3]) image;
    
    GLfloat vertices[8*300*300];
    GLuint indices[6*299*299];
    
    
    int vertexPointer = 0;
    for (int i = 0;i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            int k = vertexPointer*8;
            vertices[k] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            vertices[k+1] = getHeight(j, i, pixels[i][j][0], pixels[i][j][1], pixels[i][j][2]);
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

    return loader.loadToVAO(vertices, sizeof(vertices), indices, sizeof(indices));
}

float Terrain::getHeight(int x, int z, unsigned char r, unsigned char g, unsigned char b) {
    if (x < 0 || x >= 256 || z >= 256 || z < 0) return 0;
    
    float height = (float)r * (float)g * (float)b;
    height /= this->MAX_PIXEL_COLOR;
    height *= this->MAX_HEIGHT;
    
    return height;
}

RawModel Terrain::getModel() {
    return this->Model;
}

TerrainTexture Terrain::getBlendMap() {
    return this->BlendMap;
}

TerrainTexturePack Terrain::getTexturePack() {
    return this->TexturePack;
}

GLfloat Terrain::getX() {
    return this->x;
}

GLfloat Terrain::getZ() {
    return this->z;
}


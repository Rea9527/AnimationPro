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
            vertices[k+1] = getHeight(i, j, pixels);
            vertices[k+2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
            
            glm::vec3 normal = calculateNormal(i, j, pixels);
            vertices[k+3] = normal.x;
            vertices[k+4] = normal.y;
            vertices[k+5] = normal.z;
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

float Terrain::getHeight(int x, int z, unsigned char (*pixels)[300][3]) {
    if (x < 0 || x >= 300 || z < 0 || z >= 300) return 0;
    float height = (float)pixels[x][z][0] * (float)pixels[x][z][1] * (float)pixels[x][z][2];
    height /= this->MAX_PIXEL_COLOR;
    height *= this->MAX_HEIGHT;
    
    return height;
}

glm::vec3 Terrain::calculateNormal(int x, int z, unsigned char (*pixels)[300][3]) {
    float heightL = getHeight(x-1, z, pixels);
    float heightR = getHeight(x+1, z, pixels);
    float heightU = getHeight(x, z-1, pixels);
    float heightD = getHeight(x, z+1, pixels);
    
    glm::vec3 normal = glm::vec3(heightL-heightR, 2.0f, heightD-heightU);
    normal = glm::normalize(normal);
    return normal;
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


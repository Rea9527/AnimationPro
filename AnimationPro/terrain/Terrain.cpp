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
    this->VERTEX_COUNT = 256;
    this->MAX_HEIGHT = 60;
    this->MAX_PIXEL_COLOR = 256 * 256 * 256;
}

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, string heightMap) {
    
    this->SIZE = 1600;
    this->VERTEX_COUNT = 256;
    this->MAX_HEIGHT = 100;
    this->MAX_PIXEL_COLOR = 256 * 256 * 256;
    this->TexturePack = texturePack;
    this->BlendMap = blendMap;
    this->x = gridX * SIZE;
    this->z = gridZ * SIZE;
    this->Model = generateTerrain(loader, heightMap);
    
}


RawModel Terrain::generateTerrain(Loader loader, string heightMap) {
    int width, height, channel;
    unsigned char* image = SOIL_load_image(heightMap.c_str(), &width, &height, &channel, SOIL_LOAD_RGB);
    this->VERTEX_COUNT = height;
    unsigned char (*pixels)[256][3] = (unsigned char (*)[256][3]) image;
    
    GLfloat vertices[8*this->VERTEX_COUNT*this->VERTEX_COUNT];
    GLuint indices[6*(this->VERTEX_COUNT-1)*(this->VERTEX_COUNT-1)];
    
    
    int vertexPointer = 0;
    for (int i = 0;i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            int k = vertexPointer*8;
            //position
            vertices[k] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            GLfloat height = getHeight(i, j, pixels);
            this->heights[i][j] = height;
            vertices[k+1] = height;
            vertices[k+2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
            //normal
            glm::vec3 normal = calculateNormal(i, j, pixels);
            vertices[k+3] = normal.x;
            vertices[k+4] = normal.y;
            vertices[k+5] = normal.z;
            //texture
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

    return loader.loadToVAO(vertices, (GLsizei)sizeof(vertices), indices, (GLsizei)sizeof(indices));
}

GLfloat Terrain::getHeightOfTerrain(GLfloat worldX, GLfloat worldZ) {
    
    GLfloat terrainX = worldX;
    GLfloat terrainZ = worldZ;
    GLfloat gridSquareSize = this->SIZE / ((GLfloat)this->VERTEX_COUNT-1);
    
    int gridX = terrainX / gridSquareSize;
    int gridZ = terrainZ / gridSquareSize;
    if (gridX < 0 || gridX >= this->VERTEX_COUNT || gridZ < 0 || gridZ >= this->VERTEX_COUNT) {
        return 0;
    }
    
    GLfloat coordX = fmod(terrainX, gridSquareSize) / gridSquareSize;
    GLfloat coordZ = fmod(terrainZ, gridSquareSize) / gridSquareSize;
    
    GLfloat result;
    if (coordX < (1 - coordZ)) {
        result = this->barryCentric(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1, heights[gridX+1][gridZ], 0), glm::vec3(0, heights[gridX][gridZ+1], 1), glm::vec2(coordX, coordZ));
    } else {
        result = this->barryCentric(glm::vec3(1, heights[gridX+1][gridZ], 0), glm::vec3(1, heights[gridX+1][gridZ+1], 1), glm::vec3(0, heights[gridX][gridZ+1], 1), glm::vec2(coordX, coordZ));
    }
    
    return result;
}

GLfloat Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
    GLfloat det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    GLfloat l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    GLfloat l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    GLfloat l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}


float Terrain::getHeight(int x, int z, unsigned char (*pixels)[256][3]) {
    if (x < 0 || x >= 256 || z < 0 || z >= 256) return 0;
    float r = (float)pixels[x][z][0];
    float g = (float)pixels[x][z][1];
    float b = (float)pixels[x][z][2];
    float height = ((r * 256 + g) * 256 + b);
    height /= this->MAX_PIXEL_COLOR;
    height *= this->MAX_HEIGHT;
    
    return height;
}

glm::vec3 Terrain::calculateNormal(int x, int z, unsigned char (*pixels)[256][3]) {
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


//
//  Terrain.hpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include <cstdio>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL/SOIL.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../texture/TerrainTexture.hpp"
#include "../texture/TerrainTexturePack.hpp"
#include "../models/RawModel.hpp"
#include "../loader/Loader.hpp"



class Terrain {
  
public:
    
    Terrain();
    Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, string heightMap);
    
    RawModel generateTerrain(Loader loader, string heightMap);
    
    GLfloat getHeightOfTerrain(GLfloat worldX, GLfloat worldZ);
    
    RawModel getModel();
    TerrainTexture getBlendMap();
    TerrainTexturePack getTexturePack();
    
    GLfloat getX();
    GLfloat getZ();
    
private:
    
    float getHeight(int x, int z, unsigned char (*pixels)[256][3]);
    glm::vec3 calculateNormal(int x, int z, unsigned char (*pixels)[256][3]);
    
    GLfloat barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 p);
    
    GLfloat x;
    GLfloat z;
    GLfloat heights[256][256];
    
    RawModel Model;
    TerrainTexture BlendMap;
    TerrainTexturePack TexturePack;
    
    int SIZE;
    int VERTEX_COUNT;
    int MAX_HEIGHT;
    int MAX_PIXEL_COLOR;
    
};

#endif /* Terrain_hpp */

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

#include "TerrainTexture.hpp"
#include "TerrainTexturePack.hpp"
#include "RawModel.hpp"
#include "Loader.hpp"



class Terrain {
  
public:
    
    Terrain();
    Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap);
    
    RawModel generateTerrain(Loader loader);
    
    RawModel getModel();
    TerrainTexture getBlendMap();
    TerrainTexturePack getTexturePack();
    
    GLfloat getX();
    GLfloat getZ();
    
private:
    GLfloat x;
    GLfloat z;
    
    RawModel Model;
    TerrainTexture BlendMap;
    TerrainTexturePack TexturePack;
    
    int SIZE;
    int VERTEX_COUNT;
};

#endif /* Terrain_hpp */

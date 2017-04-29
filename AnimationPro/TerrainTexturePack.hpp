//
//  TerrainTexturePack.hpp
//  AnimationPro
//
//  Created by 陈主润 on 28/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TerrainTexturePack_hpp
#define TerrainTexturePack_hpp

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "TerrainTexture.hpp"


class TerrainTexturePack {
    
public:
    TerrainTexturePack();
    TerrainTexturePack(TerrainTexture bgTerrain, TerrainTexture rTerrain, TerrainTexture gTerrain, TerrainTexture bTerrain);
    
    TerrainTexture getBgTerrain();
    TerrainTexture getRTerrain();
    TerrainTexture getGTerrain();
    TerrainTexture getBTerrain();
    
private:
    TerrainTexture BgTerrain;
    TerrainTexture RTerrain;
    TerrainTexture GTerrain;
    TerrainTexture BTerrain;
    
};

#endif /* TerrainTexturePack_hpp */

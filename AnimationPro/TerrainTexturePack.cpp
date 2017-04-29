//
//  TerrainTexturePack.cpp
//  AnimationPro
//
//  Created by 陈主润 on 28/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TerrainTexturePack.hpp"



TerrainTexturePack::TerrainTexturePack() {}

TerrainTexturePack::TerrainTexturePack(TerrainTexture bgTerrain, TerrainTexture rTerrain, TerrainTexture gTerrain, TerrainTexture bTerrain) {
    this->BgTerrain = bgTerrain;
    this->RTerrain = rTerrain;
    this->GTerrain = gTerrain;
    this->BTerrain = bTerrain;
}

TerrainTexture  TerrainTexturePack::getBgTerrain() {
    return this->BgTerrain;
}

TerrainTexture TerrainTexturePack::getRTerrain() {
    return this->RTerrain;
}

TerrainTexture TerrainTexturePack::getGTerrain() {
    return this->GTerrain;
}

TerrainTexture TerrainTexturePack::getBTerrain() {
    return this->BTerrain;
}

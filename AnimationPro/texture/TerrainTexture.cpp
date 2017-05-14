//
//  TerrainTexture.cpp
//  AnimationPro
//
//  Created by 陈主润 on 28/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TerrainTexture.hpp"



TerrainTexture::TerrainTexture() {}

TerrainTexture::TerrainTexture(GLuint textureId) {
    this->TextureId = textureId;
}

GLuint TerrainTexture::getTextureId() {
    return this->TextureId;
}

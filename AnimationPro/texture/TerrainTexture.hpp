//
//  TerrainTexture.hpp
//  AnimationPro
//
//  Created by 陈主润 on 28/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TerrainTexture_hpp
#define TerrainTexture_hpp

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>


class TerrainTexture {
    
public:
    TerrainTexture();
    TerrainTexture(GLuint textureId);
    
    GLuint getTextureId();
    
private:
    GLuint TextureId;
};

#endif /* TerrainTexture_hpp */

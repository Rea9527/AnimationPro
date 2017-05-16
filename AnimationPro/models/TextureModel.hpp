//
//  TextureModel.hpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TextureModel_hpp
#define TextureModel_hpp

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>

#include "ModelTexture.hpp"
#include "RawModel.hpp"

class TextureModel {
    
public:
    TextureModel();
    TextureModel(RawModel raw, ModelTexture texture);
    RawModel getRawModel();
    ModelTexture getModelTexture();
    
private:
    RawModel rawModel;
    ModelTexture modelTexture;
};

#endif /* TextureModel_hpp */

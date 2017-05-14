//
//  TextureModel.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "TextureModel.hpp"


TextureModel::TextureModel(RawModel raw, ModelTexture texture) {
    this->rawModel = raw;
    this->modelTexture = texture;
}

RawModel TextureModel::getRawModel() {
    return this->rawModel;
}

ModelTexture TextureModel::getModelTexture() {
    return this->modelTexture;
}

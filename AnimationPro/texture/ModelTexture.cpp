//
//  ModelTexture.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ModelTexture.hpp"


ModelTexture::ModelTexture() { }

ModelTexture::ModelTexture(GLuint textureId) {
    this->TextureId = textureId;
}

void ModelTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->TextureId);
}

GLuint ModelTexture::getId() {
    return this->TextureId;
}

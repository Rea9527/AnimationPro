//
//  RawModel.cpp
//  CGHws
//
//  Created by 陈主润 on 20/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "RawModel.hpp"


RawModel::RawModel() { }

RawModel::RawModel(GLuint vaoid, GLsizei count) {
    this->vaoID = vaoid;
    this->vertexCount = count;
}

GLuint RawModel::getVAO() {
    return this->vaoID;
}

GLsizei RawModel::getVertexCount() {
    return this->vertexCount;
}

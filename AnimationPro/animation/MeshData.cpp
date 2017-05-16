//
//  MeshData.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "MeshData.hpp"


MeshData::MeshData(float vertices[], float textureCoords[], float normals[], int indices[],
                   int jointIds[], float vertexWeights[], int verticesCount) {
    this->vertices = vertices;
    this->textureCoords = textureCoords;
    this->normals = normals;
    this->indices = indices;
    this->jointIds = jointIds;
    this->vertexWeights = vertexWeights;
    
    this->verticesCount = verticesCount;
}

int* MeshData::getJointIds() {
    return this->jointIds;
}

float* MeshData::getVertexWeights() {
    return this->vertexWeights;
}

float* MeshData::getVertices() {
    return this->vertices;
}

float* MeshData::getTextureCoords() {
    return this->textureCoords;
}

float* MeshData::getNormals() {
    return this->normals;
}

int* MeshData::getIndices() {
    return this->indices;
}

int MeshData::getVertexCount() {
    return this->verticesCount;
}


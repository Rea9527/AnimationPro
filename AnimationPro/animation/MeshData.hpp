//
//  MeshData.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef MeshData_hpp
#define MeshData_hpp

#include <iostream>


class MeshData {
    
public:
    MeshData(float vertices[], float textureCoords[], float normals[], int indices[],
             int jointIds[], float vertexWeights[], int verticesCount);
    
    int* getJointIds();
    
    float* getVertexWeights();
    
    float* getVertices();
    
    float* getTextureCoords();
    
    float* getNormals();
    
    int* getIndices();
    
    int getVertexCount();
    
private:
    float *vertices;
    float *textureCoords;
    float *normals;
    int *indices;
    int *jointIds;
    float *vertexWeights;
    
    int verticesCount;
};

#endif /* MeshData_hpp */

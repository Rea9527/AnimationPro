//
//  TextMeshData.hpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TextMeshData_hpp
#define TextMeshData_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class TextMeshData {
    
public:
    TextMeshData();
    TextMeshData(vector<float> positions, vector<float> texCoords);
    
    vector<float> getVertexPositions();
    
    vector<float> getTextureCoords();
    
    int getVertexCount();
    
private:
    
    vector<float> positions;
    vector<float> texCoords;
};

#endif /* TextMeshData_hpp */

//
//  FontType.hpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef FontType_hpp
#define FontType_hpp

#include <iostream>
#include <string>
#include "TextMeshCreator.hpp"

using namespace std;

class FontType {
public:
    FontType();
    FontType(int textureAtlas, string filePath);
    
    int getTextureAtlas();
};

#endif /* FontType_hpp */

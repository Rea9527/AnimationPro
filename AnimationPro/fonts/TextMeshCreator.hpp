//
//  TextMeshCreator.hpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TextMeshCreator_hpp
#define TextMeshCreator_hpp

#include <iostream>
#include "TextMeshData.hpp"



class TextMeshCreator {
public:
    TextMeshCreator();
    TextMeshCreator(string filePath);
    
private:
    TextMeshData textMeshData;
    
};

#endif /* TextMeshCreator_hpp */

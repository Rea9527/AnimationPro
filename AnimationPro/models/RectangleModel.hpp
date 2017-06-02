//
//  RectangleModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 02/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef RectangleModel_hpp
#define RectangleModel_hpp

#include <iostream>

#include "TextureModel.hpp"
#include "../loader/Loader.hpp"

class RectangleModel {
    
public:
    RectangleModel();
    
    void load(string path);
    void draw();
    
    RawModel getModel();
    ModelTexture getTexture();
    
private:
    RawModel model;
    ModelTexture texture;
    Loader loader;
    
};

#endif /* RectangleModel_hpp */

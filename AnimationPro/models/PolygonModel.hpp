//
//  PolygonModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 25/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef PolygonModel_hpp
#define PolygonModel_hpp

#include <iostream>

#include "RawModel.hpp"
#include "../loader/Loader.hpp"

class PolygonModel {
    
public:
    PolygonModel();
    
    void load();
    void draw();
    
    RawModel getModel();
    
private:
    RawModel rawModel;
    Loader loader;
    
};

#endif /* PolygonModel_hpp */

//
//  StaticShader.hpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef StaticShader_hpp
#define StaticShader_hpp

#include <iostream>

#include "Shader.hpp"

class StaticShader : public Shader {
    
public:
    
    StaticShader();
    StaticShader(string vertexPath, string fragmentPath);

    
};

#endif /* StaticShader_hpp */
//
//  StaticShader.cpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "StaticShader.hpp"



StaticShader::StaticShader() { }

StaticShader::StaticShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) { }

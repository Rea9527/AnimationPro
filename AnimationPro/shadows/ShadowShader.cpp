//
//  ShadowShader.cpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ShadowShader.hpp"


ShadowShader::ShadowShader() : Shader() { }

ShadowShader::ShadowShader(string vertexPath, string fragmentPath) : Shader(vertexPath, fragmentPath) { }

void ShadowShader::getAllUniformLocations() {
    this->mvp_loc = this->getUniformLocation("MVP");
}

void ShadowShader::loadMVP(glm::mat4 mvp) {
    glUniformMatrix4fv(this->mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
}


//
//  ShadowShader.hpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ShadowShader_hpp
#define ShadowShader_hpp

#include "../shaders/Shader.hpp"


class ShadowShader : public Shader {
    
public:
    ShadowShader();
    ShadowShader(string vertexPath, string fragmentPath);
    
    void getAllUniformLocations();
    
    void loadMVP(glm::mat4 mvp);
    
private:
    
    GLuint mvp_loc;
};

#endif /* ShadowShader_hpp */

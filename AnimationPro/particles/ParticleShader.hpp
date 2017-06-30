//
//  ParticleShader.hpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ParticleShader_hpp
#define ParticleShader_hpp

#include "../shaders/Shader.hpp"


class ParticleShader : public Shader {
    
public:
    ParticleShader();
    ParticleShader(string vertexPath, string fragmentPath);
    
    void getAllUniformLocations();
    
    void loadModelMat(glm::mat4 model);
    void loadProjectionViewMatrix(glm::mat4 projectionViewMat);
    void loadMVP(glm::mat4 mvp);
    
private:
    
    GLuint modelLoc;
    GLuint projectionViewLoc;
    GLuint mvp_loc;
};

#endif /* ParticleShader_hpp */

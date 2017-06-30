//
//  ParticleRenderer.hpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ParticleRenderer_hpp
#define ParticleRenderer_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include "ParticleGenerator.hpp"


class ParticleRenderer {
    
public:
    ParticleRenderer() { }
    ParticleRenderer(ParticleShader shader);
    
    void render(ParticleGenerator particles, glm::mat4 projectionMatrix, float dt);
    
private:
    ParticleShader shader;
};

#endif /* ParticleRenderer_hpp */

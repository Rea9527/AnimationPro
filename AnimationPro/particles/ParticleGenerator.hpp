//
//  ParticleGenerator.hpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ParticleGenerator_hpp
#define ParticleGenerator_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ParticleShader.hpp"
#include "../texture/ModelTexture.hpp"
#include "../loader/Loader.hpp"


// Represents a single particle and its state
struct Particle {
    glm::vec3 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;
    
    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
class ParticleGenerator
{
public:
    // Constructor
    ParticleGenerator(ParticleShader shader, ModelTexture texture, GLuint amount);
    // Update all particles
    void Update(GLfloat dt, GLuint newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
    // Render all particles
    void Draw();
private:
    //loader
    Loader loader;
    // State
    std::vector<Particle> particles;
    GLuint amount;
    // Render state
    ParticleShader shader;
    ModelTexture texture;
    RawModel model;
    // Initializes buffer and vertex attributes
    void init();
    // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    GLuint firstUnusedParticle();
    // Respawns particle
    void respawnParticle(Particle &particle, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
};

#endif /* ParticleGenerator_hpp */

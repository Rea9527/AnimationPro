//
//  ParticleGenerator.cpp
//  AnimationPro
//
//  Created by 陈主润 on 29/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ParticleGenerator.hpp"


ParticleGenerator::ParticleGenerator(ParticleShader shader, ModelTexture texture, GLuint amount)
: shader(shader), texture(texture), amount(amount)
{
    this->init();
}

void ParticleGenerator::Update(GLfloat dt, GLuint newParticles, glm::vec3 offset) {
    // Add new particles
    for (GLuint i = 0; i < newParticles; ++i) {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], offset);
    }
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i) {
        Particle &p = this->particles[i];
        p.Life -= dt; // reduce life
//        cout <<  i << " " << p.Life << endl;
        if (p.Life > 0.0f) {	// particle is alive, thus update
            p.Position += p.Velocity * dt;
        }
    }
    cout << this->particles[0].Life << endl;
}

// Render all particles
void ParticleGenerator::Draw()
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    for (Particle particle : this->particles) {
        if (particle.Life > 0.0f) {
            this->shader.setVec3("offset", particle.Position);
            this->shader.setVec4("color", particle.Color);
            this->texture.bind();
            glBindVertexArray(this->model.getVAO());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
    // Set up mesh and attribute properties
    float particle_quad[] = {
        // positions          // texture coords
        0.5f,  0.0f, 0.5f,   1.0f, 1.0f,   // top right
        0.5f, 0.0f, -0.5f,   1.0f, 0.0f,   // bottom right
        -0.5f, 0.0f, -0.5f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.0f, 0.5f,  0.0f, 1.0f    // top left
    };
    
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    this->model = this->loader.loadPosAndTex(particle_quad, sizeof(particle_quad), indices, sizeof(indices));
    
    
    // Create this->amount default particle instances
    for (GLuint i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle() {
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, glm::vec3 offset) {
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    offset.x = random;
    offset.z = random;
    offset.y = 10.0f;
    particle.Position = offset;
    particle.Color = glm::vec4(1.0, 1.0, 1.0, 1.0f);
    particle.Life = 0.6f;
    GLfloat vel = ((rand() % 200) - 200) / 10.0f - 10.0f;
    particle.Velocity = glm::vec3(0.0f, vel, 0.0f);
}

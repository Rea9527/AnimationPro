//
//  TerrainShader.hpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TerrainShader_hpp
#define TerrainShader_hpp

#include <iostream>

#include "Shader.hpp"
#include "../terrain/Terrain.hpp"


class TerrainShader : public Shader {
    
public:
    TerrainShader();
    TerrainShader(string vertexPath, string fragmentPath);
    
    void addDirLight(DirectionalLight light);
    void loadViewPos(GLfloat x, GLfloat y, GLfloat z);
    
    void loadTextureLoc();
    void connectTexture();
    void loadShadowMapMatrix(glm::mat4 shadowMapMatrix);
    
    void getAllUniformLocations();
    
    void loadModelMat(glm::mat4 model);
    void loadProjectionViewMatrix(glm::mat4 projectionViewMat);
    
private:
    //lights
    GLint matShineLoc;
    GLint viewPosLoc;
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;
    
    GLuint bgTextureLoc;
    GLuint rTextureLoc;
    GLuint gTextureLoc;
    GLuint bTextureLoc;
    GLuint blendMapLoc;
    GLuint shadowMapMatrixLoc;
    GLuint shadowMapLoc;
    
    GLuint modelLoc;
    GLuint projectionViewLoc;
};

#endif /* TerrainShader_hpp */

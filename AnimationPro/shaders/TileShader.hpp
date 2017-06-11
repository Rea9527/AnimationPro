//
//  TileShader.hpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TileShader_hpp
#define TileShader_hpp

#include "Shader.hpp"

class TileShader : public Shader {
    
public:
    TileShader();
    TileShader(string vertexPath, string fragmentPath);
    
    void addDirLight(DirectionalLight light);
    void loadViewPos(GLfloat x, GLfloat y, GLfloat z);
    
    void loadTextureLoc();
    void connectTexture();
    void loadShadowMapMatrix(glm::mat4 shadowMapMatrix);
    
    void getAllUniformLocations();
    
    void loadModelMat(glm::mat4 model);
    void loadModelViewMatrix(glm::mat4 modelViewMat);
    void loadProjectionViewMatrix(glm::mat4 projectionViewMat);
    
private:
    //lights
    GLint matShineLoc;
    GLint viewPosLoc;
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;
    
    GLuint textureLoc;
    GLuint shadowMapMatrixLoc;
    GLuint shadowMapLoc;
    
    GLuint modelLoc;
    GLuint modelViewLoc;
    GLuint projectionViewLoc;
};

#endif /* TileShader_hpp */

//
//  StaticShader.hpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ModelShader_hpp
#define ModelShader_hpp

#include <iostream>

#include "Shader.hpp"

class ModelShader : public Shader {
    
public:
    ModelShader();
    ModelShader(string vertexPath, string fragmentPath);

    
    void addPointLight(PointLight light);
    void addDirectionalLight(DirectionalLight light);
    void loadViewPos(GLfloat x, GLfloat y, GLfloat z);
    
    void getAllUniformLocations();
    
    void loadModelMat(glm::mat4 model);
    void loadProjectionViewMatrix(glm::mat4 projectionViewMat);
    
private:

    //lights
    GLint matShineLoc;
    GLint viewPosLoc;
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;
    
    GLint modelLoc;
    GLint projectionViewLoc;
};

#endif /* ModelShader_hpp */

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
#include "Terrain.hpp"


class TerrainShader : public Shader {
    
public:
    TerrainShader();
    TerrainShader(const GLchar* vertexPath, const GLchar* fragmentPath);
    
private:
    //lights
    GLint matShineLoc;
    GLint viewPosLoc;
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;
};

#endif /* TerrainShader_hpp */

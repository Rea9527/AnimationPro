//
//  TerrainRender.hpp
//  glfwTest
//
//  Created by 陈主润 on 24/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TerrainRender_hpp
#define TerrainRender_hpp

#include <iostream>
#include <vector>
#include "../shaders/TerrainShader.hpp"
#include "../terrain/Terrain.hpp"
#include "../camera/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class TerrainRender {
    
public:
    TerrainRender(TerrainShader shader);
    
    void render(vector<Terrain> terrains, glm::mat4 projectionView, glm::mat4 toShadowMapMatrix, GLuint shadowMap, Camera camera);
    
    void addDirLight(DirectionalLight dirLight);
    
private:
    TerrainShader shader;
    
    void prepareTerrain(Terrain terrain, GLuint shadowMap);
    void loadModelMat(Terrain terrain, glm::mat4 viewMat);
    void bindTexture(Terrain terrain, GLuint shadowMap);
    void unbindTextureModel();
};

#endif /* TerrainRender_hpp */

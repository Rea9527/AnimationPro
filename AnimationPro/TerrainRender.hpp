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
#include "TerrainShader.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class TerrainRender {
    
public:
    TerrainRender(TerrainShader shader);
    
    void render(vector<Terrain> terrains, glm::mat4 projection, glm::mat4 view, Camera camera);
    
    void addDirLight(DirectionalLight dirLight);
    
private:
    TerrainShader shader;
    
    void prepareTerrain(Terrain terrain);
    void loadModelMat(Terrain terrain);
    void bindTexture(Terrain terrain);
    void unbindTextureModel();
};

#endif /* TerrainRender_hpp */

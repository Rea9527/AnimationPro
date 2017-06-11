//
//  TileRenderer.hpp
//  AnimationPro
//
//  Created by 陈主润 on 12/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef TileRenderer_hpp
#define TileRenderer_hpp

#include <iostream>
#include <vector>
#include "../shaders/TileShader.hpp"
#include "../models/RectangleModel.hpp"
#include "../camera/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class TileRenderer {
    
public:
    TileRenderer(TileShader shader);
    
    void render(RectangleModel model, glm::mat4 toShadowMapMatrix, GLuint shadowMap, Camera camera);
    
    void addDirLight(DirectionalLight dirLight);
    
private:
    TileShader shader;
    
    void unbindTextureModel();
    void bindTexture(RectangleModel tile, GLuint shadowMap);
};

#endif /* TileRenderer_hpp */

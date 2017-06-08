//
//  cubeRender.hpp
//  AnimationPro
//
//  Created by 陈主润 on 25/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef cubeRender_hpp
#define cubeRender_hpp

#include <iostream>

#include "../camera/Camera.hpp"
#include "../shaders/StaticShader.hpp"
#include "../models/PolygonModel.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeRender {
    
public:
    CubeRender(StaticShader shader);
    void render(PolygonModel cube);

    void unbind();
    
private:
    StaticShader Shader;
    
    
};

#endif /* cubeRender_hpp */

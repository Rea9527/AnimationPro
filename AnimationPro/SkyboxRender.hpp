//
//  SkyboxRender.hpp
//  AnimationPro
//
//  Created by 陈主润 on 05/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef SkyboxRender_hpp
#define SkyboxRender_hpp

#include <iostream>

#include "StaticShader.hpp"
#include "Skybox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class SkyboxRender {
    
public:
    SkyboxRender();
    SkyboxRender(StaticShader shader);
    
    void render(Skybox skybox, glm::mat4 view, glm::mat4 projection);
    
    
private:
    
    vector<const char*> Faces;
    StaticShader Shader;
};

#endif /* SkyboxRender_hpp */

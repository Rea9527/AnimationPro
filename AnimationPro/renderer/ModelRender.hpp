//
//  ModelRender.hpp
//  AnimationPro
//
//  Created by 陈主润 on 25/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ModelRender_hpp
#define ModelRender_hpp

#include <iostream>

#include "../camera/Camera.hpp"
#include "../models/ObjModel.hpp"
#include "../shaders/ModelShader.hpp"

#include "../lights/DirectionalLight.hpp"
#include "../lights/PointLight.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ModelRender {
    
public:
    ModelRender(ModelShader shader);
    
    void render(ObjModel objModel, Camera camera);
    void renderMultiple(ObjModel objModel, Camera camera);
    
    void addLight(PointLight pointLight, DirectionalLight directionalLight);
    
    void prepare();
    void unbind();

private:
    ModelShader Shader;
};

#endif /* ModelRender_hpp */

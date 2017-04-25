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

#include "Camera.hpp"
#include "ObjModel.hpp"
#include "ModelShader.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ModelRender {
    
public:
    ModelRender(ModelShader shader, ObjModel objModel);
    
    void render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Camera camera);
    
    void addLight(PointLight pointLight, DirectionalLight directionalLight);
    
    void prepare();
    void unbind();

private:
    ModelShader Shader;
    ObjModel Model;
};

#endif /* ModelRender_hpp */

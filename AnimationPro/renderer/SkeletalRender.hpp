//
//  SkeletalRender.hpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef SkeletalRender_hpp
#define SkeletalRender_hpp

#include <iostream>

#include "../camera/Camera.hpp"
#include "../models/skeletalModel/SkeletalModel.hpp"
#include "../shaders/ModelShader.hpp"

#include "../lights/DirectionalLight.hpp"
#include "../lights/PointLight.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SkeletalRender {
    
public:
    SkeletalRender(ModelShader shader);
    void render(SkeletalModel &skeletalModel, Camera camera);
    
    void addLight(PointLight pointLight, DirectionalLight directionalLight);
    
    void unbind();
    
private:
    ModelShader Shader;

    
};

#endif /* SkeletalRender_hpp */

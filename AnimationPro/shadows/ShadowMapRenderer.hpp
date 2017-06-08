//
//  ShadowMapRenderer.hpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ShadowMapRenderer_hpp
#define ShadowMapRenderer_hpp

#include <iostream>

#include "../utils/Utils.hpp"
#include "../camera/Camera.hpp"
#include "../lights/DirectionalLight.hpp"

#include "./ShadowShader.hpp"
#include "./ShadowBox.hpp"
#include "./ShadowFrameBuffer.hpp"

#include "../models/skeletalModel/SkeletalModel.hpp"
#include "../models/ObjModel.hpp"
#include "../models/PolygonModel.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShadowMapRenderer {
    
public:
    ShadowMapRenderer();
    ShadowMapRenderer(Camera camera);
    
    void render(ObjModel model);
    void render(SkeletalModel model);
    void render(PolygonModel model);
    
    glm::mat4 getToShadowMapMatrix();
    
    GLuint getShadowMap();
    
    glm::mat4 getLightSpaceTransform();
    
    void prepare(DirectionalLight light, Camera camera);
    void finish();
    void cleanUp();
    
private:
    
    void updateLightViewMatrix(glm::vec3 direction, glm::vec3 center);
    void updateOrthoProjectionMatrix(float width, float height, float length);
    
    glm::mat4 createOffset();
    
    
    void loadMvp(glm::mat4 modelMatrix);
    
    
    ShadowShader shader;
    ShadowFrameBuffer shadowFBO;
    ShadowBox shadowBox;
    
    glm::mat4 projectionMatrix;
    glm::mat4 lightViewMatrix;
    glm::mat4 projectionViewMatrix;
    glm::mat4 offset;
    
    int SHADOW_MAP_SIZE;
    
};

#endif /* ShadowMapRenderer_hpp */

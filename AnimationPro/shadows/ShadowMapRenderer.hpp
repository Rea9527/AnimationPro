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

#include "../camera/Camera.hpp"
#include "./ShadowShader.hpp"
#include "./ShadowBox.hpp"
#include "./ShadowFrameBuffer.hpp"

#include "../lights/DirectionalLight.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShadowMapRenderer {
    
public:
    ShadowMapRenderer();
    ShadowMapRenderer(Camera camera);
    
    void render(DirectionalLight light);
    
    glm::mat4 getToShadowMapMatrix();
    
    GLuint getShadowMap();
    
    glm::mat4 getLightSpaceTransform();
    
    void updateLightViewMatrix(glm::vec3 direction, glm::vec3 center);
    void updateOrthoProjectionMatrix(float width, float height, float length);
    
    glm::mat4 createOffset();
    
    void prepare();
    void unbind();
    
    void cleanUp();
    
private:
    
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

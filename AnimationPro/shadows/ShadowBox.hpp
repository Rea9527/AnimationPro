//
//  ShadowBox.hpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ShadowBox_hpp
#define ShadowBox_hpp

#include <iostream>
#include <string>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include "../camera/Camera.hpp"
#include "../utils/Utils.hpp"

using namespace std;

class ShadowBox {
    
public:
    ShadowBox();
    ShadowBox(glm::mat4 lightViewMat, Camera camera);
    
    void update(Camera cam);
    
    glm::vec3 getCenter();
    float getWidth();
    float getHeight();
    float getLength();
    
private:
    vector<glm::vec4> calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector,
                                       glm::vec3 centerNear, glm::vec3 centerFar);
    
    glm::vec4 calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction,
                                               float width);
    
    glm::mat4 calculateCameraRotationMatrix();
    
    void calculateWidthsAndHeights();
    
    float getAspectRatio();
    
    float OFFSET;
    glm::vec4 UP;
    glm::vec4 FORWARD;
    float SHADOW_DISTANCE;
    
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
    glm::mat4 lightViewMatrix;
    Camera cam;
    
    float farHeight, farWidth, nearHeight, nearWidth;
};


#endif /* ShadowBox_hpp */

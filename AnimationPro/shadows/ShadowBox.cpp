//
//  ShadowBox.cpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ShadowBox.hpp"


ShadowBox::ShadowBox() {
    this->OFFSET = 15;
    this->UP = glm::vec4(0, 1.0f, 0, 0);
    this->FORWARD = glm::vec4(0, 0, -1.0f, 0);
    this->SHADOW_DISTANCE = 450;
}

ShadowBox::ShadowBox(glm::mat4 lightViewMat, Camera camera) : ShadowBox() {
    this->lightViewMatrix = lightViewMat;
    this->cam = camera;
    this->calculateWidthsAndHeights();

}

void ShadowBox::update(Camera cam) {
//    this->cam = cam;
    glm::mat4 rotation = calculateCameraRotationMatrix();
    glm::vec3 forwardVector = glm::vec3(rotation * this->FORWARD);
    
    glm::vec3 toFar = glm::vec3(forwardVector) * SHADOW_DISTANCE;
    glm::vec3 toNear = glm::vec3(forwardVector) * Utils::NEAR_PLANE;
    glm::vec3 centerNear = toNear + this->cam.getPos();
    glm::vec3 centerFar = toFar + this->cam.getPos();
    
    vector<glm::vec4> points = calculateFrustumVertices(rotation, forwardVector, centerNear,
                                                 centerFar);
    
    bool first = true;
    for (glm::vec4 point : points) {
        if (first) {
            minX = point.x;
            maxX = point.x;
            minY = point.y;
            maxY = point.y;
            minZ = point.z;
            maxZ = point.z;
            first = false;
            continue;
        }
        if (point.x > maxX) {
            maxX = point.x;
        } else if (point.x < minX) {
            minX = point.x;
        }
        if (point.y > maxY) {
            maxY = point.y;
        } else if (point.y < minY) {
            minY = point.y;
        }
        if (point.z > maxZ) {
            maxZ = point.z;
        } else if (point.z < minZ) {
            minZ = point.z;
        }
    }
    maxZ += OFFSET;
}

glm::vec3 ShadowBox::getCenter() {
    float x = (minX + maxX) / 2.0f;
    float y = (minY + maxY) / 2.0f;
    float z = (minZ + maxZ) / 2.0f;
    glm::vec4 cen(x, y, z, 1);
    glm::mat4 invertedLight = glm::inverse(this->lightViewMatrix);
    return glm::vec3(invertedLight * cen);
}

float ShadowBox::getWidth() {
    return maxX - minX;
}

float ShadowBox::getHeight() {
    return maxX - minX;
}

float ShadowBox::getLength() {
    return maxX - minX;
}

vector<glm::vec4> ShadowBox::calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar) {
    glm::vec3 upVector = glm::vec3(rotation * this->UP);
    glm::vec3 rightVector = glm::cross(forwardVector, upVector);
    glm::vec3 downVector = glm::vec3(-upVector.x, -upVector.y, -upVector.z);
    glm::vec3 leftVector = glm::vec3(-rightVector.x, -rightVector.y, -rightVector.z);
    glm::vec3 farTop = centerFar + glm::vec3(upVector.x * farHeight,
                                                           upVector.y * farHeight, upVector.z * farHeight);
    glm::vec3 farBottom = centerFar + glm::vec3(downVector.x * farHeight,
                                                        downVector.y * farHeight, downVector.z * farHeight);
    glm::vec3 nearTop = centerNear + glm::vec3(upVector.x * nearHeight,
                                                            upVector.y * nearHeight, upVector.z * nearHeight);
    glm::vec3 nearBottom = centerNear + glm::vec3(downVector.x * nearHeight,
                                                        downVector.y * nearHeight, downVector.z * nearHeight);
    vector<glm::vec4> points;
    points.push_back(calculateLightSpaceFrustumCorner(farTop, rightVector, farWidth));
    points.push_back(calculateLightSpaceFrustumCorner(farTop, leftVector, farWidth));
    points.push_back(calculateLightSpaceFrustumCorner(farBottom, rightVector, farWidth));
    points.push_back(calculateLightSpaceFrustumCorner(farBottom, leftVector, farWidth));
    points.push_back(calculateLightSpaceFrustumCorner(nearTop, rightVector, nearWidth));
    points.push_back(calculateLightSpaceFrustumCorner(nearTop, leftVector, nearWidth));
    points.push_back(calculateLightSpaceFrustumCorner(nearBottom, rightVector, nearWidth));
    points.push_back(calculateLightSpaceFrustumCorner(nearBottom, leftVector, nearWidth));
    
//    cout << points[0][0] << " " << points[0][1] << " " << points[0][2] << endl;
//    cout << points[1][0] << " " << points[1][1] << " " << points[1][2] << endl;
//    cout << points[2][0] << " " << points[2][1] << " " << points[2][2] << endl;
//    cout << points[3][0] << " " << points[3][1] << " " << points[3][2] << endl;
//    cout << points[4][0] << " " << points[4][1] << " " << points[4][2] << endl;
//    cout << points[5][0] << " " << points[5][1] << " " << points[5][2] << endl;
//    cout << points[6][0] << " " << points[6][1] << " " << points[6][2] << endl;
//    cout << points[7][0] << " " << points[7][1] << " " << points[7][2] << endl;
//    cout << endl;
    return points;
}

glm::vec4 ShadowBox::calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width) {
    glm::vec3 point = startPoint + glm::vec3(direction.x * width, direction.y * width, direction.z * width);
    glm::vec4 pointz = glm::vec4(point, 1.0f);
    pointz = lightViewMatrix * pointz;
    return pointz;
}

glm::mat4 ShadowBox::calculateCameraRotationMatrix() {
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(-cam.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(-cam.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    return rotation;
}

void ShadowBox::calculateWidthsAndHeights() {
    farWidth = (float) (SHADOW_DISTANCE * tan(glm::radians(cam.Zoom)));
    nearWidth = (float) (Utils::NEAR_PLANE * tan(glm::radians(cam.Zoom)));
    farHeight = farWidth / getAspectRatio();
    nearHeight = nearWidth / getAspectRatio();

}

float ShadowBox::getAspectRatio() {
    return Utils::WIN_WIDTH / Utils::WIN_HEIGHT;
}

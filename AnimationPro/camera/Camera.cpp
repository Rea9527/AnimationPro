//
//  Camera.cpp
//  CGHws
//
//  Created by 陈主润 on 19/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera() {
    this->STATE = ACTIVE;
    this->Pos = glm::vec3(0.0f, 0.0f, 4.0f);
    this->initUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->Yaw = 0.0f;
    this->Pitch = 0.0f;
    this->Speed = 40.0f;
    this->Sensitivity = 0.25f;
    this->Zoom = 45.0f;
    this->updateCameraPos();
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch) {
    this->STATE = ACTIVE;
    this->Pos = pos;
    this->initUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->Speed = 40.0f;
    this->Sensitivity = 0.25f;
    this->Zoom = 45.0f;
    this->updateCameraPos();
}

glm::mat4 Camera::getViewMat() {
    return glm::lookAt(this->Pos, this->Pos + this->Front, this->Up);
}

void Camera::move(CameraMovement moveDir, GLfloat deltaTime) {
    if (STATE == DISABLE) return;
    GLfloat cameraSpeed = this->Speed * deltaTime;
    if (moveDir == CAM_FOWARD)
        this->Pos += cameraSpeed * this->Front;
    else if (moveDir == CAM_BACKWARD)
        this->Pos -= cameraSpeed * this->Front;
    else if (moveDir == CAM_LEFT)
        this->Pos -= glm::normalize(glm::cross(this->Front, this->Up)) * cameraSpeed;
    else if (moveDir == CAM_RIGHT)
        this->Pos += glm::normalize(glm::cross(this->Front, this->Up)) * cameraSpeed;
}

void Camera::rotate(GLfloat xoff, GLfloat yoff) {
    if (STATE == DISABLE) return;
    xoff *= this->Sensitivity;
    yoff *= this->Sensitivity;
    
    this->Yaw += xoff;
    this->Pitch += yoff;
    
    if(this->Pitch > 89.0f)
        this->Pitch = 89.0f;
    if(this->Pitch < -89.0f)
        this->Pitch = -89.0f;
    
    this->updateCameraPos();
}

void Camera::zoom(GLfloat yoff) {
    if (STATE == DISABLE) return;
    if(this->Zoom >= 1.0f && this->Zoom <= 45.0f)
        this->Zoom -= yoff;
    if(this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if(this->Zoom >= 45.0f)
        this->Zoom = 45.0f;
}

void Camera::updateCameraPos() {
    if (this->STATE == DISABLE) return;
    glm::vec3 front;
    
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    this->Right = glm::normalize(glm::cross(this->Front, this->initUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
    
}

void Camera::disable() {
    glm::vec3 v(0.0f, 0.0f, 0.0f);
    this->Pos = v;
    this->Front = v;
    this->Up = v;
    this->STATE = DISABLE;
}

glm::vec3 Camera::getPos() {
    return this->Pos;
}

float Camera::getYaw() {
    return this->Yaw;
}

float Camera::getPitch() {
    return this->Pitch;
}

void Camera::setTarget(glm::vec3 target) {
    glm::lookAt(this->Pos, this->Pos + this->Front, this->Up);
}

void Camera::setSpeed(GLfloat speed) {
    this->Speed = speed;
}

void Camera::setSensitivity(GLfloat sensitivity) {
    this->Sensitivity = sensitivity;
}

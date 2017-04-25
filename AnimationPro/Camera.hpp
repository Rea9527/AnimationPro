//
//  Camera.hpp
//  CGHws
//
//  Created by 陈主润 on 19/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <iostream>

//glew
#define GLEW_STATIC
#include <GL/glew.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



enum CameraMovement {
    CAM_FOWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT
};

enum CameraState {
    DISABLE,
    ACTIVE
};


class Camera {
public:

    Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch);
    
    glm::mat4 getViewMat();
    void move(CameraMovement moveDir, GLfloat deltaTime);
    void rotate(GLfloat xoff, GLfloat yoff);
    void zoom(GLfloat yoff);
    
    void setSensitivity(GLfloat sensitivity);
    void setSpeed(GLfloat speed);
    void setTarget(glm::vec3 target);
    
    glm::vec3 getPos();
    
    void disable();
    
    glm::vec3 Pos;
    GLfloat Zoom;
    
private:
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 initUp;
    
    
    GLfloat Speed;
    GLfloat Sensitivity;
    GLfloat Yaw;
    GLfloat Pitch;
    
    GLboolean STATE;
    
    void updateCameraPos();
    
    
};

#endif /* Camera_hpp */

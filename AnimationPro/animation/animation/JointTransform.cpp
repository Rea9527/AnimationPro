//
//  JointTransform.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "JointTransform.hpp"


JointTransform::JointTransform() { }

JointTransform::JointTransform(glm::vec3 position, Quaternion rotation) {
    this->position = position;
    this->rotation = rotation;
}

JointTransform JointTransform::interpolate(JointTransform frameA, JointTransform frameB, float progression) {
    glm::vec3 pos = interpolate(frameA.position, frameB.position, progression);
    Quaternion rot = Quaternion::interpolate(frameA.rotation, frameB.rotation, progression);
    
    return JointTransform(pos, rot);
}

glm::mat4 JointTransform::getLocalTransform() {
    glm::mat4 matrix = glm::mat4();
    matrix = glm::translate(matrix, position);
    matrix = matrix * rotation.toRotationMatrix();
    return matrix;
}

glm::vec3 JointTransform::interpolate(glm::vec3 start, glm::vec3 end, float progression) {
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    return glm::vec3(x, y, z);
}


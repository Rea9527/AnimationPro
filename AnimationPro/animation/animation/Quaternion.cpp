//
//  Quaternion.cpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Quaternion.hpp"


Quaternion::Quaternion() { }

Quaternion::Quaternion(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    this->normalize();
}

void Quaternion::normalize() {
    float mag = (float)sqrt(w * w + x * x + y * y + z * z);
    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
}

glm::mat4 Quaternion::toRotationMatrix() {
    glm::mat4 mat = glm::mat4();
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yz = y * z;
    float yw = y * w;
    float zw = z * w;
    float xSquared = x * x;
    float ySquared = y * y;
    float zSquared = z * z;
    
    mat[0][0] = 1 - 2 * (ySquared + zSquared);
    mat[0][1] = 2 * (xy - zw);
    mat[0][2] = 2 * (xz + yw);
    mat[0][3] = 0;
    mat[1][0] = 2 * (xy + zw);
    mat[1][1] = 1 - 2 * (xSquared + zSquared);
    mat[1][2] = 2 * (yz - xw);
    mat[1][3] = 0;
    mat[2][0] = 2 * (xz - yw);
    mat[2][1] = 2 * (yz + xw);
    mat[2][2] = 1 - 2 * (xSquared + ySquared);
    mat[2][3] = 0;
    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
    
    return mat;
}

Quaternion Quaternion::fromMatrix(glm::mat4 mat) {
    float w, x, y, z;
    float diagonal = mat[0][0] + mat[1][1] + mat[2][2];
    if (diagonal > 0) {
        float w4 = (float) (sqrt(diagonal + 1.0f) * 2.0f);
        w = w4 / 4.0f;
        x = (mat[2][1] - mat[1][2]) / w4;
        y = (mat[0][2] - mat[2][0]) / w4;
        z = (mat[1][0] - mat[0][1]) / w4;
    } else if ((mat[0][0] > mat[1][1]) && (mat[0][0] > mat[2][2])) {
        float x4 = (float) (sqrt(1.0f + mat[0][0] - mat[1][1] - mat[2][2]) * 2.0f);
        w = (mat[2][1] - mat[1][2]) / x4;
        x = x4 / 4.0f;
        y = (mat[0][1] + mat[1][0]) / x4;
        z = (mat[0][2] + mat[2][0]) / x4;
    } else if (mat[1][1] > mat[2][2]) {
        float y4 = (float) (sqrt(1.0f + mat[1][1] - mat[0][0] - mat[2][2]) * 2.0f);
        w = (mat[0][2] - mat[2][0]) / y4;
        x = (mat[0][1] + mat[1][0]) / y4;
        y = y4 / 4.0f;
        z = (mat[1][2] + mat[2][1]) / y4;
    } else {
        float z4 = (float) (sqrt(1.0f + mat[2][2] - mat[0][0] - mat[1][1]) * 2.0f);
        w = (mat[1][0] - mat[0][1]) / z4;
        x = (mat[0][2] + mat[2][0]) / z4;
        y = (mat[1][2] + mat[2][1]) / z4;
        z = z4 / 4.0f;
    }
    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::interpolate(Quaternion a, Quaternion b, float blend) {
    Quaternion result = Quaternion(0, 0, 0, 1);
    float dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    float blendI = 1.0f - blend;
    if (dot < 0) {
        result.w = blendI * a.w + blend * -b.w;
        result.x = blendI * a.x + blend * -b.x;
        result.y = blendI * a.y + blend * -b.y;
        result.z = blendI * a.z + blend * -b.z;
    } else {
        result.w = blendI * a.w + blend * b.w;
        result.x = blendI * a.x + blend * b.x;
        result.y = blendI * a.y + blend * b.y;
        result.z = blendI * a.z + blend * b.z;
    }
    result.normalize();
    return result;
}

//
//  Utils.cpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Utils.hpp"


float Utils::frameTime = 1.0f / 60.0f;

float Utils::WIN_WIDTH = 720.0f;
float Utils::WIN_HEIGHT = 720.0f;

float Utils::NEAR_PLANE = 0.1f;
float Utils::FOV = 45.0f;

Utils::Utils() { }

GLint Utils::loadTextureFromFile(const char* path, string directory) {
    //Generate texture ID and load texture data
    string filename = string(path);
    filename = directory + '/' + filename;
    
//    std::cout << "Texture Path: " << filename << std::endl;
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if (!image) {
        cout << "SOIL_LOAD_IMAGE: FILE NOT FOUND" << endl;
    }
    
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}

glm::mat4 Utils::aiMatToGlmMat(aiMatrix4x4 mat) {
    glm::mat4 tmp;
    tmp[0][0] = mat.a1;
    tmp[1][0] = mat.b1;
    tmp[2][0] = mat.c1;
    tmp[3][0] = mat.d1;
    
    tmp[0][1] = mat.a2;
    tmp[1][1] = mat.b2;
    tmp[2][1] = mat.c2;
    tmp[3][1] = mat.d2;
    
    tmp[0][2] = mat.a3;
    tmp[1][2] = mat.b3;
    tmp[2][2] = mat.c3;
    tmp[3][2] = mat.d3;
    
    tmp[0][3] = mat.a4;
    tmp[1][3] = mat.b4;
    tmp[2][3] = mat.c4;
    tmp[3][3] = mat.d4;
    
    return tmp;
}

aiMatrix4x4 Utils::GlmMatToAiMat(glm::mat4 mat) {
    return aiMatrix4x4(mat[0][0],mat[0][1],mat[0][2],mat[0][3],
                       mat[1][0],mat[1][1],mat[1][2],mat[1][3],
                       mat[2][0],mat[2][1],mat[2][2],mat[2][3],
                       mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
}

float Utils::timeToFrame(float time)
{
    float frame = 0.041666666667;
    return time / frame;
}

glm::vec2 Utils::framesToTime(glm::vec2 frames) {
    float frame = 0.041666666667;
    return frames * frame;
}

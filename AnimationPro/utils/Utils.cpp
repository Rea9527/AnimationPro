//
//  Utils.cpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Utils.hpp"


float Utils::frameTime = 0.0f;

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
    glm::mat4 glmMat;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            glmMat[i][j] = mat[i][j];
    
    return glmMat;
}

aiMatrix4x4 Utils::GlmMatToAiMat(glm::mat4 mat) {
    aiMatrix4x4 aiMat;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            aiMat[i][j] = mat[i][j];
    
    return aiMat;
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

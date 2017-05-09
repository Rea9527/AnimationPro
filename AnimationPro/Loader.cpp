//
//  Loader.cpp
//  glfwTest
//
//  Created by 陈主润 on 10/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Loader.hpp"


Loader::Loader() {}

Loader::~Loader() {
    
}


void Loader::cleanUp() {
    for (auto vao : vaos)
        glDeleteVertexArrays(1, &vao);
    for (auto vbo : vbos)
        glDeleteBuffers(1, &vbo);
    for (auto ebo : vbos)
        glDeleteBuffers(1, &ebo);
    GLuint tt[100], i = 0;
    for (auto texture : textures)
        tt[i++] = texture;
    glDeleteTextures(i, tt);
}

RawModel Loader::loadToVAO(GLfloat vertices[], GLsizei size, GLuint indices[], GLsizei isize) {
    
    GLuint vaoID = createVAO();
    RawModel rawModel(vaoID, isize/sizeof(GLfloat));
    storeDataToArrayList(vertices, size);
    createEBO(indices, isize);
    setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    setAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    setAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6* sizeof(GLfloat)));
    unbind();
    
    return rawModel;
}

RawModel Loader::loadPosToVAO(GLfloat vertices[], GLsizei size, GLsizei count) {
    GLuint vaoID = createVAO();
    RawModel rawModel(vaoID, count);
    storeDataToArrayList(vertices, size);
    setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    unbind();
    return rawModel;
}

GLuint Loader::loadTexture(string path) {
    GLuint textureId;
    GLint texWidth, texHeight;
    unsigned char* image = SOIL_load_image(path.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGBA);
    //texture 1
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    this->textures.push_back(textureId);
    // Set our texture parameters
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.2f);
    // set tex image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    return textureId;
}

GLuint Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Loader::storeDataToArrayList(GLfloat vertices[], GLsizei size) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    
}

void Loader::setAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void Loader::createEBO(GLuint indices[], GLsizei size) {
    GLuint eboID;
    glGenBuffers(1, &eboID);
    ebos.push_back(eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}




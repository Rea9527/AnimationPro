//
//  Loader.hpp
//  glfwTest
//
//  Created by 陈主润 on 10/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#define GLEW_STATIC

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "RawModel.hpp"


class Loader {
public:
    Loader();
    ~Loader();
    //load
    RawModel loadToVAO(GLfloat vertices[], GLsizei size, GLuint indices[], GLsizei isize);
    GLuint loadTexture(GLchar path[]);
    void setAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    // bind EBO
    void createEBO(GLuint indices[], GLsizei size);
    
    void unbind();
    
    void cleanUp();
    
private:
    
    
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> ebos;
    std::vector<GLuint> textures;
    
    GLuint createVAO();
    
    void storeDataToArrayList(GLfloat vertices[], GLsizei size);
};

#endif /* Loader.hpp */

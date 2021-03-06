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
#include <string>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "../models/RawModel.hpp"

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Loader {
public:
    Loader();
    ~Loader();
    //load pos colors textures
    RawModel loadToVAO(GLfloat vertices[], GLsizei size, GLuint indices[], GLsizei isize);
    RawModel loadToVAO(GLfloat vertices[], GLsizei size, GLsizei count);
    //load pos
    RawModel loadPosToVAO(GLfloat vertices[], GLsizei size, GLsizei count);
    //load pos and texcoords
    RawModel loadPosAndTex(GLfloat vertices[], GLsizei size, GLuint indices[], GLsizei isize);
    
    GLuint loadTexture(string path);
    GLuint loadInstance(glm::vec3 translations[], int count);
    
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

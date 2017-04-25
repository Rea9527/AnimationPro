//
//  color_triangle.hpp
//  glfwTest
//
//  Created by 陈主润 on 01/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <iostream>
#include <vector>
// glew
#define GLEW_STATIC
#include <GL/glew.h>

#include "PointLight.hpp"
#include "DirectionalLight.hpp"


class Shader {
public:
    // program id
    GLuint Program;
    
    Shader();
    // create vertex and fragment shaders by paths
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    //getAllUniformLocations
    void getAllUniformLocations();
    
    void loadProjectionMat(const GLfloat* projectionPtr);
    void loadViewMat(const GLfloat* viewPtr);
    void loadModelMat(const GLfloat* modelPtr);

    // run and stop program
    void Use();
    void Stop();
    
private:
    
    GLint projectionLoc;
    GLint modelLoc;
    GLint viewLoc;

};

#endif /* shader_hpp */

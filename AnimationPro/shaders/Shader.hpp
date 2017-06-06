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
#include <string>
// glew
#define GLEW_STATIC
#include <GL/glew.h>

#include "../lights/PointLight.hpp"
#include "../lights/DirectionalLight.hpp"

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
public:
    // program id
    GLuint Program;
    
    Shader();
    // create vertex and fragment shaders by paths
    Shader(string vertexPath, string fragmentPath);
    
    GLint getUniformLocation(string name);
    //getAllUniformLocations
    void getAllUniformLocations();
    
    void loadProjectionMat(const GLfloat* projectionPtr);
    void loadViewMat(const GLfloat* viewPtr);
    void loadModelMat(const GLfloat* modelPtr);
    
    void loadMVP(glm::mat4 mvp);

    // run and stop program
    void Use();
    void Stop();
    
private:
    
    GLint projectionLoc;
    GLint modelLoc;
    GLint viewLoc;
    
    GLint mvpLoc;
};

#endif /* shader_hpp */

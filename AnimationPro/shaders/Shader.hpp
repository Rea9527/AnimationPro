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
    

    void loadMVP(glm::mat4 mvp);
    
    //set
    void setMat4(GLuint loc, glm::mat4 mat);
    void setInt(GLuint loc, GLint num);

    // run and stop program
    void Use();
    void Stop();
    
private:
    GLuint mvpLoc;
    
};

#endif /* shader_hpp */

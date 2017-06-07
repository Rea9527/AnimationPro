//
//  color_triangle.cpp
//  glfwTest
//
//  Created by 陈主润 on 01/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include <fstream>
#include <sstream>

#include "Shader.hpp"

Shader::Shader() {}

Shader::Shader(string vertexPath, string fragmentPath) {
    
    //create vertex shader
    std::ifstream vertexFile, fragmentFile;
    vertexFile.open(vertexPath.c_str(), std::ios::in);
    fragmentFile.open(fragmentPath.c_str(), std::ios::in);
    std::stringstream vertexSS, fragmentSS;
    vertexSS << vertexFile.rdbuf();
    fragmentSS << fragmentFile.rdbuf();
    vertexFile.close();
    fragmentFile.close();
    
    std::string vertexStr, fragmentStr;
    const GLchar *vertexCode, *fragmentCode;
    vertexStr = vertexSS.str();
    fragmentStr = fragmentSS.str();
    vertexCode = vertexStr.c_str();
    fragmentCode = fragmentStr.c_str();
    
    
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar errInfo[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errInfo);
        std::cout << "ERROR: VERTEX SHADER CREATE!" << std::endl;
        std::cout << "VERTEX: " << errInfo << std::endl << std::endl;
    }
    //fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errInfo);
        std::cout << "ERROR: FRAGMENT SHADER CREATE!" << std::endl;
        std::cout << "FRAGMENT: " << errInfo << std::endl << std::endl;
    }
    
    //create Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertexShader);
    glAttachShader(this->Program, fragmentShader);
    glLinkProgram(this->Program);
    //print if error
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, errInfo);
        std::cout << "ERROR: CREATE SHADER PROGRAM ERROR" << std::endl;
        std::cout << "SHADER PROGRAM: " << errInfo << std::endl << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(string name) {
    return glGetUniformLocation(this->Program, name.c_str());
}


void Shader::loadMVP(glm::mat4 mvp) {
    glUniformMatrix4fv(this->mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}

//setter
void Shader::setMat4(GLuint loc, glm::mat4 mat) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setInt(GLuint loc, GLint num) {
    glUniform1i(loc, num);
}

void Shader::Use() {
    glUseProgram(this->Program);
}

void Shader::Stop() {
    glUseProgram(0);
}

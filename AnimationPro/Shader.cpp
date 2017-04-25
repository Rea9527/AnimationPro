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

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    
    //create vertex shader
    std::ifstream vertexFile, fragmentFile;
    vertexFile.open(vertexPath, std::ios::in);
    fragmentFile.open(fragmentPath, std::ios::in);
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
    }
    //fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errInfo);
        std::cout << "ERROR: FRAGMENT SHADER CREATE!" << errInfo << std::endl;
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
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::getAllUniformLocations() {
    this->projectionLoc = glGetUniformLocation(this->Program, "projection");
    this->viewLoc = glGetUniformLocation(this->Program, "view");
    this->modelLoc = glGetUniformLocation(this->Program, "model");
}

void Shader::loadProjectionMat(const GLfloat* projectionPtr) {
    glUniformMatrix4fv(this->projectionLoc, 1, GL_FALSE, projectionPtr);
}

void Shader::loadViewMat(const GLfloat *viewPtr) {
    glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, viewPtr);
}

void Shader::loadModelMat(const GLfloat *modelPtr) {
    glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, modelPtr);
}

void Shader::Use() {
    glUseProgram(this->Program);
}

void Shader::Stop() {
    glUseProgram(0);
}

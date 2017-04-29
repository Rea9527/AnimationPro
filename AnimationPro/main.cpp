//
//  main.cpp
//  glfwTest
//
//  Created by 陈主润 on 21/02/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

// glew
#define GLEW_STATIC
#include <GL/glew.h>
// glfw
#define GLFW_INCLUDE_GLCOREARB //to include gl3.h
#include <GLFW/glfw3.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "ModelShader.hpp"
#include "StaticShader.hpp"
#include "TerrainShader.hpp"

#include "TerrainRender.hpp"
#include "ModelRender.hpp"

#include "Loader.hpp"
#include "Camera.hpp"
#include "ObjModel.hpp"

using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoff, double yoff);
void updateMovement();

GLfloat WIN_WIDTH = 640, WIN_HEIGHT = 480;

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 dirLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f)
};

glm::vec3 pointLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, -4.0f)
    
};


//camera
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = WIN_WIDTH/2, lastY = WIN_HEIGHT/2;
bool firstMouse = true;

glm::vec3 cameraPos   = glm::vec3(700.0f, 50.0f, 250.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
Camera myCamera(cameraPos, cameraUp, -180.0f, 0.0f);



int main(int argc, const char * argv[]) {
    //===============================
    // --init--
    //set up GLFW
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Project", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    
    // set up GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "GLEW initialization error!" << endl;
        return -1;
    }
    
    // set viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //===============================
    
    
    // draw rectangle with two triangle
    GLfloat points[] = {
        //points(3)           //normal(3)       //texture
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f,   0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        
        //points(3)           //colors(3)       //texture
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f,  -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f,   0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        
        //points(3)           //colors(3)       //texture
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,   -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        
        //points(3)           //colors(3)       //texture
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        
        //points(3)           //colors(3)       //texture
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        
        //points(3)           //colors(3)       //texture
        -0.5f, 0.5f,  0.5f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        
        4, 5, 6,
        4, 6, 7,
        
        8, 9, 10,
        8, 10, 11,
        
        12, 13, 14,
        12, 14, 15,
        
        16, 17, 18,
        16, 18, 19,
        
        20, 21, 22,
        20, 22, 23
    };
    //===============================
    
    string root = "./shaderSources/";
    //===============================
    //build shader program
    ModelShader modelShader( root+"modelVS.vs", root+"modelFS.frag" );
    StaticShader myShader( root+"vertexShader.vs", root+"fragmentShader.frag" );
    TerrainShader terrainShader( root+"terrainVS.vs", root+"terrainFS.frag" );
    
    ObjModel houseModel("./assets/oldhouse/oldhouse/oldhouse.obj");
    ModelRender houseRender(modelShader);
    ObjModel pussModel("./assets/puss/Puss_in_Boots.obj");
    ModelRender pussRender(modelShader);
    ObjModel treeModel("./assets/trees9/trees9.3ds");
    ModelRender treeRender(modelShader);
    
    
    Loader loader;
    //==============================
    root = "./assets/terrain/";
    TerrainTexture bgTexture = TerrainTexture(loader.loadTexture(root+"grass.png"));
    TerrainTexture rTexture = TerrainTexture(loader.loadTexture(root+"mud.png"));
    TerrainTexture gTexture = TerrainTexture(loader.loadTexture(root+"flowers.png"));
    TerrainTexture bTexture = TerrainTexture(loader.loadTexture(root+"path.png"));
    
    TerrainTexturePack texturePack = TerrainTexturePack(bgTexture, rTexture, gTexture, bTexture);
    TerrainTexture blendMap = TerrainTexture(loader.loadTexture(root+"blendMap.png"));
    
    Terrain terrain1 = Terrain(0, 0, loader, texturePack, blendMap);
    Terrain terrain2 = Terrain(1, 0, loader, texturePack, blendMap);
    
    vector<Terrain> terrains;
    terrains.push_back(terrain1);
    terrains.push_back(terrain2);
    TerrainRender terrainRender(terrainShader);
    //==============================
    
    
    //==============================
    //read texture image
    GLuint texture1 = loader.loadTexture("./assets/container2.png");
    GLuint texture2 = loader.loadTexture("./assets/specularMap.png");
    myShader.Use();
    glUniform1i(glGetUniformLocation(myShader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(myShader.Program, "material.specular"), 1);
    myShader.Stop();
    //==============================
    
    
    //==============================
    //rectangle
    RawModel cube = loader.loadToVAO(points, sizeof(points), indices, sizeof(indices));
    //==============================
    
    //Lights
    DirectionalLight dirLight = DirectionalLight(dirLightAttrib[0], dirLightAttrib[1], dirLightAttrib[2], dirLightAttrib[3]);
    PointLight pointLight = PointLight(pointLightAttrib[0], pointLightAttrib[1], pointLightAttrib[2], pointLightAttrib[3], 1.0f, 0.09f, 0.032f);
    
    //set keycallback
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
//    myCamera.disable();
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // drawing loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        
        updateMovement();
        
        glm::mat4 model = glm::mat4(), view, projection;
        GLfloat angle;
        view = myCamera.getViewMat();
        angle = glm::radians(myCamera.Zoom);
        projection = glm::perspective(angle, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
        
        //terrain
        //==============================
        terrainRender.render(terrains, projection, view);

        //puss
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(550.0f, 11.5f, 200.0f));
        model = glm::scale(model, glm::vec3(15, 15, 15));
        pussRender.addLight(pointLight, dirLight);
        pussRender.render(pussModel, projection, view, model, myCamera);
        
        
        //puss
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(400.0f, 0, 200.0f));
        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        houseRender.addLight(pointLight, dirLight);
        houseRender.render(houseModel, projection, view, model, myCamera);
        
        //tree
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(400.0f, 0.0f, 200.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        treeRender.addLight(pointLight, dirLight);
        treeRender.render(treeModel, projection, view, model, myCamera);
        
        
        //==============================
//        myShader.Use();
//        myShader.getAllUniformLocations();
//        
//        //bind texture
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//        
//        
//        //model
//        glm::mat4 baseModel;
//        angle = glm::radians(-180.0f);
//        baseModel = glm::rotate(baseModel, angle, glm::vec3(0.5f, 1.0f, 1.0f));
////        //view
//        myShader.loadViewMat(glm::value_ptr(view));
////        //projection
//        myShader.loadProjectionMat(glm::value_ptr(projection));
//
//        for (GLuint i = 0; i < 10; i++) {
//            model = glm::translate(baseModel, cubePositions[i]);
//            angle = glm::radians(-55.0f * (i+1) * (float)glfwGetTime() / 5);
//            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//            
//            myShader.loadModelMat(glm::value_ptr(model));
//            
//            //draw
//            glBindVertexArray(cube.getVAO());
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//            glBindVertexArray(0);
//        }

        //==============================
        
        
        glfwSwapBuffers(window);
    }

    loader.cleanUp();
    
    glfwTerminate();
    return 0;
}

void updateMovement() {
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    if (keys[GLFW_KEY_W])
        myCamera.move(CAM_FOWARD, deltaTime);
    else if (keys[GLFW_KEY_S])
        myCamera.move(CAM_BACKWARD, deltaTime);
    else if (keys[GLFW_KEY_A])
        myCamera.move(CAM_LEFT, deltaTime);
    else if (keys[GLFW_KEY_D])
        myCamera.move(CAM_RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    GLfloat offset_x, offset_y;
//    std::cout << xpos << " " << ypos << std::endl;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    offset_x = xpos - lastX;
    offset_y = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    myCamera.rotate(offset_x, offset_y);
}

void scroll_callback(GLFWwindow *window, double xoff, double yoff) {
    myCamera.zoom(yoff);
}

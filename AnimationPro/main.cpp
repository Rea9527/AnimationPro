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
#include "SkyboxRender.hpp"

#include "Loader.hpp"
#include "Camera.hpp"
#include "ObjModel.hpp"

using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoff, double yoff);
void updateMovement();

GLfloat WIN_WIDTH = 640, WIN_HEIGHT = 480;

glm::vec3 dirLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),//ambient
    glm::vec3(0.0f, 0.0f, 0.0f),//diffuse
    glm::vec3(0.0f, 0.0f, 0.0f),//specular
    glm::vec3(-0.2f, -1.0f, -0.3f)//direction
};

glm::vec3 pointLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),//am
    glm::vec3(0.0f, 0.0f, 0.0f),//di
    glm::vec3(0.0f, 0.0f, 0.0f),//spec
    glm::vec3(0.0f, 0.0f, -4.0f)//pos
    
};


//camera
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = WIN_WIDTH/2, lastY = WIN_HEIGHT/2;
bool firstMouse = true;

glm::vec3 cameraPos   = glm::vec3(940.0f, 10.0f, 420.0f);
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
    StaticShader skyboxShader( root+"skyboxVS.vs", root+"skyboxFS.frag" );
    TerrainShader terrainShader( root+"terrainVS.vs", root+"terrainFS.frag" );
    
    ObjModel houseModel("./assets/oldhouse/oldhouse/oldhouse.obj");
    ModelRender houseRender(modelShader);
    ObjModel pussModel("./assets/puss/Puss_in_Boots.obj");
    ModelRender pussRender(modelShader);
    ObjModel treeModel("./assets/tree3/tree/tree.obj");
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
    //skybox
    SkyboxRender skyboxRender(skyboxShader);
    vector<const char*> faces;
    faces.push_back("./assets/skybox/cloudtop/right.jpg");
    faces.push_back("./assets/skybox/cloudtop/left.jpg");
    faces.push_back("./assets/skybox/cloudtop/top.jpg");
    faces.push_back("./assets/skybox/cloudtop/bottom.jpg");
    faces.push_back("./assets/skybox/cloudtop/back.jpg");
    faces.push_back("./assets/skybox/cloudtop/front.jpg");
    Skybox skybox = Skybox(loader, faces);
    
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
        
        
        //skybox
        //==============================
        glDepthMask(GL_FALSE);
        skyboxRender.render(skybox, view, projection);
        glDepthMask(GL_TRUE);
        
        //terrain
        //==============================
        terrainRender.render(terrains, projection, view);

        //puss
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(880.0f, 1.2f, 420.0f));
        model = glm::scale(model, glm::vec3(2, 2, 2));
        pussRender.addLight(pointLight, dirLight);
        pussRender.render(pussModel, projection, view, model, myCamera);
        
        
        //house
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(850.0f, 0, 420.0f));
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        houseRender.addLight(pointLight, dirLight);
        houseRender.render(houseModel, projection, view, model, myCamera);
        
        //tree
        //==============================
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(550.0f, 11.5f, 200.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        treeRender.addLight(pointLight, dirLight);
        treeRender.render(treeModel, projection, view, model, myCamera);
        
        
        
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

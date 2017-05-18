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

#include "shaders/ModelShader.hpp"
#include "shaders/StaticShader.hpp"
#include "shaders/TerrainShader.hpp"

#include "renderer/TerrainRender.hpp"
#include "renderer/ModelRender.hpp"
#include "renderer/SkyboxRender.hpp"
#include "renderer/SkeletalRender.hpp"

#include "loader/Loader.hpp"
#include "camera/Camera.hpp"
#include "models/ObjModel.hpp"
#include "models/skeletalModel/SkeletalModel.hpp"

using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoff, double yoff);
void updateMovement();

GLfloat WIN_WIDTH = 640, WIN_HEIGHT = 480;

glm::vec3 dirLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),//ambient
    glm::vec3(0.8f, 0.8f, 0.8f),//diffuse
    glm::vec3(0.3f, 0.4f, 0.2f),//specular
    glm::vec3(-800.0f, 200.0f, 600.0f)//direction
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

glm::vec3 cameraPos   = glm::vec3(940.0f, 100.0f, 600.0f);
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
    
    string root = "shaders/shaderSources/";
    //===============================
    //build shader program
    ModelShader modelShader( root+"modelVS.vs", root+"modelFS.frag" );
    ModelShader manShader ( root+"skeletalModelVS.vs", root+"skeletalModelFS.frag" );
    StaticShader skyboxShader( root+"skyboxVS.vs", root+"skyboxFS.frag" );
    TerrainShader terrainShader( root+"terrainVS.vs", root+"terrainFS.frag" );
    
    //house
    ObjModel houseModel("assets/oldhouse/oldhouse/oldhouse.obj");
    ModelRender houseRender(modelShader);
    ObjModel pussModel("assets/puss/Puss_in_Boots.obj");
    ModelRender pussRender(modelShader);
    
    //table chair
    ObjModel chairModel("assets/chair_table/chair.obj");
    ObjModel tableModel("assets/chair_table/table.obj");
    ModelRender chairRender(modelShader);
    ModelRender tableRender(modelShader);
    
    //window
    ObjModel windowModel("assets/window/file.obj");
    ModelRender windowRender(modelShader);
    
    //man
    SkeletalModel manModel("assets/man/model.dae");
    SkeletalRender manRender(manShader);
    
    
    
    Loader loader;
    //==============================
    //terrain
    root = "assets/terrain/";
    TerrainTexture bgTexture = TerrainTexture(loader.loadTexture(root+"grass.png"));
    TerrainTexture rTexture = TerrainTexture(loader.loadTexture(root+"mud.png"));
    TerrainTexture gTexture = TerrainTexture(loader.loadTexture(root+"flowers.png"));
    TerrainTexture bTexture = TerrainTexture(loader.loadTexture(root+"path.png"));
    
    TerrainTexturePack texturePack = TerrainTexturePack(bgTexture, rTexture, gTexture, bTexture);
    TerrainTexture blendMap = TerrainTexture(loader.loadTexture(root+"blendMap.png"));
    
    Terrain terrain1 = Terrain(0, -1, loader, texturePack, blendMap, "assets/heightMap4.jpg");
//    Terrain terrain2 = Terrain(1, 0, loader, texturePack, blendMap, "assets/heightMap4.jpg");
    
    vector<Terrain> terrains;
    terrains.push_back(terrain1);
//    terrains.push_back(terrain2);
    TerrainRender terrainRender(terrainShader);
    //==============================
    
    
    //==============================
    //skybox
    SkyboxRender skyboxRender(skyboxShader);
    vector<const char*> faces;
    faces.push_back("assets/skybox/cloudtop/right.jpg");
    faces.push_back("assets/skybox/cloudtop/left.jpg");
    faces.push_back("assets/skybox/cloudtop/top.jpg");
    faces.push_back("assets/skybox/cloudtop/bottom.jpg");
    faces.push_back("assets/skybox/cloudtop/back.jpg");
    faces.push_back("assets/skybox/cloudtop/front.jpg");
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
        
        //terrain
        //==============================
        terrainRender.addDirLight(dirLight);
        terrainRender.render(terrains, projection, view, myCamera);
        
        //man
        //==============================
        model = glm::mat4();
        GLfloat x = 880.0f, z = 650.0f;
        GLfloat y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1, 1, 1));
        manRender.addLight(pointLight, dirLight);
        manRender.render(manModel, projection, view, model, myCamera);

        //puss
        //==============================
        model = glm::mat4();
        x = 880.0f, z = 640.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(2, 2, 2));
        pussRender.addLight(pointLight, dirLight);
        pussRender.render(pussModel, projection, view, model, myCamera);
        
        //house
        //==============================
        model = glm::mat4();
        x = 850.0f, z = 640.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        houseRender.addLight(pointLight, dirLight);
        houseRender.render(houseModel, projection, view, model, myCamera);
        
        //window
        //==============================
        model = glm::mat4();
        x = 872.f, z = 652.0f;
        y = terrain1.getHeightOfTerrain(x, z) + 1.0f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
        windowRender.render(windowModel, projection, view, model, myCamera);
        
        //table
        //==============================
        model = glm::mat4();
        x = 865.0f, z = 650.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        chairRender.render(chairModel, projection, view, model, myCamera);
        
        model = glm::mat4();
        x = 865.0f, z = 650.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        tableRender.render(tableModel, projection, view, model, myCamera);
        
        
        //skybox
        //==============================
        glDepthFunc(GL_LEQUAL);
        skyboxRender.render(skybox, view, projection);
        glDepthFunc(GL_LESS);
        
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

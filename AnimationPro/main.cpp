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
#include "renderer/cubeRender.hpp"
#include "renderer/RectangleRender.hpp"


#include "loader/Loader.hpp"
#include "camera/Camera.hpp"

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
    glm::vec3(-1.0f, 1.0f, 0.0f)//direction
};

glm::vec3 pointLightAttrib[] {
    glm::vec3(1.0f, 1.0f, 1.0f),//am
    glm::vec3(1.0f, 1.0f, 1.0f),//di
    glm::vec3(0.4f, 0.4f, 0.4f),//spec
    glm::vec3(870.0f, 3.0f, 650.0f)//pos
    
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
    StaticShader staticShader( root+"emptyVS.vs", root+"emptyFS.frag" );
    
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
    
    //radio
    ObjModel radioModel("assets/radio/radio.obj");
    ModelRender radioRender(modelShader);
    
    //man
    SkeletalModel manModel("assets/man/model.dae");
    static Animation idle("anim", Utils::framesToTime(glm::vec2(21, 40)), 2);
    static Animation walk("anim", Utils::framesToTime(glm::vec2(1, 20)), 2);
    manModel.addAnimation(walk);
    manModel.setIdleAnimation(idle);
    manModel.playAnimation(walk, true, false);
    SkeletalRender manRender(manShader);
    
    //mask
    PolygonModel cube;
    cube.load();
    CubeRender cubeRender(staticShader);
    
    //tile
    RectangleModel tile;
    tile.load("assets/tile/1.jpg");
    RectangleRender tileRenderer(modelShader);
    
    //trees
    ObjModel treeModel("assets/trees/1/file.obj");
    ModelRender treeRenderer(modelShader);
    
    
    
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
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xff);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // drawing loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwPollEvents();
        
        updateMovement();
        
        glm::mat4 model, view, projection, mvp;
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
//        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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
        
        //mask cube
        //==============================
//        glStencilFunc(GL_ALWAYS, 1, 0xff);
//        glStencilMask(0xff);
        model = glm::mat4();
        x = 871.5f, z = 637.5f;
        y = terrain1.getHeightOfTerrain(x, z) + 2.5f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.3f, 4.8f, 3.1f));
        cubeRender.render(cube, projection, view, model);
        
        //house
        //==============================
//        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
//        glStencilMask(0x00);
        model = glm::mat4();
        x = 850.0f, z = 640.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        houseRender.addLight(pointLight, dirLight);
        houseRender.render(houseModel, projection, view, model, myCamera);
        
        //tile
        //==============================
        model = glm::mat4();
        x = 864.5f, z = 644.8f;
        y = terrain1.getHeightOfTerrain(x, z) + 0.05f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(14.0f, 1.0f, 25.0f));
        tileRenderer.addLight(pointLight, dirLight);
        tileRenderer.render(tile, projection, view, model, myCamera);
        
        //radio
        //==============================
        model = glm::mat4();
        x = 870.0f, z = 651.0f;
        y = terrain1.getHeightOfTerrain(x, z) + 2.0f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
        radioRender.render(radioModel, projection, view, model, myCamera);
        
        
        //table
        //==============================
        model = glm::mat4();
        x = 870.0f, z = 652.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
        chairRender.render(chairModel, projection, view, model, myCamera);
        
        model = glm::mat4();
        x = 870.0f, z = 652.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
        tableRender.render(tableModel, projection, view, model, myCamera);
        
        //tree
        //==============================
        model = glm::mat4();
        x = 875.0f, z = 652.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        treeRenderer.render(treeModel, projection, view, model, myCamera);
        
        
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

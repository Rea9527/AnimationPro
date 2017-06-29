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
#include <stdlib.h>
#include <time.h>

#include "shaders/ModelShader.hpp"
#include "shaders/StaticShader.hpp"
#include "shaders/TerrainShader.hpp"

#include "renderer/TerrainRender.hpp"
#include "renderer/ModelRender.hpp"
#include "renderer/SkyboxRender.hpp"
#include "renderer/SkeletalRender.hpp"
#include "renderer/cubeRender.hpp"
#include "renderer/RectangleRender.hpp"
#include "shadows/ShadowMapRenderer.hpp"
#include "renderer/TileRenderer.hpp"


#include "loader/Loader.hpp"
#include "camera/Camera.hpp"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoff, double yoff);
void updateMovement();

GLfloat WIN_WIDTH = 720, WIN_HEIGHT = 720;

glm::vec3 dirLightAttrib[] {
    glm::vec3(0.8f, 0.8f, 0.8f),//ambient
    glm::vec3(0.8f, 0.8f, 0.8f),//diffuse
    glm::vec3(0.1f, 0.1f, 0.1f),//specular
    glm::vec3(0.0f, -400.0f, 500.0f)//direction
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

float housePosx = 1400.0f, housePosz = 1400.0f;
glm::vec3 cameraPos   = glm::vec3(housePosx + 150.0f, 20.0f, housePosz);
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
    
    //===============================
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xff);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    string root = "shaders/shaderSources/";
    //===============================
    //build shader program
    ModelShader modelShader( root+"modelVS.vs", root+"modelFS.frag" );
    ModelShader manShader ( root+"skeletalModelVS.vs", root+"skeletalModelFS.frag" );
    StaticShader skyboxShader( root+"skyboxVS.vs", root+"skyboxFS.frag" );
    TerrainShader terrainShader( root+"terrainVS.vs", root+"terrainFS.frag" );
    StaticShader staticShader( root+"emptyVS.vs", root+"emptyFS.frag" );
    TileShader tileShader( root+"tileVS.vs", root+"tileFS.frag" );
    
    //house
    ObjModel houseModel("assets/oldhouse/oldhouse/oldhouse.obj");
    ModelRender houseRender(modelShader);
    SkeletalModel pussModel("assets/cow/cow.dae");
    static Animation cowwalk("anim", Utils::framesToTime(glm::vec2(1, 20)), 2);
    pussModel.addAnimation(cowwalk);
    pussModel.playAnimation(cowwalk, true, false);
    SkeletalRender pussRender(manShader);
    
    //table chair
    ObjModel chairModel("assets/chair_table/chair.obj");
    ObjModel tableModel("assets/chair_table/table.obj");
    ModelRender chairRender(modelShader);
    ModelRender tableRender(modelShader);
    
    //radio
    ObjModel radioModel("assets/radio/radio.obj");
    ModelRender radioRender(modelShader);
    
    //man
    SkeletalModel manModel("assets/man/walk.dae");
//    SkeletalModel manModel("assets/cow/cow.dae");
    static Animation idle("anim", Utils::framesToTime(glm::vec2(21, 40)), 2);
    static Animation walk("anim", Utils::framesToTime(glm::vec2(1, 40)), 2);
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
    TileRenderer tileRenderer(tileShader);
    
    //shadowmap renderer
    ShadowMapRenderer shadowMapRenderer(myCamera);
    
    
    Loader loader;
    //==============================
    //terrain
    root = "assets/terrain/";
    TerrainTexture bgTexture = TerrainTexture(loader.loadTexture(root+"grass3.png"));
    TerrainTexture rTexture = TerrainTexture(loader.loadTexture(root+"grass3.png"));
    TerrainTexture gTexture = TerrainTexture(loader.loadTexture(root+"grass3.png"));
    TerrainTexture bTexture = TerrainTexture(loader.loadTexture(root+"grass3.png"));
    
    TerrainTexturePack texturePack = TerrainTexturePack(bgTexture, rTexture, gTexture, bTexture);
    TerrainTexture blendMap = TerrainTexture(loader.loadTexture(root+"blendMap.png"));
    
    Terrain terrain1 = Terrain(0, -1, loader, texturePack, blendMap, "assets/heightMap4.jpg");
//    Terrain terrain2 = Terrain(1, 0, loader, texturePack, blendMap, "assets/heightMap4.jpg");
    
    vector<Terrain> terrains;
    terrains.push_back(terrain1);
//    terrains.push_back(terrain2);
    TerrainRender terrainRender(terrainShader);
    //==============================
    
    
    //trees
    ObjModel treeModel("assets/trees/2/tree1.obj");
    cout << treeModel.getVerticesSize() << endl;
    ModelRender treeRenderer(modelShader);
    vector<glm::mat4> treeModelMats;
    GLfloat maxX = 1300, minX = 400, maxZ = 1300, minZ = 400;
    float randx, randy, randz;
    for (int i = 0; i < 20; i++) {
        glm::mat4 mat = glm::mat4();
        srand((unsigned)time(NULL));
//        randx = fmod(rand(), (maxX-minX+1))+ minX;
//        randz = fmod(rand(), (maxZ - minZ + 1)) + minZ;
        randx = maxX - i * 10;
        randz = maxZ + i * 10;
        float randy = terrain1.getHeightOfTerrain(randx, randz) - 1.0f;
        mat = glm::translate(mat, glm::vec3(randx, randy, randz));
//        mat = glm::rotate(mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        mat = glm::scale(mat, glm::vec3(1.0f, 1.0f, 1.0f));
        treeModelMats.push_back(mat);
    }
    
    
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
//    myCamera.disable();

    // drawing loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwPollEvents();
        
        updateMovement();
        
        GLfloat x, y, z;
        glm::mat4 model, view, projection, mvp, projectionViewMatirx, skyboxProjectionViewMat;
        GLfloat angle;
        view = myCamera.getViewMat();
        angle = glm::radians(myCamera.Zoom);
        projection = glm::perspective(angle, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
        projectionViewMatirx = projection * view;
        skyboxProjectionViewMat = projection * glm::mat4(glm::mat3(view));
        
        //terrain
        //==============================
        terrainRender.addDirLight(dirLight);
        terrainRender.render(terrains, projectionViewMatirx, shadowMapRenderer.getToShadowMapMatrix(), shadowMapRenderer.getShadowMap(), myCamera);
        
        //tile
        //==============================
        model = glm::mat4();
        x = housePosx + 14.5f, z = housePosz + 4.8f;
        y = terrain1.getHeightOfTerrain(x, z) + 0.05f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(14.0f, 1.0f, 25.0f));
        tile.modelMatrix = model;
        tile.projectionViewMatrix = projectionViewMatirx;
        tileRenderer.addDirLight(dirLight);
        tileRenderer.render(tile, shadowMapRenderer.getToShadowMapMatrix(), shadowMapRenderer.getShadowMap(), myCamera);
        
        

        //prepare model
        //====================================================================================
        //====================================================================================
        
        //house
        model = glm::mat4();
        x = housePosx, z = housePosz;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
        houseModel.modelMatrix = model;
        houseModel.projectionViewMatrix = projectionViewMatirx;
        
        //puss
        model = glm::mat4();
        x = housePosx + 60.0f, z = housePosz - 10.0f;
        y = terrain1.getHeightOfTerrain(x, z) + 1.0f;
        model = glm::translate(model, glm::vec3(x, y, z));
//        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
        pussModel.modelMatrix = model;
        pussModel.projectionViewMatrix = projectionViewMatirx;
        
        //man
        model = glm::mat4();
        x = housePosx + 30.0f, z = housePosz + 10.0f;
        y = terrain1.getHeightOfTerrain(x, z) + 1.2f;
        float dis = fmod((float)glfwGetTime(), 100.0f);
        model = glm::translate(model, glm::vec3(x + dis, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1, 1, 1));
        manModel.modelMatrix = model;
        manModel.projectionViewMatrix = projectionViewMatirx;
        
        //mask cube
        model = glm::mat4();
        x = 871.5f, z = 637.5f;
        y = terrain1.getHeightOfTerrain(x, z) + 2.5f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, glm::vec3(0.3f, 4.8f, 3.1f));
        cube.modelMatrix = model;
        cube.projectionViewMatrix = projectionViewMatirx;
        
        //radio
        model = glm::mat4();
        x = housePosx + 20.0f, z = housePosz + 11.0f;
        y = terrain1.getHeightOfTerrain(x, z) + 2.0f;
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
        radioModel.modelMatrix = model;
        radioModel.projectionViewMatrix = projectionViewMatirx;
        
        //chair
        model = glm::mat4();
        x = housePosx + 20.0f, z = housePosz + 12.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
        chairModel.modelMatrix = model;
        chairModel.projectionViewMatrix = projectionViewMatirx;
        
        //table
        model = glm::mat4();
        x = housePosx + 20.0f, z = housePosz + 12.0f;
        y = terrain1.getHeightOfTerrain(x, z);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
        tableModel.modelMatrix = model;
        tableModel.projectionViewMatrix = projectionViewMatirx;
        
        //tree
        treeModel.modelMatrix = treeModelMats[0];
        treeModel.projectionViewMatrix = projectionViewMatirx;
        
        
        //skybox
        skybox.projectionViewMatrix = skyboxProjectionViewMat;
        //====================================================================================
        //====================================================================================
        
        
        
        //render shadow
        //====================================================================================
        //====================================================================================
        shadowMapRenderer.prepare(dirLight, myCamera);
        //puss
        shadowMapRenderer.render(pussModel);
        //man
        shadowMapRenderer.render(manModel);
        //house
        shadowMapRenderer.render(houseModel);
//        tree
        shadowMapRenderer.render(treeModel);
        
        //chair
        shadowMapRenderer.render(chairModel);

        shadowMapRenderer.finish();
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
//        glClear(GL_DEPTH_BUFFER_BIT);
        //====================================================================================
        //====================================================================================
        
        
        
        //render model
        //====================================================================================
        //====================================================================================
        
        //puss
        //==============================
        pussRender.addLight(pointLight, dirLight);
        pussRender.render(pussModel, myCamera);
        
        //man
        //==============================
        manRender.addLight(pointLight, dirLight);
        manRender.render(manModel, myCamera);
        
        //house
        //==============================
        houseRender.addLight(pointLight, dirLight);
        houseRender.render(houseModel, myCamera);
        
        //radio
        //==============================
        radioRender.render(radioModel, myCamera);
        
        
        //table
        //==============================
        chairRender.render(chairModel, myCamera);
        tableRender.render(tableModel, myCamera);
        
        //tree
        //==============================
            treeModel.modelMatrix = treeModelMats[0];
            treeRenderer.addLight(pointLight, dirLight);
            treeRenderer.render(treeModel, myCamera);
        

        
        
        
        //skybox
        //==============================
        glDepthFunc(GL_LEQUAL);
        skyboxRender.render(skybox);
        glDepthFunc(GL_LESS);
        
        glfwSwapBuffers(window);
    }
    
    shadowMapRenderer.cleanUp();
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
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
    if (firstMouse) {
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

//
//  Skybox.hpp
//  AnimationPro
//
//  Created by 陈主润 on 03/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "../loader/Loader.hpp"
#include "../texture/ModelTexture.hpp"

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

class Skybox {

public:
    Skybox();
    Skybox(Loader loader, vector<const char*> faces);
    
    RawModel getModel();
    ModelTexture getTexture();
    
    // transformation
    glm::mat4 projectionViewMatrix;
    
private:
    GLuint loadCubeMap(vector<const char*> faces);
    void configFaces();
    RawModel configVertexData(Loader loader);
    
    RawModel Model;
    ModelTexture Texture;
};

#endif /* Skybox_hpp */

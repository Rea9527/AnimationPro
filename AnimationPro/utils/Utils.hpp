//
//  Utils.hpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL/SOIL.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Utils {
    
public:
    Utils();
    
    static GLint loadTextureFromFile(const char* path, string directory);
    
    static glm::mat4 aiMatToGlmMat(aiMatrix4x4 mat);
    static aiMatrix4x4 GlmMatToAiMat(glm::mat4 mat);
    
    static float timeToFrame(float time);
    
    static glm::vec2 framesToTime(glm::vec2 frames);
    
    static float frameTime;

};

#endif /* Utils_hpp */

//
//  AMesh.hpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef AMesh_hpp
#define AMesh_hpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../animation/Bone.hpp"
#include "../shaders/ModelShader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

#define NUM_BONES_PER_VEREX 4


struct BoneVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    
    GLint IDs[NUM_BONES_PER_VEREX] = {0};
    float Weights[NUM_BONES_PER_VEREX] = {0};

};

struct AnimatedTexture {
    GLuint id;
    string type;
    aiString path;
};

struct AnimatedMaterial {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
    float shininess;
};


class AMesh {
public:
    
    Skeleton sceneLoaderSkeleton;
    
    vector<BoneVertex> Vertices;
    vector<AnimatedTexture> Textures;
    vector<AnimatedMaterial> Materials;
    vector<GLuint> Indices;
    
    AMesh();
    AMesh(vector<BoneVertex> vertices, vector<AnimatedTexture> textures, vector<AnimatedMaterial> materials, vector<GLuint> indices);
    
    void Draw(Shader shader, Skeleton skeleton);
    
private:
    GLuint VAO, VBO, EBO;
    
    void setUp();
    
};

#endif /* AMesh_hpp */

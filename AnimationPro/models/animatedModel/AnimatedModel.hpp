//
//  AnimatedModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 15/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef AnimatedModel_hpp
#define AnimatedModel_hpp

#include <iostream>
#include <vector>

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../mesh/Mesh.hpp"
#include "../TextureModel.hpp"
#include "Joint.hpp"
#include "../../animation/animation/Animation.hpp"

using namespace std;

class AnimatedModel {
    
public:
    AnimatedModel();
    AnimatedModel(GLchar* path, TextureModel model, Joint rootJoint, int jointCount);
    
    TextureModel getTextureModel();
    
    Joint getRootJoint();
    
    glm::mat4* getJointTransforms();
    
    void Draw(Shader shader);
    
    void clean();
    void update();
    
private:
    
    vector<Texture> Loaded_textures;
    vector<Mesh> Meshes;
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void processBones();
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    string directory;
    
    
    void addJointToArray(Joint headJoint, glm::mat4 jointMats[]);
    TextureModel textureModel;
    
    Joint rootJoint;
    int jointCount;

};

#endif /* AnimatedModel_hpp */


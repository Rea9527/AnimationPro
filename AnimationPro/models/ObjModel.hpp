//
//  ObjModel.hpp
//  glfwTest
//
//  Created by 陈主润 on 23/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ObjModel_hpp
#define ObjModel_hpp

#include <iostream>

#include "../utils/Utils.hpp"
#include "../mesh/Mesh.hpp"

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ObjModel {
    
public:
    ObjModel();
    ObjModel(GLchar* path);
    
    void Draw(Shader shader);
    void DrawInstance(Shader shader, int count);
    
    void loadInstanceTranslation(glm::mat4 modelMatrixs[], int count);
    
    int getVerticesSize();
    // transformation
    glm::mat4 modelMatrix;
    glm::mat4 projectionViewMatrix;
    
private:
    vector<Texture> Loaded_textures;
    vector<Mesh> Meshes;
    
    string directory;
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    string name;
    
};

#endif /* ObjModel_hpp */

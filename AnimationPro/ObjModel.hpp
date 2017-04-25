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
#include "Mesh.hpp"

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ObjModel {
    
public:
    ObjModel();
    ObjModel(GLchar* path);
    
    void Draw(Shader shader);
    
private:
    vector<Texture> Loaded_textures;
    vector<Mesh> Meshes;
    string directory;
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
};

#endif /* ObjModel_hpp */

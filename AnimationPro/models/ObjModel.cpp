//
//  ObjModel.cpp
//  glfwTest
//
//  Created by 陈主润 on 23/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "ObjModel.hpp"


ObjModel::ObjModel() {}

ObjModel::ObjModel(GLchar* path) {
    this->loadModel(path);
}

void ObjModel::Draw(Shader shader) {
    for (GLuint i = 0; i < this->Meshes.size(); i++) {
        this->Meshes[i].Draw(shader);
    }
}


void ObjModel::loadModel(string path) {
    Assimp::Importer importor;
    const aiScene* scene = importor.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importor.GetErrorString() << endl;
        return;
    }
    
    this->directory = path.substr(0, path.find_last_of("/"));
    this->processNode(scene->mRootNode, scene);
}

void ObjModel::processNode(aiNode *node, const aiScene *scene) {
    
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->Meshes.push_back(this->processMesh(mesh, scene));
    }

    
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh ObjModel::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    vector<Material> materials;
    
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        
        vertices.push_back(vertex);
    }
    //indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    //materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* AiMaterial = scene->mMaterials[mesh->mMaterialIndex];
        
        aiColor4D color;
        Material material;
        if (AI_SUCCESS == aiGetMaterialColor(AiMaterial, AI_MATKEY_COLOR_AMBIENT, &color)) {
            material.ambient.r = color.r;
            material.ambient.g = color.g;
            material.ambient.b = color.b;
        }
        
        if (AI_SUCCESS == aiGetMaterialColor(AiMaterial, AI_MATKEY_COLOR_DIFFUSE, &color)) {
            material.diffuse.r = color.r;
            material.diffuse.g = color.g;
            material.diffuse.b = color.b;
        }
        
        if (AI_SUCCESS == aiGetMaterialColor(AiMaterial, AI_MATKEY_COLOR_SPECULAR, &color)) {
            material.specular.r = color.r;
            material.specular.g = color.g;
            material.specular.b = color.b;
        }
        
        materials.push_back(material);
        
        
        
        vector<Texture> diffuseMaps = this->loadMaterialTextures(AiMaterial,
                                                                         aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }
    
    
    return Mesh(vertices, textures, materials, indices);
}

vector<Texture> ObjModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString path;
        mat->GetTexture(type, i, &path);
        GLboolean skip = false;
        for (GLuint j = 0; j < this->Loaded_textures.size(); j++)
        {
            if(std::strcmp(this->Loaded_textures[j].path.C_Str(), path.C_Str()) == 0)
            {
                textures.push_back(this->Loaded_textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = Utils::loadTextureFromFile(path.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = path;
            textures.push_back(texture);
            this->Loaded_textures.push_back(texture);
        }
    }
    
    return textures;
}

int ObjModel::getVerticesSize() {
    return this->Meshes[0].Vertices.size();
}


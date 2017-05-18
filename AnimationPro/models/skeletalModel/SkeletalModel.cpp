//
//  SkeletalModel.cpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "SkeletalModel.hpp"


SkeletalModel::SkeletalModel() {
    this->isAnimated = false;
}

SkeletalModel::SkeletalModel(GLchar* path) {
    this->isAnimated = false;
    this->loadModel(path);
}

void SkeletalModel::Draw(Shader shader) {
    if (this->Meshes.size() != 0) {
        skeleton = this->Meshes[0].sceneLoaderSkeleton;
    }
    
    if (isAnimated) {
        this->updateSkeleton();
    }
    
    for (GLuint i = 0; i < this->Meshes.size(); i++) {
        this->Meshes[i].Draw(shader);
    }
}


void SkeletalModel::loadModel(string path) {
    Assimp::Importer importor;
    scene = importor.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importor.GetErrorString() << endl;
        return;
    }
    
    this->recursiveNodeProcess(scene->mRootNode);
    this->animNodeProcess();
    
    globalInverseTransform = Utils::aiMatToGlmMat(scene->mRootNode->mTransformation);
    globalInverseTransform = glm::inverse(globalInverseTransform);
    
    this->directory = path.substr(0, path.find_last_of("/"));
    this->processNode(scene->mRootNode, scene);
    this->processBone();
}

void SkeletalModel::processNode(aiNode *node, const aiScene *scene) {
    
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->Meshes.push_back(this->processMesh(mesh, scene));
    }
    
    
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

AMesh SkeletalModel::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<BoneVertex> vertices;
    vector<GLuint> indices;
    vector<AnimatedTexture> textures;
    vector<glm::vec4> weights(mesh->mNumVertices, glm::vec4(0, 0, 0, 0));
    vector<glm::vec4> ids;

    
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        BoneVertex vertex;
        
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
    //bones
    for (GLuint i = 0; i < mesh->mNumBones; i++) {
        int WEIGHTS_PER_VERTEX = 4;
        
        aiBone* bone = mesh->mBones[i];
        for (int j = 0; j < bone->mNumWeights; j++) {
            aiVertexWeight weight = bone->mWeights[j];
            unsigned int vertexStart = weight.mVertexId;
            
            for (int k = 0; k < WEIGHTS_PER_VERTEX; k++) {
//                cout << k << endl;
                if (weights.at(vertexStart)[k] == 0) {
                    weights.at(vertexStart)[k] = weight.mWeight;
                    weights.at(vertexStart)[k] = i;
                    vertices.at(weight.mVertexId).Weights[k] = i;
                    vertices.at(weight.mVertexId).IDs[k] = weight.mWeight;
                    break;
                }
            }
        }
        
    }
    //materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<AnimatedTexture> diffuseMaps = this->loadMaterialTextures(material,
                                                                 aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<AnimatedTexture> specularMaps = this->loadMaterialTextures(material,
                                                                  aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return AMesh(vertices, textures, indices);
}

void SkeletalModel::recursiveNodeProcess(aiNode *node) {
    Nodes.push_back(node);
    
    for(int i = 0; i < node->mNumChildren; i++)
        recursiveNodeProcess(node->mChildren[i]);
}

// multiple animations ?????
void SkeletalModel::animNodeProcess() {
    if(scene->mNumAnimations == 0)
        return;
    
    for(int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
        NodesAnima.push_back(scene->mAnimations[0]->mChannels[i]);
}

//bones processing
void SkeletalModel::processBone() {
    for(int i = 0; i < scene->mNumMeshes; i++)
    {
        for(int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
        {
            //Here we're just storing the bone information that we loaded
            //with ASSIMP into the formats our Bone class will recognize.
            std::string b_name = scene->mMeshes[i]->mBones[j]->mName.data;
            glm::mat4 b_mat = glm::transpose(Utils::aiMatToGlmMat(scene->mMeshes[i]->mBones[j]->mOffsetMatrix));
            
            std::cout<<"Bone "<<j<<" "<<b_name<<std::endl;

            Bone bone(&this->Meshes.at(i), i, b_name, b_mat);
            bone.setNode(this->findAiNode(b_name));
            bone.setNodeAnim(this->findAiNodeAnim(b_name));
            
            if(bone.getNodeAnim() == nullptr)
                std::cout<<"No Animations were found for " + b_name<<std::endl;
            
            //Finally, we push the Bone into our vector. Yay.
            this->Bones.push_back(bone);
        }
    }
    
    
    for(int i = 0; i < this->Bones.size(); i++) {
        //Here we cycle through the existing bones and match them up with
        //their parents, the code here is pretty self explanatory.
        std::string b_name = this->Bones.at(i).getName();
        if (this->findAiNode(b_name)) {
            string parent_name = this->findAiNode(b_name)->mParent->mName.data;
            if (this->findBone(parent_name)) {
                Bone* p_bone = this->findBone(parent_name);
                this->Bones.at(i).setParentBone(p_bone);
                
                if(p_bone == nullptr)
                    std::cout<<"Parent Bone for "<<b_name<<" does not exist (is nullptr)"<<std::endl;
            }
            
        }
        
    }
    
    if(this->Meshes.size() > 0)
        this->Meshes.at(0).sceneLoaderSkeleton.init(Bones, globalInverseTransform);
}

Bone* SkeletalModel::findBone(string name) {
    for (Bone bone : this->Bones) {
        if (bone.getName() == name) {
            return &bone;
        }
    }
    return nullptr;
}

aiNode* SkeletalModel::findAiNode(string name) {
    for (aiNode* node : this->Nodes) {
        if (node->mName.data == name) {
            return node;
        }
    }
    return nullptr;
}

aiNodeAnim* SkeletalModel::findAiNodeAnim(string name) {
    for (aiNodeAnim* nodeAnim : this->NodesAnima) {
        if (nodeAnim->mNodeName.data == name) {
            return nodeAnim;
        }
    }
    return nullptr;
}

int SkeletalModel::findBoneIdByName(string name) {
    for (int i = 0; i < Bones.size(); i++) {
        if (Bones[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

//skeleton
void SkeletalModel::updateSkeleton() {
    this->skeleton.update();
}

vector<AnimatedTexture> SkeletalModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
    vector<AnimatedTexture> textures;
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
            AnimatedTexture texture;
            texture.id = Utils::loadTextureFromFile(path.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = path;
            textures.push_back(texture);
            this->Loaded_textures.push_back(texture);
        }
    }
    
    return textures;
}



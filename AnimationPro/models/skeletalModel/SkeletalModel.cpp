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

SkeletalModel::~SkeletalModel() {
//    cout << "skeletal model destroy..." << endl;
}

SkeletalModel::SkeletalModel(GLchar* path) {
    this->isAnimated = false;
    this->loadModel(path);
}

void SkeletalModel::Draw(Shader shader) {
    
    if (!this->Meshes.empty())
        this->skeleton = this->Meshes[0].sceneLoaderSkeleton;

    if (this->isAnimated) {
        this->updateSkeleton();
    }
    
    for (GLuint i = 0; i < this->Meshes.size(); i++) {
        this->Meshes[i].Draw(shader, this->skeleton);
    }
    
}


void SkeletalModel::loadModel(string path) {
    Assimp::Importer importor;
    scene = importor.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importor.GetErrorString() << endl;
        return;
    }
    
    globalInverseTransform = Utils::aiMatToGlmMat(scene->mRootNode->mTransformation);
    globalInverseTransform = glm::inverse(globalInverseTransform);
//    globalInverseTransform = glm::transpose(globalInverseTransform);

    this->directory = path.substr(0, path.find_last_of("/"));
    this->processNode(scene->mRootNode, scene);
    
    this->loadNode(scene->mRootNode);
    this->processBone();
    if (scene->HasAnimations()) {
        this->Meshes[0].sceneLoaderSkeleton.m_animations.resize(scene->mNumAnimations);
        for(unsigned int i=0; i < scene->mNumAnimations; i++){
            this->loadNodeAnim(scene->mAnimations[i], this->Meshes[0].sceneLoaderSkeleton.m_animations[i]);
            
            if(this->Meshes[0].sceneLoaderSkeleton.m_animations[i].m_name.empty())
                this->Meshes[0].sceneLoaderSkeleton.m_animations[i].m_name = "anim";
        }
    }
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
    vector<AnimatedMaterial> materials;
    vector<glm::vec4> weights(mesh->mNumVertices, glm::vec4(0, 0, 0, 0));
    vector<glm::vec4> ids(mesh->mNumVertices, glm::vec4(0, 0, 0, 0));

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
        
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = 1 - mesh->mTextureCoords[0][i].y;
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
            unsigned int vertexID = weight.mVertexId;
            for (int k = 0; k < WEIGHTS_PER_VERTEX; k++) {
                if (weights.at(vertexID)[k] == 0) {
                    weights.at(vertexID)[k] = weight.mWeight;
                    ids.at(vertexID)[k] = i;
                    vertices.at(vertexID).IDs[k] = i;
                    vertices.at(vertexID).Weights[k] = weight.mWeight;
                    break;
                }
            }
        }
        
    }
    
    
    //materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* AiMaterial = scene->mMaterials[mesh->mMaterialIndex];
        
        aiColor4D color;
        AnimatedMaterial material;
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
        


        vector<AnimatedTexture> diffuseMaps = this->loadMaterialTextures(AiMaterial,
                                                                 aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    }
    
    return AMesh(vertices, textures, materials, indices);
}

unsigned int SkeletalModel::loadNode(aiNode *node) {

    string nodeName = (string)node->mName.data;
    if (this->nodeNameMap.find(nodeName) != this->nodeNameMap.end()) return 0;
    
    unsigned int index = (unsigned int)this->Nodes.size();
    this->Nodes.push_back(BoneNodeData());
    this->Nodes[index].m_name = nodeName;
    this->Nodes[index].m_id = (unsigned int)this->Nodes.size();
    this->Nodes[index].m_parentID = (node->mParent ? nodeNameMap[node->mParent->mName.data] : 0);
    
    auto tempMat = node->mTransformation;
    tempMat.Transpose();
    this->Nodes[index].m_transform = Utils::aiMatToGlmMat(tempMat);
    
    unsigned int childIndex;
    this->nodeNameMap.insert(pair<string, unsigned int>(this->Nodes[index].m_name, this->Nodes[index].m_id));
    this->Nodes[index].m_childNameList.resize(node->mNumChildren);
    for(unsigned int i=0; i<node->mNumChildren; i++) {
        childIndex = this->loadNode(node->mChildren[i]);
        this->Nodes[index].m_childNameList[i] = childIndex;
    }
    
    return index;
}


void SkeletalModel::loadNodeAnim(aiAnimation *ptrAiAnimation, AnimationData &animation) {
    
    unsigned int i,j;
    animation.m_name = ptrAiAnimation->mName.data;
    animation.m_duration = ptrAiAnimation->mDuration;
    animation.m_ticksPerSecond = ptrAiAnimation->mTicksPerSecond;
//    cout << animation.m_duration << " " << animation.m_ticksPerSecond << endl;
    
    unsigned int npos = ptrAiAnimation->mChannels[0]->mNumPositionKeys;
    unsigned int nrot = ptrAiAnimation->mChannels[0]->mNumRotationKeys;
    
    animation.m_node.resize(ptrAiAnimation->mNumChannels);
    for (i=0; i<ptrAiAnimation->mNumChannels; i++) {
        animation.m_node[i].m_equalFrames = (ptrAiAnimation->mChannels[i]->mNumPositionKeys ==
                                             ptrAiAnimation->mChannels[i]->mNumRotationKeys);
        
        if(npos != ptrAiAnimation->mChannels[i]->mNumPositionKeys) animation.m_node[i].m_equalFrames = false;
        if(nrot != ptrAiAnimation->mChannels[i]->mNumRotationKeys) animation.m_node[i].m_equalFrames = false;
        
        animation.m_node[i].m_name = string(ptrAiAnimation->mChannels[i]->mNodeName.data);
        animation.m_nodeNameToIndexMap.insert(pair<string,unsigned int>(animation.m_node[i].m_name,i));
        
        animation.m_node[i].m_positionFrame.resize(ptrAiAnimation->mChannels[i]->mNumPositionKeys);
        for (j=0; j<ptrAiAnimation->mChannels[i]->mNumPositionKeys; j++) {
            
            animation.m_node[i].m_positionFrame[j].first = ptrAiAnimation->mChannels[i]->mPositionKeys[j].mTime;
            animation.m_node[i].m_positionFrame[j].second.x = ptrAiAnimation->mChannels[i]->mPositionKeys[j].mValue.x;
            animation.m_node[i].m_positionFrame[j].second.y = ptrAiAnimation->mChannels[i]->mPositionKeys[j].mValue.y;
            animation.m_node[i].m_positionFrame[j].second.z = ptrAiAnimation->mChannels[i]->mPositionKeys[j].mValue.z;
        }
        
        animation.m_node[i].m_rotationFrame.resize(ptrAiAnimation->mChannels[i]->mNumRotationKeys);
        for (j=0; j<ptrAiAnimation->mChannels[i]->mNumRotationKeys; j++) {
            
            animation.m_node[i].m_rotationFrame[j].first = ptrAiAnimation->mChannels[i]->mRotationKeys[j].mTime;
            animation.m_node[i].m_rotationFrame[j].second.w = ptrAiAnimation->mChannels[i]->mRotationKeys[j].mValue.w;
            animation.m_node[i].m_rotationFrame[j].second.x = ptrAiAnimation->mChannels[i]->mRotationKeys[j].mValue.x;
            animation.m_node[i].m_rotationFrame[j].second.y = ptrAiAnimation->mChannels[i]->mRotationKeys[j].mValue.y;
            animation.m_node[i].m_rotationFrame[j].second.z = ptrAiAnimation->mChannels[i]->mRotationKeys[j].mValue.z;
            
        }
        
    }
    
}

//bones processing
void SkeletalModel::processBone() {
    for(int i = 0; i < scene->mNumMeshes; i++) {
        for(int j = 0; j < scene->mMeshes[i]->mNumBones; j++) {
            //get bone name
            string b_name = scene->mMeshes[i]->mBones[j]->mName.data;
            
            glm::mat4 b_mat;
            auto tempMat = scene->mMeshes[i]->mBones[j]->mOffsetMatrix;
            b_mat = Utils::aiMatToGlmMat(tempMat);
            b_mat = glm::transpose(b_mat);

//            cout << "Bone " << i << " " << j << " " << b_name << endl;
            
            BoneNodeData node = this->findBoneNode(b_name);
            this->boneNameMap[node.m_name] = j;
            //create bone using node
            Bone bone(node);
            
            bone.localTransform = b_mat;
            
            //Finally, we push the Bone into our vector. Yay.
            this->Bones.push_back(bone);
        }
    }
    
    for (int i = 0; i < this->Bones.size(); i++) {
        for (int j = 0; j < this->Bones[i].m_childId.size(); j++) {
            
            this->Bones[i].m_childId[j] = this->boneNameMap[this->Nodes[this->Bones[i].m_childId[j]].m_name];
        }
    }
    
    if(this->Meshes.size() > 0) {
        this->Meshes[0].sceneLoaderSkeleton.init(Bones, globalInverseTransform);
    }
    
}

Bone* SkeletalModel::findBone(unsigned int id) {
    for (int i = 0; i < this->Bones.size(); i++) {
        if (this->nodeNameMap[this->Bones[i].name] == id) {
            return &this->Bones.at(i);
        }
    }
    return nullptr;
}

BoneNodeData SkeletalModel::findBoneNode(string name) {
    for (int i = 0; i < this->Nodes.size(); i++) {
        if (this->Nodes[i].m_name == name) {
            return this->Nodes.at(i);
        }
    }
    return BoneNodeData();
}


//skeleton
void SkeletalModel::updateSkeleton() {
    this->Meshes[0].sceneLoaderSkeleton.update();
}

//animation
void SkeletalModel::addAnimation(Animation& in_anim) {
    this->animations.push_back(in_anim);
}

Animation* SkeletalModel::findAnimation(std::string anim_to_find) {
    for (int i = 0; i < this->animations.size(); i++) {
        if (this->animations[i].name == anim_to_find) {
            return &this->animations[i];
        }
    }
    return nullptr;
}

void SkeletalModel::setIdleAnimation(Animation animation) {
    this->Meshes[0].sceneLoaderSkeleton.setIdleAnimation(&animation);
}

void SkeletalModel::playAnimation(Animation& anim, bool loop, bool reset_to_start) {
    this->Meshes[0].sceneLoaderSkeleton.playAnimation(anim, loop, reset_to_start);
    this->isAnimated = true;
}

void SkeletalModel::stopAnimating() {
    this->Meshes[0].sceneLoaderSkeleton.stopAnimating();
    this->isAnimated = false;
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
            cout << texture.id << " " << path.C_Str() << endl;
            texture.type = typeName;
            texture.path = path;
            textures.push_back(texture);
            this->Loaded_textures.push_back(texture);
        }
    }
    
    return textures;
}



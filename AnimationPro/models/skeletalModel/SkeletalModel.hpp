//
//  SkeletalModel.hpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef SkeletalModel_hpp
#define SkeletalModel_hpp

#include <iostream>
#include <map>

#include "../../utils/Utils.hpp"
#include "../../mesh/AMesh.hpp"
#include "../../animation/Bone.hpp"

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class SkeletalModel {
    
public:
    SkeletalModel();
    ~SkeletalModel();
    SkeletalModel(GLchar* path);
    
    void Draw(Shader shader);
    
    void setIdleAnimation(Animation animtion);
    void addAnimation(Animation& in_anim);
    Animation* findAnimation(std::string anim_to_find);
    void playAnimation(Animation& anim, bool loop = false, bool reset_to_start = false);
    void stopAnimating();
    
    Skeleton getSkeleton();
    
    bool isAnimated;
    
    // transformation
    glm::mat4 modelMatrix;
    glm::mat4 projectionViewMatrix;
    
private:
    vector<AnimatedTexture> Loaded_textures;
    vector<AMesh> Meshes;
    
    vector<BoneNodeData> Nodes;
    vector<vector<AnimationData>> NodesAnima;
    map<string, unsigned int> nodeNameMap;
    unsigned int loadNode(aiNode *node);
    void loadNodeAnim(aiAnimation *AiAnimation, AnimationData &animation);
    
    vector<Bone> Bones;
    map<string, unsigned int> boneNameMap;
    
    const aiScene* scene;
    
    string directory;
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    AMesh processMesh(aiMesh* mesh, const aiScene* scene);
    void processBone();

    
    vector<AnimatedTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    //bones
    glm::mat4 globalInverseTransform;
    Bone* findBone(unsigned int id);
    BoneNodeData findBoneNode(string name);
    
    
    virtual void updateSkeleton();
    Skeleton skeleton;
    vector<Animation> animations;
};





#endif /* SkeletalModel_hpp */

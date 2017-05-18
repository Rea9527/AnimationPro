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
    SkeletalModel(GLchar* path);
    
    void Draw(Shader shader);
    
private:
    vector<AnimatedTexture> Loaded_textures;
    vector<AMesh> Meshes;
    
    vector<aiNode*> Nodes;
    vector<aiNodeAnim*> NodesAnima;
    vector<Bone> Bones;
    
    const aiScene* scene;
    
    string directory;
    
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    AMesh processMesh(aiMesh* mesh, const aiScene* scene);
    void processBone();
    
    void recursiveNodeProcess(aiNode* node);
    void animNodeProcess();
    
    vector<AnimatedTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    //bones
    glm::mat4 globalInverseTransform;
    Bone* findBone(string name);
    aiNode* findAiNode(string name);
    aiNodeAnim* findAiNodeAnim(string name);
    int findBoneIdByName(string name);
    
    
    bool isAnimated;
    void updateSkeleton();
    Skeleton skeleton;
    vector<Animation> animations;
    void addAnimation(Animation& in_anim);
    Animation* findAnimation(std::string anim_to_find);
    void playAnimation(Animation& anim, bool loop = false, bool reset_to_start = false);
    void stopAnimating();
};





#endif /* SkeletalModel_hpp */

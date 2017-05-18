//
//  Bone.hpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Bone_hpp
#define Bone_hpp

#include <iostream>
#include <string>
#include <vector>

#include "../utils/Utils.hpp"

using namespace std;

class AMesh;
class Bone;

//skeleton
class Skeleton {
    
public:
    Skeleton();
    Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform);
    
    void init(vector<Bone> bones, glm::mat4 globalTransform);
    Bone* findBone(string name);
    void updateBoneMatsVector();
    void update();
    
private:
    vector<Bone> bones;
    glm::mat4 globalInverseTransform;
    vector<glm::mat4> boneMats;
};

//bone
class Bone {
    
public:
    
    Bone();
    Bone(AMesh* in_mesh, uint in_id, string in_name, glm::mat4 in_o_mat);
    
    glm::mat4 GetParentTransforms();
    
    string getName();
    aiNode* getNode();
    aiNodeAnim* getNodeAnim();
    glm::mat4 getLocalTransform();
    
    void setNode(aiNode* node);
    void setNodeAnim(aiNodeAnim* nodeAnim);
    void setParentBone(Bone* parent);
    
private:
    string name;
    uint id;
    AMesh *mesh;
    
    aiNode* node;
    aiNodeAnim* nodeAnim;
    
    Bone* parentBone;
    glm::mat4 parentTransform;
    glm::mat4 localTransform;
    
    Skeleton* parentSkeleton;
    
};

#endif /* Bone_hpp */

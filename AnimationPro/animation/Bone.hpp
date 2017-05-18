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
#include "./Animation.hpp"

using namespace std;

class AMesh;
class Bone;

//skeleton
class Skeleton {
    
public:
    Skeleton();
    Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform);
    
    void init(vector<Bone> bones, glm::mat4 globalInvTransform);
    
    void playAnimation(Animation &anim, bool loop, bool reset_to_start);
    void stopAnimating();
    void setIdleAnimation(Animation* anim);
    
    Bone* findBone(string name);
    void updateBoneMatsVector();
    void update();
    
private:
    vector<Bone> bones;
    glm::mat4 globalInverseTransform;
    vector<glm::mat4> boneMats;
    
    float time;
    
    float start_time;
    float end_time;
    
    Animation* active_animation;
    Animation* idle_animation;
    
    bool anim_play;
    bool anim_loop;
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
    Skeleton* getParentSkeleton();
    
    void setNode(aiNode* node);
    void setNodeAnim(aiNodeAnim* nodeAnim);
    void setParentBone(Bone* parent);
    void setParentSkeleton(Skeleton* skeleton);
    
    void updateKeyframeTransform(float time);
    
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
    
    //Keyframe Data
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;
    glm::vec3 p1;
    glm::vec3 p2;
    
    unsigned int findPosition(float time);
    glm::vec3 calcInterpolatedPosition(float time);
    unsigned int findRotation(float time);
    glm::quat calcInterpolatedRotation(float time);
    
};

#endif /* Bone_hpp */

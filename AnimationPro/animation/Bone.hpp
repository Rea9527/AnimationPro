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
#include <map>

#include "../utils/Utils.hpp"
#include "./Animation.hpp"

using namespace std;

class AMesh;
class Bone;

struct BoneNodeData {
    unsigned int m_id;
    unsigned int m_parentID;
    string m_name;
    vector<unsigned int> m_childNameList;
    glm::mat4 m_transform; //transforms from node space to parent space
};

struct AnimationNodeData {
    string m_name;
    bool m_equalFrames; //true if m_positionFrame.size() == m_rotationFrame.size()
    vector<pair<double, glm::vec3>> m_positionFrame;
    vector<pair<double, glm::vec4>> m_rotationFrame;
};

struct AnimationData {
    string m_name;
    double m_duration;
    double m_ticksPerSecond;
    map<string, unsigned int> m_nodeNameToIndexMap;
    vector<AnimationNodeData> m_node;
    
    bool hasAnim;
};

//skeleton
class Skeleton {
    
public:
    Skeleton();
    Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform);
    
    ~Skeleton();
    
    void init(vector<Bone> bones, glm::mat4 globalInvTransform);
    
    void playAnimation(Animation &anim, bool loop, bool reset_to_start);
    void stopAnimating();
    void setIdleAnimation(Animation* anim);
    
    void updateKeyframeTransform(float time);
    
    void transformBone(unsigned int boneId, const glm::mat4 &parentTransform, float time);
    void update();
    
    bool isPlaying();
    
    vector<AnimationData> m_animations;
    vector<Bone> bones;
    vector<glm::mat4> boneMats;
    
private:
    
    glm::mat4 globalInverseTransform;
    
    float time;
    
    float start_time;
    float end_time;
    
    Animation* active_animation;
    Animation* idle_animation;
    
    bool anim_play;
    bool anim_loop;
    
    //Keyframe Data
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;
    glm::vec3 p1;
    glm::vec3 p2;
    
    unsigned int findPosition(AnimationNodeData animationNode, float time);
    glm::vec3 calcInterpolatedPosition(AnimationNodeData animationNode, float time);
    unsigned int findRotation(AnimationNodeData animationNode, float time);
    glm::quat calcInterpolatedRotation(AnimationNodeData animationNode, float time);
};

//bone
class Bone {
    
public:
    
    string name;
    uint id;
    
    unsigned int m_parentId;
    Bone* parentBone;
    vector<unsigned int> m_childId;
    
    glm::mat4 m_transform;
    glm::mat4 localTransform;
    
    Bone();
    Bone(const BoneNodeData &node);
    ~Bone();
    
};

#endif /* Bone_hpp */

//
//  Bone.cpp
//  AnimationPro
//
//  Created by 陈主润 on 17/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Bone.hpp"


Bone::Bone() {
    name = "";
    id = -1;
}

Bone::Bone(const BoneNodeData &node) {
    this->name = node.m_name;
    this->m_parentId = node.m_parentID;
    this->m_childId = node.m_childNameList;
    this->m_transform = node.m_transform;
}

Bone::~Bone() { }



//skeleton

Skeleton::Skeleton() {
    time = start_time = end_time = 0;
    active_animation = nullptr;
    
    anim_loop = false;
    anim_play = false;
}

Skeleton::Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform) {
    this->init(bones, globalInvTransform);
}

Skeleton::~Skeleton() {

}

void Skeleton::init(vector<Bone> bones, glm::mat4 globalInvTransform) {
    this->bones = bones;
    this->boneMats.push_back(glm::mat4());
    
    this->globalInverseTransform = globalInvTransform;
    
    time = start_time = end_time = 0;
    active_animation = nullptr;
    idle_animation = nullptr;
    
    anim_loop = false;
    anim_play = false;

}

void Skeleton::playAnimation(Animation& anim, bool loop, bool reset_to_start)
{
    //If there's an animation currently playing
    if(active_animation != nullptr) {
        if(anim.priority < active_animation->priority)
            active_animation = &anim;
        else
            return;
    } else {
        active_animation = &anim;
    }
    
    start_time = active_animation->start_time;
    end_time = active_animation->end_time;
    
    anim_play = true;
    anim_loop = loop;

    if(reset_to_start)
        time = active_animation->start_time;
}

//This function stops animating
void Skeleton::stopAnimating() {
    time = end_time;
    active_animation = nullptr;
    anim_play = false;
}

void Skeleton::setIdleAnimation(Animation* in_anim) {
    this->idle_animation = in_anim;
}

void Skeleton::transformBone(unsigned int boneId, const glm::mat4 &parentTransform, float time) {
    if (bones.size() == 0) return;
    
    if (boneId > this->bones.size() - 1) {
        return;
    } else {
        glm::mat4 localFinalTransform = parentTransform * this->bones.at(boneId).m_transform;
        
        glm::mat4 boneMatrix = this->globalInverseTransform * localFinalTransform
        * this->bones.at(boneId).localTransform;
        
        this->boneMats.at(boneId) = boneMatrix;
        
        for (unsigned int i = 0; i < this->bones.at(boneId).m_childId.size(); i++) {
            transformBone(this->bones.at(boneId).m_childId[i], localFinalTransform, time);
        }
    }
}

void Skeleton::update() {
    
    if (!anim_play) return;
    
    time += Utils::frameTime;
    
    if(time < start_time)
        time = start_time;
    
    if(time > end_time) {
        if(anim_loop) time = start_time;
        else this->stopAnimating();
    }
    
    glm::mat4 identity(1.0f);
    this->boneMats.clear();
    this->boneMats.resize(100, identity);
    this->transformBone(0, identity, time);
    
    
    this->updateKeyframeTransform(time);
    
}

bool Skeleton::isPlaying() {
    return this->anim_play;
}

//key frames
void Skeleton::updateKeyframeTransform(float time) {
    for (AnimationData animation : this->m_animations) {
        if (animation.m_name == this->active_animation->name) {
            for (AnimationNodeData animationNode : animation.m_node) {
                pos = this->calcInterpolatedPosition(animationNode, time);
                rot = this->calcInterpolatedRotation(animationNode, time);
                scale = glm::vec3(1.0);
                
                glm::mat4 mat;
                mat = glm::translate(mat, pos);
                mat *= glm::mat4_cast(rot);
                mat = glm::scale(mat, scale);

                for (int i = 0; i < this->bones.size(); i++) {
                    if (this->bones[i].name == animationNode.m_name) {
                        this->bones[i].m_transform = mat;
                        break;
                    }
                    

                }
            }
        }
    }

}

unsigned int Skeleton::findPosition(AnimationNodeData animationNode, float time) {
    for(unsigned int i = 0 ; i < animationNode.m_positionFrame.size() - 1 ; i++) {
        if (!animationNode.m_positionFrame.empty()){
            if(time < (float)animationNode.m_positionFrame[i + 1].first)
                return i;
        }
        
    }
    return 0;
}

unsigned int Skeleton::findRotation(AnimationNodeData animationNode, float time) {
    for(unsigned int i = 0 ; i < animationNode.m_rotationFrame.size() - 1 ; i++)
    {
        //Same as with the position.
        if (!animationNode.m_rotationFrame.empty()){
            
            if(time < (float)animationNode.m_rotationFrame[i + 1].first)
                return i;
        }
    }
    return 0;
}

glm::vec3 Skeleton::calcInterpolatedPosition(AnimationNodeData animationNode, float time) {
    if (animationNode.m_positionFrame.size() == 1) {
        glm::vec3 val = animationNode.m_positionFrame[0].second;
        val = glm::normalize(val);
        return val;
    }
    
    unsigned int PositionIndex = this->findPosition(animationNode, time);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    
    //DeltaTime is the amount of time between the two keyframes.
    float DeltaTime = animationNode.m_positionFrame[NextPositionIndex].first - animationNode.m_positionFrame[PositionIndex].first;
    //the percentage
    float Factor = (time - (float)animationNode.m_positionFrame[PositionIndex].first) / DeltaTime;
    
    //The start and end positions (the position values of each of the keyframes)
    const glm::vec3 StartPosition = animationNode.m_positionFrame[PositionIndex].second;
    const glm::vec3 EndPosition = animationNode.m_positionFrame[NextPositionIndex].second;
    
    //and here we linearly interpolate between the two keyframes.
    glm::vec3 val = glm::mix(StartPosition, EndPosition, Factor);
    val = glm::normalize(val);
    
    return val;
}

glm::quat Skeleton::calcInterpolatedRotation(AnimationNodeData animationNode, float time) {
    if(animationNode.m_rotationFrame.size() == 1) {
        glm::vec4 assimp_val = animationNode.m_rotationFrame[0].second;
        glm::quat val(assimp_val.w, assimp_val.x, assimp_val.y, assimp_val.z);
        return val;
    }
    
    unsigned int RotationIndex = this->findRotation(animationNode, time);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    
    float DeltaTime = animationNode.m_rotationFrame[NextRotationIndex].first - animationNode.m_rotationFrame[RotationIndex].first;
    float Factor = (time - (float)animationNode.m_rotationFrame[RotationIndex].first) / DeltaTime;
    
    const glm::vec4& StartRotationQ = animationNode.m_rotationFrame[RotationIndex].second;
    const glm::vec4& EndRotationQ = animationNode.m_rotationFrame[NextRotationIndex].second;
    
    glm::quat r1(StartRotationQ.w, StartRotationQ.x, StartRotationQ.y, StartRotationQ.z);
    glm::quat r2(EndRotationQ.w, EndRotationQ.x, EndRotationQ.y, EndRotationQ.z);
    
    glm::quat val = glm::slerp(r1, r2, Factor);
    val = glm::normalize(val);
    
    return val;
}


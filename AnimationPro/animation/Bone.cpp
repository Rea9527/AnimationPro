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

Bone::Bone(AMesh* in_mesh, uint in_id, string in_name, glm::mat4 in_o_mat) {
    id = in_id;
    name = in_name;
    localTransform = in_o_mat;
    
    mesh = in_mesh;
    
    parentBone = nullptr;
    node = nullptr;
}

glm::mat4 Bone::GetParentTransforms() {
    Bone* b = parentBone;
    vector<glm::mat4> mats;
    
    while(b != nullptr) {
        glm::mat4 tmp_mat = Utils::aiMatToGlmMat(b->node->mTransformation);
        mats.push_back(tmp_mat);
        
        b = b->parentBone;
    }
    
    glm::mat4 concatenated_transforms;
    for(int i = (int)mats.size()-1; i >= 0; i--)
        concatenated_transforms *= mats.at(i);
    
    return concatenated_transforms;
}

//key frames
void Bone::updateKeyframeTransform(float time) {
    if(this->nodeAnim == nullptr)
        return;
    
    pos = this->calcInterpolatedPosition(time);
    rot = this->calcInterpolatedRotation(time);
    scale = glm::vec3(1.0);
    
    glm::mat4 mat;
    mat = glm::translate(mat, pos);
    mat *= glm::mat4_cast(rot);
    mat = glm::scale(mat, scale);
    
    node->mTransformation = Utils::GlmMatToAiMat(mat);
}

unsigned int Bone::findPosition(float time) {
    for(unsigned int i = 0 ; i < this->nodeAnim->mNumPositionKeys - 1 ; i++) {
        //If the time passed in is less than the time of the next
        //keyframe, then this is the keyframe we want!
        if(time < (float)this->nodeAnim->mPositionKeys[i + 1].mTime)
            return i;
    }
    return 0;
}

unsigned int Bone::findRotation(float time) {
    for(unsigned int i = 0 ; i < this->nodeAnim->mNumRotationKeys - 1 ; i++)
    {
        //Same as with the position.
        if(time < (float)this->nodeAnim->mRotationKeys[i + 1].mTime)
            return i;
    }
    return 0;
}

glm::vec3 Bone::calcInterpolatedPosition(float time) {
    if(this->nodeAnim->mNumPositionKeys == 1) {
        aiVector3D assimp_val = this->nodeAnim->mPositionKeys[0].mValue;
        glm::vec3 val(assimp_val.x, assimp_val.y, assimp_val.z);
        return val;
    }
    
    //The index of our current position, as well as the index that follows.
    //This will allow us to interpolate between the two values.
    unsigned int PositionIndex = this->findPosition(time);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    
    //DeltaTime is the amount of time between the two keyframes.
    float DeltaTime = this->nodeAnim->mPositionKeys[NextPositionIndex].mTime - this->nodeAnim->mPositionKeys[PositionIndex].mTime;
    //the percentage
    float Factor = (time - (float)this->nodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    
    //The start and end positions (the position values of each of the keyframes)
    const aiVector3D StartPosition = this->nodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D EndPosition = this->nodeAnim->mPositionKeys[NextPositionIndex].mValue;
    
    //Here we convert them to glm matrices...
    glm::vec3 p1(StartPosition.x,StartPosition.y,StartPosition.z);
    glm::vec3 p2(EndPosition.x,EndPosition.y,EndPosition.z);
    
    
    //and here we linearly interpolate between the two keyframes.
    glm::vec3 val = glm::mix(p1,p2,Factor);
    
    return val;
}

glm::quat Bone::calcInterpolatedRotation(float time) {
    if(this->nodeAnim->mNumRotationKeys == 1)
    {
        aiQuaternion assimp_val = this->nodeAnim->mRotationKeys[0].mValue;
        glm::quat val(assimp_val.w,assimp_val.x,assimp_val.y,assimp_val.z);
        return val;
    }
    
    unsigned int RotationIndex = this->findRotation(time);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    
    float DeltaTime = this->nodeAnim->mRotationKeys[NextRotationIndex].mTime - this->nodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = (time - (float)this->nodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    
    const aiQuaternion& StartRotationQ = this->nodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = this->nodeAnim->mRotationKeys[NextRotationIndex].mValue;
    
    glm::quat r1(StartRotationQ.w,StartRotationQ.x,StartRotationQ.y,StartRotationQ.z);
    glm::quat r2(EndRotationQ.w,EndRotationQ.x,EndRotationQ.y,EndRotationQ.z);
    
    glm::quat val = glm::slerp(r1, r2, Factor);
    return val;
}

string Bone::getName() {
    return this->name;
}

aiNode* Bone::getNode() {
    return this->node;
}

aiNodeAnim* Bone::getNodeAnim() {
    return this->nodeAnim;
}

glm::mat4 Bone::getLocalTransform() {
    return this->localTransform;
}

Skeleton* Bone::getParentSkeleton() {
    return this->parentSkeleton;
}

void Bone::setNode(aiNode* node) {
    this->node = node;
}

void Bone::setNodeAnim(aiNodeAnim* nodeAnim) {
    this->nodeAnim = nodeAnim;
}

void Bone::setParentBone(Bone *parent) {
    this->parentBone = parent;
}

void Bone::setParentSkeleton(Skeleton* skeleton) {
    this->parentSkeleton = skeleton;
}



//skeleton

Skeleton::Skeleton() {
    time = start_time = end_time = 0;
    active_animation = nullptr;
    
    anim_loop = false;
}

Skeleton::Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform) {
    this->init(bones, globalInvTransform);
}

void Skeleton::init(vector<Bone> bones, glm::mat4 globalInvTransform) {
    this->bones = bones;
    
    this->globalInverseTransform = globalInvTransform;
    
    time = start_time = end_time = 0;
    active_animation = nullptr;
    idle_animation = nullptr;
    
    anim_loop = false;
    
    for(int i = 0; i < bones.size(); i++)
        bones.at(i).setParentSkeleton(this);
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
    
    //The reset_to_start variable determines whether or not the animation
    //should restart upon playing.
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

Bone* Skeleton::findBone(string name) {
    for (Bone bone : this->bones) {
        if (bone.getName() == name)
            return &bone;
    }
    return nullptr;
}

void Skeleton::updateBoneMatsVector() {

    if(bones.size() == 0)
        return;
    
    boneMats.clear();

    for (int i = 0; i < 100; i++) {
        //If we are past the number of bones in the actual skeleton, we simply
        //pass in an identity matrix.
        if(i > bones.size() - 1) {
            boneMats.push_back(glm::mat4(1.0));
        } else {
            glm::mat4 concatenated_transformation = bones.at(i).GetParentTransforms()
                                        * Utils::aiMatToGlmMat(bones.at(i).getNode()->mTransformation);

            boneMats.push_back(globalInverseTransform * concatenated_transformation
                               * bones.at(i).getLocalTransform());
        }
    }
}

void Skeleton::update() {
    this->updateBoneMatsVector();
    
    if(!anim_play)
        //If we're not playing an animation, then just give up, do nothing.
        return;
    
    time += Utils::frameTime * 0.001f;
    
    if(time < start_time)
        time = start_time;
    
    if(time > end_time) {
        if(anim_loop) time = start_time;
        else this->stopAnimating();
    }
    
    for(int i = 0; i < bones.size(); i++)
        bones.at(i).updateKeyframeTransform(time);
}

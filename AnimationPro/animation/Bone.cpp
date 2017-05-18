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

void Bone::setNode(aiNode* node) {
    this->node = node;
}

void Bone::setNodeAnim(aiNodeAnim* nodeAnim) {
    this->nodeAnim = nodeAnim;
}

void Bone::setParentBone(Bone *parent) {
    this->parentBone = parent;
}



//skeleton

Skeleton::Skeleton() { }

Skeleton::Skeleton(vector<Bone> bones, glm::mat4 globalInvTransform) {
    this->bones = bones;
    this->globalInverseTransform = globalInverseTransform;
}

void Skeleton::init(vector<Bone> bones, glm::mat4 globalTransform) {
    
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
}

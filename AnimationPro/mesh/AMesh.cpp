//
//  AMesh.cpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "AMesh.hpp"


AMesh::AMesh() { }

AMesh::AMesh(vector<BoneVertex> vertices, vector<AnimatedTexture> textures, vector<GLuint> indices) {
    this->Vertices = vertices;
    this->Textures = textures;
    this->Indices = indices;
    
    this->setUp();
}

void AMesh::setUp() {
    cout << "vertices size: " << this->Vertices.size() << endl;
    cout << "textures size: " <<  this->Textures.size() << endl;
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    
    glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(BoneVertex), &this->Vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint), &this->Indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(BONE_POSITION_LOCATION);
    glVertexAttribPointer(BONE_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)0);
    
    glEnableVertexAttribArray(BONE_NORMAL_LOCATION);
    glVertexAttribPointer(BONE_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, Normal));
    
    glEnableVertexAttribArray(BONE_TEXCOORD_LOCATION);
    glVertexAttribPointer(BONE_TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, TexCoords));
    
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, IDs));
    
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, Weights));
    
    glBindVertexArray(0);
}

void AMesh::Draw(Shader shader) {
    GLuint diffuseNr = 1, specularNr = 1;
    
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        stringstream ss;
        string number;
        string name = this->Textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++;
        else if (name == "texture_specular")
            ss << specularNr++;
        number = ss.str();
        
        glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->Textures[i].id);
    }

    
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);
    
//    glUniformMatrix4fv(glGetUniformLocation(shaderID,"gBones"),
//                       parentGObj->skeleton.boneMats.size(),
//                       GL_FALSE,
//                       glm::value_ptr(parentGObj->skeleton.boneMats[0]));
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    for (GLuint i = 0; i < this->Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}






//aiMatrix4x4 AMesh::boneTransform(float TimeInSeconds, vector<aiMatrix4x4>& Transforms) {
//    aiMatrix4x4 Identity;
//    Identity.InitIdentity();
//    
//    float TicksPerSecond = m_pScene->mAnimations[0]->mTicksPerSecond != 0 ?
//    m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f;
//    float TimeInTicks = TimeInSeconds * TicksPerSecond;
//    float AnimationTime = fmod(TimeInTicks, m_pScene->mAnimations[0]->mDuration);
//    
//    ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);
//    
//    Transforms.resize(m_NumBones);
//    
//    for (uint i = 0 ; i < m_NumBones ; i++) {
//        Transforms[i] = m_BoneInfo[i].FinalTransformation;
//    }
//}


//void AMesh::readNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform)
//{
//    string NodeName(pNode->mName.data);
//    
//    const aiAnimation* pAnimation = m_pScene->mAnimations[0];
//    
//    Matrix4f NodeTransformation(pNode->mTransformation);
//    
//    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
//    
//    if (pNodeAnim) {
//        // Interpolate scaling and generate scaling transformation matrix
//        aiVector3D Scaling;
//        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
//        Matrix4f ScalingM;
//        ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);
//        
//        // Interpolate rotation and generate rotation transformation matrix
//        aiQuaternion RotationQ;
//        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
//        Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());
//        
//        // Interpolate translation and generate translation transformation matrix
//        aiVector3D Translation;
//        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
//        Matrix4f TranslationM;
//        TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);
//        
//        // Combine the above transformations
//        NodeTransformation = TranslationM * RotationM * ScalingM;
//    }
//    
//    Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;
//    
//    if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
//        uint BoneIndex = m_BoneMapping[NodeName];
//        m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation *
//        m_BoneInfo[BoneIndex].BoneOffset;
//    }
//    
//    for (uint i = 0 ; i < pNode->mNumChildren ; i++) {
//        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
//    }
//}

void AMesh::calcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    uint RotationIndex = findRotation(AnimationTime, pNodeAnim);
    uint NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}

uint AMesh::findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);
    
    for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
}

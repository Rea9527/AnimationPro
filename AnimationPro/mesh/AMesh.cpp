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

void AMesh::Draw(Shader shader, Skeleton skeleton) {
    GLuint diffuseNr = 1, specularNr = 1, ambientNr = 1;
    
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        stringstream ss;
        string number;
        string name = this->Textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++;
        else if (name == "texture_specular")
            ss << specularNr++;
        else if (name == "texture_ambient")
            ss << ambientNr;
        number = ss.str();
        
        cout << name << endl;
        glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->Textures[i].id);
    }
    
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "gBones"),
                       (GLsizei)skeleton.boneMats.size(),
                       GL_FALSE,
                       glm::value_ptr(skeleton.boneMats[0]));
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

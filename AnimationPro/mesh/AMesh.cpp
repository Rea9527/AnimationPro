//
//  AMesh.cpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "AMesh.hpp"


AMesh::AMesh() { }

AMesh::AMesh(vector<BoneVertex> vertices, vector<AnimatedTexture> textures, vector<AnimatedMaterial> materials, vector<GLuint> indices) {
    this->Vertices = vertices;
    this->Textures = textures;
    this->Materials = materials;
    this->Indices = indices;
    
    this->setUp();
}

void AMesh::setUp() {
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    
    glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(BoneVertex), &this->Vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint), &this->Indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, Normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, TexCoords));
    
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, IDs));
    
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(BoneVertex), (GLvoid*)offsetof(BoneVertex, Weights));
    glBindVertexArray(0);
}

void AMesh::Draw(Shader shader, Skeleton skeleton) {
    
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        glUniform1i(glGetUniformLocation(shader.Program, "diffuseMap"), i);
        glBindTexture(GL_TEXTURE_2D, this->Textures[i].id);
    }
    
    glUniform3fv(glGetUniformLocation(shader.Program, "material.ambient"), 1, glm::value_ptr(this->Materials[0].ambient));
    glUniform3fv(glGetUniformLocation(shader.Program, "material.diffuse"), 1, glm::value_ptr(this->Materials[0].diffuse));
    glUniform3fv(glGetUniformLocation(shader.Program, "material.specular"), 1, glm::value_ptr(this->Materials[0].specular));
    
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 32.0f);

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

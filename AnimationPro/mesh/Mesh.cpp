//
//  Mesh.cpp
//  glfwTest
//
//  Created by 陈主润 on 23/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Mesh.hpp"


Mesh::Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<Material> materials, vector<GLuint> indices) {
    this->Vertices = vertices;
    this->Textures = textures;
    this->Materials = materials;
    this->Indices = indices;
    
    this->setUp();
}

void Mesh::setUp() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    
    glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), &this->Vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint), &this->Indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::loadInstance(glm::mat4 *modelMatrixs, int count) {
    GLuint instanceBuf;
    glGenBuffers(1, &instanceBuf);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * count, modelMatrixs, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    GLsizei vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
    
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    
    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
    this->prepare(shader);
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    this->finish();
}

void Mesh::DrawInstance(Shader shader, int count) {
    this->prepare(shader);
    
    glBindVertexArray(this->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0, count);
//    glDrawElements(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    this->finish();
}

void Mesh::prepare(Shader shader) {
    GLuint diffuseNr = 1;
    
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        stringstream ss;
        string number;
        string name = this->Textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++;
        number = ss.str();
        
        glUniform1i(glGetUniformLocation(shader.Program, "tex"), i);
        glBindTexture(GL_TEXTURE_2D, this->Textures[i].id);
    }
    
    
    glUniform3fv(glGetUniformLocation(shader.Program, "material.ambient"), 1, glm::value_ptr(this->Materials[0].ambient));
    glUniform3fv(glGetUniformLocation(shader.Program, "material.diffuse"), 1, glm::value_ptr(this->Materials[0].diffuse));
    glUniform3fv(glGetUniformLocation(shader.Program, "material.specular"), 1, glm::value_ptr(this->Materials[0].specular));
    
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 32.0f);
}

void Mesh::finish() {
    for (GLuint i = 0; i < this->Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

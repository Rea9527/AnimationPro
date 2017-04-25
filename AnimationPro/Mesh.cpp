//
//  Mesh.cpp
//  glfwTest
//
//  Created by 陈主润 on 23/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Mesh.hpp"


Mesh::Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<GLuint> indices) {
    this->Vertices = vertices;
    this->Textures = textures;
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
    
    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
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
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(this->Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    for (GLuint i = 0; i < this->Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

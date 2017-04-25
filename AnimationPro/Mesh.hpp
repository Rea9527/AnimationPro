//
//  Mesh.hpp
//  glfwTest
//
//  Created by 陈主润 on 23/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id;
    string type;
    aiString path;
};

class Mesh {
public:
    vector<Vertex> Vertices;
    vector<Texture> Textures;
    vector<GLuint> Indices;
    
    Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<GLuint> indices);
    void Draw(Shader shader);
    
private:
    GLuint VAO, VBO, EBO;
    void setUp();
};

#endif /* Mesh_hpp */

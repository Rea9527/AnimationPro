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

#include "../shaders/Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
    float shininess;
};

class Mesh {
public:
    vector<Vertex> Vertices;
    vector<Texture> Textures;
    vector<Material> Materials;
    vector<GLuint> Indices;
    
    Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<Material> materials, vector<GLuint> indices);
    void Draw(Shader shader);
    void DrawInstance(Shader shader, int count);
    
    void loadInstance(glm::mat4 modelMatrixs[], int count);
    
private:
    GLuint VAO, VBO, EBO;
    void setUp();
    void prepare(Shader shader);
    void finish();
};

#endif /* Mesh_hpp */

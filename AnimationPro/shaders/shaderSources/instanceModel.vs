#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in mat4 instance;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;


uniform mat4 normalModel;
uniform mat4 projectionView;

void main() {
    
    gl_Position = projectionView * instance * vec4(position, 1.0);
    
    Normal = mat3(transpose(inverse(instance))) * normal;
    FragPos = vec3(instance * vec4(position, 1.0));
    TexCoords = texCoord;
}

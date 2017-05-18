#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in uvec4 ids;
layout (location = 4) in vec4 weights;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

out uvec4 Ids;
out vec4 Weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    Normal = vec3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0));
    TexCoords = texCoord;
    
    Ids = ids;
    Weights = weights;
}

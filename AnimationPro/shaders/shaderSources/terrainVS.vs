#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec4 ShadowCoords;

uniform mat4 model;
uniform mat4 modelView;
uniform mat4 projectionView;
uniform mat4 toShadowMapSpace;


void main() {
    vec4 worldPosition = model * vec4(position, 1.0);
    gl_Position = projectionView * worldPosition;
    
    TexCoords = texCoord;
    Normal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0));
    ShadowCoords = toShadowMapSpace * vec4(FragPos, 1.0f);
}



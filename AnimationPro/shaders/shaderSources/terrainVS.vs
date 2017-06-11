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

const float shadowDistance = 100.0;
const float transitionDistance = 10.0;

void main() {
    vec4 worldPosition = model * vec4(position, 1.0);
    gl_Position = projectionView * worldPosition;
    
    ShadowCoords = toShadowMapSpace * vec4(vec3(worldPosition), 1.0f);
    
    TexCoords = texCoord;
    Normal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0));
    
    vec4 positionRelativeToCam = modelView * vec4(position, 1.0);
    float dist = length(positionRelativeToCam.xyz);
    dist = dist - (shadowDistance - transitionDistance);
    dist = dist / transitionDistance;
    ShadowCoords.w = clamp(1.0f - dist, 0.0, 1.0f);
}



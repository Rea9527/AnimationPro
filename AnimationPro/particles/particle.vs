#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projectionView;
uniform mat4 model;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 1.0f;
    TexCoords = texCoords;
    ParticleColor = color;
    gl_Position = projectionView * model * vec4((pos * scale) + offset, 1.0);
}

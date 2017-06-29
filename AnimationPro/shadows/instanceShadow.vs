#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instance;

out vec3 pos;
out vec2 TexCoords;

uniform mat4 MVP;

uniform mat4 projectionView;

void main() {

    gl_Position = projectionView * instance * vec4(position, 1.0f);
    pos = position;
    
    TexCoords = texCoords;
}

#version 330 core

layout (location = 0) in vec3 position;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 MVP;

out vec3 pos;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    pos = position;
}

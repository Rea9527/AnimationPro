#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in ivec4 ids;
layout (location = 4) in vec4 weights;


uniform mat4 MVP;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

out vec3 pos;

void main() {
    mat4 boneTransform = gBones[ids[0]] * weights[0];
    boneTransform += gBones[ids[1]] * weights[1];
    boneTransform += gBones[ids[2]] * weights[2];
    boneTransform += gBones[ids[3]] * weights[3];
    
    vec4 Tpos = boneTransform * vec4(position, 1.0f);
    gl_Position = MVP * Tpos;
    pos = position;
}

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in ivec4 ids;
layout (location = 4) in vec4 weights;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

const int MAX_WEIGHTS = 4;
const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

uniform mat4 model;
uniform mat4 projectionView;


void main() {
    
    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);
    
    for(int i=0;i<MAX_WEIGHTS;i++){
        mat4 jointTransform = gBones[ids[i]];
        vec4 posePosition = jointTransform * vec4(position, 1.0);
        totalLocalPos += posePosition * weights[i];
        
        vec4 worldNormal = jointTransform * vec4(normal, 0.0);
        totalNormal += worldNormal * weights[i];
    }
    
    gl_Position = projectionView * model * totalLocalPos;
//    gl_Position = projectionView * model * vec4(position, 1.0f);
    Normal = totalNormal.xyz;
    TexCoords = texCoord;
    FragPos = (model * totalLocalPos).xyz;
    
//    mat4 boneTransform = gBones[ids[0]] * weights[0];
//    boneTransform += gBones[ids[1]] * weights[1];
//    boneTransform += gBones[ids[2]] * weights[2];
//    boneTransform += gBones[ids[3]] * weights[3];
//    
//    vec4 Tpos = boneTransform * vec4(position, 1.0f);
//    gl_Position = projectionView * model * Tpos;
//    vec4 BNormal = boneTransform * vec4(normal, 1.0f);
//    Normal = mat3(transpose(inverse(model))) * BNormal.xyz;
//    FragPos = vec3(model * vec4(position, 1.0));
//    TexCoords = texCoord;
}

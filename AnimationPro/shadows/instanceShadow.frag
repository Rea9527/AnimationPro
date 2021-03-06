#version 330 core

in vec3 pos;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D diffuseMap;

void main() {
    
    float alpha = texture(diffuseMap, TexCoords).a;
    if (alpha < 0.1) discard;
    
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    
}

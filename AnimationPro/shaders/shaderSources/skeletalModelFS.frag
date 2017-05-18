#version 330 core


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

in vec4 Ids;
in vec4 Weights;

out vec4 color;

struct Material {
    float shininess;
    
    sampler2D texture_specular1;
    sampler2D texture_diffuse1;
};
uniform Material material;


void main() {
//    vec4 weightColor = vec4(Weights.xyz, 1.0);
    vec4 texColor1 = texture(material.texture_diffuse1, TexCoords);
    vec4 texColor2 = texture(material.texture_specular1, TexCoords);
    color = texColor1 + texColor2;
}
#version 330 core


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct Material {
    float shininess;
    
    sampler2D texture_specular1;
    sampler2D texture_diffuse1;
    sampler2D texture_ambient1;
};
uniform Material material;

uniform vec3 viewPos;

void main() {
    vec4 texColor1 = texture(material.texture_diffuse1, TexCoords);
    vec4 texColor2 = texture(material.texture_specular1, TexCoords) * 20;
    vec4 texColor3 = texture(material.texture_ambient1, TexCoords);
    color = texColor1;
}

#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 color;

uniform vec3 viewPos;


struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;


struct PointLight {
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLights[1];

struct Material {
    float shininess;
    
    sampler2D texture_specular1;
    sampler2D texture_diffuse1;
};
uniform Material material;

bool isTransparent = false;

vec3 getDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main() {
    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = getDirLight(dirLight, norm, viewDir);
    for (int i = 0; i < 1; i++)
        result += getPointLight(pointLights[i], norm, FragPos, viewDir);
    
    color = vec4(result, 1);

}

vec3 getDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec4 texture_1 = texture(material.texture_diffuse1, TexCoords);
    vec4 texture_2 = texture(material.texture_specular1, TexCoords);
    
    if (texture_1.a < 0.1) discard;
    if (texture_2.a < 0.1) discard;
    
    
    vec3 ambient  = light.ambient * vec3(texture_1);
    vec3 diffuse  = light.diffuse * diff * vec3(texture_1);
    vec3 specular = light.specular * spec * vec3(texture_2);
    
    
    return (ambient + diffuse + specular);
}

vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    
    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    
    vec3 ambient  = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));
    
    
    float dis = length(light.pos - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
    
    return (ambient + diffuse + specular) * attenuation;
}

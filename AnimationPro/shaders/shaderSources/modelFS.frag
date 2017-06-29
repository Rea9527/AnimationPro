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
    
    vec3 specular;
    vec3 diffuse;
    vec3 ambient;
};
uniform Material material;

uniform sampler2D tex;

bool isTransparent = false;

void getDirLight(DirLight light, vec3 normal, vec3 viewDir);
void getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 ambientSum = vec3(0), diffuseSum = vec3(0), specularSum = vec3(0);

void main() {
    
    // Properties
//    vec3 norm = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);
////    
//    getDirLight(dirLight, norm, viewDir);
//    for (int i = 0; i < 1; i++)
//        getPointLight(pointLights[i], norm, FragPos, viewDir);
    
    vec4 texColor = texture(tex, TexCoords);
    if (texColor.a < 0.1) discard;
//    color = texColor * vec4(ambientSum + diffuseSum, 1.0f) + vec4(specularSum, 1.0f);
    color = texColor;

}

void getDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    
    ambientSum += ambient;
    diffuseSum += diffuse;
    specularSum += specular;
}

void getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    
    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    
    float dis = length(light.pos - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
    
    ambientSum += ambient * attenuation;
    diffuseSum += diffuse * attenuation;
    specularSum += specular * attenuation;
}

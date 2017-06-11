#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 ShadowCoords;

out vec4 color;

uniform vec3 viewPos;

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;


uniform float shininess;

uniform sampler2D bgTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform sampler2D shadowMap;


void main() {
    
    vec4 shadow = texture(shadowMap, ShadowCoords.xy);
    
    float objNearestLight = texture(shadowMap, ShadowCoords.xy).r;
    float lightFactor = 1.0f;
    if (ShadowCoords.z > objNearestLight) {
        lightFactor = 1.0f - (ShadowCoords.w * 0.4f);
    }
    
    
    vec4 blendMapColor = texture(blendMap, TexCoords);
    
    float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
    vec2 tiledCoords = TexCoords * 40;
    vec4 bgTextureColor = texture(bgTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
    vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
    vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;
    
    vec4 totalColor = bgTextureColor + rTextureColor + gTextureColor + bTextureColor;
//    color = totalColor;
    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 lightDir = normalize(-dirLight.direction);
    // Diffuse shading
    float diff = max(dot(norm, lightDir), 0.2);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // Combine results
    vec3 diffuse  = dirLight.diffuse  * diff * lightFactor;
    vec3 specular = dirLight.specular * spec;
    
    
    color = totalColor * (vec4(diffuse, 1.0f) + vec4(dirLight.ambient * lightFactor, 1.0f)) + vec4(specular, 1.0f);
//    color = vec4(vec3(objNearestLight), 1.0f);
//    color = shadow;
    
    
}




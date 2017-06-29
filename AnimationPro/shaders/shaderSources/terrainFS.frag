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


float ShadowCalculation() {
    vec3 projCoords = ShadowCoords.xyz / ShadowCoords.w;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(dirLight.direction);

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9;
    
    if(projCoords.z > 1.0)
        shadow = 0.0;
    
    return 1 - shadow;
}

void main() {
    
    vec4 blendMapColor = texture(blendMap, TexCoords);
    
    float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
    vec2 tiledCoords = TexCoords * 40;
    vec4 bgTextureColor = texture(bgTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
    vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
    vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;
    
    vec4 totalColor = bgTextureColor + rTextureColor + gTextureColor + bTextureColor;
//    color = totalColor;
        
    //get shadow
    float lightFactor = ShadowCalculation();
    
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
    vec3 diffuse  = dirLight.diffuse  * diff;
    vec3 specular = dirLight.specular * spec;
    
    
    color = totalColor * ((vec4(diffuse, 1.0f) + vec4(specular, 1.0f)) * lightFactor + vec4(dirLight.ambient, 1.0f));
    
    
}




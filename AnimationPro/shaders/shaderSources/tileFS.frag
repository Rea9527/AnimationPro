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

uniform float shininess;

uniform sampler2D tex;
uniform sampler2D shadowMap;

float ShadowCalculation() {
    // perform perspective divide
    vec3 projCoords = ShadowCoords.xyz / ShadowCoords.w;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(dirLight.direction);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
    
    return 1 - shadow;
}

void main() {
    
    vec4 totalColor = texture(tex, TexCoords);
    if (totalColor.a < 0.1) discard;
    
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
    
    
    color = totalColor * ((vec4(diffuse, 1.0f) + vec4(specular, 1.0f)) * lightFactor + vec4(dirLight.ambient, 1.0f)) ;
    
}



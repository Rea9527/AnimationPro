#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D bgTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

void main() {
    
    vec4 blendMapColor = texture(blendMap, TexCoords);
    
    float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
    vec2 tiledCoords = TexCoords * 40;
    vec4 bgTextureColor = texture(bgTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
    vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
    vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;
    
    vec4 totalColor = bgTextureColor + rTextureColor + gTextureColor + bTextureColor;
    
    color = totalColor;
    
}


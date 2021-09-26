#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct DirectionalLight
{
    sampler2D dirShadowMap;
    float ambientStrength;
    vec3 colour;
    vec3 direction;
    bool isActive;
    mat4 dirLightSpaceMatrix;
};

out VS_OUT
{
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
    vec4 DirFragPosLightSpace;
} vs_out;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform DirectionalLight dirLight;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos,1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.TexCoords = aTexCoords;    
    vs_out.DirFragPosLightSpace = dirLight.dirLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
}

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

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
    mat3 TBN;
} vs_out;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform DirectionalLight dirLight;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos,1.0));
    vec3 norm = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.TexCoords = aTexCoords;    
    vs_out.DirFragPosLightSpace = dirLight.dirLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position =  projection * view * model * vec4(aPos, 1.0);

   vec3 T = normalize(vec3(model * vec4(aTangent,   0.0)) * norm);
   vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)) * norm);
   vec3 N = normalize(vec3(model * vec4(aNormal,    0.0)) * norm);
   mat3 TBN = mat3(T, B, N);
   vs_out.TBN = TBN;

}

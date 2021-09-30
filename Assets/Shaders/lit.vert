#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;

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

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];


void main()
{
    vec4 totalPosition =  vec4(aPos,1.0f);
    vec3 localNormal = vec3(1.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * weights[i];
        localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
   }
    
    
    vs_out.FragPos = vec3(model * vec4(aPos,1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * localNormal;  
    vs_out.TexCoords = aTexCoords;    
    vs_out.DirFragPosLightSpace = dirLight.dirLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position =  projection * view * model * totalPosition;
}

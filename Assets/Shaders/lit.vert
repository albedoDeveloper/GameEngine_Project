#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;
layout (location = 5) in vec3 aTangent;
layout (location = 6) in vec3 aBitangent;

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
uniform int animate;
uniform int normalMapping;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main()
{
    vec4 totalPosition = vec4(aPos,1.0f);
    vec3 localNormal = vec3(1.0f);
    vec3 norm = vec3(1.0f);
    if(animate == 1)
    {
        totalPosition = vec4(0.0f);
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

        vs_out.FragPos = vec3(model * totalPosition);
        norm = mat3(transpose(inverse(model))) * localNormal; 
    } 
    
    else
    {
         vs_out.FragPos = vec3(model * vec4(aPos,1.0));
         norm = mat3(transpose(inverse(model))) * aNormal; 
    }

    
    vs_out.Normal = norm;
    vs_out.TexCoords = aTexCoords;    

    vs_out.DirFragPosLightSpace = dirLight.dirLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    
    if(animate == 1)
         gl_Position =  projection * view * model * totalPosition;

    else
        gl_Position =  projection * view * model * vec4(aPos,1.0f);

   //create TBN matrix
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(norm, 0.0)));
    T = normalize(T - dot(T,N) * N);
    vec3 B = cross(N,T);
    mat3 TBN = transpose(mat3(T, B, N));
    vs_out.TBN = TBN;

}

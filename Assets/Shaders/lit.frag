#version 330 core

struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct PointLight 
{
    samplerCube depthCubeMap;
    vec3 position;
    float farPlane;
  
    float ambientStrength;
    vec3 colour;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight
{
    sampler2D dirShadowMap;
    float ambientStrength;
    vec3 colour;
    vec3 direction;
    bool isActive;
};

// function declarations
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texCoords, float shadow);
vec3 CalcDirectionaLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow, vec2 texCoords);
float DirShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir);
float PointShadowCalculation(vec3 fragPos, PointLight light);

// uniforms
#define NR_POINT_LIGHTS 2 
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numOfPointLights = 0;
uniform DirectionalLight dirLight;
uniform Material material;
uniform vec3 viewPos = vec3(0,0,0);

// out
layout(location = 0) out vec4 FragColor;

// in from vertex shader
in VS_OUT
{
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
    vec4 DirFragPosLightSpace;
} vs_in;

void main()
{
    // properties
    vec3 norm = normalize(vs_in.Normal);
    vec3 viewDir = normalize(viewPos - vs_in.FragPos);
    vec3 result = vec3(0,0,0);

    if (numOfPointLights > 0)
    {
        float p1Shadow = PointShadowCalculation(vs_in.FragPos, pointLights[0]);
        result += CalcPointLight(pointLights[0], norm, vs_in.FragPos, viewDir, vs_in.TexCoords, p1Shadow); 
    }
    if (numOfPointLights > 1)
    {
        float p2Shadow = PointShadowCalculation(vs_in.FragPos, pointLights[1]);
        result += CalcPointLight(pointLights[1], norm, vs_in.FragPos, viewDir, vs_in.TexCoords, p2Shadow); 
    }

    if (dirLight.isActive)
    {
        float dirShadow = DirShadowCalculation(vs_in.DirFragPosLightSpace, norm, dirLight.direction);
        result += CalcDirectionaLight(dirLight, norm, vs_in.FragPos, viewDir, dirShadow, vs_in.TexCoords);
    }

    FragColor = vec4(result, texture(material.texture_diffuse1, vs_in.TexCoords).w);
} 

float PointShadowCalculation(vec3 fragPos, PointLight light)
{
    float bias = 0.05;

    vec3 fragToLight = fragPos - light.position; 
    float closestDepth = texture(light.depthCubeMap, fragToLight).r;
    closestDepth *=light.farPlane;  
    float currentDepth = length(fragToLight); 
    float shadowSum = currentDepth -  bias > closestDepth ? 1.0 : 0.0; 

    return shadowSum;
}

float DirShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    float biasMultiplier = 0.5f;
    float bias = max((0.005 * biasMultiplier) * (1.0 - dot(normal, lightDir)), (0.0005 * biasMultiplier));  

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5; 
    float closestDepth = texture(dirLight.dirShadowMap, projCoords.xy).r;   
    float currentDepth = projCoords.z;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    // soft shadow PCF
    vec2 texelSize = 1.0 / textureSize(dirLight.dirShadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(dirLight.dirShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    return shadow;
}


vec3 CalcDirectionaLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow, vec2 texCoords)
{
    vec3 lightDir = normalize(-light.direction);

    // ambient
    vec3 ambientColour = light.colour * light.ambientStrength;
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient  = ambientColour * vec3(texture(material.texture_diffuse1, texCoords));
    vec3 diffuse  = light.colour  * diff * vec3(texture(material.texture_diffuse1, texCoords));
    vec3 specular = light.colour * spec * vec3(texture(material.texture_specular1, texCoords));
    return (ambient + (diffuse + specular) * (1.0 - shadow));
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texCoords, float shadow)
{
    // ambient
    vec3 ambientColour = light.colour * light.ambientStrength;

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = ambientColour * vec3(texture(material.texture_diffuse1, texCoords));
    vec3 diffuse  = light.colour  * diff * vec3(texture(material.texture_diffuse1, texCoords));
    vec3 specular = light.colour * spec * vec3(texture(material.texture_specular1, texCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + (diffuse + specular) * (1.0 - shadow));
} 

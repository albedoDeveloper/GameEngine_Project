#version 330 core

struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct PointLight 
{
    vec3 position;
  
    float ambientStrength;
    vec3 colour;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight
{
    float ambientStrength;
    vec3 colour;
    vec3 direction;
};

// function declarations
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirectionaLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow);
float ShadowCalculation(vec4 fragPosLightSpacen, vec3 normal, vec3 lightDir);

#define NR_POINT_LIGHTS 3 
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numOfPointLights;

uniform DirectionalLight dirLight;
uniform bool dirLightActive;

layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;
  
uniform Material material;
uniform sampler2D shadowMap;
uniform vec3 viewPos;

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result;

    float shadow = ShadowCalculation(FragPosLightSpace, norm, dirLight.direction);

    for(int i = 0; i < numOfPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
    
    if (dirLightActive)
        result += CalcDirectionaLight(dirLight, norm, FragPos, viewDir, shadow);

    FragColor = vec4(result, texture(material.texture_diffuse1, TexCoords).w);
} 


float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    float biasMultiplier = 0.5f;
    float bias = max((0.005 * biasMultiplier) * (1.0 - dot(normal, lightDir)), (0.0005 * biasMultiplier));  

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5; 
    float closestDepth = texture(shadowMap, projCoords.xy).r;   
    float currentDepth = projCoords.z;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    // soft shadow PCF
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    return shadow;
}


vec3 CalcDirectionaLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow)
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
    vec3 ambient  = ambientColour * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.colour  * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.colour * spec * vec3(texture(material.texture_specular1, TexCoords));
    return (ambient + (diffuse + specular) * (1.0 - shadow));
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // ambient
    vec3 ambientColour = light.colour * light.ambientStrength;

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = ambientColour * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.colour  * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.colour * spec * vec3(texture(material.texture_specular1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

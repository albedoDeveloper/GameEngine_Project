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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

#define NR_POINT_LIGHTS 3 
uniform PointLight pointLights[NR_POINT_LIGHTS];

layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
  
uniform Material material;
uniform vec3 viewPos;
uniform int numOfPointLights;

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result;

    for(int i = 0; i < numOfPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
    
    FragColor = vec4(result, texture(material.texture_diffuse1, TexCoords).w);
} 

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
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
    vec3 ambient  = ambientColour  * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse  = light.colour  * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.colour * spec * vec3(texture(material.texture_specular1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

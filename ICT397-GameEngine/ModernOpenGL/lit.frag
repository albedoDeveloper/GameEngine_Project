#version 330 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
  
uniform Light light;  
uniform Material material;
uniform vec3 ambientLightColor;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoords).rgb;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * texture(material.texture_diffuse1, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoords).rgb;

    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;  

    vec3 result = (ambient + diffuse + specular); 
    
    FragColor = vec4(result, texture(material.texture_diffuse1, TexCoords).w);
}

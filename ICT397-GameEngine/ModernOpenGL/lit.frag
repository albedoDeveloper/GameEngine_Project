#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;
uniform vec3 viewPos;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 whitelightpos;
uniform vec3 lightColor1;
uniform vec3 lightColor2;
uniform vec3 whitelightColor;

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 result;
    float spec;
    vec3 specular;
    vec3 ambient = whitelightColor * 0.03;
    vec3 lightDir;
    float diff;
    float distance;
    float attenuation;
    vec3 diffuse;
    float specularStrength = 0.9;
    vec3 reflectDir;

    ////light 1
    //lightDir = normalize(lightPos1 - FragPos);
    //diff = max(dot(norm, lightDir), 0.0);
    //diffuse = diff * lightColor1;
    //reflectDir = reflect(-lightDir, norm);
    //spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //specular = specularStrength * spec * lightColor1;
    //distance = length(lightPos1 - FragPos);
    //attenuation = 1.0 / (1 + 0.22 * distance + 0.20 * (distance * distance));
    //diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    //result += (diffuse + specular) * vec3(texture(texture_diffuse1, TexCoords));

    ////light 2
    //lightDir = normalize(lightPos2 - FragPos);
    //diff = max(dot(norm, lightDir), 0.0);
    //diffuse = diff * lightColor2;
    //reflectDir = reflect(-lightDir, norm);
    //spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //specular = specularStrength * spec * lightColor2;
    //distance = length(lightPos1 - FragPos);
    //attenuation = 1.0 / (1 + 0.7 * distance + 0.8 * (distance * distance));
    //diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    //result += (diffuse + specular) * vec3(texture(texture_diffuse1, TexCoords)); 

    //white light
    lightDir = normalize(whitelightpos - FragPos);
    diff = max(dot(norm, lightDir), 0.0);
    diffuse = diff * whitelightColor;
    reflectDir = reflect(-lightDir, norm);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    specular = specularStrength * spec * whitelightColor;
    distance = length(whitelightpos - FragPos);
    attenuation = 1.0 / (1 + 0.7 * distance + 0.8 * (distance * distance));
    diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    result += (diffuse + specular + ambient) * vec3(texture(texture_diffuse1, TexCoords)); 
    
    FragColor = vec4(result, texture(texture_diffuse1, TexCoords).w);
}

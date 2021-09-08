#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 whitelightpos;
uniform vec3 lightColor1;
uniform vec3 lightColor2;
uniform vec3 whitelightColor;

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 result;

    // phase 2: Point lights
    vec3 lightDir = normalize(lightPos1 - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    float distance = length(lightPos1 - FragPos);
    float attenuation = 1.0 / (1 + 0.07 * distance + 0.017 * (distance * distance));
    diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    result += lightColor1 * diff * vec3(texture(texture_diffuse1, TexCoords));

    lightDir = normalize(lightPos2 - FragPos);
    diff = max(dot(Normal, lightDir), 0.0);
    distance = length(lightPos2 - FragPos);
    attenuation = 1.0 / (1 + 0.07 * distance + 0.017 * (distance * distance));
    diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    result += lightColor2 * diff * vec3(texture(texture_diffuse1, TexCoords));

    lightDir = normalize(whitelightpos - FragPos);
    // attenuation
    distance = length(whitelightpos - FragPos);
    attenuation = 1.0 / (1 + 0.7 * distance + 1.8 * (distance * distance));
    diff = max(dot(Normal, lightDir), 0.0) * attenuation;
    result += whitelightColor * diff * vec3(texture(texture_diffuse1, TexCoords));

    //result += CalcPointLight(lightPos2, norm, FragPos, lightColor2, TexCoords);     
    
    FragColor = vec4(result, texture(texture_diffuse1, TexCoords).w);
}

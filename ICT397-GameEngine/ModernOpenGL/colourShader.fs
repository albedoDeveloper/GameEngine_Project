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
    result += lightColor1 * diff * vec3(texture(texture_diffuse1, TexCoords));

    lightDir = normalize(lightPos2 - FragPos);
    diff = max(dot(Normal, lightDir), 0.0);
    result += lightColor2 * diff * vec3(texture(texture_diffuse1, TexCoords));

    lightDir = normalize(whitelightpos - FragPos);
    diff = max(dot(Normal, lightDir), 0.0);
    result += whitelightColor * diff * vec3(texture(texture_diffuse1, TexCoords));

    //result += CalcPointLight(lightPos2, norm, FragPos, lightColor2, TexCoords);     
    
    FragColor = vec4(result, texture(texture_diffuse1, TexCoords).w);
}

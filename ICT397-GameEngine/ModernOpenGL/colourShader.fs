#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{    
    vec3 texColor = texture(texture_diffuse1, TexCoords).xyz;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambientLightColor + diffuse) * texColor;
    FragColor = vec4(result, texture(texture_diffuse1, TexCoords).w);
}

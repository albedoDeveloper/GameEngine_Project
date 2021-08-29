#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;

void main()
{    
    vec3 texColor = texture(texture_diffuse1, TexCoords).xyz;
    //FragColor = vec4(ambientLightColor * texColor, 1.0);
    vec3 lightpos = vec3(-20,0,0); //temp
    vec3 lightColor = vec3(1,1,1); //temp
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightpos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambientLightColor + diffuse) * texColor;
    FragColor = vec4(result, 1.0);
}

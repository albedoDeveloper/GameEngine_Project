#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;

void main()
{    
    vec3 texColor = texture(texture_diffuse1, TexCoords).xyz;
    FragColor = vec4(ambientLightColor * texColor, 1.0);
}

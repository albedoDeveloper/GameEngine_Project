#version 330 core

struct Material 
{
    sampler2D texture_diffuse1;
};

layout (location = 0) out vec4 FragColor;

uniform Material material;

in vec2 TexCoords;
in vec3 Normal;

void main()
{   
    FragColor = texture(material.texture_diffuse1, TexCoords);
}

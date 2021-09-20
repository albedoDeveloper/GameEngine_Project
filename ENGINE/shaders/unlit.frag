#version 330 core

struct Material 
{
    sampler2D texture_diffuse1;
};

uniform Material material;
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main()
{   
    FragColor = texture(material.texture_diffuse1, TexCoords);
}

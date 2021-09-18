#version 330 core
out vec4 FragColour;

uniform vec3 ourColour;

void main()
{
   FragColour = vec4(ourColour,1.0f);
}

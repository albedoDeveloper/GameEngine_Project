#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientLightColor;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightColor1;
uniform vec3 lightColor2;

//vec3 CalcPointLight(vec3 lightPos, vec3 normal, vec3 fragPos, vec3 diffuseColor, vec2 TexCoords)
//{
//    vec3 lightDir = normalize(lightPos - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // attenuation
//    float distance = length(lightPos - fragPos);
//    //float attenuation = 1.0 / (light.constant + light.linear * distance + 
//  		//	     light.quadratic * (distance * distance));    
//    // combine results
//    //vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse  = diffuseColor  * diff * vec3(texture(diffuseColor, TexCoords));
//    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    //ambient  *= attenuation;
//    //diffuse  *= attenuation;
//    //specular *= attenuation;
//    return diffuse;
//}

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

    //result += CalcPointLight(lightPos2, norm, FragPos, lightColor2, TexCoords);     
    
    FragColor = vec4(result, texture(texture_diffuse1, TexCoords).w);
}

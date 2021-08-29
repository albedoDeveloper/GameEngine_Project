#pragma once
#include <glew/GL/glew.h>
#include <glm/glm/glm.hpp>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>



class Shader
{

    void CreateShaders(unsigned int& shadername, const GLchar* const* actualShader, int typeOfShader);
    void ShaderLinking(unsigned int& shadername, unsigned int& vertexShader);
    
    public:
        std::string shaderName;
        unsigned int ID;
        bool useShaderForLoop();
        Shader(const char* vertexPath, const char* fragmentPath);

        void setShaderBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setShaderInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setShaderFloat(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setVec4(const std::string& name, const glm::vec4& value) const
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }        
        void setVec3(const std::string& name, const glm::vec3& value) const
        {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setMat4(const std::string& name, const glm::mat4& mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
};


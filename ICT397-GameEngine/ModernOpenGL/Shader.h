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
#include "../Transform.h"
#include "../Matrix4f.h"

class Shader
{
public:
	
	/// <summary>
	/// The shadername id of the shader
	/// </summary>
	std::string shaderName;
	/// <summary>
	/// Contains the opengl ID of the shader
	/// </summary>
	unsigned int ID;

	/// <summary>
	/// Sets this shader object to the current opengl shader instance
	/// </summary>
	virtual void Use() const;
	
	/// /// <summary>
	/// Creates the shader and sets the vertex shader file and the fragment shader file to it, based upon the user
	/// </summary>
	/// <param name="vertexPath"></param>
	/// <param name="fragmentPath"></param>
	Shader(const char *vertexPath, const char *fragmentPath);

	/// <summary>
	/// Sets a global bool uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	
	/// <summary>
	/// Sets a global int uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	/// <summary>
	/// Sets a global vector4 uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	//void SetVec4(const std::string &name, const glm::vec4 &value) const
	//{
	//	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	//}
	
	/// <summary>
	/// Sets a global vector 3 uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetVec3(const std::string &name, Vector3f value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value.ValuePtr());
	}
	
	/// <summary>
	/// Sets a global matrix 4x4 uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetMat4(const std::string &name, Matrix4f mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.ValuePtr());
	}

private:
	/// <summary>
	/// Sets a global vector uniform in the shader
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void CreateShaders(unsigned int &shadername, const GLchar *const *actualShader, int typeOfShader);
	void ShaderLinking(unsigned int &shadername, unsigned int &vertexShader);
};

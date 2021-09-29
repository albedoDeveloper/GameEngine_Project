/*****************************************************************//**
 * \file   Shader.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

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

	/**
	 * shader class.
	 */
class Shader
{
public:
		/// /// <summary>
		/// Creates the shader and sets the vertex shader file and the fragment shader file to it, based upon the user
		/// </summary>
		/// <param name="vertexPath"></param>
		/// <param name="fragmentPath"></param>
	Shader(const char *vertexPath, const char *fragmentPath);

	Shader(const char *vertexPath, const char *geometryPath, const char *fragmentPath);

		/// <summary>
		/// Sets this shader object to the current opengl shader instance
		/// </summary>
	virtual void Use() const;

		/// <summary>
		/// Sets a global bool uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void SetBoolUniform(const std::string &name, bool value) const;

		/// <summary>
		/// Sets a global int uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void SetIntUniform(const std::string &name, int value) const;

		/// <summary>
		/// Sets a global vector4 uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void SetFloatUniform(const std::string &name, float value) const;

		/**
		 * sec vec4 uniform for this shader program.
		 *
		 * \param name
		 * \param value
		 */
	void SetVec4Uniform(const std::string &name, const glm::vec4 &value) const;

		/**
		 * sec vec3 uniform for this shader program.
		 *
		 * \param name
		 * \param value
		 */
	void SetVec3Uniform(const std::string &name, Vector3f value) const;

		/// <summary>
		/// Sets a global matrix 4x4 uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void SetMat4Uniform(const std::string &name, Matrix4f mat) const;

	void SetMat4UniformTrue(const std::string& name, Matrix4f mat) const;

		/**
		 * get shader name.
		 *
		 * \return
		 */
	std::string GetShaderName() const;

		/**
		 * set shader name.
		 *
		 * \param shaderName
		 */
	void SetShaderName(const std::string &shaderName);

		/**
		 * get id.
		 *
		 * \return
		 */
	unsigned int GetID() const;

		/**
		 * set id.
		 *
		 * \param ID
		 */
	void SetID(unsigned int ID);

private:
		/// <summary>
		/// Sets a global vector uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void CreateShaders(unsigned int &shadername, const char *const *actualShader, int typeOfShader);

		/// <summary>
		/// Sets a global vector uniform in the shader
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
	void ShaderLinking(unsigned int &vertexShader, unsigned int &fragShader);

	void ShaderLinking(unsigned int &vertexShader, unsigned &geometryShader, unsigned int &fragShader);

		/// <summary>
		/// The shadername id of the shader
		/// </summary>
	std::string m_shaderName;

		/// <summary>
		/// Contains the opengl ID of the shader
		/// </summary>
	unsigned int m_ID;
};

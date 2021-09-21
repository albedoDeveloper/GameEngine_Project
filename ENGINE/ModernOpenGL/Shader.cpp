#include "Shader.h"
#include "../Utility.h"
#include <iostream>
#include <glad/glad.h>

void Shader::Use() const
{
	glUseProgram(m_ID); CHECK_GL_ERROR;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	//Variables to open the shader file
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// convert stream into string
		vertexShaderCode = vShaderStream.str();
		fragmentShaderCode = fShaderStream.str();

		const char *vShaderCode = vertexShaderCode.c_str();
		const char *fShaderCode = fragmentShaderCode.c_str();

		unsigned int fragmentShader;
		unsigned int vertexShader;

		CreateShaders(vertexShader, &vShaderCode, 0);
		CreateShaders(fragmentShader, &fShaderCode, 2);
		ShaderLinking(vertexShader, fragmentShader);
	}


	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

Shader::Shader(const char *vertexPath, const char *geometryPath, const char *fragmentPath)
{
	//Variables to open the shader file
	std::string vertexShaderCode;
	std::string geomShaderCode;
	std::string fragmentShaderCode;
	std::ifstream vShaderFile;
	std::ifstream gShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexPath);
		gShaderFile.open(geometryPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, gShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		gShaderFile.close();
		fShaderFile.close();

		// convert stream into string
		vertexShaderCode = vShaderStream.str();
		geomShaderCode = gShaderStream.str();
		fragmentShaderCode = fShaderStream.str();

		const char *vShaderCode = vertexShaderCode.c_str();
		const char *gShaderCode = geomShaderCode.c_str();
		const char *fShaderCode = fragmentShaderCode.c_str();

		unsigned int fragmentShader;
		unsigned int geomShader;
		unsigned int vertexShader;

		CreateShaders(vertexShader, &vShaderCode, 0);
		CreateShaders(geomShader, &gShaderCode, 1);
		CreateShaders(fragmentShader, &fShaderCode, 2);
		ShaderLinking(vertexShader, geomShader, fragmentShader);
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::SetBoolUniform(const std::string &name, bool value) const
{
	glUseProgram(m_ID); CHECK_GL_ERROR;
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str()); CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetBoolUniform(): invalid uniform name: " << name << std::endl;
	}
	glUniform1i(uniformLoc, (int)value); CHECK_GL_ERROR;
}

void Shader::SetIntUniform(const std::string &name, int value) const
{
	glUseProgram(m_ID); CHECK_GL_ERROR;
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str()); CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetIntUniform(): invalid uniform name: " << name << std::endl;
	}
	glUniform1i(uniformLoc, value); CHECK_GL_ERROR;
}

void Shader::SetFloatUniform(const std::string &name, float value) const
{
	glUseProgram(m_ID);
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str());
	CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetFloatUniform(): invalid uniform name: " << name << std::endl;
	}
	glUniform1f(uniformLoc, value);
	CHECK_GL_ERROR
}

void Shader::SetVec4Uniform(const std::string &name, const glm::vec4 &value) const
{
	glUseProgram(m_ID);
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str());
	CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetVec4Uniform(): invalid uniform name: " << name << std::endl;
	}
	glUniform4fv(uniformLoc, 1, &value[0]);
	CHECK_GL_ERROR
}

void Shader::SetVec3Uniform(const std::string &name, Vector3f value) const
{
	glUseProgram(m_ID); CHECK_GL_ERROR;
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str()); CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetVec3Uniform(): invalid uniform name: " << name << std::endl;
	}
	glUniform3fv(uniformLoc, 1, value.ValuePtr()); CHECK_GL_ERROR
}

void Shader::SetMat4Uniform(const std::string &name, Matrix4f mat) const
{
	glUseProgram(m_ID); CHECK_GL_ERROR;
	int uniformLoc = glGetUniformLocation(m_ID, name.c_str()); CHECK_GL_ERROR;
	if (uniformLoc == -1)
	{
		std::cerr << "[ERROR] SetMat4Uniform(): invalid uniform name: " << name << std::endl;
	}
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, mat.ValuePtr()); CHECK_GL_ERROR;
}

void Shader::CreateShaders(unsigned int &shadername, const char *const *actualShader, int typeOfShader)
{
	int  success;
	std::string infoLog;

	//Determine the type of shader
	if (typeOfShader == 0)
	{
		shadername = glCreateShader(GL_VERTEX_SHADER); CHECK_GL_ERROR;
	}
	else if (typeOfShader == 1)
	{
		shadername = glCreateShader(GL_GEOMETRY_SHADER); CHECK_GL_ERROR;
	}
	else if (typeOfShader == 2)
	{
		shadername = glCreateShader(GL_FRAGMENT_SHADER); CHECK_GL_ERROR;
	}
	else
	{
		std::cerr << "[Error] in function Shader::CreateShader | typeOfShader invalid\n";
	}

	glShaderSource(shadername, 1, actualShader, NULL); CHECK_GL_ERROR;
	glCompileShader(shadername); CHECK_GL_ERROR;
	glGetShaderiv(shadername, GL_COMPILE_STATUS, &success); CHECK_GL_ERROR;

	if (!success)
	{
		glGetShaderInfoLog(shadername, 512, NULL, infoLog.data()); CHECK_GL_ERROR;
		std::cout << "ERROR::SHADER::" << typeOfShader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::ShaderLinking(unsigned int &vertexShader, unsigned int &fragmentShader)
{
	int  success;
	char infoLog[512];

	m_ID = glCreateProgram(); CHECK_GL_ERROR;

	glAttachShader(m_ID, vertexShader); CHECK_GL_ERROR;
	glAttachShader(m_ID, fragmentShader); CHECK_GL_ERROR;
	glLinkProgram(m_ID); CHECK_GL_ERROR;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success); CHECK_GL_ERROR;

	if (!success)
	{
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog); CHECK_GL_ERROR;
		std::cout << "ERROR::SHADER::LINKER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::ShaderLinking(unsigned int &vertex, unsigned &geometry, unsigned int &frag)
{
	int  success;
	char infoLog[512];

	m_ID = glCreateProgram(); CHECK_GL_ERROR;

	glAttachShader(m_ID, vertex); CHECK_GL_ERROR;
	glAttachShader(m_ID, geometry); CHECK_GL_ERROR;
	glAttachShader(m_ID, frag); CHECK_GL_ERROR;
	glLinkProgram(m_ID); CHECK_GL_ERROR;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success); CHECK_GL_ERROR;

	if (!success)
	{
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog); CHECK_GL_ERROR;
		std::cout << "ERROR::SHADER::LINKER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

std::string Shader::GetShaderName() const
{
	return m_shaderName;
}

void Shader::SetShaderName(const std::string &shaderName)
{
	m_shaderName = shaderName;
}

unsigned int Shader::GetID() const
{
	return m_ID;
}

void Shader::SetID(unsigned int m_ID)
{
	m_ID = m_ID;
}

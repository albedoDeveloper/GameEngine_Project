#include <glew/GL/glew.h>
#include "Shader.h"


void Shader::Use() const
{
	glUseProgram(m_ID);
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
		CreateShaders(fragmentShader, &fShaderCode, 1);
		ShaderLinking(vertexShader, fragmentShader);
		SetBoolUniform("dirLightActive", false);
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
		CreateShaders(fragmentShader, &fShaderCode, 1);
		ShaderLinking(vertexShader, fragmentShader);
		SetBoolUniform("dirLightActive", false);
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::SetBoolUniform(const std::string &name, bool value) const
{
	glUseProgram(m_ID);
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::SetIntUniform(const std::string &name, int value) const
{
	glUseProgram(m_ID);
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetFloatUniform(const std::string &name, float value) const
{
	glUseProgram(m_ID);
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetVec4Uniform(const std::string &name, const glm::vec4 &value) const
{
	glUseProgram(m_ID);
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3Uniform(const std::string &name, Vector3f value) const
{
	glUseProgram(m_ID);
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, value.ValuePtr());
}

void Shader::SetMat4Uniform(const std::string &name, Matrix4f mat) const
{
	glUseProgram(m_ID);
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, mat.ValuePtr());
}

void Shader::CreateShaders(unsigned int &shadername, const GLchar *const *actualShader, int typeOfShader)
{
	int  success;
	std::string infoLog;

	//Determine the type of shader
	if (typeOfShader == 0)
		shadername = glCreateShader(GL_VERTEX_SHADER);
	else if (typeOfShader == 1)
		shadername = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shadername, 1, actualShader, NULL);
	glCompileShader(shadername);
	glGetShaderiv(shadername, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shadername, 512, NULL, infoLog.data());
		std::cout << "ERROR::SHADER::" << typeOfShader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::ShaderLinking(unsigned int &vertexShader, unsigned int &fragmentShader)
{
	int  success;
	char infoLog[512];

	m_ID = glCreateProgram();

	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
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

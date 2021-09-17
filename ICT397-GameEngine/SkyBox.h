#pragma once
#include "ModernOpenGL/AModel.h"
#include "ModernOpenGL/Shader.h"

class SkyBox
{
public:
	void CreateSkybox(std::vector<std::string> skyBoxFaces);
	void DrawSkybox(const glm::mat4 &persepective, const glm::mat4 &view);
	void CreateVAOandVBO();

private:
	unsigned texID, VAO, VBO;
	Shader *skyBoxShader = nullptr;
	std::vector<float> skyboxVertices = {
		-1000.0f,  1000.0f, -1000.0f,
		-1000.0f, -1000.0f, -1000.0f,
		1000.0f, -1000.0f, -1000.0f,
		1000.0f, -1000.0f, -1000.0f,
		1000.0f,  1000.0f, -1000.0f,
		-1000.0f,  1000.0f, -1000.0f,

		-1000.0f, -1000.0f,  1000.0f,
		-1000.0f, -1000.0f, -1000.0f,
		-1000.0f,  1000.0f, -1000.0f,
		-1000.0f,  1000.0f, -1000.0f,
		-1000.0f,  1000.0f,  1000.0f,
		-1000.0f, -1000.0f,  1000.0f,

		1000.0f, -1000.0f, -1000.0f,
		1000.0f, -1000.0f,  1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		1000.0f,  1000.0f, -1000.0f,
		1000.0f, -1000.0f, -1000.0f,

		-1000.0f, -1000.0f,  1000.0f,
		-1000.0f,  1000.0f,  1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		1000.0f, -1000.0f,  1000.0f,
		-1000.0f, -1000.0f,  1000.0f,

		-1000.0f,  1000.0f, -1000.0f,
		1000.0f,  1000.0f, -1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		1000.0f,  1000.0f,  1000.0f,
		-1000.0f,  1000.0f,  1000.0f,
		-1000.0f,  1000.0f, -1000.0f,

		-1000.0f, -1000.0f, -1000.0f,
		-1000.0f, -1000.0f,  1000.0f,
		1000.0f, -1000.0f, -1000.0f,
		1000.0f, -1000.0f, -1000.0f,
		-1000.0f, -1000.0f,  1000.0f,
		1000.0f, -1000.0f,  1000.0f
	};
};

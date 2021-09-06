#include "SkyBox.h"
#include <stbi_image/stb_image.h>

void SkyBox::CreateSkybox(std::vector<std::string> skyBoxFaces)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < skyBoxFaces.size(); i++)
	{
		unsigned char* data = stbi_load(skyBoxFaces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}

		else
		{
			std::cout << "Failed to load skybox texture: " << skyBoxFaces[i] << std::endl;
			stbi_image_free(data);
		}

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	skyBoxShader = new Shader("../ICT397-GameEngine/ModernOpenGL/skyBoxVertexShader.vs", "../ICT397-GameEngine/ModernOpenGL/skyBoxColourShader.fs");
	CreateVAOandVBO();
}

void SkyBox::DrawSkybox(glm::mat4 persepective, glm::mat4 view)
{
	glDepthMask(GL_FALSE);
	skyBoxShader->useShaderForLoop();
	skyBoxShader->setMat4("projection", persepective);
	skyBoxShader->setMat4("view", glm::mat4(glm::mat3(view)));
	
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);

}

void SkyBox::CreateVAOandVBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), &skyboxVertices.data()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glBindVertexArray(0);
}



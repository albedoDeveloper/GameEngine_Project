#include "SkyBox.h"
#include <stbi_image/stb_image.h>

void SkyBox::CreateSkybox(std::vector<std::string> textures)
{
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		unsigned char *data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}

		else
		{
			std::cout << "Failed to load skybox texture: " << textures[i] << std::endl;
			stbi_image_free(data);
		}

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	skyBoxShader = new Shader("./shaders/simple.vert", "./shaders/skyBox.frag");
	CreateVAOandVBO();
}

void SkyBox::DrawSkybox(Matrix4f projection, Matrix4f view, Shader &shader)
{
	glDepthMask(GL_FALSE);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	shader.Use();
	shader.SetMat4Uniform("projection", projection);
	shader.SetMat4Uniform("view", view);

	glBindVertexArray(m_VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void SkyBox::DrawSkybox(Matrix4f projection, Matrix4f view)
{
	glDepthMask(GL_FALSE);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	skyBoxShader->Use();
	skyBoxShader->SetMat4Uniform("projection", projection);
	skyBoxShader->SetMat4Uniform("view", view);

	glBindVertexArray(m_VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void SkyBox::CreateVAOandVBO()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), &skyboxVertices.data()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glBindVertexArray(0);
}

#include "SkyBox.h"
#include <stbi_image/stb_image.h>
#include "Utility.h"
#include <glad/glad.h>

void SkyBox::CreateSkybox(std::vector<std::string> textures)
{
	glGenTextures(1, &m_texID); CHECK_GL_ERROR();
	glActiveTexture(GL_TEXTURE0); CHECK_GL_ERROR();
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID); CHECK_GL_ERROR();
	int width, height, nrChannels;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		unsigned char *data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data
			);
			CHECK_GL_ERROR();
			stbi_image_free(data);
		}

		else
		{
			std::cout << "Failed to load skybox texture: " << textures[i] << std::endl;
			stbi_image_free(data);
		}

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); CHECK_GL_ERROR();

	skyBoxShader = new Shader("../Assets/Shaders/skybox.vert", "../Assets/Shaders/skybox.frag");
	CreateVAOandVBO();
}

void SkyBox::DrawSkybox(Matrix4f projection, Matrix4f view)
{
	glDepthMask(GL_FALSE); CHECK_GL_ERROR();
	glEnable(GL_CULL_FACE); CHECK_GL_ERROR();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); CHECK_GL_ERROR();
	skyBoxShader->SetMat4Uniform("projection", projection);
	view.RemoveTranslation();
	skyBoxShader->SetMat4Uniform("view", view);

	glBindVertexArray(m_VAO); CHECK_GL_ERROR();
	glActiveTexture(GL_TEXTURE0); CHECK_GL_ERROR();
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID); CHECK_GL_ERROR();
	glDrawArrays(GL_TRIANGLES, 0, 36); CHECK_GL_ERROR();
	glDepthMask(GL_TRUE); CHECK_GL_ERROR();
}

void SkyBox::CreateVAOandVBO()
{
	glGenVertexArrays(1, &m_VAO); CHECK_GL_ERROR();
	glGenBuffers(1, &m_VBO); CHECK_GL_ERROR();

	glBindVertexArray(m_VAO); CHECK_GL_ERROR();
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); CHECK_GL_ERROR();

	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), &skyboxVertices.data()[0], GL_STATIC_DRAW); CHECK_GL_ERROR();

	glEnableVertexAttribArray(0); CHECK_GL_ERROR();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); CHECK_GL_ERROR();
	glBindVertexArray(0); CHECK_GL_ERROR();
}

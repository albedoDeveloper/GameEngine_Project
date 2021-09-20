/*****************************************************************//**
 * \file   SkyBox.h
 * \author ProcrastoWare
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "ModernOpenGL/AModel.h"
#include "ModernOpenGL/Shader.h"

	/**
	 * skybox class.
	 */
class SkyBox
{
public:
		/**
		 * creates skybox graphics related stuff.
		 *
		 * \param skyBoxFaces
		 */
	void CreateSkybox(std::vector<std::string> textures);

		/**
		 * draw skybox.
		 *
		 * \param persepective
		 * \param view
		 */
	void DrawSkybox(Matrix4f projection, Matrix4f view);

private:
	unsigned m_texID, m_VAO, m_VBO;

		/** shader program to use for rendering */
	Shader *skyBoxShader = nullptr;

		/**
		 * graphics specific setup. TODO move this to graphics engine
		 */
	void CreateVAOandVBO();

		/** skybox verts */
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

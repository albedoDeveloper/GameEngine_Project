#include "mesh.h"

void Mesh::SetupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
	// vertex tangent

	glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	SetupMesh();
};
#include "../GraphicsEngine.h" //debug
void Mesh::Draw(const Shader *shader) const
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int textureUnit = 0; textureUnit < textures.size(); textureUnit++)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		std::string number;
		std::string name = textures[textureUnit].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(normalNr++);
		}
		else if (name == "texture_height")
		{
			number = std::to_string(heightNr++);
		}

		shader->SetIntUniform(("material." + name + number).c_str(), textureUnit);
		glBindTexture(GL_TEXTURE_2D, textures[textureUnit].id);
	}

	// send shadowMap to shader
	glActiveTexture(GL_TEXTURE2);
	GRAPHICS->BindDepthMapTexture();
	shader->SetIntUniform("shadowMap", 2);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_TEXTURE_2D);
}
/*****************************************************************//**
 * \file   CStaticMesh.h
 * \brief  Static Mesh Component
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"
#include "ModernOpenGL/AModel.h"
#include <string>

//enum declare
enum ShaderSelection
{
	lit, unlit, debug
};

static const char *enum_str[] =
{ "lit", "unlit", "debug" };

	/**
	 * @brief A static mesh containing information on a model
	*/
class CStaticMesh : public CComponent
{
public:
		/**
		* @brief constructor taking parent data
		* @param parent The parent transform for this component's transform
		* @param parentObj The object to which this component belongs
		*/
	CStaticMesh(Transform *parent, GameObject *parentObj);

		/**
		* @brief constructor taking parent as argument
		* @param parent pointer to parent transform for this component's transform
		* @param parentObj pointer to parent object of this component
		*/
	AModel &GetModel();

		/**
		* @brief model mutator taking factory key
		* @param modelKey the asset factory key of the model to assign
		*/
	AModel &AssignModelByKey(std::string modelKey);

		/**
		* @brief assigns shader
		*
		* \param shader Shader name
		*/
	void AssignShader(std::string shader);

	void AssignShaderEnum(ShaderSelection shader);

		/**
		* @brief displays the mesh's model on the screen
		*/
	virtual void Render();

		/**
		* @brief save the component
		* \param j json to save to
		*/
	virtual void Save(nlohmann::json &j);

		/**
		* @brief loads the component from saved state
		* \param j json to save to
		*/
	virtual void Load(nlohmann::json &j);

		/**
		* @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/** @brief the model this mesh is storing */
	AModel *m_model;

		/** @brief pointer to the shader */
	Shader *m_shader;

	/** @brief shader index */
	int m_shaderSelect = 0;

	ShaderSelection m_selectedShader;


};

#pragma once

#include "CComponent.h"
#include "ModernOpenGL/AModel.h"
#include <string>

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

	void AssignShader(std::string);

	/**
	 * @brief displays the mesh's model on the screen
	*/
	virtual void Render();

	/**
	 * @brief saves the component
	*/
	virtual void Save(nlohmann::json &j);

	/**
	 * @brief loads the component from saved state
	*/
	virtual void Load(nlohmann::json &j);

	/**
	 * @brief Draws to imgui
	*/
	virtual void DrawToImGui();

	/**
 * @brief the model this mesh is storing
*/
	AModel *m_model;

	Shader *m_shader;
};

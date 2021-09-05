#pragma once

#include "Component.h"
#include "ModernOpenGL/Model.h"
#include <string>

/**
 * @brief A static mesh containing information on a model
*/
class CStaticMesh : public Component 
{
public:
	/**
	 * @brief constructor taking parent data
	 * @param parent The parent transform for this component's transform
	 * @param parentObj The object to which this component belongs
	*/
	CStaticMesh(Transform* parent, GameObject* parentObj);
	/**
	 * @brief model mutator
	 * @param model the asset model to assign
	*/
	void AssignModel(Model* model);

	/**
	 * @brief constructor taking parent as argument
	 * @param parent pointer to parent transform for this component's transform
	 * @param parentObj pointer to parent object of this component
	*/
	Model* GetModel();

	/**
	 * @brief model mutator taking factory key
	 * @param modelKey the asset factory key of the model to assign
	*/
	Model* AssignModelByKey(std::string modelKey);

	/**
	 * @brief initialises the mesh at program start
	*/
	virtual void Start();
	/**
	 * @brief updates ongoing behaviour for the mesh each frame
	*/
	virtual void Update();
	/**
	 * @brief displays the mesh's model on the screen
	*/
	virtual void Render();

	/**
	 * @brief render called after the first render
	*/
	virtual void LateRender();

	/**
	 * @brief saves the component
	*/
	virtual void Save(nlohmann::json& j);

	/**
	 * @brief loads the component from saved state
	*/
	virtual void Load(nlohmann::json& j);

	/**
 * @brief the model this mesh is storing
*/
	Model* m_model;

protected:

};

#pragma once

#include "Component.h"
#include "AModel.h"
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
	void AssignModel(AModel* model);

	/**
	 * @brief constructor taking parent as argument
	 * @param parent pointer to parent transform for this component's transform
	 * @param parentObj pointer to parent object of this component
	*/
	AModel* GetModel();

	/**
	 * @brief model mutator taking factory key
	 * @param modelKey the asset factory key of the model to assign
	*/
	AModel* AssignModelByKey(std::string modelKey);

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

protected:
	/**
	 * @brief the model this mesh is storing
	*/
	AModel* m_model;
};

/*******************************************************************
 * \file   CCollider.h
 * \brief  Collider Component
 *
 * \date   September 2021
 *********************************************************************/
#pragma once
#include "CComponent.h"
#include <bulletphysics/btBulletCollisionCommon.h>
#include <memory>

	/**
	 * @brief Collider Component
	*/
class CCollider : public CComponent
{
public:
		/**
		 * Tag for what shape this collider is.
		 */
	enum class Shape
	{
		Box, Sphere, None
	};

		/**
		 * @brief constructor taking parent as argument
		 * @param parent pointer to parent transform for this component's transform
		 * @param parentObj pointer to parent object of this component
		*/
	CCollider(Transform *parent, GameObject *parentObj);

		/**
		 * Destructor.
		 *
		 */
	~CCollider();

		/**
		 * Check what shape tag this collider is.
		 *
		 * \return
		 */
	Shape GetShape() const;

		/**
		 * @brief initialises the component at start of program
		*/
	void Start();
		/**
		 * @brief updates ongoing behaviour each frame
		*/
	void Update();

		/**
		 * @brief saves the component
		*/
	void Save(nlohmann::json &j);
		/**
		 * @brief loads the component from saved state
		*/
	void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/**
		 * @brief accesses active state
		*/
	bool GetActive();

		/**
		 * @brief mutates active state
		*/
	void SetActive(bool activeStatus);

		/**
		* @ brief enables or disables collider similar to Set active but doesn't affect saved condition
		*/
	void EnableDisable(bool activeStatus);

		/**
		 * The offset the colliders have off the model.
		 */
	glm::vec3 m_offset;

		/** @brief whether the collider is registered with the collider manager */
	bool m_isRegistered = false;

		/** @brief whether the collider is allowed to rotate */
	bool m_allowRotation;

		/** @brief check if active */
	bool m_active;

		/**
		 * @brief A pointer to the collisionbody which contains all the colliders on the model
		 */
	btCollisionObject *m_colObj;

		/**
		 * @brief list of the Vertices of the concave collider, if in use.
		 */
	std::vector<float> concaveVertices;

		/**
		 * list of indices of the concave collider, if in use.
		 */
	std::vector<int> concaveIndices;

		/**
		 * @brief Updates the colliders with any transformations changes based on the colliders model
		 *
		 */
	void UpdateCollider();

		/**
		 * @brief Creates a box collider around the object. Can either be automatically resized to fit the object, manually sized and placed, or statically placed.
		 *
		 * \param x
		 * \param y
		 * \param z
		 * \param offsetX
		 * \param offsetY
		 * \param offsetZ
		 * \param autoSize
		 * \param layer
		 * \param allowRotation
		 */
	void AddBoxCollider(float x = 0.2, float y = 0.2, float z = 0.2, float offsetX = 0, float offsetY = 0, float offsetZ = 0, bool autoSize = true, int layer = 0, bool allowRotation = true, int colMask = 31);

		/**
		 * Attach sphere collider.
		 */
	void AddSphereCollider();

		/**
		 * @brief Creates a convex/polygon collider around the object. Currently is not working.
		 *
		 */
	void AddConvexCollider();

		/**
		 * Get half size of mesh in X direction.
		 */
	float GetXHalfSize() const;

		/**
		 * Get half size of mesh in Y direction.
		 */
	float GetYHalfSize() const;

		/**
		 * Get half size of mesh in Z direction.
		 */
	float GetZHalfSize() const;

		/**
		 * Remove or add this collider to collision world.
		 */
	virtual void SetIsActive(bool isActive);

private:
		/// @brief mesh x half size
	float m_XHalfSize;

		/// @brief mesh y half size
	float m_YHalfSize;

		/// @brief mesh z half size
	float m_ZHalfSize;

		/// @brief shape tag of collider
	Shape m_shape;

	friend class CollisionManager;
};

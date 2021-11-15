/*******************************************************************
 * \file   PhysicsManager.h
 * \brief  Physics manager
 *
 * \date   November 2021
 *********************************************************************/

#pragma once

#include <vector>
#include "CRigidBody.h"

class Manifold;

/**
 * Physics manager class, handles rigidbodies in scene.
 *
 */
class PhysicsManager
{
public:
		/**
		 * Grab the singleton instance.
		 *
		 * \return
		 */
	static PhysicsManager *Instance();

		/**
		 * resolve contact points for all registered bodies.
		 *
		 * \param manifolds
		 */
	void ResolveContactPoints(std::vector<Manifold> &manifolds);

		/**
		 * Register a rigidbody.
		 *
		 * \param body
		 */
	void RegisterRigidBody(CRigidBody *body);

		/**
		 * Apply newtons laws of motion on all registered bodies.
		 *
		 */
	void IntegrateBodies();

private:
		/**
		 * collection of registered bodies.
		 */
	std::vector<CRigidBody *> m_bodies;

		/**
		 * Calculate restitution for current copntact, based on both bodies.
		 *
		 * \param manifolds
		 * \pre col1 of each manifold should always have a rigidbody
		 */
	void PrepareContacts(std::vector<Manifold> &manifolds);

		/**
		 * calculate impulses on each contact.
		 *
		 * \param manifolds
		 * \pre col1 of each manifold should always have a rigidbody
		 */
	void ResolveImpulses(std::vector<Manifold> &manifolds);

		/**
		 * apply linear projection on deepest penetrating contact per manifold.
		 *
		 * \param manifolds
		 * \pre col1 of each manifold should always have a rigidbody
		 */
	void ResolveInterpenetration(std::vector<Manifold> &manifolds);
};

#define PHYSICS PhysicsManager::Instance()

#pragma once

#include <vector>
#include "CRigidBody.h"

class Manifold;

class PhysicsManager
{
public:
	static PhysicsManager *Instance();
	void ResolveContactPoints(std::vector<Manifold> &manifolds);
	void RegisterRigidBody(CRigidBody *body);
	//void IntegrateAccelerations();
	//void IntegrateVelocities();
	void IntegrateBodies();

private:
	std::vector<CRigidBody *> m_bodies;

	void PrepareContacts(std::vector<Manifold> &manifolds);
	void ResolveImpulses(std::vector<Manifold> &manifolds);
	void ResolveInterpenetration(std::vector<Manifold> &manifolds);
};

#define PHYSICS PhysicsManager::Instance()

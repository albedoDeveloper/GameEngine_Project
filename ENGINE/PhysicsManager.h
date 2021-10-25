#pragma once

#include <vector>
#include "CRigidBody.h"

struct Manifold;

class PhysicsManager
{
public:
	static PhysicsManager *Instance();
	void ResolveContactPoints(std::vector<Manifold> &manifolds);
	void RegisterRigidBody(CRigidBody *body);
	//void IntegrateAccelerations();
	//void IntegrateVelocities();
	void IntegrateBodies();
	void ResolveImpulses(std::vector<Manifold> &manifolds);

private:
	std::vector<CRigidBody *> m_bodies;

	//void PrepareContacts(ContactInfo &contactInfo);
	void ResolveInterpenetration(std::vector<Manifold> &manifolds);
};

#define PHYSICS PhysicsManager::Instance()

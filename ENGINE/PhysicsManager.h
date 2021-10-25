#pragma once

#include <vector>
#include "CRigidBody.h"

struct ContactInfo;

class PhysicsManager
{
public:
	static PhysicsManager &Instance();
	void ResolveContactPoints(ContactInfo &contactInfo);
	void RegisterRigidBody(CRigidBody *body);
	void IntegrateAccelerations();
	void IntegrateVelocities();
	void ResolveImpulses(ContactInfo &contactInfo);

private:
	std::vector<CRigidBody *> m_bodies;

	//void PrepareContacts(ContactInfo &contactInfo);
	void ResolveInterpenetration(ContactInfo &contactInfo);
};

#define PHYSICS PhysicsManager::Instance()

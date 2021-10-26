#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "MiscMath.h"

PhysicsManager *PhysicsManager::Instance()
{
	static PhysicsManager instance;
	return &instance;
}

void PhysicsManager::ResolveContactPoints(std::vector<Manifold> &manifolds)
{
	if (manifolds.size() < 1) return;

	PrepareContacts(manifolds);

	ResolveImpulses(manifolds);

	ResolveInterpenetration(manifolds);
}

void PhysicsManager::RegisterRigidBody(CRigidBody *body)
{
	m_bodies.push_back(body);
}

void PhysicsManager::PrepareContacts(std::vector<Manifold> &manifolds)
{
	// prepare contacts
	for (unsigned pair = 0; pair < manifolds.size(); pair++)
	{
		manifolds[pair].Prepare();
		//for (unsigned contact = 0; contact < manifolds[pair].contactPoints.size(); contact++)
		//{
		//	Manifold &contactPair = manifolds[pair];
		//	assert(contactPair.col1->GetParentObject()->GetCRigidBody() || contactPair.col2->GetParentObject()->GetCRigidBody());
		//	manifolds[pair].contactPoints[contact].Prepare();
		//}
	}
}

void PhysicsManager::ResolveInterpenetration(std::vector<Manifold> &manifolds)
{
	//resolves interpenetrations
	for (unsigned pair = 0; pair < manifolds.size(); pair++) // loop through each manifold apply linear projection to biggest penetrating contact point
	{
		float maxPenPointIndex = 0;
		float maxPen = manifolds[pair].contactPoints[maxPenPointIndex].penDepth;
		for (unsigned point = 0; point < manifolds[pair].contactPoints.size(); point++)
		{
			Manifold::ContactPoint &contactPoint = manifolds[pair].contactPoints[point];
			if (contactPoint.penDepth > maxPen)
			{
				maxPen = contactPoint.penDepth;
				maxPenPointIndex = point;
			}
		}
		Manifold::ContactPoint &contactPoint = manifolds[pair].contactPoints[maxPenPointIndex];
		Vector3f normal = contactPoint.worldNormal;
		CRigidBody *rb1 = manifolds[pair].col1->GetParentObject()->GetComponent<CRigidBody>();
		CRigidBody *rb2 = manifolds[pair].col2->GetParentObject()->GetComponent<CRigidBody>();
		assert(rb1);
		if (rb1 && rb2)
		{
			float totalInverseMass = rb1->GetInverseMass() + rb2->GetInverseMass();
			Vector3f movePerIMass = contactPoint.worldNormal * maxPen / totalInverseMass;
			rb1->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb1->GetInverseMass() * -1);
			rb2->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb2->GetInverseMass());
			manifolds[pair].col1->UpdateCollider();
			manifolds[pair].col2->UpdateCollider();
		}
		else if (rb1 && !rb2)
		{
			Vector3f move = contactPoint.worldNormal * maxPen;
			rb1->GetParentObject()->GetTransform()->TranslateV(move * -1);
			manifolds[pair].col1->UpdateCollider();
		}
	}
}

void PhysicsManager::IntegrateBodies()
{
	for (unsigned i = 0; i < m_bodies.size(); i++)
	{
		if (m_bodies[i]->GetParentObject()->GetActive())
		{
			m_bodies[i]->Integrate();
		}
	}
}

void PhysicsManager::ResolveImpulses(std::vector<Manifold> &manifolds)
{
	//resolve impulses
	unsigned numManifolds = manifolds.size();
	for (int pair = 0; pair < numManifolds; pair++)
	{
		Manifold &manifold = manifolds[pair];
		CRigidBody *rb1 = manifolds[pair].col1->GetParentObject()->GetComponent<CRigidBody>();
		CRigidBody *rb2 = manifolds[pair].col2->GetParentObject()->GetComponent<CRigidBody>();
		assert(rb1);
		const float invMass1 = rb1->GetInverseMass();
		float invMass2{};
		if (rb2)
		{
			invMass2 = rb2->GetInverseMass();
		}

		const Matrix3f J1invWorld = (rb1->GetTransform().GetWorldTransform().GetRelativeOrientation().Mat3Cast() * rb1->GetInertiaTensor() * rb1->GetTransform().GetWorldTransform().GetRelativeOrientation().Mat3Cast().Transpose()).Inverse();
		Matrix3f J2invWorld;
		if (rb2)
		{
			J2invWorld = (rb2->GetTransform().GetWorldTransform().GetRelativeOrientation().Mat3Cast() * rb2->GetInertiaTensor() * rb2->GetTransform().GetWorldTransform().GetRelativeOrientation().Mat3Cast().Transpose()).Inverse();
		}
		const Vector3f angVel1 = rb1->GetAngularVelocity();
		Vector3f angVel2;
		if (rb2)
		{
			angVel2 = rb2->GetAngularVelocity();
		}
		Vector3f bodiesRelVel = rb1->GetVelocity(); // relative velocity of the two rigid bodies, or just body 1 if there is no second body
		if (rb2)
		{
			bodiesRelVel -= rb2->GetVelocity();
		}

		unsigned numContactPoints = manifolds[pair].contactPoints.size();
		for (unsigned contact = 0; contact < numContactPoints; contact++)
		{
			Manifold::ContactPoint &thisContact = manifolds[pair].contactPoints[contact];
			const Vector3f normal = thisContact.worldNormal;
			const Vector3f r1 = thisContact.col1LocalPoint;
			Vector3f r2;
			if (rb2)
			{
				r2 = thisContact.col2LocalPoint;
			}

			// angular impulse momentum equation - See book "Introduction to Game Development - by Rabin"
			float impulse = 0.f;
			if (rb2)
			{
				impulse =
					((-1 * (1 + manifold.restitution) * (normal.dotProduct(bodiesRelVel) + angVel1.dotProduct(r1.crossProduct(normal)) - angVel2.dotProduct(r2.crossProduct(normal)))) /
					(invMass1 + invMass2 + ((r1.crossProduct(normal) * J1invWorld).dotProduct(r1.crossProduct(normal)) + ((r2.crossProduct(normal) * J2invWorld).dotProduct(r2.crossProduct(normal))))));
			}
			else
			{
				impulse =
					(-1 * (1 + manifold.restitution) * (rb1->GetVelocity()).dotProduct(normal)) /
					(invMass1 + (J1invWorld * (r1.crossProduct(normal)).crossProduct(r1)).dotProduct(normal)); // not 100% sure about this one
			}
			impulse /= numContactPoints;

			// linear impulse - seperating velocity
			Vector3f rb1NewVel = rb1->GetVelocity() + (impulse * normal) * rb1->GetInverseMass();
			rb1->SetVelocity(rb1NewVel);
			if (rb2)
			{
				Vector3f rb2NewVel = rb2->GetVelocity() - (impulse * normal) * rb2->GetInverseMass();
				rb2->SetVelocity(rb2NewVel);
			}

			// angular impulse
			Vector3f angularImpulse1 = impulse * J1invWorld * r1.crossProduct(normal);
			rb1->AddAngularVelocity(angularImpulse1);
			if (rb2)
			{
				Vector3f angularImpulse2 = impulse * J2invWorld * r2.crossProduct(normal);
				rb2->SubtractAngularVelocity(angularImpulse2);
			}
		}
	}
}

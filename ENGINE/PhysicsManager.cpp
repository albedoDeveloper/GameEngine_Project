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
	for (unsigned pair = 0; pair < manifolds.size(); pair++)
	{
		manifolds[pair].Prepare();
	}
}

void PhysicsManager::ResolveInterpenetration(std::vector<Manifold> &manifolds)
{
	for (unsigned pair = 0; pair < manifolds.size(); pair++) // loop through each manifold apply linear projection to biggest penetrating contact point
	{
		// find deepest interpenetrating contact
		float maxPenPointIndex = 0;
		float maxPen = manifolds[pair].contactPoints[maxPenPointIndex].GetPenDepth();
		for (unsigned point = 0; point < manifolds[pair].contactPoints.size(); point++)
		{
			Manifold::ContactPoint &contactPoint = manifolds[pair].contactPoints[point];
			if (contactPoint.GetPenDepth() > maxPen)
			{
				maxPen = contactPoint.GetPenDepth();
				maxPenPointIndex = point;
			}
		}

		Manifold::ContactPoint &contactPoint = manifolds[pair].contactPoints[maxPenPointIndex];
		Vector3f normal = contactPoint.GetWorldNormal();
		CRigidBody *rb1 = manifolds[pair].col1->GetParentObject()->GetComponent<CRigidBody>();
		CRigidBody *rb2 = manifolds[pair].col2->GetParentObject()->GetComponent<CRigidBody>();
		assert(rb1); // double check if col1 has a rigidbody, this should always be the case since the collision manager will make sure of this
		if (rb1 && rb2) // if both colliders have a rigidbody then seperate them proportional to their masses
		{
			float totalInverseMass = rb1->GetInverseMass() + rb2->GetInverseMass();
			Vector3f movePerIMass = contactPoint.GetWorldNormal() * maxPen / totalInverseMass;
			rb1->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb1->GetInverseMass() * -1);
			rb2->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb2->GetInverseMass());
			manifolds[pair].col1->UpdateCollider();
			manifolds[pair].col2->UpdateCollider();
		}
		else if (rb1 && !rb2) // if only col1 has a rigidbody then move it by the full interpenetration amount
		{
			Vector3f move = contactPoint.GetWorldNormal() * maxPen;
			rb1->GetParentObject()->GetTransform()->TranslateV(move * -1
			);
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
	unsigned numManifolds = manifolds.size();
	for (int m = 0; m < numManifolds; m++)
	{
		Manifold &manifold = manifolds[m];
		CRigidBody *rb1 = manifolds[m].col1->GetParentObject()->GetComponent<CRigidBody>();
		CRigidBody *rb2 = manifolds[m].col2->GetParentObject()->GetComponent<CRigidBody>();
		assert(rb1); // double check if col1 has a rigidbody, this should always be true because the collision manager will make sure of this
		const float invMass1 = rb1->GetInverseMass();
		float invMass2{};
		if (rb2)
		{
			invMass2 = rb2->GetInverseMass();
		}

		const Matrix3f J1invWorld = rb1->GetInverseWorldInertiaTensor();
		Matrix3f J2invWorld;
		if (rb2)
		{
			J2invWorld = rb2->GetInverseWorldInertiaTensor();
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

		unsigned numContactPoints = manifolds[m].contactPoints.size();
		for (unsigned contact = 0; contact < numContactPoints; contact++)
		{
			Manifold::ContactPoint &thisContact = manifolds[m].contactPoints[contact];
			const Vector3f normal = thisContact.GetWorldNormal();
			const Vector3f r1 = thisContact.GetCol1LocalPoint();
			Vector3f r2;
			if (rb2)
			{
				r2 = thisContact.GetCol2LocalPoint();
			}

			float impulse = 0.f;
			if (rb2)
			{
				// angular impulse momentum equation - See book "Introduction to Game Development - by Rabin"
				impulse =
					((-1 * (1 + manifold.restitution) * (normal.dotProduct(bodiesRelVel) + angVel1.dotProduct(r1.crossProduct(normal)) - angVel2.dotProduct(r2.crossProduct(normal)))) /
					(invMass1 + invMass2 + ((r1.crossProduct(normal) * J1invWorld).dotProduct(r1.crossProduct(normal)) + ((r2.crossProduct(normal) * J2invWorld).dotProduct(r2.crossProduct(normal))))));
			}
			else
			{
				// simplified angular impulse equation which only takes into account one rigidbody, colliding against an immovable object
				impulse =
					(-1 * (1 + manifold.restitution) * (rb1->GetVelocity()).dotProduct(normal)) /
					(invMass1 + (J1invWorld * (r1.crossProduct(normal)).crossProduct(r1)).dotProduct(normal));
			}
			impulse /= numContactPoints;

			// linear impulse
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

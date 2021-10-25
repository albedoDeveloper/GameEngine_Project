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

	//PrepareContacts(manifolds);

	ResolveInterpenetration(manifolds);

	//ResolveImpulses(manifolds);
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
		for (unsigned contact = 0; contact < manifolds[pair].contactPoints.size(); contact++)
		{
			Manifold &contactPair = manifolds[pair];
			assert(contactPair.col1->GetParentObject()->GetCRigidBody() || contactPair.col2->GetParentObject()->GetCRigidBody());
			manifolds[pair].contactPoints[contact].Prepare();
		}
	}
}

void PhysicsManager::ResolveInterpenetration(std::vector<Manifold> &manifolds)
{
	//const float percent = 0.2f;
	//const float slop = 0.01f;

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
		CRigidBody *rb1 = manifolds[pair].contactPoints[0].parentManifold->col1->GetParentObject()->GetComponent<CRigidBody>();
		CRigidBody *rb2 = manifolds[pair].contactPoints[0].parentManifold->col2->GetParentObject()->GetComponent<CRigidBody>();
		assert(rb1);
		if (rb1 && rb2)
		{
			float totalInverseMass = rb1->GetInverseMass() + rb2->GetInverseMass();
			Vector3f movePerIMass = contactPoint.worldNormal / totalInverseMass;
			rb1->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb1->GetInverseMass() * -1);
			rb2->GetParentObject()->GetTransform()->TranslateV(movePerIMass * rb2->GetInverseMass());
		}
		else if (rb1 && !rb2)
		{
			Vector3f movePerIMass = contactPoint.worldNormal;
			rb1->GetParentObject()->GetTransform()->TranslateV(movePerIMass * -1);
		}
	}

	//CRigidBody *rb1 = contactPoint.col1->GetParentObject()->GetComponent<CRigidBody>();
	//CRigidBody *rb2 = contactPoint.col2->GetParentObject()->GetComponent<CRigidBody>();
	//float angularInertia1{}, angularInertia2{};
	//float linearInertia1{}, linearInertia2{};
	//float totalInertia{ 0 };
	//if (rb1)
	//{
	//	Matrix3f inverseWorldInertiaTensor = rb1->GetWorldInertiaTensor().Inverse();
	//	// Use the same procedure as for calculating frictionless
	//	// velocity change to work out the angular inertia.
	//	Vector3f angularInertiaWorld = contactPoint.col1LocalPoint.crossProduct(contactPoint.worldNormal);
	//	angularInertiaWorld = inverseWorldInertiaTensor * angularInertiaWorld;
	//	angularInertiaWorld = angularInertiaWorld.crossProduct(contactPoint.col1LocalPoint);
	//	angularInertia1 = angularInertiaWorld.dotProduct(contactPoint.worldNormal);
	//	// The linear component is simply the inverse mass.
	//	linearInertia1 = rb1->GetInverseMass();
	//	// Keep track of the total inertia from all components.
	//	totalInertia += linearInertia1 + angularInertia1;

	//}
	//if (rb2)
	//{
	//	Matrix3f inverseWorldInertiaTensor = rb2->GetWorldInertiaTensor().Inverse();
	//	// Use the same procedure as for calculating frictionless
	//	// velocity change to work out the angular inertia.
	//	Vector3f angularInertiaWorld = contactPoint.col2LocalPoint.crossProduct(contactPoint.worldNormal);
	//	angularInertiaWorld = inverseWorldInertiaTensor * angularInertiaWorld;
	//	angularInertiaWorld = angularInertiaWorld.crossProduct(contactPoint.col2LocalPoint);
	//	angularInertia2 = angularInertiaWorld.dotProduct(contactPoint.worldNormal);
	//	// The linear component is simply the inverse mass.
	//	linearInertia2 = rb2->GetInverseMass();
	//	// Keep track of the total inertia from all components.
	//	totalInertia += linearInertia2 + angularInertia2;

	//	//rotational
	//	Vector3f impulsiveTorque = contactPoint.col1LocalPoint.crossProduct(contactPoint.worldNormal);
	//	Vector3f impulsePerMove = inverseWorldInertiaTensor * impulsiveTorque;
	//	Vector3f rotationPerMove = impulsePerMove * 1 / angularInertia2;
	//}

	//float inverseInertia = 1 / totalInertia;
	//float linearMove1 = contactPoint.penDepth * linearInertia1 * inverseInertia;
	//float linearMove2 = -contactPoint.penDepth * linearInertia2 * inverseInertia;
	//float angularMove1 = contactPoint.penDepth * angularInertia1 * inverseInertia;
	//float angularMove2 = -contactPoint.penDepth * angularInertia2 * inverseInertia;

	//rb1->GetTransform().TranslateV(contactPoint.worldNormal * linearMove1);
	//if (rb2)
	//{
	//	rb2->GetTransform().TranslateV(contactPoint.worldNormal * linearMove2);
	//}

	//if (rb1)
	//{
	//	//rotational
	//	Matrix3f inverseWorldInertiaTensor = rb1->GetWorldInertiaTensor().Inverse();
	//	Vector3f impulsiveTorque = contactPoint.col1LocalPoint.crossProduct(contactPoint.worldNormal);
	//	Vector3f impulsePerMove = inverseWorldInertiaTensor * impulsiveTorque;
	//	Vector3f rotationPerMove = impulsePerMove * 1 / angularInertia1;
	//	Vector3f rotation = rotationPerMove * angularMove1;
	//}
	//if (rb2)
	//{
	//	//rotational
	//	Matrix3f inverseWorldInertiaTensor = rb2->GetWorldInertiaTensor().Inverse();
	//	Vector3f impulsiveTorque = contactPoint.col2LocalPoint.crossProduct(contactPoint.worldNormal);
	//	Vector3f impulsePerMove = inverseWorldInertiaTensor * impulsiveTorque;
	//	Vector3f rotationPerMove = impulsePerMove * 1 / angularInertia2;
	//	Vector3f rotation = rotationPerMove * angularMove2;
	//}
}

void PhysicsManager::IntegrateBodies()
{
	for (unsigned i = 0; i < m_bodies.size(); i++)
	{
		m_bodies[i]->Integrate();
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

		unsigned numContactPoints = manifolds[pair].contactPoints.size();
		for (unsigned contact = 0; contact < numContactPoints; contact++)
		{
			Manifold::ContactPoint &thisContact = manifolds[pair].contactPoints[contact];
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
			const Vector3f normal = thisContact.worldNormal;
			float penetration = thisContact.penDepth;
			const Vector3f r1 = thisContact.col1LocalPoint;
			Vector3f r2;
			if (rb2)
			{
				r2 = thisContact.col2LocalPoint;
			}
			//Vector3f contactWorldPos = rb1->GetTransform().GetWorldTransform().GetRelativePosition() + r1 + (-1 * normal * (penetration / 2));
			//Vector3f contactRelVel = rb1->GetAngularVelocity().crossProduct(r1) + rb1->GetVelocity(); // relative velocity of the two objects at the contact point
			//if (rb2)
			//{
			//	contactRelVel -= rb2->GetAngularVelocity().crossProduct(r2) + rb2->GetVelocity();
			//}
			//float contactRelVelAlongNormal = contactRelVel.dotProduct(normal);
	/*		if (contactRelVelAlongNormal < 0)
			{
				std::cout << "seperating\n";
				return;
			}*/

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
				//impulse =
				//	((-1 * (1 + 0) * (normal.dotProduct(relVel) + angVel1.dotProduct(r1.crossProduct(normal)))) /
				//	(invMass1 + ((r1.crossProduct(normal) * J1invWorld).dotProduct(r1.crossProduct(normal)))));
				impulse =
					(-1 * (1 + manifold.restitution) * (rb1->GetVelocity()).dotProduct(normal)) /
					(invMass1 + (J1invWorld * (r1.crossProduct(normal)).crossProduct(r1)).dotProduct(normal));
			}

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

#include "RigidBody.h"


//RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass)
//	: myPosition(position), myVelocity(velocity), myMass(mass), RigidBody::m_shapeID(shapeID)
//{
//	//m_shapeID = shapeID;
//	//myPosition = position;
//	//myVelocity = velocity;
//	//myMass = mass;
//}


void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	//if you are kinematic, dont do anything here
	if (isKinematic)
	{
		//brute force the position and velocity so it cannot move
		//(creates interesting bounce visual when collision happens)
		myPosition = startPosition;
		myVelocity = glm::vec2(0);
		return;
	}

	applyForce(gravity * myMass);
	myVelocity -= myVelocity * myDrag * timeStep;
	myPosition += myVelocity * timeStep;
}

void RigidBody::setKinematic(bool new_state)
{
	isKinematic = new_state;
}

void RigidBody::applyForce(glm::vec2 force)
{
	//my velocity becomes force divided by my mass
	myVelocity += force/myMass;
}

void RigidBody::applyForceToObject(RigidBody* object2, glm::vec2 force)
{
	//applies the force to myself and then negative of the same force to the other rigidbody
	object2->applyForce(force);
	this->applyForce(-force);
}

void RigidBody::setVelocity(glm::vec2 new_velocity)
{
	myVelocity = new_velocity;
}

void RigidBody::resolveCollision(RigidBody* other, glm::vec2 collision_normal)
{
	glm::vec2 normal = glm::normalize(collision_normal);

	glm::vec2 relativeVelocity = other->getVelocity() - myVelocity;

	//float elasticity = 1;

	//heres the math
	float j =
		glm::dot(-(1 + myElasticity * other->myElasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / myMass) + (1 / other->getMass())));
	
	glm::vec2 force = normal * j;
	//if i am kinematic and the other is not
	if (this->isKinematic && !other->isKinematic)
	{
		//only apply the force to the other
		other->applyForce(force);
	}
	//if i am not kinematic and the other IS kinematic
	if (!this->isKinematic && other->isKinematic)
	{
		applyForce(-force);
	}
	//if both are not kinematic
	if (!this->isKinematic && !other->isKinematic)
	{
		applyForceToObject(other, force);
	}
	
}

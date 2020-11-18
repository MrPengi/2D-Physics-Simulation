#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"


class Spring :public PhysicsObject
{
public:
	Spring(RigidBody* body1, RigidBody* body2,
		float rest_length, float spring_coefficient, float damping
		/*glm::vec2 contact1, glm::vec2 contact2*/);

	void fixedUpdate(glm::vec2 gravity, float timeStep);
	//virtual void debug() = 0;
	void makeGizmo();

	
	RigidBody* bodyOne;
	RigidBody* bodyTwo;

	//glm::vec2 contactOne; //position of attachment (bodyOne's position)?
	//glm::vec2 contactTwo; //position of attachment (bodyTwo's position)?

	float myDamping;
	float restLength;
	float springCoefficient;


};


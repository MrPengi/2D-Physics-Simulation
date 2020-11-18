#pragma once
#include "PhysicsObject.h"

class RigidBody;

class Plane :public PhysicsObject
{
public:

	// constructor takes normal, distance, elasticity and colour
	Plane(glm::vec2 a_normal,
		 float a_distance, float elasticity, glm::vec4 a_color);

	glm::vec2 get_normal();
	void set_normal(glm::vec2 a_normal);

	float get_distance();
	void set_distance(float a_distance);

	void makeGizmo();

	//unique resolve collision function as Plane does not inherit from RigidBody
	void resolveCollisionWithPlane(RigidBody* other);

	void fixedUpdate(glm::vec2 gravity, float timeStep) override;

	glm::vec4 myColor;

private:
	glm::vec2 myNormal;
	
	float myDistance = 0.0f;
};


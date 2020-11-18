#include "Plane.h"
#include <limits>
#include "RigidBody.h"

Plane::Plane(glm::vec2 a_normal /* = { 0.0f, 1.0f }*/,
	const float a_distance /*= 0.0f*/,float elasticity, glm::vec4 a_color) :
	myNormal(a_normal),
	myDistance(a_distance),
	myColor(a_color),
	PhysicsObject(ShapeType::PLANE, elasticity)
{
	set_normal(myNormal);
}

glm::vec2 Plane::get_normal()
{
	return myNormal;
}

void Plane::set_normal(glm::vec2 a_normal)
{
	if (glm::length(a_normal) <= 0.0f)
	{
		
	}
	else
	{
		myNormal = glm::normalize(a_normal);
	}
}

float Plane::get_distance() 
{
	return myDistance;
}

void Plane::set_distance(float a_distance)
{
	myDistance = a_distance;
}

void Plane::makeGizmo()
{
	glm::vec2 centrePoint = myNormal * myDistance;
	glm::vec2 draw_direction(myNormal.y, -myNormal.x);
	aie::Gizmos::add2DLine(centrePoint + (draw_direction * 500.0f), centrePoint + (draw_direction * -500.0f), myColor);
}

void Plane::resolveCollisionWithPlane(RigidBody* other)
{
	glm::vec2 relativeVelocity = other->getVelocity();

	//float elasticity = 1;

	float j =
		glm::dot(-(1 + myElasticity * other->GetElasticity()) * (relativeVelocity), get_normal()) /
		glm::dot(get_normal(), get_normal() * (1 / other->getMass()));

	glm::vec2 force = get_normal() * j;
	
	other->applyForce(force);
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{

}
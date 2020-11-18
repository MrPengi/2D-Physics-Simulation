#include "AABB.h"
#include <cmath>

//const vector_2 aligned_bounding_box::DEFAULT_EXTENTS = { 5.0f, 5.0f };

AABB::AABB(glm::vec2 a_position /*= vector_2()*/,
	glm::vec2 a_extents /*= DEFAULT_EXTENTS*/, glm::vec2 a_velocity, float mass, float drag, float elasticity, glm::vec4 color) :
	RigidBody(ShapeType::AABB, a_position, a_velocity, mass, drag, elasticity),
	myExtents(a_extents), myColour(color)
{}

glm::vec2 AABB::get_position()
{
	return myPosition;
}

void AABB::set_position(glm::vec2 a_position)
{
	myPosition = a_position;
}

glm::vec2 AABB::get_extents()
{
	return myExtents;
}

void AABB::set_extents(glm::vec2 a_extents)
{
	myExtents = { abs(a_extents.x), abs(a_extents.y) };
}

float AABB::get_width() 
{
	return myWidth;
}

float AABB::get_height()
{
	return myHeight;
}

glm::vec2 AABB::get_min()
{
	return myPosition - 0.5f * myExtents;
}

glm::vec2 AABB::get_max()
{
	return myPosition + 0.5f * myExtents;
}

bool AABB::checkCollision(PhysicsObject* pOther)
{
	return false;
}

void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(myPosition, myExtents * 0.5f, myColour);
}
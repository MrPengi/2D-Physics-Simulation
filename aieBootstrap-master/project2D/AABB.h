#pragma once
#include "RigidBody.h"


class AABB: public RigidBody
{	
public:

	//static const vector_2 DEFAULT_EXTENTS;

	//constructor takes in position, extents, velocity, mass, drag, elasticity and colour
	AABB(glm::vec2 a_position, glm::vec2 a_extents, glm::vec2 a_velocity, float mass, float drag, float elasticity, glm::vec4 color);

	glm::vec2 get_position();
	void set_position(glm::vec2 a_position);

	glm::vec2 get_extents();
	void set_extents(glm::vec2 a_extents);

	float get_width();
	float get_height();

	glm::vec2 get_min();
	glm::vec2 get_max();

	bool checkCollision(PhysicsObject* pOther);
	void makeGizmo();

	glm::vec4 myColour;

private:
	
	union
	{
		glm::vec2 myExtents;
		struct
		{
			float myWidth;
			float myHeight;
		};
		};

};


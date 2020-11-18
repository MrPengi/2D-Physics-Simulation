#pragma once
#include "glm/glm.hpp"
#include "AABB.h"
#include "Circle.h"
#include "Plane.h"

class CollisionManager
{
public:
	static glm::vec2 circle_vs_circle(PhysicsObject* a_circle_A,
								PhysicsObject* a_circle_B);

	static glm::vec2 aabb_vs_aabb(PhysicsObject* a_aabb_A,
						PhysicsObject* a_aabb_B);

	 static glm::vec2 line_vs_line(PhysicsObject* a_line_A,
							PhysicsObject* a_line_B);

	 static glm::vec2 aabb_vs_circle(PhysicsObject* a_aabb,
							 PhysicsObject* a_circle);

	 static glm::vec2 circle_vs_aabb(PhysicsObject* a_circle,
						 PhysicsObject* a_aabb);

	 static glm::vec2 circle_vs_line(PhysicsObject* a_circle,
						PhysicsObject* a_line);

	 static glm::vec2 line_vs_circle(PhysicsObject* a_line,
		 PhysicsObject* a_circle);

	 static glm::vec2 aabb_vs_line(PhysicsObject* a_aabb,
						PhysicsObject* a_line);

	 static glm::vec2 line_vs_aabb(PhysicsObject* a_line,
		 PhysicsObject* a_aabb);


private:
	 glm::vec2 clamp(glm::vec2& a_vector_2,
		 glm::vec2& a_min,
		 glm::vec2& a_max);
};


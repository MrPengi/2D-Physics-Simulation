#include "CollisionManager.h"
#include <cmath>

#include "AABB.h"
#include "Circle.h"
#include "Plane.h"
#include <iostream>

glm::vec2 CollisionManager::circle_vs_circle( PhysicsObject* a_circle_A,  PhysicsObject* a_circle_B)
{
	const Circle* c1 = (Circle*)a_circle_A;
	const Circle* c2 = (Circle*)a_circle_B;


	glm::vec2 displacement = (c1->getPosition() - c2->getPosition());
	float radiusA = c1->getRadius();
	float radiusB = c2->getRadius();
	float sum_of_radii = radiusA + radiusB;//a_circle_A.getRadius() + a_circle_B.getRadius();
	float overlap = (sum_of_radii)-glm::length(displacement);
	//std::cout << radiusA << " + " << radiusB <<" == " << sum_of_radii << "\n";
	if (overlap > 0.0f)
	{
		//swap sides and add radius
		return glm::normalize(displacement) * overlap;
	}
	return glm::vec2(0);
	//return (glm::length(displacement) < sum_of_radii);
}

glm::vec2 CollisionManager::aabb_vs_aabb(
	PhysicsObject* a_aabb_A,
	PhysicsObject* a_aabb_B)
{
	
	AABB* AABB1 = (AABB*)a_aabb_A;
	AABB* AABB2 = (AABB*)a_aabb_B;

	const float maxOverlap = 10000000.0f;
	float overlap = maxOverlap;

	glm::vec2 overlapVector = glm::vec2(0.0f);

	if (AABB1->get_max().x > AABB2->get_min().x)
	{//abs
 		float localOverlap = abs(AABB1->get_max().x - AABB2->get_min().x);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(-overlap, 0);
			
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	if (AABB1->get_min().x < AABB2->get_max().x)
	{
 		float localOverlap = abs(AABB1->get_min().x - AABB2->get_max().x);
		if (localOverlap < overlap)
		{
			overlap = -localOverlap;
			overlapVector = glm::vec2(overlap, 0);
			
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	if (AABB1->get_max().y > AABB2->get_min().y)
	{
		float localOverlap = abs(AABB1->get_max().y - AABB2->get_min().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, -overlap);
			
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	if (AABB1->get_min().y < AABB2->get_max().y)
	{
		float localOverlap = abs(AABB1->get_min().y - AABB2->get_max().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, overlap);
			
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	//return !(a_aabb_A.get_max().x < a_aabb_B.get_min().x ||
		//a_aabb_A.get_min().x > a_aabb_B.get_max().x ||
		//a_aabb_A.get_max().y < a_aabb_B.get_min().y ||
		//a_aabb_A.get_min().y > a_aabb_B.get_max().y);
	return overlapVector;
}

//dont do or worry about
glm::vec2 CollisionManager::line_vs_line(PhysicsObject* a_line_A,
	PhysicsObject* a_line_B)
{
	return glm::vec2(0);
}


glm::vec2 CollisionManager::aabb_vs_circle(
	PhysicsObject* a_aabb,
	 PhysicsObject* a_circle)
{
	//std::cout << "aabb_vs_circle called \n";
	AABB* aabb = (AABB*)a_aabb;
	Circle* circle = (Circle*)a_circle;

	glm::vec2 clampedCentre = glm::clamp(circle->getPosition(), aabb->get_min(), aabb->get_max());

	glm::vec2 displacement = clampedCentre - circle->getPosition();

	float overlap = circle->getRadius() - glm::length(displacement);
	
	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * -overlap;
	}

	//glm::vec2 clamped_centre = clamp(a_circle.getPosition(), a_aabb.get_min(), a_aabb.get_max());
	//glm::vec2 displacement = clamped_centre - a_circle.getPosition();
	return  glm::vec2(0); //(displacement.length() < a_circle.getRadius());
}

//calls aabb_vs_circle
glm::vec2 CollisionManager::circle_vs_aabb(PhysicsObject* a_circle,
	 PhysicsObject* a_aabb)
{
	return aabb_vs_circle(a_aabb, a_circle);
}


glm::vec2 CollisionManager::circle_vs_line(
	PhysicsObject* a_circle,
	PhysicsObject* a_line)
{
	//std::cout << "circle_vs_line called \n";
	Circle* circle = (Circle*)a_circle;
	Plane* line = (Plane*)a_line;


	float position_dot_normal = glm::dot(circle->getPosition(), line->get_normal());
		
	float distance = position_dot_normal - (line->get_distance() + circle->getRadius());
	if (distance < 0.0f)
	{
		return line->get_normal() * - distance;
	}
	else
	{ 
		return glm::vec2(0.0f);
	}
	
}

//calls circle_vs_line
glm::vec2 CollisionManager::line_vs_circle(PhysicsObject* a_line,
	PhysicsObject* a_circle)
{

	return circle_vs_line(a_circle, a_line);
}

glm::vec2 CollisionManager::aabb_vs_line(
	PhysicsObject* a_aabb,
	PhysicsObject* a_line)
{
	//std::cout << "aabb_vs_circle called \n";
	AABB* aabb = (AABB*)a_aabb;
	Plane* plane = (Plane*)a_line;
	
	glm::vec2 extents = 0.5f * aabb->get_extents();
	glm::vec2 extentsNegX = 0.5f * glm::vec2(-aabb->get_extents().x, aabb->get_extents().y);

	float dotExtents = glm::dot(extents, plane->get_normal());
	float dotExtentsNegX = glm::dot(extentsNegX, plane->get_normal());

	float radius = fmax(fabsf(dotExtents), fabsf(dotExtentsNegX));

	Circle projection(aabb->getPosition(), glm::vec2(0), aabb->getMass(), radius, 0, 0, glm::vec4(0));

	return circle_vs_line(&projection, a_line);
}

//calls aabb_vs_line
glm::vec2 CollisionManager::line_vs_aabb(PhysicsObject* a_line,
	PhysicsObject* a_aabb)
{
	return aabb_vs_line(a_aabb, a_line);
}



glm::vec2 CollisionManager::clamp(
	 glm::vec2& a_vector_2,
	 glm::vec2& a_min,
	 glm::vec2& a_max)
{
	return { fminf(fmaxf(a_vector_2.x, a_min.x), a_max.x),
			 fminf(fmaxf(a_vector_2.y, a_min.y), a_max.y) };
}
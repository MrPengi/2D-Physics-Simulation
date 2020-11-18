#include "Spring.h"
#include "RigidBody.h"


Spring::Spring(RigidBody* body1, RigidBody* body2,
	float rest_length, float spring_coefficient, float damping
	/*glm::vec2 contact1, glm::vec2 contact2*/)
	: PhysicsObject(ShapeType::JOINT, 0)
{
	bodyOne = body1;
	bodyTwo = body2;
	restLength = rest_length;
	springCoefficient = spring_coefficient;
	myDamping = damping;
	//contactOne = contact1;
	//contactTwo = contact2;
};

void Spring::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	glm::vec2 p2 = bodyTwo->myPosition;
	glm::vec2 p1 = bodyOne->myPosition;
	glm::vec2 dist = p2 - p1;
	float length = sqrtf(dist.x * dist.x + dist.y * dist.y);

	// apply damping
	glm::vec2 relativeVelocity = bodyTwo->getVelocity() - bodyOne->getVelocity();

	// F = -kX - bv
	glm::vec2 force = dist * springCoefficient * (restLength - length) - myDamping * relativeVelocity;
	

	
	bodyOne->applyForce(-force * timeStep/*, p1 - bodyOne->getPosition()*/);
	bodyTwo->applyForce(force * timeStep/*, p2 - bodyTwo->getPosition()*/);

}



void Spring::makeGizmo()
{
	aie::Gizmos::add2DLine(bodyOne->getPosition(), bodyTwo->getPosition(), glm::vec4(1,0,1,1));
}
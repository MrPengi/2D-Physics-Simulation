#include "Circle.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include "CollisionManager.h"

Circle::Circle(glm::vec2 position, glm::vec2 velocity, float mass, float radius,float drag, float elasticity,glm::vec4 colour)
    : RigidBody(ShapeType::CIRCLE, position, velocity, mass, drag, elasticity)
{ 
    myRadius = radius;
    myColour = colour; 
}


Circle::~Circle()
{

}

void Circle::makeGizmo()
{
    aie::Gizmos::add2DCircle(myPosition, myRadius, 20, myColour);
}

bool Circle::checkCollision(PhysicsObject* pOther)
 {
   CollisionManager check;
   //return check.circle_vs_circle(*this, (Circle&)*pOther);
   return false;
}

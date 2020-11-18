#pragma once
#include "PhysicsObject.h"

#ifndef _RIGID_BODY_H
#define _RIGID_BODY_H

class RigidBody : public PhysicsObject
{
public:
    
    //constructor takes shapeID, position, velocity, mass, drag and elasticity
    RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass, float drag, float elasticity)
        : PhysicsObject(shapeID, elasticity), myPosition(position), myVelocity(velocity), myMass(mass), myDrag(drag)
    {
        isKinematic = false;
        startPosition = myPosition;
    }


    ~RigidBody() {}

    //updates the rigidbody
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    //virtual void debug();
    //applies a force to the rigidbody
    void applyForce(glm::vec2 force);
    //applies a force to this rigidbody and another rigidbody
    void applyForceToObject(RigidBody* object2, glm::vec2 force);

    virtual bool checkCollision(PhysicsObject* pOther) = 0;

    const glm::vec2 getPosition() const  { return myPosition; }
 
    const glm::vec2 getVelocity() const { return myVelocity; }
    const float getMass() const { return myMass; }
    bool getKinematic() { return isKinematic; }

    void setPosition(glm::vec2 position) { myPosition = position; }

    void setVelocity(glm::vec2 new_velocity);

    void setKinematic(bool new_state);

    //resolves a collision between two rigidbodies
    void resolveCollision(RigidBody* other, glm::vec2 collision_normal);
    
    glm::vec2 myPosition;
    glm::vec2 myVelocity;
    glm::vec2 startPosition;
    float myMass; 
    float myDrag;
    bool isKinematic = false;
 

};

#endif

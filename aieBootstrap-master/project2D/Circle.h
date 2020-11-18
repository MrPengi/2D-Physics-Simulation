#include "RigidBody.h"
#pragma once

#ifndef _CIRCLE_H
#define _CIRCLE_H
class Circle : public RigidBody
{
public:

    //constructor
    Circle(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float drag, float elasticity, glm::vec4 colour);
    ~Circle();

    //makes the circle that gets drawn to screen
    void makeGizmo();
    bool checkCollision(PhysicsObject* pOther);

    const  float getRadius() const { return myRadius; }
    const glm::vec4 getColour() const { return myColour; }

    protected:
    float myRadius;
    glm::vec4 myColour;

};


#endif
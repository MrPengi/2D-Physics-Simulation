#include "glm/vec2.hpp"
#include "CollisionManager.h"
#include <vector>
#include <functional>
using collisionFunction = std::function < glm::vec2(PhysicsObject*, PhysicsObject*) >;
class PhysicsObject;

#pragma once
#ifndef _PHYSICS_SCENE_H
#define _PHYSICS_SCENE_H



class PhysicsScene
{
public:

    //constructor
    PhysicsScene();

    //destructor
    ~PhysicsScene();

    //adds a physics object to the scene
    void addObject(PhysicsObject* object);

    //removes a chosen physics object from the scene
    void removeObject(PhysicsObject* object);

    //temp function to remove all objects (destructor does this anyways)
    void removeAllObjects();

    //standad update
    void update(float dt);

    void updateGizmos();

    //set gravity
    void setGravity(glm::vec2 gravity) { m_gravity = gravity; }

    //get gravity
    glm::vec2 getGravity() { return m_gravity; }

    //set the timeStep
    void setTimeStep(float timeStep) { m_timeStep = timeStep; }

    //get the timeStep
    float getTimeStep() { return m_timeStep; }

   
   static const collisionFunction collisionFunctions[];
    

protected: 
    glm::vec2 m_gravity;
    float m_timeStep;
    //list of physics objects that will be in the scene
    std::vector<PhysicsObject*> m_objects;


};

#endif //! _PHYSICS_SCENE_H

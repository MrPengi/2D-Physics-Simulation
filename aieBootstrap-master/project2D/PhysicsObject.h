#include "glm/glm.hpp"
#include "Gizmos.h"
#include <vector>

#pragma once


//enum of the shape types
enum class ShapeType {
    JOINT = -1, //-1 (used with Spring code)
    CIRCLE, //0
    AABB, //1
    PLANE, //2
    COUNT, //3 (used with collisions earlier)
};

//enum class ShapeType {
//    PLANE, //0
//    CIRCLE, //1
//    AABB, //2
//    COUNT //3
//};

class PhysicsObject
{
protected: 

    

   
    //constructor (note: this class is pure virtual)
    PhysicsObject(ShapeType a_shapeID, float elasticity) : m_shapeID(a_shapeID), myElasticity(elasticity) {}

    ShapeType m_shapeID;
    float myElasticity;
public:
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
    //virtual void debug() = 0;
    virtual void makeGizmo() = 0;
    virtual void resetPosition() {};
    ShapeType GetShapeType() { return m_shapeID; };
    float GetElasticity() { return myElasticity; }
};



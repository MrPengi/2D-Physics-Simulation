#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include <list>
#include <iostream>



//using collisionFunction = std::function < glm::vec2(PhysicsObject*, PhysicsObject*) >;
const collisionFunction PhysicsScene::collisionFunctions[] =
{
	CollisionManager::circle_vs_circle, CollisionManager::circle_vs_aabb, CollisionManager::circle_vs_line,
	CollisionManager::aabb_vs_circle, CollisionManager::aabb_vs_aabb, CollisionManager::aabb_vs_line,
	CollisionManager::line_vs_circle, CollisionManager::line_vs_aabb, CollisionManager::line_vs_line
};


//CollisionManager::line_vs_line, CollisionManager::line_vs_circle, CollisionManager::line_vs_aabb,
//CollisionManager::circle_vs_line, CollisionManager::circle_vs_circle, CollisionManager::circle_vs_aabb,
//CollisionManager::aabb_vs_line, CollisionManager::aabb_vs_circle, CollisionManager::aabb_vs_aabb,

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

//the destructor takes care of deleting the objects in the scene
PhysicsScene::~PhysicsScene()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		delete m_objects[i];
		m_objects[i] = nullptr;
	}
	m_objects.clear();
}

//adds new object to the back of the vector
void PhysicsScene::addObject(PhysicsObject* object)
{
	m_objects.push_back(object);
}


void PhysicsScene::removeObject(PhysicsObject* object)
{
	//find location, and then delete it
	auto location = std::find(m_objects.begin(), m_objects.end(), object);
	m_objects.erase(location);
	delete object;
	object = nullptr;
}


void PhysicsScene::removeAllObjects()
{
	m_objects.clear();
}

void PhysicsScene::update(float dt)
{
	// update physics at a fixed time step 

	float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{ 
		for (auto pObject : m_objects)
		{
			pObject->fixedUpdate(m_gravity, m_timeStep);
		}  
		accumulatedTime -= m_timeStep; 
	
	}
	
	int objectCount = m_objects.size();

	//collision code
	for (int outer = 0; outer < objectCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < objectCount; inner++)
		{
			PhysicsObject* objectOne = m_objects[outer];
			PhysicsObject* objectTwo = m_objects[inner];
			ShapeType shapeIDOne = objectOne->GetShapeType();
			ShapeType shapeIDTwo = objectTwo->GetShapeType();

			//if either shape ID is a joint do NOT do collision code!!!
			if (shapeIDOne == ShapeType::JOINT  || shapeIDTwo == ShapeType::JOINT)
			{
			
				continue;
			}
				
			

			int FunctionID = ((int)shapeIDOne * int(ShapeType::COUNT) + (int)shapeIDTwo);
			collisionFunction CollisionFunctionPtr = collisionFunctions[FunctionID];

			if (CollisionFunctionPtr != nullptr)
			{
				//did a collision occour?
				auto result = CollisionFunctionPtr(objectOne, objectTwo);
				
				
				//scene not detecting collision???
				if (glm::length(result) > 0.001)
				{
					//debuging line which prints which collision function called when collision happens
					//std::cout << "collisionFunctionPtr = " <<(int)FunctionID << "\n";

					//RigidBody* r1 = (RigidBody*)objectOne;
					//RigidBody* r2 = (RigidBody*)objectTwo;
					
					//dynamic cast prevents plane from dissapearing entirely???
					RigidBody* r1 = dynamic_cast <RigidBody*>(objectOne);
					RigidBody* r2 = dynamic_cast <RigidBody*>(objectTwo);

					/*if (r1)
					{
						(r1->setVelocity(glm::vec2(0, 0)));
					}

					if (r2)
					{
						(r2->setVelocity(glm::vec2(0, 0)));
					}*/

					if (r1 && r2)
					{
						r1->setPosition(r1->getPosition() + 0.5f * result);
						r2->setPosition(r2->getPosition() - 0.5f * result);
						r1->resolveCollision(r2, result);

					}
					else if (r1)
					{
						r1->setPosition(r1->getPosition() + result);
						Plane* p = (Plane*)objectTwo;
						p->resolveCollisionWithPlane(r1);
					}
					else if (r2)
					{
						r2->setPosition(r2->getPosition() + result);
						Plane* p = (Plane*)objectOne;
						p->resolveCollisionWithPlane(r2);
					}
				}

			}

		}

	}



	//dirty physics code
	//static std::list<PhysicsObject*> dirty;
	//for (auto pObject : m_objects)
	//{
	//	for (auto pOtherObject : m_objects)
	//	{
	//		if (pObject == pOtherObject)
	//			continue;

	//		if (std::find(dirty.begin(), dirty.end(), pObject) != dirty.end() &&
	//			std::find(dirty.begin(), dirty.end(), pOtherObject) != dirty.end())
	//			continue;


	//		RigidBody* pRigid = dynamic_cast<RigidBody*>(pOtherObject);

	//		if (pRigid->checkCollision(pObject))
	//		{
	//			//std::cout << "COLLISION HAPPENED";
	//			pRigid->applyForceToObject(dynamic_cast<RigidBody*>(pObject), pRigid->getVelocity() * pRigid->getMass());
	//			dirty.push_back(pRigid);
	//			dirty.push_back(pOtherObject);
	//		}


	//	}
	//}
	//dirty.clear();

}

void PhysicsScene::updateGizmos()
{
	for (auto pObject : m_objects)
	{
		pObject->makeGizmo();
	}
}











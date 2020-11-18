#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Plane;
class AABB;
class Circle;
class PhysicsScene;
class Spring;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();



	aie::Renderer2D*	m_2dRenderer;
	//aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float randomNumberOne;
	float randomNumberTwo;

	PhysicsScene* myPhysicsScene;
	Circle* myCircle;
	Circle* mySecondCircle;
	Circle* myThirdCircle;
	Circle* myFourthCircle;

	AABB* myAABB;
	AABB* mySecondAABB;
	AABB* myThirdAABB;
	AABB* myFourthAABB;

	Plane* myPlane;
	Plane* mySecondPlane;
	Plane* myThirdPlane;
	Plane* myFourthPlane;

	Spring* mySpring;
	Spring* mySecondSpring;

	float m_timer;
	

};
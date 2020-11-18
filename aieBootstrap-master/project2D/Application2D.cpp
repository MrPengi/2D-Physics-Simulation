#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "PhysicsScene.h"
#include "Spring.h"
#include "Circle.h"
#include <ctime>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	setVSync(true);
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	//m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	srand(time(nullptr));

	m_timer = 0;

	myPhysicsScene = new PhysicsScene();
	myPhysicsScene->setTimeStep(0.016f);
	//myPhysicsScene->setGravity(glm::vec2(0, 1));

	//add the circles
	myCircle = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 0.1f, 5, 0.1f, 1,glm::vec4(1, 1, 0, 1));
	mySecondCircle = new Circle(glm::vec2(30, 1), glm::vec2(0, 0), 1, 3, 0, 1, glm::vec4(0.5f, 0, 1, 1));
	myThirdCircle = new Circle(glm::vec2(-60, 1), glm::vec2(0, 0), 1, 6, 1, 1, glm::vec4(0.9f, 0, 0.4f, 1));
	myFourthCircle = new Circle(glm::vec2(0, 0), glm::vec2(40, 0), 1, 6, 0, 0.9f, glm::vec4(1, 0, 1, 1));

	//add the AABBs
	myAABB = new AABB(glm::vec2(-30, 5), glm::vec2(5, 5), glm::vec2(0), 1, 0.5f, 0.3f, glm::vec4(1, 0.3f, 0, 1));
	mySecondAABB = new AABB(glm::vec2(0, 20), glm::vec2(10, 10), glm::vec2(0), 1, 0.5f, 1, glm::vec4(0, 0.7f, 1, 1));
	myThirdAABB = new AABB(glm::vec2(-10, 60), glm::vec2(7, 7), glm::vec2(0), 3, 2, 0.3f, glm::vec4(0.1f, 0.3f, 1, 1));
	myFourthAABB = new AABB(glm::vec2(-30, -30), glm::vec2(11, 11), glm::vec2(0), 1, 1, 0.5f, glm::vec4(0.1f, 0.9f, 0, 1));

	//add the planes
	myPlane = new Plane(glm::vec2(0, 100), -50.0f, 1, glm::vec4(1, 0.3f, 1, 1));
	mySecondPlane = new Plane(glm::vec2(10, 0), -80.0f, 1, glm::vec4(1, 0.3f, 1, 1));
	myThirdPlane = new Plane(glm::vec2(-10, 0), -80.0f, 1, glm::vec4(1, 0.3f, 1, 1));
	myFourthPlane = new Plane(glm::vec2(0, -100), -50.0f, 1, glm::vec4(1, 0.3f, 1, 1));

	mySpring = new Spring((RigidBody*)myThirdCircle, (RigidBody*)myFourthCircle, 4, 2, 0.1f/*, myThirdCircle->getPosition(), myFourthCircle->getPosition()*/);
	mySecondSpring = new Spring((RigidBody*)myThirdAABB, (RigidBody*)myThirdCircle, 4, 2, 0.1f/*, myThirdAABB->getPosition(), myThirdCircle->getPosition()*/);

	//add the circles to the physicsScene
	myPhysicsScene->addObject(myCircle);
	myPhysicsScene->addObject(mySecondCircle);
	myPhysicsScene->addObject(myThirdCircle);
	myPhysicsScene->addObject(myFourthCircle);

	//add the AABBs to the physicsScene
	myPhysicsScene->addObject(myAABB);
	myPhysicsScene->addObject(mySecondAABB);
	myPhysicsScene->addObject(myThirdAABB);
	myPhysicsScene->addObject(myFourthAABB);

	//add the planes to the physicsScene
	myPhysicsScene->addObject(myPlane);
	myPhysicsScene->addObject(mySecondPlane);
	myPhysicsScene->addObject(myThirdPlane);
	myPhysicsScene->addObject(myFourthPlane);

	//mySecondAABB->setKinematic(true);
	myFourthCircle->setKinematic(true);


	myPhysicsScene->addObject(mySpring);
	myPhysicsScene->addObject(mySecondSpring);

	myPhysicsScene->setGravity(glm::vec2(0, -1));
	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	//delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
	//deleting the physicsScene takes care of deleting the objects added to it
	delete myPhysicsScene;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	//update the random numbers
	randomNumberOne = rand() % 50;
	randomNumberTwo = rand() % 50;

	//clear gizmos
	aie::Gizmos::clear();

	//update the physicsScene and the Gizmos
	myPhysicsScene->update(deltaTime);
	myPhysicsScene->updateGizmos();

	//myCircle->makeGizmo();


	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	/*if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;*/

	//when space is pressed, make all circles and aabbs have a random force applied
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		//myCircle->applyForce(glm::vec2(-30, 0));
		//mySecondAABB->applyForce(glm::vec2(0, -100));
		myCircle->applyForce(glm::vec2(randomNumberOne, randomNumberTwo));
		mySecondCircle->applyForce(glm::vec2(randomNumberOne, randomNumberTwo));
		myThirdCircle->applyForce(glm::vec2(randomNumberOne, randomNumberTwo));
		myFourthCircle->applyForce(glm::vec2(randomNumberOne, randomNumberTwo));
	}

	//makes gravity go up
	if (input->wasKeyPressed(aie::INPUT_KEY_UP))
	{
		myPhysicsScene->setGravity(glm::vec2(0, 5));
	}

	//makes gravity go down
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
	{
		myPhysicsScene->setGravity(glm::vec2(0, -5));
	}

	//makes gravity go left
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
	{
		myPhysicsScene->setGravity(glm::vec2(-5, 0));
	}

	//makes gravity go right
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		myPhysicsScene->setGravity(glm::vec2(5, 0));
	}

	//m_2dRenderer->setCameraPos(camPosX, camPosY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	//m_2dRenderer->setRenderColour(0.5f, 0, 1, 1);
	//m_2dRenderer->drawCircle(30, 30, 5, 1);

	//m_2dRenderer->drawLine(0, 20, 2000, 20, 5);

	//// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	//m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	//// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);


	//GIZMOS RELATED DRAWING STUFFS
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));



	
	// output some text, uses the last used colour
	/*char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);*/

	// done drawing sprites
	m_2dRenderer->end();
}
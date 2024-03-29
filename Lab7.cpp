#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	
	//Add impulse to bag
	ball.applyImpulse(Vector2f(1, 0));
	
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	//Create Left wall
	PhysicsRectangle wallLeft;
	wallLeft.setSize(Vector2f(20, 600));
	wallLeft.setCenter(Vector2f(10, 300));
	wallLeft.setStatic(true);
	world.AddPhysicsBody(wallLeft);

	//Create Right wall
	PhysicsRectangle wallRight;
	wallRight.setSize(Vector2f(20, 600));
	wallRight.setCenter(Vector2f(790, 300));
	wallRight.setStatic(true);
	world.AddPhysicsBody(wallRight);

	//Create Celing
	PhysicsRectangle celing;
	celing.setSize(Vector2f(800, 20));
	celing.setCenter(Vector2f(400, 10));
	celing.setStatic(true);
	world.AddPhysicsBody(celing);

	//Create box
	PhysicsRectangle box;
	box.setSize(Vector2f(100, 200));
	box.setCenter(Vector2f(700, 300));
	box.setStatic(true);
	world.AddPhysicsBody(box);


	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	//Bang counter
	int bangCount(0);
	box.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (bangCount < 2) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);

		//Draw Walls, Celing, & box
		window.draw(wallLeft);
		window.draw(wallRight);
		window.draw(celing);
		window.draw(box);

		window.display();
	}
}

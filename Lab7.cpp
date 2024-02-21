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

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
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

		//Draw Walls & Celing
		window.draw(wallLeft);
		window.draw(wallRight);
		window.draw(celing);

		window.display();
	}
}

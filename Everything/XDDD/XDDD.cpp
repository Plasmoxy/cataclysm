// XDDD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////
int main(int argc, char * argv) {

	cout << "STARTING APP" << endl;

	// Create the main window
	sf::RenderWindow App(sf::VideoMode(800, 500, 32), "XDD Cube - SFML OpenGL");

	// Create a clock for measuring time elapsed
	sf::Clock clock;

	//prepare OpenGL surface for HSR
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.3f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 1000.0f);//fov, aspect, zNear, zFar

	bool rotate = true;
	float angle = 0.f;

	float dt = 0;
	float t_stamp = clock.getElapsedTime().asMilliseconds();

	// Start game loop
	while (App.isOpen()) {

		float currentTime = clock.getElapsedTime().asMilliseconds();
		dt = t_stamp - currentTime;
		t_stamp = currentTime;

		// Process events
		sf::Event Event;
		while (App.pollEvent(Event)) {
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				App.close();

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)) {
				rotate = !rotate;
			}

		}

		//Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations for the cube
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);

		if (rotate) {
			angle += dt*(0.001f);
		}
		glRotatef(angle * 50, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 90, 0.f, 0.f, 1.f);

		//Draw a cube
		glBegin(GL_QUADS);//draw some squares
		glVertex3i(50, 50, 50);
		glVertex3i(0, 50, 50);
		glVertex3i(0, 100, 50);
		glVertex3i(0, 100, 0);

		glEnd();


		App.display();
	}

	cout << "APP END" << endl;
	return EXIT_SUCCESS;
}
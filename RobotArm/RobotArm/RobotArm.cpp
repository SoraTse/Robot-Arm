// RobotArm.cpp : Defines the entry point for the console application.
//

//Aaron Tse C00172925
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "SFML/Window/Event.hpp"
#include <iostream> 
#include <cmath> 

int main()
{
	//Main window
	sf::RenderWindow window(sf::VideoMode(900, 700, 32), "SFML First Program");
	window.setFramerateLimit(60);

	//=========================================================================
	//4 triangles creating one arm
	const int size = 6;

	//Both parts of the arm
	sf::VertexArray FirstArm(sf::Triangles, size);
	sf::VertexArray SecondArm(sf::Triangles, size);

	//point declaration for triangles in arm
	sf::Vector2f tripoints[size];
	tripoints[0] = sf::Vector2f(0, 15);
	tripoints[1] = sf::Vector2f(80, 15);
	tripoints[2] = sf::Vector2f(80, -15);

	tripoints[3] = sf::Vector2f(0, -15);
	tripoints[4] = tripoints[0];
	tripoints[5] = tripoints[2];

	//6 triangles creating claw, so 18 points
	const int clawSize = 18;

	//Both claws
	sf::VertexArray firstClaw(sf::Triangles, clawSize);
	sf::VertexArray secondClaw(sf::Triangles, clawSize);

	//The first claws points
	sf::Vector2f clawtripoints[clawSize];
	clawtripoints[0] = sf::Vector2f(0, 7.5);
	clawtripoints[1] = sf::Vector2f(80, 7.5);
	clawtripoints[2] = sf::Vector2f(80, -7.5);

	clawtripoints[3] = sf::Vector2f(0, -7.5);
	clawtripoints[4] = clawtripoints[0];
	clawtripoints[5] = clawtripoints[2];

	clawtripoints[12] = clawtripoints[1];
	clawtripoints[13] = sf::Vector2f(95, 7.5);
	clawtripoints[14] = sf::Vector2f(95, -65);

	clawtripoints[15] = clawtripoints[1];
	clawtripoints[16] = clawtripoints[14];
	clawtripoints[17] = sf::Vector2f(80, -65);

	// second claw points flipped to mirror the the first.
	sf::Vector2f secondclawtripoints[clawSize];
	secondclawtripoints[0] = sf::Vector2f(0, 7.5);
	secondclawtripoints[1] = sf::Vector2f(80, 7.5);
	secondclawtripoints[2] = sf::Vector2f(80, -7.5);

	secondclawtripoints[3] = sf::Vector2f(0, -7.5);
	secondclawtripoints[4] = secondclawtripoints[0];
	secondclawtripoints[5] = secondclawtripoints[2];

	secondclawtripoints[12] = secondclawtripoints[2];
	secondclawtripoints[13] = sf::Vector2f(95, -7.5);
	secondclawtripoints[14] = sf::Vector2f(95, 65);

	secondclawtripoints[15] = secondclawtripoints[2];
	secondclawtripoints[16] = secondclawtripoints[14];
	secondclawtripoints[17] = sf::Vector2f(80, 65);


	//Rotations for each peice of the robot arm
	float FirstArmRotation = 0.0;
	float SecondArmRotation = 0.0;
	float FirstClawRotation = 30.0;
	float SecondClawRotation = -30.0;
	float rotationVel = 5.0;

	//Translation Vectors for each shape
	sf::Vector2f FirstArmPos(200, 300);
	sf::Vector2f SecondArmPos(80, 0);
	sf::Vector2f FirstClawPos(80, 15);
	sf::Vector2f SecondClawPos(80, -15);

	// Start loop 
	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{ 
			if (Event.type == sf::Event::Closed)
				window.close();
 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
			//Listening for key presses to move the arms
			//first arm move up
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
				if (FirstArmRotation <= 90) FirstArmRotation += rotationVel;
			//moving down
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A))
				if (FirstArmRotation >= -90) FirstArmRotation -= rotationVel;
			//second arm part move up
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Z))
				if (SecondArmRotation <= 90) SecondArmRotation += rotationVel;
			//moving down
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::X))
				if (SecondArmRotation >= -90) SecondArmRotation -= rotationVel;
			//moving both claws outwards
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
				if (FirstClawRotation <= 90) FirstClawRotation += rotationVel;
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
				if (SecondClawRotation >= -90) SecondClawRotation -= rotationVel;
			//moving both claws in
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
				if (FirstClawRotation >= 30) FirstClawRotation -= rotationVel;
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
				if (SecondClawRotation <= -30) SecondClawRotation += rotationVel;

		}

		//--First arm part--
		//first arm part position
		sf::Transform firstArmT;
		firstArmT.translate(FirstArmPos);

		//first arm part rotations
		sf::Transform firstArmR;
		firstArmR.rotate(FirstArmRotation);

		//creates the movement
		sf::Transform firstArmM = firstArmT*firstArmR;

		//update lines
		for (int i = 0; i<size; i++) {
			FirstArm[i].position = firstArmM.transformPoint(tripoints[i]);
			FirstArm[i].color = sf::Color::Green;
		}

		//--Second arm part--
		//second arm part position
		sf::Transform secondArmT;
		secondArmT.translate(SecondArmPos);

		//second arm point rotation
		sf::Transform secondArmR;
		secondArmR.rotate(SecondArmRotation);

		//creates the movement
		sf::Transform secondArmM = firstArmT*firstArmR*secondArmT*secondArmR;


		//update lines
		for (int i = 0; i<size; i++) {
			SecondArm[i].position = secondArmM.transformPoint(tripoints[i]);
			SecondArm[i].color = sf::Color::Cyan;
		}

		//--First claw part--
		//first claw part position
		sf::Transform firstClawT;
		firstClawT.translate(FirstClawPos);

		//first claw part rotation
		sf::Transform firstClawR;
		firstClawR.rotate(FirstClawRotation);

		//creates the movement
		sf::Transform firstClawM = firstArmT*firstArmR*secondArmT*secondArmR*firstClawT*firstClawR;

		//update lines
		for (int i = 0; i<clawSize; i++) {
			firstClaw[i].position = firstClawM.transformPoint(clawtripoints[i]);
			firstClaw[i].color = sf::Color::Red;
		}

		//--Second claw part--
		//second claw part postion
		sf::Transform secondClawT;
		secondClawT.translate(SecondClawPos);

		//second claw part rotation
		sf::Transform secondClawR;
		secondClawR.rotate(SecondClawRotation);

		//creates the movement
		sf::Transform secondClawM = firstArmT*firstArmR*secondArmT*secondArmR*secondClawT*secondClawR;

		//update lines
		for (int i = 0; i<clawSize; i++) {
			secondClaw[i].position = secondClawM.transformPoint(secondclawtripoints[i]);
			secondClaw[i].color = sf::Color::Red;
		}

		window.clear();
		//Draw each of the shapes
		window.draw(FirstArm);
		window.draw(SecondArm);
		window.draw(firstClaw);
		window.draw(secondClaw);

		window.display();
	}

	return EXIT_SUCCESS;
}


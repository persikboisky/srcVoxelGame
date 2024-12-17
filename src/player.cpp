#define PI 3.14

#include "Player.hpp"
#include "window/Camera.hpp"
#include "window/Window.hpp"
#include "window/Event.hpp"
#include "window/Cursor.hpp"
#include "graphics/Shader.hpp"
#include "load/JSON.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

const int FOV = json::getValueFromJSON("./assets/config.json", "FOV");
const int KEY_UP = json::getValueFromJSON("./assets/config.json", "KEY_UP");
const int KEY_DOWN = json::getValueFromJSON("./assets/config.json", "KEY_DOWN");
const int KEY_FRONT = json::getValueFromJSON("./assets/config.json", "KEY_FRONT");
const int KEY_REAR = json::getValueFromJSON("./assets/config.json", "KEY_REAR");
const int KEY_LEFT = json::getValueFromJSON("./assets/config.json", "KEY_LEFT");
const int KEY_RIGHT = json::getValueFromJSON("./assets/config.json", "KEY_RIGHT");

const float SPEED_MOUSE = 1.5f;
const float SPEED_CAMERA = 0.01f;

const float acceleration = 2.0f;   

Camera camera(glm::vec3(2, 0, 2), FOV); 

float deltaX = 0;
float deltaY = 0;
float moveX = 0.0f, moveZ = 0.0f;

bool Cursor = true;

void player::review()
{
	double mouseX = Event::mouse::GetMouseCordX() - (float)Window::width / 2.0f;
	double mouseY = Event::mouse::GetMouseCordY() - (float)Window::height / 2.0f;

	deltaX += 1 / (float)Window::width * -(float)mouseX;
	deltaY += 1 / (float)Window::height * -(float)mouseY;

	if (deltaX >= PI * 2) deltaX -= PI * 2;
	if (deltaX <= -PI * 2) deltaX += PI * 2;

	if (deltaY >= PI * 2) deltaY -= PI * 2;
	if (deltaY <= -PI * 2) deltaY += PI * 2;

	//std::cout << deltaX << ":" << deltaY << std::endl;
	cursor::setPosition(640, 360);
	
	camera.resetRotate();
	camera.rotate(deltaY, deltaX, 0.0f);

}

void player::move()
{ 

	if (deltaX >= 0)
	{
		if (deltaX <= PI / 2)
		{
			moveX = (deltaX / 157.0f) * acceleration;
			moveZ = (0.01f - deltaX / 157.0f) * acceleration;
		}
		else if (deltaX < PI)
		{
			moveX = (0.01f - (deltaX - 1.57f) / 157.0f) * acceleration;
			moveZ = ((1.57f - deltaX) / 157.0f) * acceleration;
		}
		else if (deltaX < PI / 2 + PI)
		{
			moveX = (PI - deltaX) / 157.0f * acceleration; 
			moveZ = -(0.01f - (deltaX - PI) / 157.0f) * acceleration;
		}
		else if (deltaX < PI * 2)
		{
			moveX = -(0.01f - (deltaX - (PI / 2 + PI)) / 157.0f) * acceleration;
			moveZ = -((PI / 2 + PI - deltaX) / 157.0f) * acceleration;
		}
	}
	else
	{
		if (deltaX > -(PI / 2.0f)) 
		{
			moveX = (deltaX / 157.0f) * acceleration;
			moveZ = (0.01f + deltaX / 157.0f) * acceleration;
		}
		else if (deltaX > -PI)
		{
			moveX = -(0.01f + (deltaX + 1.57f) / 157.0f) * acceleration;
			moveZ = ((1.57f + deltaX) / 157.0f) * acceleration;
		}
		else if (deltaX > -(PI / 2 + PI))
		{
			moveX = -((PI + deltaX) / 157.0f) * acceleration; 
			moveZ = -(0.01f + (deltaX + PI) / 157.0f) * acceleration;
		}
		else if (deltaX > -(PI * 2))
		{
			moveX = (0.01f + (deltaX + (PI / 2 + PI)) / 157.0f) * acceleration;
			moveZ = -((PI / 2 + PI + deltaX) / 157.0f) * acceleration;
		}
	}

	if (Event::key::getKey(GLFW_KEY_LEFT_CONTROL))
	{
		moveX *= 2.0f;
		moveZ *= 2.0f;
	}


	if (Event::key::getKey(KEY_REAR)) camera.move(moveX, 0.0f, moveZ);
	else if (Event::key::getKey(KEY_FRONT)) camera.move(-moveX, 0.00f, -moveZ);

	if (Event::key::getKey(KEY_LEFT)) camera.move(-moveZ, 0.0f, moveX);
	else if (Event::key::getKey(KEY_RIGHT)) camera.move(moveZ, 0.0f, -moveX);

	if (Event::key::getKey(KEY_DOWN)) camera.move(0.0f, -SPEED_CAMERA, 0.0f);
	else if (Event::key::getKey(KEY_UP)) camera.move(0.0f, SPEED_CAMERA, 0.0f);
}

void player::update()
{
	review();
	move();
	shader::setValueUniform(camera.getProj() * camera.getView(), "matCamera");
}
#include <iostream>

#include "Ship.h"

#include <Core/Engine.h>

double Ship::shipLength = 35;

Ship::Ship()
{
}

Ship::Ship(std::string name, glm::vec2 center, double speed, glm::vec3 color)
{
	this->name = name;
	this->center = center;
	this->color = color;
	height = sqrt(3) * shipLength / 2.5;
	this->speed = speed;
	angle = 0;
	timeOfDestroy = 0;
	scaleFactor = 1;

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 4, 3
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-shipLength / 2, -height, 0), color),
		VertexFormat(glm::vec3(shipLength / 2, -height, 0), color),
		VertexFormat(glm::vec3(-shipLength / 2,  height, 0), color),
		VertexFormat(glm::vec3(shipLength / 2,  height, 0), color)
	};

	setIndices(indices);
	setVertices(vertices);
}

double Ship::getHeight() {
	return height;
}

void Ship::doubleSpeed()
{
	speed *= 2;
}

void Ship::setSpeed(double speed)
{
	this->speed = speed;
}

double Ship::getSpeed()
{
	return speed;
}

void Ship::updateCenterX(double value) {
	center = glm::vec2(center.x + value, center.y);
}

void Ship::updateCenterY(double value) {
	center = glm::vec2(center.x, center.y + value);
}

void Ship::setTimeOfDestroy(double value)
{
	timeOfDestroy = value;
}

double Ship::getTimeOfDestroy()
{
	return timeOfDestroy;
}

double Ship::getScaleFactor()
{
	return scaleFactor;
}

void Ship::decrementScaleFactor(double value)
{
	scaleFactor -= value;
}

#include <iostream>
#include "Star.h"

double Star::length = 16;
double Star::height = 24;
double Star::period = 2.5;

Star::Star(std::string name, glm::vec3 color)
{
	this->name = name;
	this->color = color;
	speed = 1.5;
	visible = false;
	timeOfLastUse = 0;
	inUse = false;

	std::vector<unsigned short> indices =
	{
		0, 2, 1,
		0, 4, 2,
		0, 3, 4,
		0, 1, 3,
		1, 6, 3,
		1, 2, 7,
		2, 4, 5,
		4, 3, 8
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-length / 2, length / 2, 0), color),
		VertexFormat(glm::vec3(length / 2, length / 2, 0), color),
		VertexFormat(glm::vec3(- length / 2, -length / 2, 0), color),
		VertexFormat(glm::vec3(length / 2, -length / 2, 0), color),
		VertexFormat(glm::vec3(length / 2 + height, 0, 0), color),
		VertexFormat(glm::vec3(-length / 2 - height, 0, 0), color),
		VertexFormat(glm::vec3(0, length / 2 + height, 0), color),
		VertexFormat(glm::vec3(0, -length / 2 - height, 0), color)
	};

	setIndices(indices);
	setVertices(vertices);
}

bool Star::isVisible()
{
	return visible;
}

void Star::setVisibility(bool value)
{
	visible = value;
}

bool Star::isInUse()
{
	return inUse;
}

void Star::useStarGun(bool value)
{
	inUse = value;
}

void Star::updateCenterY(double value) {
	center = glm::vec2(center.x, center.y + value);
}

double Star::getSpeed()
{
	return speed;
}

void Star::updateTimeOfLastUse(double currentTime)
{
	timeOfLastUse = currentTime;
}

double Star::getTimeOfLastUse()
{
	return timeOfLastUse;
}
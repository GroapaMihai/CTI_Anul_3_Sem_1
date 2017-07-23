#include <iostream>

#include "Tower.h"

#include <Core/Engine.h>

float Tower::shootingInterval = 5;

Tower::Tower(glm::vec3 position, float scale)
{
	this->position = position;
	this->scale = scale;
}

glm::vec3 Tower::getPosition()
{
	return position;
}

float Tower::getScale()
{
	return scale;
}

void Tower::setTimeOfLastShoot(double time)
{
	this->timeOfLastShoot = time;
}

double Tower::getTimeOfLastShoot()
{
	return timeOfLastShoot;
}

void Tower::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

glm::mat4 Tower::getModelMatrix()
{
	return modelMatrix;
}
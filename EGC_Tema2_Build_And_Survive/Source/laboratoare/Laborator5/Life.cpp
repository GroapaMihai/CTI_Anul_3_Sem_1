#include <iostream>

#include "Life.h"

#include <Core/Engine.h>

Life::Life()
{

}

void Life::setDisplacement(glm::vec3 displacement)
{
	this->displacement = displacement;
}

void Life::setAxis(char axis)
{
	this->axis = axis;
}

glm::vec3 Life::getDisplacement()
{
	return displacement;
}

char Life::getAxis()
{
	return axis;
}
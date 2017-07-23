#include <iostream>

#include "PlayerShip.h"

#include <Core/Engine.h>

PlayerShip::PlayerShip(std::string name, glm::vec2 center, double speed, glm::vec3 color)
{
	this->name = name;
	this->center = center;
	this->color = color;
	height = sqrt(3) * Ship::shipLength / 2.5;
	this->speed = speed;
	lifes = 3;
	starGuns = 0;

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

int PlayerShip::getLifes()
{
	return lifes;
}

void PlayerShip::addLife()
{
	lifes++;
}

void PlayerShip::removeLife()
{
	lifes--;
}

void PlayerShip::addStarGun()
{
	starGuns++;
}

void PlayerShip::removeStarGun()
{
	starGuns--;
}

int PlayerShip::nrOfStarGuns()
{
	return starGuns;
}
#include <iostream>

#include "Bullet.h"

#include <Core/Engine.h>

double Bullet::bulletLength = 30;
double Bullet::bulletWidth = 10;
double Bullet::bulletSpeed = 6;

Bullet::Bullet(std::string name, glm::vec3 color)
{
	this->name = name;
	this->color = color;

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		3, 1, 2
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-bulletWidth / 2, -bulletLength / 2, 0), color),
		VertexFormat(glm::vec3(-bulletWidth / 2,  bulletLength / 2, 0), color),
		VertexFormat(glm::vec3(bulletWidth / 2,  bulletLength / 2, 0), color),
		VertexFormat(glm::vec3(bulletWidth / 2, -bulletLength / 2, 0), color)
	};

	setIndices(indices);
	setVertices(vertices);
}
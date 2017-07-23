#include <iostream>

#include "Heart.h"

#include <Core/Engine.h>

double Heart::length = 14;

Heart::Heart(std::string name, glm::vec3 color)
{
	this->name = name;
	this->color = color;
	speed = 1.5;

	std::vector<unsigned short> indices =
	{
		8, 15, 7,
		15, 6, 7,
		8, 1, 13,
		5, 6, 14,
		11, 2, 9,
		2, 3, 9,
		3, 4, 10,
		4, 12, 10,
		11, 13, 2,
		13, 1, 2,
		2, 1, 3,
		1, 0, 3,
		0, 4, 3,
		0, 5, 4,
		5, 12, 4,
		5, 14, 12,
		8, 0, 1,
		8, 7, 0,
		7, 5, 0,
		7, 6, 5
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-length, 0, 0), color),
		VertexFormat(glm::vec3(-length, length, 0), color),
		VertexFormat(glm::vec3(0, length, 0), color),
		VertexFormat(glm::vec3(length, length, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, -length, 0), color),
		VertexFormat(glm::vec3(0, -length, 0), color),
		VertexFormat(glm::vec3(-length, -length, 0), color),
		VertexFormat(glm::vec3(-length, 2 * length, 0), color),
		VertexFormat(glm::vec3(length, 2 * length, 0), color),
		VertexFormat(glm::vec3(-2 * length, length, 0), color),
		VertexFormat(glm::vec3(2 * length, length, 0), color),
		VertexFormat(glm::vec3(-2 * length, 0, 0), color),
		VertexFormat(glm::vec3(2 * length, 0, 0), color),
		VertexFormat(glm::vec3(0, - 2 * length, 0), color)
	};

	setIndices(indices);
	setVertices(vertices);
}

bool Heart::isVisible()
{
	return visible;
}

void Heart::setVisibility(bool value)
{
	visible = value;
}

void Heart::updateCenterY(double value) {
	center = glm::vec2(center.x, center.y + value);
}

double Heart::getSpeed()
{
	return speed;
}
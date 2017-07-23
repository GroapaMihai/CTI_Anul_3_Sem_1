#include <iostream>

#include "MyRectangle.h"

#include <Core/Engine.h>

MyRectangle::MyRectangle(std::string name, double length, double width, glm::vec3 color)
{
	this->name = name;
	this->length = length;
	this->width = width;
	this->color = color;

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		3, 1, 2
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-width / 2, -length / 2, 0), color),
		VertexFormat(glm::vec3(-width / 2,  length / 2, 0), color),
		VertexFormat(glm::vec3(width / 2,  length / 2, 0), color),
		VertexFormat(glm::vec3(width / 2, -length / 2, 0), color)
	};

	setIndices(indices);
	setVertices(vertices);
}
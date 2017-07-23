#include <iostream>

#include "Rectangle.h"

#include <Core/Engine.h>

std::vector<unsigned short> Rectangle::indices =
{
	0, 3, 1,
	1, 3, 2
};

Rectangle::Rectangle(std::string name, glm::vec3 leftBottomCorner, double length, double width, glm::vec3 color)
{
	this->name = name;
	this->leftBottomCorner = leftBottomCorner;
	this->length = length;
	this->width = width;
	this->color = color;
}

Mesh* Rectangle::CreateMesh()
{
	double x = leftBottomCorner.x;
	double y = leftBottomCorner.y;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftBottomCorner, color),
		VertexFormat(glm::vec3(x + width, y, 0), color),
		VertexFormat(glm::vec3(x + width, y + length, 0), color),
		VertexFormat(glm::vec3(x, y + length, 0), color)
	};

	// Create the VAO and bind it
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Create the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Check for OpenGL errors
	CheckOpenGLError();

	Mesh* rectangle = new Mesh(name);
	rectangle->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));

	return rectangle;
}
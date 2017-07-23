#include <iostream>
#include <Core/Engine.h>
#include "WireFrame.h"

WireFrame::WireFrame()
{
	smallSquareSide = 0.05f;
	nrOfSquares = 100;
	int i, j;

	for (i = 0; i < (nrOfSquares - 1) * nrOfSquares; i++)
		if ((i + 1) % nrOfSquares == 0)
			continue;
		else
		{
			indices.push_back(i);
			indices.push_back(i + nrOfSquares);
			indices.push_back(i + nrOfSquares + 1);
			indices.push_back(i);
			indices.push_back(i + nrOfSquares + 1);
			indices.push_back(i + 1);
		}

	for (i = 0; i < nrOfSquares; i++)
		for (j = 0; j < nrOfSquares; j++)
			vertices.push_back(VertexFormat(glm::vec3(j * smallSquareSide, 0, i * smallSquareSide), glm::vec3(0, 0, 1)));


}
void WireFrame::setName(std::string name)
{
	this->name = name;
}

std::string WireFrame::getName()
{
	return name;
}

void WireFrame::setIndices(std::vector<unsigned short> indices)
{
	this->indices = indices;
}

void WireFrame::setVertices(std::vector<VertexFormat> vertices)
{
	this->vertices = vertices;
}

void WireFrame::setColor(glm::vec3 color)
{
	this->color = color;
}

Mesh* WireFrame::CreateMesh()
{
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

	Mesh* mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));

	return mesh;
}

float WireFrame::getWireFrameWidth()
{
	return nrOfSquares * smallSquareSide;
}
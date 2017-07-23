#include "Point.h"

Point::Point(std::string name, double radius, glm::vec3 color)
{
	this->name = name;
	this->radius = radius;
	this->color = color;
	setCenter(glm::vec2(0, 0));

	//construiesc lista de puncte tinand cont de raza
	int step = 5;
	double x, y;

	// creare vertecsi
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
	for (double u = 0; u <= 360; u += step)
	{
		x = radius * cos(glm::radians(u));
		y = radius * sin(glm::radians(u));
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
	}

	int triangles = 360 / step;

	// adaugare indici
	for (int i = 1; i < triangles; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back((i + 1) % (triangles + 1));
	}

	indices.push_back(0);
	indices.push_back(triangles);
	indices.push_back(1);

	setIndices(indices);
	setVertices(vertices);
}

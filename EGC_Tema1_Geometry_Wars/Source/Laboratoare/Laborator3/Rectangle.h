#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Rectangle
{
public:
	Rectangle(std::string name, glm::vec3 leftBottomCorner, double length, double width, glm::vec3 color);
	Mesh* CreateMesh();

protected:
	std::string name;
	glm::vec3 leftBottomCorner;
	double length;
	double width;
	glm::vec3 color;
	static std::vector<unsigned short> indices;
};


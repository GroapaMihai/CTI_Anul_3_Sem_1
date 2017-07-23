#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class MyRectangle : public GameObject
{
	public:
		MyRectangle(std::string name, double length, double width, glm::vec3 color);

	protected:
		double length;
		double width;
		glm::vec3 color;
};


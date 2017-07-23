#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class Point : public GameObject
{
	public:
		Point(std::string name, double radius, glm::vec3 color);

	protected:
		double radius;
};
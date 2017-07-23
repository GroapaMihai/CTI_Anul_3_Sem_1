#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "Point.h"

class Circle
{
	public:
		Circle(double radius, double pointRadius, int step, glm::vec3 color);
		std::vector<Point*> getPoints();
		glm::vec3 getColor();

	protected:
		double radius;
		double pointRadius;
		std::vector<Point*> points;
		glm::vec3 color;
};
#include "Circle.h"

Circle::Circle(double radius, double pointRadius, int step, glm::vec3 color)
{
	this->radius = radius;
	this->color = color;
	double x, y;
	Point* p;

	for (double u = 0; u <= 360; u += step)
	{
		x = radius * cos(glm::radians(u));
		y = radius * sin(glm::radians(u));
		p = new Point("point", pointRadius, color);
		p->setCenter(glm::vec2(x, y));
		points.push_back(p);
	}
}

std::vector<Point*> Circle::getPoints()
{
	return points;
}

glm::vec3 Circle::getColor()
{
	return color;
}
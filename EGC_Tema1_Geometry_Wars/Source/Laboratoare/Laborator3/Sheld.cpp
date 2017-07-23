#include "Shield.h"

Shield::Shield(double radius, double centerPointRadius, MyColor color)
{
	backgroundPoint = new Point("point", radius, color.brown);
	centralPoint = new Point("point", centerPointRadius, color.white);
	speed = 1.5;
}

std::vector<Point*> Shield::getPoints()
{
	return points;
}


bool Shield::isVisible()
{
	return visible;
}

void Shield::setVisibility(bool value)
{
	visible = value;
}

void Shield::updateCenterY(double value) {
	center = glm::vec2(center.x, center.y + value);
}

double Shield::getSpeed()
{
	return speed;
}

double Shield::getRadius()
{
	return radius;
}
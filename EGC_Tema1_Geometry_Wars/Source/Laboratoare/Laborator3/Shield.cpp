#include "Shield.h"

double Shield::period = 5;
double Shield::collectibleRadius = 30;
double Shield::shieldRadius = 120;
double Shield::smallPointRadius = 6;

Shield::Shield(glm::vec3 color)
{
	collectible = new Circle(collectibleRadius, smallPointRadius, 36, color);
	centralPoint = new Point("point", smallPointRadius, color);
	shield = new Circle(shieldRadius, smallPointRadius, 12, color);
	speed = 1.5;
}

std::vector<Point*> Shield::getCollectiblePoints()
{
	return collectible->getPoints();
}

std::vector<Point*> Shield::getShieldPoints()
{
	return shield->getPoints();
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

bool Shield::isInUse()
{
	return inUse;
}

void Shield::useShield(bool value)
{
	inUse = value;
}

void Shield::updateTimeOfLastUse(double currentTime)
{
	timeOfLastUse = currentTime;
}

double Shield::getTimeOfLastUse()
{
	return timeOfLastUse;
}

double Shield::getSpeed()
{
	return speed;
}
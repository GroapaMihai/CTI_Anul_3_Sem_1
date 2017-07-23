#include <iostream>

#include "Enemy.h"

#include <Core/Engine.h>

float Enemy::initialScale = 1;
float Enemy::initialLength = 2.3f;
float Enemy::initialWidth = 1;
float Enemy::initialHeight = 2.5f;
float Enemy::diagonal = sqrt(Enemy::initialLength * Enemy::initialLength + Enemy::initialWidth * Enemy::initialWidth);
float Enemy::fallingInterval = 2.5f;
float Enemy::fallingSpeed = 0.8f;

Enemy::Enemy(std::string name, glm::vec3 position, float scale, float angle, double health)
{
	this->name = name;
	this->position = position;
	this->scale = scale;
	this->angle = angle;
	this->health = health;
	segment = 1;
	fallingAngle = 0;
}

std::string Enemy::getName()
{
	return name;
}

void Enemy::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Enemy::getPosition()
{
	return position;
}

void Enemy::shrink(float step)
{
	scale = max(scale - step, 0);
}

float Enemy::getScale()
{
	return scale;
}

float Enemy::getAngle()
{
	return angle;
}

void Enemy::updateAngle(float x, float z)
{
	if (segment == 1)
	{
		turningAngle = atan(abs(x / z));
		angle -= RADIANS(90);
		angle -= turningAngle;
	}
	else if (segment == 2)
		angle = RADIANS(90);

	segment++;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

float Enemy::getSpeed()
{
	return speed;
}

int Enemy::getSegment()
{
	return segment;
}

void Enemy::decreaseHealth(int value)
{
	health -= value;
}

bool Enemy::isDead()
{
	return (health <= 0);
}

void Enemy::updateFallingAngle(float value)
{
	fallingAngle += value;
}

float Enemy::getFallingAngle()
{
	return fallingAngle;
}

void Enemy::setTimeOfDead(double time)
{
	timeOfDead = time;
}

double Enemy::getTimeOfDead()
{
	return timeOfDead;
}

void Enemy::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

glm::mat4 Enemy::getModelMatrix()
{
	return modelMatrix;
}
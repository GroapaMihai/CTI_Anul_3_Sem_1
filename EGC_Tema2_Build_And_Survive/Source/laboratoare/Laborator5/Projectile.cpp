#include <iostream>

#include "Projectile.h"

#include <Core/Engine.h>

float Projectile::pistolShootInterval = 0.8f;
float Projectile::sniperShootInterval = 0.4f;
float Projectile::grenadeShootInterval = 1.6f;

int Projectile::launchAngle = 45;
float Projectile::gravity_acc = 9.8f;
int Projectile::V0 = 10;
float Projectile::Vy_0 = V0 * sin(RADIANS(launchAngle));

Projectile::Projectile(glm::vec3 position, double angle, int damage, float bound)
{
	this->position = position;
	this->angle = angle;
	this->damage = damage;
	this->bound = bound;
}

void Projectile::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Projectile::getPosition()
{
	return position;
}

void Projectile::setSpeed(float speed)
{
	this->speed = speed;
}

float Projectile::getSpeed()
{
	return speed;
}

double Projectile::getAngle()
{
	return angle;
}

void Projectile::setScale(float scale)
{
	this->scale = scale;
}

float Projectile::getScale()
{
	return scale;
}

int Projectile::getDamage()
{
	return damage;
}

float Projectile::getBound()
{
	return bound;
}

void Projectile::setType(int type)
{
	this->type = type;
}

int Projectile::getType()
{
	return type;
}

void Projectile::setTimeOfLaunch(double time)
{
	timeOfLaunch = time;
}

double Projectile::getTimeOfLaunch()
{
	return timeOfLaunch;
}

float Projectile::getVelocity_Y(double time)
{
	velocity_Y = Projectile::Vy_0 - Projectile::gravity_acc * time;
	return velocity_Y;
}
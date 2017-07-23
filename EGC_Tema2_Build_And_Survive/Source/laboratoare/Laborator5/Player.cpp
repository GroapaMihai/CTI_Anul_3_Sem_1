#include <iostream>

#include "Player.h"

#include <Core/Engine.h>

float Player::radius = 1;
float Player::fallingInterval = 2.5f;
float Player::fallingSpeed = 0.8f;

Player::Player(std::string name, glm::vec3 position, float speed)
{
	this->name = name;
	this->position = position;
	this->speed = speed;
	fallingAngle = 0;
	angle = 90;
	currentGun = 1;
	timeOfLastPistolShoot = 0;
	timeOfLastSniperShoot = 0;
	timeOfLastGrenadeShoot = 0;
}

std::string Player::getName()
{
	return name;
}

glm::vec3 Player::getPosition()
{
	return position;
}

float Player::getSpeed()
{
	return speed;
}

void Player::updateCenterX(float value)
{
	position = glm::vec3(position.x + value, position.y, position.z);
}

void Player::updateCenterZ(float value)
{
	position = glm::vec3(position.x, position.y, position.z + value);
}

void Player::updateFallingAngle(float value)
{
	fallingAngle += value;
}

float Player::getFallingAngle()
{
	return fallingAngle;
}

void Player::setAngle(float angle)
{
	this->angle = angle;
}

void Player::updateAngle(float value)
{
	angle += value;
}

float Player::getAngle()
{
	return angle;
}

void Player::setCurrentGun(int currentGun)
{
	this->currentGun = currentGun;
}

int Player::getCurrentGun()
{
	return currentGun;
}

void Player::setTimeOfLastPistolShoot(double time)
{
	timeOfLastPistolShoot = time;
}

double Player::getTimeOfLastPistolShoot()
{
	return timeOfLastPistolShoot;
}

void Player::setTimeOfLastSniperShoot(double time)
{
	timeOfLastSniperShoot = time;
}

double Player::getTimeOfLastSniperShoot()
{
	return timeOfLastSniperShoot;
}

void Player::setTimeOfLastGrenadeShoot(double time)
{
	timeOfLastGrenadeShoot = time;
}

double Player::getTimeOfLastGrenadeShoot()
{
	return timeOfLastGrenadeShoot;
}

void Player::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

glm::mat4 Player::getModelMatrix()
{
	return modelMatrix;
}
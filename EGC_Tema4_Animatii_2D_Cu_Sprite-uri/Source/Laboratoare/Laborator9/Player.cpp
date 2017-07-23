#include <iostream>
#include <Core/Engine.h>
#include "Player.h"

Player::Player(glm::vec3 position)
{
	vertices =
	{
		glm::vec3(0.5f,   0.5f, 0.0f),
		glm::vec3(0.5f,  -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f,  0.5f, 0.0f)
	};

	width = vertices[0].x - vertices[3].x;
	height = vertices[3].y - vertices[1].y;

	normals =
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	textureCoords =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
	};

	indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	this->position = position;
}

std::vector<glm::vec3> Player::getVertices()
{
	return vertices;
}

std::vector<glm::vec3> Player::getNormals()
{
	return normals;
}

std::vector<glm::vec2> Player::getTextureCoords()
{
	return textureCoords;
}

std::vector<unsigned short> Player::getIndices()
{
	return indices;
}

void Player::updateTextureCoords(std::vector<glm::vec2> newTextureCoords)
{
	textureCoords = newTextureCoords;
}

void Player::addAnimation(std::string name)
{
	animations.push_back(new Animation(name));
}

void Player::addFrameToLastAnimation()
{
	int indexOfLastAnimation = animations.size() - 1;
	std::string nameOfLastAnimation = animations[indexOfLastAnimation]->getName();
	int indexOfCurrentFrame = animations[indexOfLastAnimation]->getNumberOfFrames();
	std::string currentFrameName = nameOfLastAnimation + std::to_string(indexOfCurrentFrame);

	Mesh* mesh = new Mesh(currentFrameName);
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	
	animations[indexOfLastAnimation]->addFrame(mesh);
	animations[indexOfLastAnimation]->addTextureWidth(textureCoords[3].x - textureCoords[0].x);
}

Animation* Player::getAnimationNamed(std::string name)
{
	for (int i = 0; i < animations.size(); i++)
		if (animations[i]->getName() == name)
			return animations[i];

	return NULL;
}

void Player::computeAverageTextureWidthOfAnimations()
{
	for (int i = 0; i < animations.size(); i++)
		animations[i]->computeAverageTextureWidth();
}

void Player::computeScaleFactors()
{
	for (int i = 0; i < animations.size(); i++) {
		animations[i]->computeScaleFactors();
		animations[i]->setFramePeriod();
	}
}

void Player::setCurrentAnimation(std::string animationName)
{
	currentAnimation = getAnimationNamed(animationName);
}

Animation* Player::getCurrentAnimation()
{
	return currentAnimation;
}

short Player::getDirection()
{
	return direction;
}

void Player::setDirection(short direction)
{
	this->direction = direction;
}

void Player::turnOppositeDirection()
{
	if (direction == 0)
		direction = 1;
	else
		direction = 0;
}

void Player::setSpeed(float value)
{
	speed = value;
}

float Player::getSpeed()
{
	return speed;
}

void Player::updatePosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Player::getPosition()
{
	return position;
}

void Player::setTimeOfAttack(double time)
{
	timeOfAttack = time;
}

double Player::getTimeOfAttack()
{
	return timeOfAttack;
}

double Player::getWidth()
{
	return width;
}

double Player::getHeight()
{
	return height;
}

std::string Player::getCurrentAnimationName()
{
	return currentAnimation->getName();
}
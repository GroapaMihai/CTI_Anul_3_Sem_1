#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Animation.h"

class Player
{
	public:
		Player(glm::vec3 position);
		std::vector<glm::vec3> getVertices();
		std::vector<glm::vec3> getNormals();
		std::vector<glm::vec2> getTextureCoords();
		std::vector<unsigned short> getIndices();
		void updateTextureCoords(std::vector<glm::vec2> newTextureCoords);
		void addAnimation(std::string name);
		void addFrameToLastAnimation();
		Animation* getAnimationNamed(std::string name);
		void computeAverageTextureWidthOfAnimations();
		void computeScaleFactors();
		void setCurrentAnimation(std::string animationName);
		Animation* getCurrentAnimation();
		short getDirection();
		void setDirection(short direction);
		void turnOppositeDirection();
		void setSpeed(float value);
		float getSpeed();
		void updatePosition(glm::vec3 newPosition);
		glm::vec3 getPosition();
		void setTimeOfAttack(double time);
		double getTimeOfAttack();
		double getWidth();
		double getHeight();
		std::string getCurrentAnimationName();

	protected:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		std::vector<unsigned short> indices;
		std::vector<Animation*> animations;
		Animation* currentAnimation;
		short direction;
		float speed = 2.2f;
		glm::vec3 position;
		double timeOfAttack;
		double width;
		double height;
};
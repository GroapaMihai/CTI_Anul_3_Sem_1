#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Enemy
{
	public:
		Enemy(std::string name, glm::vec3 position, float scale, float angle, double health);
		std::string getName();
		void setPosition(glm::vec3 position);
		glm::vec3 getPosition();
		void shrink(float step);
		float getScale();
		float getAngle();
		void updateAngle(float x, float z);
		void setSpeed(float speed);
		float getSpeed();
		int getSegment();
		void decreaseHealth(int value);
		bool isDead();
		void updateFallingAngle(float value);
		float getFallingAngle();
		void setTimeOfDead(double time);
		double getTimeOfDead();
		void setModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 getModelMatrix();
		static float initialScale;
		static float initialLength;
		static float initialWidth;
		static float initialHeight;
		static float diagonal;
		static float fallingInterval;
		static float fallingSpeed;

	protected:
		std::string name;
		glm::vec3 position;
		float scale;
		float angle;
		float turningAngle;
		float speed;
		int segment;
		double health;
		float fallingAngle;
		double timeOfDead;
		glm::mat4 modelMatrix;
};


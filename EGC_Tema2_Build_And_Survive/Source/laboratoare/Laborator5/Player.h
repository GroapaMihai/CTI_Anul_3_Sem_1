#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Player
{
	public:
		Player(std::string name, glm::vec3 position, float speed);
		std::string getName();
		glm::vec3 getPosition();
		float getSpeed();
		void updateCenterX(float value);
		void updateCenterZ(float value);
		void updateFallingAngle(float value);
		float getFallingAngle();
		void setAngle(float angle);
		void updateAngle(float value);
		float getAngle();
		void setCurrentGun(int currentGun);
		int getCurrentGun();
		void setTimeOfLastPistolShoot(double time);
		double getTimeOfLastPistolShoot();
		void setTimeOfLastSniperShoot(double time);
		double getTimeOfLastSniperShoot();
		void setTimeOfLastGrenadeShoot(double time);
		double getTimeOfLastGrenadeShoot();
		void setModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 getModelMatrix();
		static float radius;
		static float fallingInterval;
		static float fallingSpeed;

	protected:
		std::string name;
		glm::vec3 position;
		float speed;
		float fallingAngle;
		float angle;
		int currentGun;
		double timeOfLastPistolShoot;
		double timeOfLastSniperShoot;
		double timeOfLastGrenadeShoot;
		glm::mat4 modelMatrix;
};
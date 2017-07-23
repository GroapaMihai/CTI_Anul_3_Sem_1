#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Projectile
{
	public:
		Projectile(glm::vec3 position, double angle, int damage, float bound);
		void setPosition(glm::vec3 position);
		glm::vec3 getPosition();
		void setSpeed(float speed);
		float getSpeed();
		double getAngle();
		void setScale(float scale);
		float getScale();
		int getDamage();
		float getBound();
		void setType(int type);
		int getType();
		void setTimeOfLaunch(double time);
		double getTimeOfLaunch();
		float getVelocity_Y(double time);
		static float pistolShootInterval;
		static float sniperShootInterval;
		static float grenadeShootInterval;
		static int launchAngle;
		static float gravity_acc;
		static int V0;
		static float Vy_0;

	protected:
		glm::vec3 position;
		glm::vec3 destination;
		float speed;
		float scale;
		double angle;
		int damage;
		float bound;
		int type;
		float velocity_Y;
		double timeOfLaunch;
};


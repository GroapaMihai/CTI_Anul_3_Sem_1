#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class Ship : public GameObject
{
	public:
		Ship::Ship();
		Ship(std::string name, glm::vec2 center, double speed, glm::vec3 color);
		double getHeight();
		void doubleSpeed();
		void setSpeed(double speed);
		double getSpeed();
		void updateCenterX(double value);
		void updateCenterY(double value);
		void setTimeOfDestroy(double value);
		double getTimeOfDestroy();
		double getScaleFactor();
		void decrementScaleFactor(double value);

	
	protected:
		static double shipLength;
		double height;
		double speed;
		double timeOfDestroy;
		double scaleFactor;
};


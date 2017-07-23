#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"
#include "Point.h"
#include "Circle.h"

class Shield : public GameObject
{
	public:
		Shield(glm::vec3 color);
		std::vector<Point*> getCollectiblePoints();
		std::vector<Point*> getShieldPoints();
		static double period;
		static double collectibleRadius;
		static double shieldRadius;
		static double smallPointRadius;
		bool isVisible();
		void setVisibility(bool value);
		void updateCenterY(double value);
		bool isInUse();
		void useShield(bool value);
		void updateTimeOfLastUse(double currentTime);
		double getTimeOfLastUse();
		double getSpeed();

	protected:
		Circle* collectible;
		Point* centralPoint;
		Circle* shield;
		bool visible;
		double speed;
		bool inUse;
		double timeOfLastUse;
};
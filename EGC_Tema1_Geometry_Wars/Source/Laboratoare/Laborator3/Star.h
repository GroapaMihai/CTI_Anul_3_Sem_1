#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class Star : public GameObject
{
public:
	Star(std::string name, glm::vec3 color);
	static double length;
	static double height;
	static double period;
	bool isVisible();
	void setVisibility(bool value);
	bool isInUse();
	void useStarGun(bool value);
	void updateCenterY(double value);
	double getSpeed();
	void updateTimeOfLastUse(double currentTime);
	double getTimeOfLastUse();

protected:
	double speed;
	bool visible;
	bool inUse;
	double timeOfLastUse;
};


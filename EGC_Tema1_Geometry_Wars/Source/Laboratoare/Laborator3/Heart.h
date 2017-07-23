#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class Heart : public GameObject
{
	public:
		Heart(std::string name, glm::vec3 color);
		static double length;
		bool isVisible();
		void setVisibility(bool value);
		void updateCenterY(double value);
		double getSpeed();

	protected:
		double speed;
		bool visible;
};


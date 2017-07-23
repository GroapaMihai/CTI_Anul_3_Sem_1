#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "Ship.h"

class PlayerShip : public Ship
{
	public:
		PlayerShip(std::string name, glm::vec2 center, double speed, glm::vec3 color);
		int getLifes();
		void addLife();
		void removeLife();
		void addStarGun();
		void removeStarGun();
		int nrOfStarGuns();

	protected:
		int lifes;
		int starGuns;
};

#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "GameObject.h"

class Bullet : public GameObject
{
	public:
		Bullet(std::string name, glm::vec3 color);
		static double bulletLength;
		static double bulletWidth;
		static double bulletSpeed;
};


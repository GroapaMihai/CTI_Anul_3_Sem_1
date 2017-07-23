#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Tower
{
	public:
		Tower(glm::vec3 position, float scale);
		glm::vec3 getPosition();
		float getScale();
		void setTimeOfLastShoot(double time);
		double getTimeOfLastShoot();
		void setModelMatrix(glm::mat4 modelMatrix);
		glm::mat4 getModelMatrix();
		static float shootingInterval;

	protected:
		glm::vec3 position;
		float scale;
		double timeOfLastShoot;
		glm::mat4 modelMatrix;
};


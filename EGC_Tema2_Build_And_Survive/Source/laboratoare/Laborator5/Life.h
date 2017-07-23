#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Life
{
	public:
		Life();
		void setDisplacement(glm::vec3 displacement);
		void setAxis(char axis);
		glm::vec3 getDisplacement();
		char getAxis();

	protected:
		glm::vec3 displacement;
		char axis;
};


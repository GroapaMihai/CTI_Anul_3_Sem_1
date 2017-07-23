#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class GameObject
{
	public:
		void setName(std::string name);
		std::string GameObject::getName();
		void setIndices(std::vector<unsigned short> indices);
		void setVertices(std::vector<VertexFormat> vertices);
		void setCenter(glm::vec2 center);
		double getCenterX();
		double getCenterY();
		void setColor(glm::vec3 color);
		glm::vec3 getColor();
		void setAngle(double angle);
		double getAngle();
		Mesh* CreateMesh();

	protected:
		std::string name;
		std::vector<unsigned short> indices;
		std::vector<VertexFormat> vertices;
		glm::vec2 center;
		glm::vec3 color;
		double angle;
};


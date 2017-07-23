#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class WireFrame
{
	public:
		WireFrame();
		void setName(std::string name);
		std::string getName();
		void setIndices(std::vector<unsigned short> indices);
		void setVertices(std::vector<VertexFormat> vertices);
		void setColor(glm::vec3 color);
		Mesh* CreateMesh();
		float getWireFrameWidth();

	protected:
		std::string name;
		std::vector<unsigned short> indices;
		std::vector<VertexFormat> vertices;
		glm::vec3 color;
		float smallSquareSide;
		int nrOfSquares;
};
#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Animation
{
	public:
		Animation(std::string name);
		std::string getName();
		void addFrame(Mesh* frame);
		Mesh* getFrameAt(int i);
		int getNumberOfFrames();
		void addTextureWidth(double textureWidth);
		void computeAverageTextureWidth();
		void computeScaleFactors();
		double getScaleFactorAt(int i);
		void setFramePeriod();
		int getFramePeriod();

	protected:
		std::string name;
		std::vector<Mesh*> frames;
		std::vector<double> frameWidth;
		std::vector<double> scaleFactor;
		double totalTextureWidth;
		double averageTexturewidth;
		int framePeriod;
};
#include <iostream>
#include <Core/Engine.h>
#include "Animation.h"

Animation::Animation(std::string name)
{
	this->name = name;
}

std::string Animation::getName()
{
	return name;
}

void Animation::addFrame(Mesh* frame)
{
	frames.push_back(frame);
}

Mesh* Animation::getFrameAt(int i)
{
	if (i >= frames.size() || i < 0)
		return frames[0];

	return frames[i];
}

int Animation::getNumberOfFrames()
{
	return frames.size();
}

void Animation::addTextureWidth(double textureWidth)
{
	totalTextureWidth += textureWidth;
	frameWidth.push_back(textureWidth);
}

void Animation::computeAverageTextureWidth()
{
	averageTexturewidth = totalTextureWidth / frames.size();
}

void Animation::computeScaleFactors()
{
	double fraction;

	for (int i = 0; i < frames.size(); i++) {
		fraction = frameWidth[i] / averageTexturewidth;

		if (fraction < 1)
			scaleFactor.push_back(fraction);
		else
			scaleFactor.push_back(1);
	}
}

double Animation::getScaleFactorAt(int i)
{
	if (i >= frames.size() || i < 0)
		return 1;

	return scaleFactor[i];
}

void Animation::setFramePeriod()
{
	int numberOfFrames = getNumberOfFrames();

	if (numberOfFrames > 6)
		framePeriod = 15;
	else
		framePeriod = 20;
}

int Animation::getFramePeriod()
{
	return framePeriod;
}

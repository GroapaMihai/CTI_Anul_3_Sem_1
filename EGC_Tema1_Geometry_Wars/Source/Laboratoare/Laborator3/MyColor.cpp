#include <iostream>
#include "MyColor.h"

MyColor::MyColor()
{
	red = glm::vec3(1, 0, 0);
	green = glm::vec3(0, 1, 0);
	blue = glm::vec3(0, 0, 1);
	yellow = glm::vec3(1, 1, 0);
	orange = glm::vec3(1, 0.5, 0);
	cyan = glm::vec3(0, 1, 1);
	violet = glm::vec3(0.309804, 0.184314, 0.309804);
	brown = glm::vec3(0.545, 0.271, 0.075);
	magenta = glm::vec3(1, 0, 1);
	white = glm::vec3(1, 1, 1);
}
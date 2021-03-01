//Savu Ioana Rusalda 335CB
#pragma once
#include <glm\detail\type_mat.hpp>
class Heart {
public:
	float width;
	float height;
	Heart();
	glm::mat3 generateMatrix(float tx, float ty, float sx, float sy);
	void setDimension(float width, float height);
};

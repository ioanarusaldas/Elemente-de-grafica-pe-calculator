//Savu Ioana Rusalda 335CB
#pragma once
#include <glm\detail\type_mat.hpp>
class Bow {
public:
	Bow();

	float speed = 100;
	float translateY;
	float positionX, positionY;
	float rotation;

	void SetPosition(float x, float y);
	glm::mat3 bowMatrix(float tx, float ty, float radians);
};

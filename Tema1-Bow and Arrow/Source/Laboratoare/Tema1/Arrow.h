//Savu Ioana Rusalda 335CB
#pragma once
#include <glm\detail\type_mat.hpp>
class Arrow {
public:
	Arrow();
	float speed;
	float translateX;
	float translateY;
	float rotation;
	float width, height;

	void SetDimensions(float w, float h);
	glm::mat3 arrowMoveMatrix(float tx, float ty);
	glm::mat3 arrowMatrix(float tx, float ty, float radians);

};

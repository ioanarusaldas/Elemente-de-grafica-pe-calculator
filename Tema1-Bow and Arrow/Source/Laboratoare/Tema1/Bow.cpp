//Savu Ioana Rusalda 335CB
#pragma once
#include "Bow.h"
#include <Laboratoare\Tema1\Transform2D.h>
Bow::Bow() {
	translateY = 0;
	rotation = 0;

};
void Bow::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
}
glm::mat3 Bow::bowMatrix(float tx, float ty, float radians)
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(tx, ty);
	modelMatrix *= Transform2D::Translate(10,( 720 / 2));
	modelMatrix *= Transform2D::Rotate(radians);
	return modelMatrix;
}
;
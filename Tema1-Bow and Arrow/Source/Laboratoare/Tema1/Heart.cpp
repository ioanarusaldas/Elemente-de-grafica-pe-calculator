//Savu Ioana Rusalda 335CB
#pragma once
#include "Heart.h"
#include "Transform2D.h"
Heart::Heart() {}
glm::mat3 Heart::generateMatrix(float tx, float ty, float sx, float sy)
{
	glm::mat3 modelMatrix;
	modelMatrix = glm::mat3(1);
	modelMatrix = Transform2D::Translate(tx, ty);
	modelMatrix *= Transform2D::Scale(sx, sy);
	return modelMatrix;
};
void Heart::setDimension(float w, float h) {
	width = w;
	height = h;
}

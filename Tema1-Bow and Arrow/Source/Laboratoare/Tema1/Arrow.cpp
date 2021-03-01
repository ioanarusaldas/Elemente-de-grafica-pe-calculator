//Savu Ioana Rusalda 335CB
#pragma once
#include "Arrow.h"
#include <cmath>
#include <Laboratoare\Tema1\Transform2D.h>
Arrow::Arrow() {
	speed = 0;
	translateX = 10;
	translateY = 720/2;
	rotation = 0;
}
glm::mat3 Arrow::arrowMatrix(float tx, float ty, float radians)
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(10, 720 / 2 -(height / 2));
	modelMatrix *= Transform2D::Translate(tx, ty);
	modelMatrix *= Transform2D::Rotate(radians);
	return modelMatrix;
};
glm::mat3 Arrow::arrowMoveMatrix(float tx, float ty) {
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(10, 720 / 2 - 4);
	modelMatrix *= Transform2D::Translate(tx, ty);
	modelMatrix *= Transform2D::Translate(translateX, (tan(rotation) * translateX));
	modelMatrix *= Transform2D::Rotate(rotation);
	return modelMatrix;
}

void Arrow::SetDimensions(float w, float h) {
	width = w;
	height = h;
}

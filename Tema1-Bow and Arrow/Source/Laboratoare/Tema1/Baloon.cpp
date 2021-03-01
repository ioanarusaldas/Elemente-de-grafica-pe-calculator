//Savu Ioana Rusalda 335CB
#pragma once
#include <Core/Engine.h>
#include <iostream>
#include "Baloon.h"
#include "Transform2D.h"
Baloon::Baloon(Mesh* o, Mesh* tr, Mesh* t) {
	oval = o;
	triangle = tr;
	tail = t;
}

glm::mat3 Baloon::MatrixForBody(float position)
{

	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(position, 150);
	modelMatrix *= Transform2D::Scale(1, 1.35);
	return modelMatrix;
}

glm::mat3 Baloon::MatrixForTriangle(float position)
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(position, 150);
	return modelMatrix;
}

glm::mat3 Baloon::MatrixForTail(float position)
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(position, 150);
	return modelMatrix;
}

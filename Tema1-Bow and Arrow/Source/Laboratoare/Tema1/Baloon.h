//Savu Ioana Rusalda 335CB
#pragma once
class Baloon {
public:
	Mesh* oval;
	Mesh* triangle;
	Mesh* tail;
	float speed;
	Baloon();
	Baloon(Mesh* o, Mesh* tr, Mesh* t);
	glm::mat3 MatrixForBody(float position);
	glm::mat3 MatrixForTriangle(float position);
	glm::mat3 MatrixForTail(float position);

};
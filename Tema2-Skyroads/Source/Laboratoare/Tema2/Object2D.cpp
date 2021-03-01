//Savu Ioana Rusalda 335CB
#include "Object2D.h"
#include <Core/Engine.h>
#include <iostream>
using namespace std;

Mesh* Object2D::CreateRectangle(std::string name,float width,float height, glm::vec3 color)
{//functie creare dreptunghi
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),//0
		VertexFormat(corner + glm::vec3(width, 0, 0), color),//1
		VertexFormat(corner + glm::vec3(width, height, 0), color),//2
		VertexFormat(corner + glm::vec3(0, height, 0), color)//3
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	indices.push_back(0);
	indices.push_back(2);

	rectangle->SetDrawMode(GL_TRIANGLES);
	rectangle->InitFromData(vertices, indices);
	return rectangle;
}


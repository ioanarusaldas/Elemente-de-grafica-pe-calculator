//Savu Ioana Rusalda 335CB
#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Baloon.h"

namespace Object2D
{
	Mesh* CreateRectangle(std::string name, float width, float height, glm::vec3 color);
	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float lenght, glm::vec3 color);
	Mesh* CreateBow(std::string name,float length, glm::vec3 color);
	Mesh* CreateArrow(std::string name, float width,float height, glm::vec3 color);
	Mesh* CreateShuriken(std::string name, float length, glm::vec3 color);
	Mesh* CreateCircle(std::string name, float radius, glm::vec3 color);
	Baloon* CreateBaloon(std::string name, float radius, glm::vec3 color);
	Mesh* CreateHeart(std::string name, float width, float height, glm::vec3 color);
	Mesh* Butterfly(float length, glm::vec3 color);
	Mesh* Game(float lenght, glm::vec3 color);
	Mesh* Over(float lenght, glm::vec3 color);
}




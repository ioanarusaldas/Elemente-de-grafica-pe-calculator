//Savu Ioana Rusalda 335CB
#pragma once
#include "Tema2.h"
#include <vector>
#include <glm\detail\type_vec.hpp>

	
	void initPlatforms(Plane* platforms[], std::vector<glm::vec3> colors);//pozitionare initiala 
	std::vector<int> setVisibility(int current, int last, Plane* platforms[]);//setare vizibilitate
	void setColor(int row, Plane* platforms[], std::vector<glm::vec3> colors, int* distributed_colors);//setare culoare
	bool platform_Colision(Plane* platforms[], int j, int i, float sphereZ, float sphereX);//coliziune sfera-placa
	bool lateral_Colision(Plane* platforms[],int i, float sphereZ, float sphereX, bool gameOver);
	bool front_Colision(Plane* platforms[], int i, float sphereZ, float sphereX, bool gameOver);


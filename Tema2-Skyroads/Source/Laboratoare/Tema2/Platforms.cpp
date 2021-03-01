//Savu Ioana Rusalda 335CB
#pragma once
#include "Platforms.h"
#include <iostream>
using namespace std;
//pozitonare initiala platforme
void initPlatforms(Plane* platforms[], std::vector<glm::vec3> colors) {
	//parcurgere coloane
	for (int j = 0; j < 3; j++) {
		//alocare randuri platforme
		platforms[j] = (Plane*)malloc(20 * sizeof(Plane));
		//parcurgere randuri
		for (int i = 0; i < 20; i++) {
			//coordonate initiale
			platforms[j][i].center = glm::vec3(0.0, 0.0, 0.0);
			platforms[j][i].size = { 1.0,0.05,5 };
			//pozitionare platforma fata de platforma anterioara 
			//5 = dimensiune placa dupa scalare /0.5 = distanta intre placi
			if (i != 0)
				platforms[j][i].center.z = platforms[j][i - 1].center.z - 5 - 0.5;
			else
				platforms[j][i].center.z = -2.5;
			//setare vizibilitate, randul 0 va fi vizibil complet
			if ((i == 0)) {
				platforms[j][i].visible = 1;
				platforms[j][i].color = colors[3];
			}
			else {
				bool x = rand() % 2;
				platforms[j][i].visible = x;
			}
			//setare coordonata x, distanta intre placi = 0.5
			if (j != 0)
				platforms[j][i].center.x = platforms[j - 1][i].center.x + 1.5;
			else
				platforms[j][i].center.x = 1;
		}


	}
}

void setColor(int row, Plane* platforms[], std::vector<glm::vec3> colors, int* distributed_colors) {
	int nr = 0;
	int x = 0;
	int red = 0;
	//verificare numar placi vizibile pe un rand
	for (int j = 0; j < 3; j++) {
		if (platforms[j][row].visible == 1) {
			nr++;
		}
	}
	//parcurgere coloane
	for (int j = 0; j < 3; j++) {
		if (platforms[j][row].visible == 1) {
			//generare culoare random
			x = rand() % 5;
			//verificare sa nu se extraga culoarea rosu cand
			//exista mai putin de 3 placi
			if (nr != 3) {
				x = rand() % 4 + 1;
			}
			//extragere culori in functie de distributie
			while (distributed_colors[x] == 0 ) {
				if (nr != 3) {
					x = rand() % 4 + 1;
				}
				else {
					x = rand() % 5;
				}
			}
			//verificare sa nu existe 3 placi rosii pe acelasi rand
			if (x == 0)
				red += 1;
			if (red == 3) {
				x = rand() % 4 + 1;
				red -= 1;
			}
			//setare culoare platforma
			platforms[j][row].color = colors[x];
			distributed_colors[x] -= 1;
		}
	}
}
std::vector<int> setVisibility(int current, int last,Plane*platforms[]) {
	std::vector<int> visibility = { 0,0,0 };
	int nr;
	int nr2;
	int index;
	nr = 0;
	nr2 = 0;
	index = 0;
	//parcurgere coloane
	for (int j = 0; j < 3; j++) {
		//numarare platforme vizibile ultimul rand
		if (platforms[j][last].visible == 1) {
			nr = nr + 1;
			index = j;
		}
		//numarare platforme vizibile rand curent
		if (platforms[j][current].visible == 1) {
			nr2 = nr2 + 1;
		}
	}
		//o singura placa vizibla pe ultimul rand
		if (nr == 1) {
			//prima placa
			if (index == 0) {
				int x = rand() % 2;
				platforms[x][current].visible = 1;
			}
			//placa 2
			if (index == 1) {
				int x = rand() % 2;
				platforms[x + 1][current].visible = 1;
			}
			//placa 3
			if (index == 2) {
				int x = rand() % 2 + 1;
				platforms[x][current].visible = 1;
			}
		}
		else
			if (nr == 2 && platforms[0][last].visible == 1 && platforms[2][last].visible == 1) {
				//verificare vizibilitate placa 0 si 2
				int x = rand() % 2;
				if (x == 0) {
					//setare vizibilitate placi in fata celor anterioare
					platforms[0][current].visible = 1;
					platforms[2][current].visible = 1;
				}
				else {
					//setare vizibilitate placa in mijloc
					platforms[1][current].visible = 1;
				}
			}
			else
				if (nr2 == 0) {
					int x = rand() % 3;
					//vizibilitate minim o placa pe rand
					platforms[x][current].color = glm::vec3(0, 0, 1);
					platforms[x][current].visible = 1;
				}
	return visibility;
}
bool platform_Colision(Plane* platforms[],int j, int i,float sphereZ, float sphereX) {
	//verificare coliziunee sfera placa
	if ((sphereZ > (platforms[j][i].center.z - platforms[j][i].size.z / 2)) &&
		(sphereZ < (platforms[j][i].center.z + platforms[j][i].size.z / 2))) {
		if ((sphereX > platforms[j][i].center.x - platforms[j][i].size.x / 2)
			&&
			(sphereX < (platforms[j][i].center.x + platforms[j][i].size.x / 2))) {
			return true;
		}
	}
	return false;
}
bool lateral_Colision(Plane* platforms[],int i, float sphereZ, float sphereX, bool gameOver) {
	//verificare aterizare sfera intre placi pe coloana
	bool over = gameOver;
	if (sphereX < platforms[0][i].center.x - platforms[0][i].size.x / 2) {
		over = true;
	}
	else {
		if ((sphereX > platforms[0][i].center.x + platforms[0][i].size.x / 2) &&
			(sphereX < platforms[1][i].center.x - platforms[1][i].size.x / 2)) {
			over = true;
		}
		else {
			if ((sphereX > platforms[1][i].center.x + platforms[1][i].size.x / 2) &&
				(sphereX < platforms[2][i].center.x - platforms[2][i].size.x / 2)) {
				over = true;
			}
			else {
				if ((sphereX > platforms[2][i].center.x + platforms[2][i].size.x / 2)) {
					over = true;
				}
			}
		}
	}
	return over;
}
bool front_Colision(Plane* platforms[], int i, float sphereZ, float sphereX,bool gameOver) {
	//verificare aterizare sfera intre placi pe rand
	bool over = gameOver;
	for (int j = 0; j < 3; j++) {
	if ((sphereX >= platforms[j][i].center.x - platforms[j][i].size.x / 2)
		&&
		(sphereX <= (platforms[j][i].center.x + platforms[j][i].size.x / 2))) {
		if (i != 19 && (sphereZ < (platforms[j][i].center.z - platforms[j][i].size.z / 2)) &&
			(sphereZ > (platforms[j][i+1].center.z + platforms[j][i+1].size.z / 2))) {
			over = true;
		}
		else {//verificare ultima placa cu prima
			if (i == 19 && (sphereZ < (platforms[j][i].center.z - platforms[j][i].size.z / 2)) &&
				(sphereZ > (platforms[j][0].center.z + platforms[j][0].size.z / 2))) {
				over = true;
			}
		}
	}
}
	return over;
}

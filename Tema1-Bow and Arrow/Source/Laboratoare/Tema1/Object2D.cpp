//Savu Ioana Rusalda 335CB
#include "Object2D.h"
#include <Core/Engine.h>
#include <iostream>
#include "Transform2D.h"
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

Mesh* Object2D::CreateBow(std::string name, float length, glm::vec3 color)
{
	//functie creare arc
	const float PI = 3.1415926f;
	float n = 2 * PI / 100;
	int a = length;//raza1
	int b = length / 2;//raza2
	float currAngle;

	std::vector<VertexFormat> vertices = {};
	//desenare arc de cerc
	for (currAngle = -PI / 2; currAngle < PI/2; currAngle += n)
	{
		vertices.push_back(VertexFormat(glm::vec3(b * cos(currAngle), a * sin(currAngle) ,0), color));
	}
	currAngle = PI / 2;
	vertices.push_back(VertexFormat(glm::vec3(b * cos(currAngle), a * sin(currAngle),0), color));
	vertices.push_back(VertexFormat(glm::vec3(b * cos(-PI / 2), a * sin(-PI / 2),0), color));
	
	Mesh* bow = new Mesh(name);
	std::vector<unsigned short> indices = {};
	for (int i = 0; i <= 100; i += 1)
		indices.push_back(i);

	
	bow->SetDrawMode(GL_LINE_STRIP);
	bow->InitFromData(vertices, indices);
	return bow;
}

Mesh* Object2D::CreateArrow(std::string name, float width, float height, glm::vec3 color)
{
	//functie creare sageata
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),//0
		VertexFormat(corner + glm::vec3(width, 0, 0), color),//1
		VertexFormat(corner + glm::vec3(width, height, 0), color),//2
		VertexFormat(corner + glm::vec3(0, height, 0), color),//3

		VertexFormat(corner + glm::vec3(width - 10, -(height / 2), 0), color),//4
		VertexFormat(corner + glm::vec3(width + 20, height / 2, 0), color),//5
		VertexFormat(corner + glm::vec3(width - 10, height + (height / 2), 0), color)//6
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											0, 2, 3,
											4, 5, 6 };

	arrow->SetDrawMode(GL_TRIANGLES);
	arrow->InitFromData(vertices, indices);
	return arrow;
}	

Mesh* Object2D::CreateShuriken(std::string name,float length, glm::vec3 color)
{
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		//center - punct 0
		VertexFormat(corner, color),//0
		//points triangle 1
		VertexFormat(corner + glm::vec3(-length, -length, 0), color),//1
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),//2
		//points for triangle 2
		VertexFormat(corner + glm::vec3(0, -length, 0), color),//3
		VertexFormat(corner + glm::vec3(length, -length, 0), color),//4
		//points for triangle 3
		VertexFormat(corner + glm::vec3(length, 0, 0), color),//5
		VertexFormat(corner + glm::vec3(length, length, 0), color),//6
		//points for triangle 4
		VertexFormat(corner + glm::vec3(0, length, 0), color),//7
		VertexFormat(corner + glm::vec3(-length, length, 0), color),//8



	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 2, 1,//triangle 1
											0, 3, 4,//triangle 2
											0, 5, 6,//triangle 3
											0, 7, 8//triangle 4
										};

	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh* Object2D::CreateCircle(std::string name, float radius, glm::vec3 color)
{
	//functie creare cerc
	const float PI = 3.1415926f;
	float n = 2 * PI / 100;
	
	float currAngle;
	std::vector<VertexFormat> vertices = {};
	//centru
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
	//creare puncte pe cerc
	for (currAngle = 0; currAngle < 2 * PI; currAngle += n)
	{
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(currAngle), radius * sin(currAngle), 0),color));
	}
	vertices.push_back(VertexFormat(glm::vec3(radius * cos(2 * PI), radius * sin(2 * PI), 0),color));

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = {};
	for (int i = 1; i <= vertices.size(); i += 1) {
		indices.push_back(i);
		indices.push_back(0);
		indices.push_back(i + 1);
	}


	circle->SetDrawMode(GL_TRIANGLES);
	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	//functie creare triunghi
	glm::vec3 corner = leftBottomCorner;
	//calcul inaltime triunghi echilateral
	float h = (sqrt(3) / 2) * length;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length/2, -h, 0), color),
		VertexFormat(corner + glm::vec3(length/2, -h, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, };

	triangle->SetDrawMode(GL_TRIANGLES);
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Baloon * Object2D::CreateBaloon(std::string name, float radius, glm::vec3 color)
{	
	//functie creare balon
	const float PI = 3.1415926f;
	float n = 2 * PI / 100;
	float currAngle = 75 * n;
	//declarare dimensiune triunghi
	float triangleSide = 15;
	float h = (sqrt(3) / 2) * triangleSide;

	//creare corp balon
	Mesh* circle = Object2D::CreateCircle("oval", radius, color);
	//definire centru codita balon
	glm::vec3 center = glm::vec3(0, 1.35*radius * sin(currAngle), 0);
	//creare triunghi din codita balonului
	Mesh* t = Object2D::CreateTriangle("traiangle",center,15 ,color); 

	float m = 1.35 * radius * sin(currAngle) - h;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, m, 0), color),
		VertexFormat(glm::vec3(-5, m-5, 0), color),
		VertexFormat(glm::vec3(0, m - 10, 0), color),
		VertexFormat(glm::vec3(-5, m -15, 0), color),
		VertexFormat(glm::vec3(0, m-20, 0), color),
	};
	//creare codita balon
	Mesh* tail = new Mesh("tail");
	std::vector<unsigned short> indices = { 0, 1, 2,3,4 };

	tail->SetDrawMode(GL_LINE_STRIP);
	tail->InitFromData(vertices, indices);

	Baloon * baloon = new Baloon(circle, t, tail);
	return baloon;
}

Mesh* Object2D::CreateHeart(std::string name,float width, float height, glm::vec3 color)
{
	//functie creare inima
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(width / 2, 0, 0), color),//0
		VertexFormat(corner + glm::vec3(width, height, 0), color),//1
		VertexFormat(corner + glm::vec3(0, height, 0), color),//2
		VertexFormat(corner + glm::vec3(width, height + 10, 0), color),//3
		VertexFormat(corner + glm::vec3(0, height + 10, 0), color),//4
		VertexFormat(corner + glm::vec3(width/4 * 3, height + 10 + 10, 0), color),//5
		VertexFormat(corner + glm::vec3(width/4, height + 10 + 10, 0), color),//6
		VertexFormat(corner + glm::vec3(width/2, height + 10, 0), color),//7
	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											1, 3, 2,
											2, 3, 4,
											4,7,6,
											3,5,7};



	heart->SetDrawMode(GL_TRIANGLES);
	heart->InitFromData(vertices, indices);
	return heart;
}

Mesh* Object2D::Game(float length, glm::vec3 color)
{
	//functie creare string GAME
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		//litera G
		VertexFormat(corner +glm::vec3(length ,length, 0),color),//0
		VertexFormat(corner + glm::vec3(0,length, 0),color),//1
		VertexFormat(corner + glm::vec3(0,0, 0),color),//2
		VertexFormat(corner + glm::vec3(length,0, 0),color),//3
		VertexFormat(corner + glm::vec3(length,length/2, 0),color),//4
		VertexFormat(corner + glm::vec3(length/2,length/2, 0),color),//5

		//litera A la distanta length
		VertexFormat(corner+glm::vec3(length+length / 2,length, 0),color),//6
		VertexFormat(corner+glm::vec3(2*length,0, 0),color),//7
		VertexFormat(corner + glm::vec3(length,length/2, 0),color),//8
		VertexFormat(corner + glm::vec3(2 * length,length / 2, 0),color),//9

		//litera M la distanta 2*length
		VertexFormat(corner + glm::vec3(2 * length,length, 0),color),//10
		VertexFormat(corner + glm::vec3(2 * length+length/2,length/2, 0),color),//11
		VertexFormat(corner + glm::vec3(2 * length+length,length, 0),color),//12
		VertexFormat(corner + glm::vec3(2 * length+length,0, 0),color),//13

		//litera E la distanta 3*length
		VertexFormat(corner + glm::vec3(3*length+length, 0,0),color),//14
		VertexFormat(corner + glm::vec3(3*length,length / 2, 0),color),//15
		VertexFormat(corner + glm::vec3(3*length+length,length / 2, 0),color),//16
		VertexFormat(corner + glm::vec3(3*length, length,0),color),//17
		VertexFormat(corner + glm::vec3(3*length+length ,length, 0),color),//18

	};
	std::vector<unsigned short> indices = { 0,1,2,3,4,5,//G
											4,3,6,7,9,8,9,//A
											7,10,11,12,13,//M
											14,13,15,16,15,17,18,17,13,14//E
										};

	Mesh* game = new Mesh("game");
	game->SetDrawMode(GL_LINE_STRIP);
	game->InitFromData(vertices, indices);

	return game;
}
Mesh* Object2D::Over(float length, glm::vec3 color)
{
	//functie creare string OVER
	glm::vec3 corner = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		//litera O
		VertexFormat(corner ,color),//0
		VertexFormat(corner + glm::vec3(0, length,0),color),//1
		VertexFormat(corner + glm::vec3(length, length,0),color),//2
		VertexFormat(corner + glm::vec3(length ,0, 0),color),//3

		//litera V la distanta length
		VertexFormat(corner + glm::vec3(length+length/2, 0,0),color),//4
		VertexFormat(corner + glm::vec3(length+length ,length, 0),color),//5


		//litera E la distanta length
		VertexFormat(corner +glm::vec3(2*length+length ,length, 0),color),//6
		VertexFormat(corner + glm::vec3(2*length,length / 2, 0),color),//7
		VertexFormat(corner + glm::vec3(2*length+length,length / 2, 0),color),//8
		VertexFormat(corner + glm::vec3(2 * length ,0, 0) ,color),//9
		VertexFormat(corner + glm::vec3(2*length+length, 0,0),color),//10


		//litera R la distanta length
		VertexFormat(corner +glm::vec3(3 * length + 10, 0,0),color),//11
		VertexFormat(corner + glm::vec3(3*length+10, length,0),color),//12
		VertexFormat(corner + glm::vec3(3*length+length+10, length,0),color),//13
		VertexFormat(corner + glm::vec3(3*length+length+10 ,length/2, 0),color),//114
		VertexFormat(corner + glm::vec3(3*length+10 ,length/ 2, 0),color),//15
		VertexFormat(corner + glm::vec3(3*length+length +10,0, 0),color),//16


	};
	std::vector<unsigned short> indices = { 0,1,2,3,0,//O
											3,2,4,5,//V
											6,5,7,8,7,9,10,//E
											11,12,13,14,15,16};//R

	Mesh* over = new Mesh("over");

	over->SetDrawMode(GL_LINE_STRIP);
	over->InitFromData(vertices, indices);

	return over;
}
Mesh* Object2D::Butterfly(float length, glm::vec3 color)
{
	//functie creare obiect de tip fluture
	glm::vec3 corner = glm::vec3(0, 0, 0);
	const float PI = 3.1415926f;
	float n = 2 * PI / 100;
	int a = length;//raza1
	int b = length / 4;//raza2
	float currAngle;

	std::vector<VertexFormat> vertices = {};
	for (currAngle = 0; currAngle < 2*PI; currAngle += n)
	{
		vertices.push_back(VertexFormat(glm::vec3(b * cos(currAngle), a * sin(currAngle), 0), color));
	}

	vertices.push_back(VertexFormat(glm::vec3(b +length ,0, 0), glm::vec3(1, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(b + length/2, length, 0), glm::vec3(1.000, 0.412, 0.706)));

	vertices.push_back(VertexFormat(glm::vec3(b + length, -10, 0), glm::vec3(0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(b, -length, 0), glm::vec3(0.118, 0.565, 1.000)));

	vertices.push_back(VertexFormat(glm::vec3(-(b + length), 0, 0), glm::vec3(0, 1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-(b + length / 2), length, 0), glm::vec3(0.000, 0.980, 0.604)));

	vertices.push_back(VertexFormat(glm::vec3(-(b + length), -10, 0), glm::vec3(1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-b, -length, 0), glm::vec3(0.941, 0.902, 0.549)));
	
	std::vector<unsigned short> indices = {};
	for (int i = 0; i < vertices.size() - 8; i++) {
		indices.push_back(i);
		indices.push_back(0);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(vertices.size() - 8);
	indices.push_back(vertices.size() - 7);

	indices.push_back(0);
	indices.push_back(vertices.size() - 6);
	indices.push_back(vertices.size() - 5);

	indices.push_back((vertices.size()-8 )/2);
	indices.push_back(vertices.size() - 4);
	indices.push_back(vertices.size() - 3);

	indices.push_back((vertices.size() - 8) / 2);
	indices.push_back(vertices.size() - 2);
	indices.push_back(vertices.size() - 1);
	Mesh* over = new Mesh("butterfly");

	over->SetDrawMode(GL_TRIANGLES);
	over->InitFromData(vertices, indices);

	return over;
}
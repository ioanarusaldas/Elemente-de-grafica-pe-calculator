//Savu Ioana Rusalda 335CB
#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Arrow.h"
#include "Bow.h"
#include "Shuriken.h"
#include "Heart.h"


using namespace std;
std::vector<float> baloons_speed = {};
std::vector<float> baloons_coordinateY = {};
std::vector<float> shuriken_array = { };
std::vector<float> shuriken_speed = { };
Baloon* yellow_baloon;
Baloon* red_baloon;
Baloon* baloon;
Arrow* arrow;
Bow* bow;
Heart* heart;
Shuriken* shuriken;
std::vector<bool> hit = { };
std::vector<bool> baloon_animation = {};
std::vector<float> shuriken_animation = {};
int y, s;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//instantiere obiect de tip sageata si setarea dimensiunilor
	arrow = new Arrow();
	arrow->SetDimensions(75 + 20, 8);

	//instantiere obiect de tip arc si setarea dimensiunilor
	bow = new Bow();
	bow->SetPosition(10, resolution.y / 2);

	//instantiere oiect de tip shuriken
	shuriken = new Shuriken();

	//instantiere oiect de tip inima
	heart = new Heart();
	heart->setDimension(40, 20);

	//initializare variabile de joc
	arrow_move = false;
	increase_speed = false;
	grow_speed = 1;
	lifes = 3;
	gameOver = false;
	Score = 0;
	lastScore = 0;
	nrBaloons = 10;
	nrShuriken = 3;
	butterfly = false;

	//creare mesh pentru reprezentarea obiectelor tinta bonus
	Mesh* butterfly = Object2D::Butterfly(30,glm::vec3(0, 0, 0));
	AddMeshToList(butterfly);


	//creare mesh pentru reprezentarea vietilor
	Mesh* heart = Object2D::CreateHeart("heart", 40, 20, glm::vec3(1, 0, 0));
	AddMeshToList(heart);

	//creare mesh pentru reprezentarea barii de viteza
	Mesh* speed = Object2D::CreateRectangle("speed",50,20,glm::vec3(1, 0, 0));
	AddMeshToList(speed);
	//creare mesh pentru reprezentarea arcului
	Mesh* bow = Object2D::CreateBow("bow",100, glm::vec3(0, 0, 0));
	AddMeshToList(bow);

	//creare mesh pentru reprezentarea sagetii
	Mesh* arrow = Object2D::CreateArrow("arrow",75,8, glm::vec3(0, 1, 0));
	AddMeshToList(arrow);

	//creare mesh pentru reprezentarea shuriken-ului
	Mesh* shuriken = Object2D::CreateShuriken("shuriken",30,glm::vec3(0, 0,0.5));
	AddMeshToList(shuriken);

	//creare mesh pentru reprezentarea baloanelor
	red_baloon = Object2D::CreateBaloon("red_baloon",30, glm::vec3(1, 0, 0));
	yellow_baloon = Object2D::CreateBaloon("yellow_baloon", 30, glm::vec3(1, 1, 0));
	StartPosition_baloons = 900;

	//creare mesh pentru reprezentarea sfarsitului jocului
	Mesh* txt = Object2D::Game(100, glm::vec3(1, 0, 0));
	AddMeshToList(txt);
	Mesh* over = Object2D::Over(100, glm::vec3(1, 0, 0));
	AddMeshToList(over);

	//generare coordonate si viteza random pentru fiecare balon
	for (int i = 0; i < nrBaloons; i += 1) {
		y  = (rand() % ((500) - (190))) + (190);
		s = (rand() % ((250) - (70))) + (70);
		baloons_coordinateY.push_back(-y);
		baloon_animation.push_back(false);
		baloons_speed.push_back(s);
	}


	//generare coordonate si viteza random pentru fiecare shuriken
	for (int i = 0; i < nrShuriken; i += 1) {
		y = (rand() % ((3000) - (1000))) + (1000);
		shuriken_array.push_back(resolution.x + y);
		hit.push_back(false);
		shuriken_animation.push_back(1);
		s = (rand() % ((250) - (70))) + (70);
		shuriken_speed.push_back(s);
	}


}

void Tema1::FrameStart()
{
	
	glClearColor(1.000, 0.855, 0.725, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	int j;
	//verificare final de joc
	if (gameOver == false) {

		//afisare vieti
		for (int i = 0; i < lifes; i++) {
			//60 = heart->width*1.5
			modelMatrix = heart->generateMatrix(60 + 70 * i, resolution.y - 60, 1.5, 1.5);
			RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
		}
		//afisare power bar
		modelMatrix = glm::mat3(1);
		modelMatrix = Transform2D::Scale(grow_speed, 1);
		RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);

		//afisare arc
		modelMatrix = bow->bowMatrix(0, bow->translateY,bow->rotation);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
		//crestere viteza sageata
		if (increase_speed) {
			if (arrow->speed < maxSpeed) {
				arrow->speed += 30 * deltaTimeSeconds;
			}
			//crestere variabila scalare powerbar
			if (grow_speed < 10) {
				grow_speed += 0.25;
			}
			else {
				arrow->speed = maxSpeed;
			}
		}
		//verificare iesire din dimensiunile ecranului a sagetii

		if (arrow_move == true) {
			arrow->translateY = (tan(arrow->rotation) * arrow->translateX) + resolution.y / 2 - 4 + bow->translateY;
			if (!((arrow->translateX - 95 < resolution.x) && (arrow->translateY - 95 < resolution.y) &&
				(arrow->translateY + 95 > 0))) {
				arrow_move = false;
			}
			arrow->translateX += cos(arrow->rotation) * arrow->speed + deltaTimeSeconds;
			arrow->translateY += sin(arrow->rotation) * arrow->speed + deltaTimeSeconds;
			modelMatrix = arrow->arrowMoveMatrix(0, last_positionBow);
		}
		else {
			arrow->translateX = 0;
			//afisare sageata
			modelMatrix = arrow->arrowMatrix(0, bow->translateY, bow->rotation);
			arrow->rotation = bow->rotation;
			last_positionBow = bow->translateY;
		}


		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

	//baloane
		for (int i = 0; i < nrBaloons; i += 1) {
			//verificare iesire balon din ecran
			if ((baloons_coordinateY[i] + (1.35 * 30)) < resolution.y) {

				baloons_coordinateY[i] += baloons_speed[i] * deltaTimeSeconds;
			}
			else {
				//alegere coordonate random
				y = (rand() % ((500) - (190))) + (190);
				baloons_coordinateY[i] = -y;
			}
		
			if (i > 4) {
				j = i - 4;
			}
			else {
				j = i;
			}
			//verificare culoare balon
			if (i % 2 == 0) {
				baloon = yellow_baloon;
			}
			else {
				baloon = red_baloon;
			}

			//verificare activare animatie balon lovit
			if (baloon_animation[i] == false) {
			
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(0, baloons_coordinateY[i]);
				if (butterfly == false) {
					modelMatrixBody = modelMatrix;
					modelMatrixBody *= baloon->MatrixForBody(StartPosition_baloons + j * 65);

					modelMatrixTriangle = modelMatrix;
					modelMatrixTriangle *= baloon->MatrixForTriangle(StartPosition_baloons + j * 65);

					modelMatrixTail = modelMatrix;
					modelMatrixTail *= baloon->MatrixForTail(StartPosition_baloons + j * 65);
				}
				else {
					modelMatrix *= Transform2D::Translate(StartPosition_baloons + j * 65, 150);
				}
			
			}
			else {
				//aplicare animatie balon lovit
				if (baloons_coordinateY[i] < -190) {
					baloon_animation[i] = false;
					y = (rand() % ((0500) - (190))) + (190);
					baloons_coordinateY[i] = -y;
					 s = (rand() % ((250) - (70))) + (70);
					baloons_speed[i] = s;

					if (i % 2 == 0) {
						Score -= 5;
					}
					else {
						Score += 20;
					}
				}

				if (i > 4) {
					j = i - 4;
				}
				else {
					j = i;
				}
		
				baloons_coordinateY[i] = baloons_coordinateY[i] - 20;

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(0, baloons_coordinateY[i]);

				if (butterfly == false) {
					modelMatrixBody = modelMatrix;
					modelMatrixBody *= baloon->MatrixForBody(StartPosition_baloons + j * 65);

					modelMatrixTriangle = modelMatrix;
					modelMatrixTriangle *= baloon->MatrixForTriangle(StartPosition_baloons + j * 65);

					modelMatrixTail = modelMatrix;
					modelMatrixTail *= baloon->MatrixForTail(StartPosition_baloons + j * 65);
				}
				else {
					modelMatrix *= Transform2D::Translate(StartPosition_baloons + j * 65, 150);
				}
	
			}
			if (butterfly == false) {
				RenderMesh2D(baloon->oval, shaders["VertexColor"], modelMatrixBody);
				RenderMesh2D(baloon->triangle, shaders["VertexColor"], modelMatrixTriangle);
				RenderMesh2D(baloon->tail, shaders["VertexColor"], modelMatrixTail);
			}
			else {
				RenderMesh2D(meshes["butterfly"], shaders["VertexColor"], modelMatrix);
			}
			//caoliziune sageata balon
			float dx = arrow->translateX - (StartPosition_baloons + i * 65) + 95;
			float dy = arrow->translateY - 150 - baloons_coordinateY[i];
			float distance = sqrt(dx * dx + dy * dy);
			if (distance <= 30) {
				baloon_animation[i] = true;
			}
		}

		for (int i = 0; i < 3; i += 1) {
			
			if (shuriken_array[i] > -30) {
				shuriken_array[i] -= 100 * (i + 1) * deltaTimeSeconds;

			}
			else {
				y = (rand() % ((3000) - (1000))) + (1000);
				shuriken_array[i] = resolution.x + y;
				hit[i] = false;
				s = (rand() % ((250) - (70))) + (70);
				shuriken_speed[i]= s;
			}
			//coliziune sageata shuriken
			float dx1 = arrow->translateX - shuriken_array[i];
			float dy1 = arrow->translateY - (200 + (60 + 100) * i);
			float distance1 = sqrt(dx1 * dx1 + dy1 * dy1);

			if (distance1 <= 30) {
				shuriken_animation[i] = shuriken_animation[i] - 0.1;
			}
			//coliziune shuriken arc
			float dx3 = bow->positionX - shuriken_array[i];
			float dy3 = bow->positionY + bow->translateY - (200 + (60 + 100) * i);
			float distance3 = sqrt(dx3 * dx3 + dy3 * dy3);
			if (distance3 <= 100) {
				if (hit[i] == false) {
					lifes = lifes - 1;
					hit[i] = true;
				}
			}

		}

		shuriken->centerRotation += 2 * deltaTimeSeconds;

		for (int i = 0; i < 3; i += 1) {
			//verificare animatie pt shuriken lovit
			if (shuriken_animation[i] == 1) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(shuriken_array[i], 200 + (60 + 100) * i);
				modelMatrix *= Transform2D::Rotate(shuriken->centerRotation);
			}
			else {
				if (shuriken_animation[i] > 0) {
					shuriken_animation[i] = shuriken_animation[i] -0.1;
				}
				else {
					Score += 10;
					shuriken_animation[i] = 1;
					shuriken_array[i] = resolution.x + 500 * (i + 1);

				}
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(shuriken_array[i], 200 + (60 + 100) * i);
				modelMatrix *= Transform2D::Rotate(shuriken->centerRotation);
				modelMatrix *= Transform2D::Scale(shuriken_animation[i], shuriken_animation[i]);
			}
			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
		if (lifes == 0) {
			gameOver = true;
			cout << "GAME OVER!\n";
		}
		if (Score != lastScore) {
			cout << "Score: " << Score<<"\n";
			lastScore = Score;
		}
		
	}else {
	//afisare joc pierdut
	glLineWidth(8);
	modelMatrix = Transform2D::Translate(300, 500);
	RenderMesh2D(meshes["game"], shaders["VertexColor"], modelMatrix);
	modelMatrix = Transform2D::Translate(300, 300);
	RenderMesh2D(meshes["over"], shaders["VertexColor"], modelMatrix);
	glLineWidth(1);
	}
	
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		//miscare arc in sus
		if (bow->translateY + 105 < resolution.y / 2) {
			bow->translateY += bow->speed * deltaTime;
		}
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		//miscare arc in jos
		if (bow->translateY - 105 > -resolution.y / 2) {
			bow->translateY -= bow->speed * deltaTime;
		}
	}

}


void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		butterfly = true;
	}
	if (key == GLFW_KEY_B) {
		butterfly = false;
	}

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	bow->rotation = atan2(((-mouseY + resolution.y) - bow->positionY), (mouseX - bow->positionX));
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	//calculare viteza sageata
	if (button == 1 && arrow_move == false) {
		arrow->speed = 5;//initializare viteza
		increase_speed = true;
	}
	
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == 1) {
		//lansare sageata
		arrow_move = true;
		increase_speed = false;
		//resetare power bar
		grow_speed = 1;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

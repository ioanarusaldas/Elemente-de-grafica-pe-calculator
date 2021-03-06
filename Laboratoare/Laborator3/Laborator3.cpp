#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;
bool up;
int time;
bool grow;
float cx, cy;
float squareSize1;
float squareSide;
float radians;
Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	 squareSide = 100;

	// compute coordinates of square center
	cx = corner.x + squareSide / 2;
	cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = -81;
	translateY = -81;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	up = true;
	grow = false;
	time = 0;
	squareSize1 = 100;
	radians = 0;



	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations

	if (up == true) {
		
		translateX += deltaTimeSeconds * 100;
		translateY += deltaTimeSeconds * 100;

		if (time < 100) {
			time += 1;
		}
		else {
			time = 0;
			up = false;
		}
	}
	else {
		translateX -= deltaTimeSeconds * 100;
		translateY -= deltaTimeSeconds * 100;

		if (time < 100) {
			time += 1;
		}
		else {
			time = 0;
			up = true;
		}
	}
	


	//modelMatrix = glm::mat3(1);
	//modelMatrix *= Transform2D::Translate(150, 250);
	modelMatrix = Transform2D::Translate(150, 250) * Transform2D::Translate(translateX, translateY) * glm::mat3(1);
	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	if (grow == true) {

		scaleX += 1.5 *deltaTimeSeconds;
		scaleY += 1.5 *deltaTimeSeconds;
		
		if (scaleX >= 1) {

			grow = false;
		}

	}
	else {
	
		scaleX -= 1.5 *deltaTimeSeconds;
		scaleY -= 1.5*deltaTimeSeconds;
		
		if (scaleX < 0){
			grow = true;
		}
	}



	//modelMatrix = glm::mat3(1);
	//modelMatrix *= Transform2D::Translate(400, 250);
	
	modelMatrix = Transform2D::Translate(400, 250)* Transform2D::Translate(cx, cy)* Transform2D::Scale(scaleX, scaleY)* Transform2D::Translate(-cx, -cy) *glm::mat3(1);
	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);


	

	//modelMatrix = glm::mat3(1);
	//modelMatrix *= Transform2D::Translate(650, 250);
	radians += 2 * deltaTimeSeconds;
	modelMatrix = Transform2D::Translate(650, 250)* Transform2D::Translate(cx, cy) * Transform2D::Rotate(radians) * Transform2D::Translate(-cx, -cy) *glm::mat3(1);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}

#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;
int c_key;
bool c_press;
bool W_key;
bool A_key;
bool S_key;
bool D_key;
bool Q_key;
bool E_key;
int model = 1;
float x, y, z;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;



		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

		c_key = 1;
		c_press = false;

		W_key = false;
		A_key = false;
		S_key = false;
		D_key = false;
		E_key = false;
		Q_key = false;
		model = 1;
		x = 1;
		y = 0.5f;
		z = 0;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	

		if (c_key == 1) {
			glClearColor(0, 0, 0, 1);
		}
		if (c_key == 2) {
			
			glClearColor(1, 0, 1, 1);
		}




	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object


	RenderMesh(meshes["box"], glm::vec3(x, y, z), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	switch (model) {
	case 1: {RenderMesh(meshes["teapot"], glm::vec3(2, 0, 2));
	
		break;}
	case 2: {RenderMesh(meshes["box"], glm::vec3(2, 0, 2));
	
		break;}
	case 3: {RenderMesh(meshes["sphere"], glm::vec3(2, 0, 2));
	
		break;}
	default: break;
	}
	
	//coordonate: x(dreapta) y(sus) z(in fata)
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (W_key == true) {
		z -= (2 * deltaTime);
	}
	if (S_key == true) {
		z += (2 * deltaTime);
	}
	if (D_key == true) {
		x += (2 * deltaTime);
	}
	if (A_key == true) {
		x -= (2 * deltaTime);
	}
	if (Q_key == true) {
		y -= (2 * deltaTime);
	}
	if (E_key == true) {
		y += (2 * deltaTime);
	}
	
};

void Laborator1::OnKeyPress(int key, int mods)
{
	//am schimbat apasarea tastelor w,a,s,d cu sageti pentru a nu se confunda cu miscarea camerei
	// add key press event
	if (key == GLFW_KEY_C) {
		// do something
		//c_press = true;
		if (c_key == 1)
			c_key = 2;
		else {
			if (c_key == 2)
				c_key = 1;
		}
	}
	if (key == GLFW_KEY_Z) {
		// do something
		if (model == 3)
			model = 1;
		else
			model += 1;

	}
	if (key == GLFW_KEY_UP) {
		// do something
		W_key = true;
	}
	if (key == GLFW_KEY_LEFT) {
		// do something
		A_key = true;
	}
	if (key == GLFW_KEY_DOWN) {
		// do something
		S_key = true;
	}
	if (key == GLFW_KEY_RIGHT) {
		// do something
		D_key = true;
	}
	if (key == GLFW_KEY_Q) {
		// do something
		Q_key = true;
	}
	if (key == GLFW_KEY_E) {
		// do something
		E_key = true;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_C) {
		// do something
		c_press = false;
	}
	if (key == GLFW_KEY_UP) {
		// do something
		W_key = false;
	}
	if (key == GLFW_KEY_LEFT) {
		// do something
		A_key = false;
	}
	if (key == GLFW_KEY_DOWN) {
		// do something
		S_key = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		// do something
		D_key = false;
	}
	if (key == GLFW_KEY_Q) {
		// do something
		Q_key = false;
	}
	if (key == GLFW_KEY_E) {
		// do something
		E_key = false;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

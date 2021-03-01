//Savu Ioana Rusalda335CB
#include "Platforms.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include <Laboratoare\Tema2\Object2D.h>
#include <Laboratoare\Tema2\Transform2D.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}
void Tema2::SetGameVariables() {

	gameOver = false;
	jump = false;
	first_person = false;
	sphereZ = 0;
	sphereY = 0.3;
	sphereX = 2.5;
	Sphere_speed = 1.5f;
	Sphere_speed_jump = 5.0f;
	speed_block = 0;
	orangeSpeed = 5.0f;
	fuelX = 1.0f;
	maxSpeed = 4.5;
	shader = "ShaderT";

	//rosu
	colors.push_back(glm::vec3(1, 0, 0));
	//galben
	colors.push_back(glm::vec3(1, 1, 0));
	//portocaliu
	colors.push_back(glm::vec3(1.000, 0.647, 0.000));
	//verde
	colors.push_back(glm::vec3(0, 1, 0));
	//albastru
	colors.push_back(glm::vec3(0.000, 0.000, 0.804));

	//3 *20 = 60 de placi => distributie culori cu distributed_colors
	distributed_colors = (int*)malloc(5 * sizeof(int));
	distributed_colors[0] = 6;
	distributed_colors[1] = 6;
	distributed_colors[2] = 9;
	distributed_colors[3] = 12;
	distributed_colors[4] = 27;
}

void Tema2::Init()
{
	//setare camera
	cameraSpeed = 2.0f;
	renderCameraTarget = false;
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(2, 2, 3.5f), glm::vec3(2, 1, 0), glm::vec3(0, 1, 0));

	//creare placa
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//creare minge
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//creare rezervor + combustibil
	Mesh* fuel = Object2D::CreateRectangle("fuel", 1.7, 0.15, glm::vec3(1, 1, 1));
	AddMeshToList(fuel);
	Mesh* fuel_animation = Object2D::CreateRectangle("fuel_animation", 1.7, 0.15, glm::vec3(1, 0, 0));
	AddMeshToList(fuel_animation);

	//generare matrice de proiectie
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	SetGameVariables();//setare variabile de joc

	//initializare platforme
	initPlatforms(platforms, colors);

	//setare culoare + vizibilitate random
	for (int i = 1; i < 20; i++) {
		setVisibility(i, i - 1, platforms);
		setColor(i, platforms, colors, distributed_colors);
	}
	//salvare ultima platforma
	last[0] = platforms[0][19];
	last[1] = platforms[1][19];
	last[2] = platforms[2][19];
	last_index = 19;
	move_platform = false;

	//initializare shader
	{
		//shader obiecte 3D
		Shader* shader = new Shader("ShaderT");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		//shader deformare sfera
		Shader* shader = new Shader("ShaderD");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/DeformShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	//verificare combustibil terminat
	if (fuelX < 0.05) {
		gameOver = true;
	}
	if (fuelX > 1)//verificare combustibil maxim
		fuelX = 1;
	//afisare rezervor + combustibil
	glm::mat3 modelMatrix2D = glm::mat3(1);
	modelMatrix2D *= Transform2D::Translate(-2.5, 2.1);
	modelMatrix2D *= Transform2D::Scale(fuelX, 1);
	RenderMesh2D(meshes["fuel_animation"], shaders["VertexColor"], modelMatrix2D);

	modelMatrix2D = glm::mat3(1);
	modelMatrix2D *= Transform2D::Translate(-2.5, 2.1);
	RenderMesh2D(meshes["fuel"], shaders["VertexColor"], modelMatrix2D);

	//afisare placi
	{
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 3; j++) {
				if (j != 0)
					platforms[j][i].center.x = platforms[j - 1][i].center.x + 1.5;
				else
					platforms[j][i].center.x = 1;

				if (platforms[j][i].visible == 1) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, platforms[j][i].center);
					modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.05, 5));
					RenderSimpleMesh(meshes["box"], shaders["ShaderT"], modelMatrix, platforms[j][i].color);
				}
				//determinare placi care ies din camera
				if (platforms[j][i].center.z > sphereZ + 5) {
					//actualizare culori disponibile
					for (int k = 0; k < 5; k++) {
						if (platforms[j][i].color == colors[k]) {
							distributed_colors[k] += 1;
						}
					}
					platforms[j][i].center.z = last[j].center.z - 5 - 0.5;			
					last[j].center.z = platforms[j][i].center.z;
					bool x = rand() % 2;
					platforms[j][i].visible = x;
					move_platform = true;
				}
			}
			//resetare culori + vizibilitate placi
			if(move_platform) {
				setVisibility(i, last_index, platforms);
				setColor(i, platforms, colors, distributed_colors);
				last_index = i;
				move_platform = false;
			}
		}		
	}
	if(gameOver == false)
	{ 
		//stabilire pozitie camera
		if (first_person == false) {
			camera->Set(glm::vec3(platforms[0][1].center.x + 1.5, platforms[0][1].center.y + 2, sphereZ + 2.5), glm::vec3(platforms[0][1].center.x + 1.5, platforms[0][1].center.y + 1, sphereZ ), glm::vec3(0, 1, 0));
		}
		else {
			camera->Set(glm::vec3(sphereX, sphereY, sphereZ), glm::vec3(sphereX, sphereY, sphereZ - 1), glm::vec3(0, 1, 0));
		}
		//mentinere viteza constanta in functie de placa portocalie
		if (speed_block != 0) {
			speed_block -= 1;
			cameraSpeed = orangeSpeed;
		}
		else {
			cameraSpeed = Sphere_speed;
			shader = "ShaderT";
		}
		//miscare sfera + camera
		camera->MoveForward(deltaTimeSeconds * cameraSpeed);
		sphereZ -= deltaTimeSeconds * cameraSpeed;
	
		//saritura minge
		if (jump == true) {
			//actualizare viteza 
			Sphere_speed_jump += -10 * deltaTimeSeconds;
			sphereY += Sphere_speed_jump * deltaTimeSeconds + (float)(-10 * deltaTimeSeconds * deltaTimeSeconds) / 2;
			//verificare intoarcere sfera la sol
			if (sphereY < 0.3f) {
				jump = false;
				sphereY = 0.3;
				Sphere_speed_jump = 5.0f;

			}
		}
		//verificare sfera atinge platforma
		if (sphereY <= 0.3f) {
			//parcurgere randuri
			for (int i = 0; i < 20; i++) {
				//parcurgere coloane
				for (int j = 0; j < 3; j++) {
					if(platform_Colision(platforms,j,i,sphereZ, sphereX) ==  true) {
							//platforma rosie
							if (platforms[j][i].color == colors[0]) {
								gameOver = true;
							}
							//platforma galbena
							if (platforms[j][i].color == colors[1]) {
								fuelX -= 5*deltaTimeSeconds;
							}
							//platforma verde
							if (platforms[j][i].color == colors[3]) {
								//verific sa nu depaseasca valoarea maxima de scalare
								if(fuelX < 1)
									fuelX += 5 * deltaTimeSeconds;
							}
							//platforma portocalie
							if (platforms[j][i].color == colors[2]) {
								speed_block = 150;
								shader = "ShaderD";
								cameraSpeed = orangeSpeed;
							}
							//lipsa platforma
							if (platforms[j][i].visible == false) {
								gameOver = true;
							}
							//actualizare culori disponibile
							for (int k = 0; k < 5; k++) {
								if (platforms[j][i].color == colors[k]) {
									distributed_colors[k] += 1;
								}
							}
							//schimbare culoare placa in mov
							platforms[j][i].color = glm::vec3(0.580, 0.000, 0.827);
					}
				}

				//gameover laterale placi
				gameOver = lateral_Colision(platforms, i, sphereZ, sphereX,gameOver);
				//gameover in fata
				gameOver = front_Colision(platforms, i, sphereZ, sphereX,gameOver);
		
			}
		}
		fuelX -= 0.0002; //scad combustibil
	}
	else {
		sphereY -= 0.1;//animatie cazatura sfera
		cout << "GAME OVER!"<<endl;
	}
	if (first_person == false) {//afisare sfera doar in third_person
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(sphereX, sphereY, sphereZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
		RenderSimpleMesh(meshes["sphere"], shaders[shader], modelMatrix, glm::vec3(0.2, 0.5, 0.7));
	}
}

void Tema2::FrameEnd()
{
	//afisare grid
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}
void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);
	// trimitere matrice modelare
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// trimitere matrice vizualizare
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// trimitere matrice proiectie
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//trimitere culoare
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

		if (window->KeyHold(GLFW_KEY_W)) {
			//actualizare viteza sfera
			if (Sphere_speed < maxSpeed && speed_block == 0) {
				Sphere_speed += 2 * deltaTime;
				cameraSpeed = Sphere_speed;
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			//actualizare viteza sfera
			if (Sphere_speed > 1 && speed_block == 0) {
				Sphere_speed -= 2 * deltaTime;
				cameraSpeed = Sphere_speed;
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			//deplasare sfera in stanga
			if (sphereX > 0)
				sphereX -= deltaTime * Sphere_speed;
		}
		if (window->KeyHold(GLFW_KEY_D)) {
			//deplasare sfera in dreapta
			if (sphereX < 5)
				sphereX += deltaTime * Sphere_speed;
		}	
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	//detectare saritura
	if (key == GLFW_KEY_SPACE) {
		jump = true;
	}
	if (key == GLFW_KEY_C) {

		first_person = 1 - first_person;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

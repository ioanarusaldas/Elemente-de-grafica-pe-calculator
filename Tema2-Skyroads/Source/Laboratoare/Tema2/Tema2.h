#pragma once
//Savu Ioana Rusalda335CB
#include <Component/SimpleScene.h>
#include "LabCamera.h"
struct Plane {
	glm::vec3 center;
	glm::vec3 color;
	glm::vec3 size;
	int visible;

};

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void SetGameVariables();

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		Plane last[3];//ultima platforma din sir
		Plane* platforms[20];//platformele
		//coordonate sfera
		float sphereX;
		float sphereZ;
		float sphereY;
		//factor scalare cand rezervorul e plin
		float fuelX;
		float Sphere_speed;	//viteza sfera
		float orangeSpeed;	//viteza sfera cu poewrups
		float Sphere_speed_jump;//viteza saritura
		bool jump;
		bool move_platform;//reactualizare distanta platforma
		bool first_person;//schimbare camera
		bool gameOver;//sfarsit joc
		float maxSpeed; //viteza maxima sfera
		float speed_block;//blocare taste S W cand se aplica power-ups
		std::string shader;//shader folosit
		int last_index;
		float cameraSpeed; //viteza camera
		std::vector<glm::vec3> colors;//culori placi
		int * distributed_colors;//distributie culori
		glm::vec3 camera_position;
		const glm::vec3 camera_center;
};

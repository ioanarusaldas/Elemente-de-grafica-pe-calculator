//Savu Ioana Rusalda 335CB
#pragma once
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 modelMatrixBody;
	glm::mat3 modelMatrixTriangle;
	glm::mat3 modelMatrixTail;
	//float translateX, translateY;
	float scaleX, scaleY;
	float angularStep;
	float StartPosition_baloons;
	bool arrow_move;
	bool increase_speed;
	float grow_speed;
	glm::ivec2 resolution;
	Mesh* oval;
	Mesh* triangle;
	Mesh* tail;
	int lifes;
	bool gameOver;
	int Score, lastScore;
	int nrBaloons, nrShuriken;
	float butterfly;
	float last_positionBow;
	float maxSpeed = 50;
};

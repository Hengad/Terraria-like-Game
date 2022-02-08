#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

#include "..\game\Window.h"
#include "Player.h"
#include "..\..\management\ResourceManager.h"

class Camera
{
public:
	Camera();

	glm::vec2 cameraPosition; // top left corner

	bool cameraLocked;
	bool mapVisible;

	void lockCamera();
	void freeCamera();

	void showMap();
	void hideMap();

	void update(GameObject* player);
};
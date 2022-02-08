#pragma once
#include <iostream>

#include "..\..\graphics\GameObject.h"
#include "..\world\Tile.h"
#include "..\game\Window.h"

#include <GLFW\glfw3.h>

class Player : public GameObject
{
private:
	float speed;
public:
	glm::vec2 direction;
	Player(glm::vec2 pos, glm::vec4 color, glm::vec2 size, float speed);
	void update(float dt);
	void setDirection(glm::vec2 direction);
	float getSpeed() const { return speed; }
	void setSpeed(float speed) { this->speed = speed; }
};
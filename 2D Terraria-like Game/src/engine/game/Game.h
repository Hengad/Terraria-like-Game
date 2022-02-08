#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <random>

#include "Window.h"
#include "..\management\ResourceManager.h"
#include "..\management\StateManager.h"
#include "..\graphics\Renderer.h"
#include "..\world\World.h"
#include "..\player\Player.h"
#include "..\player\Camera.h"

class Game
{
private:
	GLuint m_width;
	GLuint m_height;

	GLboolean leftMouseOldState, leftMouseNewState, rightMouseOldState, rightMouseNewState;
	GLboolean keysOldState[1024];
	GLboolean keysNewState[1024];

	glm::mat4 projection;

	Camera *cam;
	Player *player;
	World *world;

	GLboolean leftMouseClicked();
	GLboolean rightMouseClicked();

public:
	StateManager stateManager;
	Renderer renderer;

	static glm::vec2 cursorPos;
	GLboolean leftMousePressed, rightMousePressed;
	GLboolean keys[1024];

	GLuint getWinWidth() const { return m_width; }
	GLuint getWinHeight() const { return m_height; }

	Game();
	~Game();

	void init();
	void processInput();
	void update(float dt);
	void render(float dt);
};
#include "Game.h"

glm::vec2 Game::cursorPos;

GLboolean Game::leftMouseClicked()
{
	leftMouseNewState = GLFW_RELEASE;

	if (leftMousePressed == GL_TRUE)
		leftMouseNewState = GLFW_PRESS;
	if (leftMouseNewState == GLFW_RELEASE && leftMouseOldState == GLFW_PRESS)
	{
		leftMouseOldState = leftMouseNewState;
		return true;
	}
	leftMouseOldState = leftMouseNewState;
	return false;
}

GLboolean Game::rightMouseClicked()
{
	return false;
}

Game::Game()
{
	this->m_width = Window::getWinWidth();
	this->m_height = Window::getWinHeight();
}

Game::~Game()
{
	delete cam;
	delete player;
	delete world;
}

void Game::init()
{
	projection = glm::ortho(0.0f, (float)Window::getWinWidth(), (float)m_height, 0.0f, -1.0f, 1.0f);
	ResourceManager::loadShader("res/shaders/generic.vert", "res/shaders/generic.frag", "shader");
	ResourceManager::loadShader("res/shaders/light.vert", "res/shaders/light.frag", "lightShader");
	ResourceManager::getShader("shader").use();
	ResourceManager::getShader("shader").setMatrix4("projection", projection);
	ResourceManager::getShader("lightShader").use();
	ResourceManager::getShader("lightShader").setMatrix4("projection", projection);

	ResourceManager::loadTexture("res/textures/grass.png", GL_FALSE, "grass");
	ResourceManager::loadTexture("res/textures/sand.png", GL_FALSE, "sand");
	ResourceManager::loadTexture("res/textures/water.png", GL_FALSE, "water");
	ResourceManager::loadTexture("res/textures/player.png", GL_FALSE, "player");
	ResourceManager::loadTexture("res/textures/torch.png", GL_TRUE, "torch");
	ResourceManager::loadTexture("res/textures/white.png", GL_FALSE, "white");

	ResourceManager::loadImage("res/textures/cursor24px.png", "cursor");

	for (int i = 0; i < 1024; i++)
		keysOldState[i] = GLFW_RELEASE;

	leftMouseOldState = GLFW_RELEASE;
	rightMouseOldState = GLFW_RELEASE;

	renderer.init(ResourceManager::getShader("shader"), ResourceManager::getShader("lightShader"));

	player = new Player(glm::vec2(2*29*50.0f+1100.0f, 2*18*50.0f+600.0f), glm::vec4(200.0f, 0.0f, 0.0f, 1.0f), glm::vec2(50.0f, 50.0f), 1200.0f);
	world = new World(glm::i32vec2(29, 18), 50.0f); // blockSize 50.0f
	cam = new Camera();
}

void Game::processInput()
{
	for (int i = 0; i < 1024; i++)
		keysNewState[i] = GLFW_RELEASE;

	if (keys[GLFW_KEY_ESCAPE] == GL_TRUE)
		keysNewState[GLFW_KEY_ESCAPE] = GLFW_PRESS;
	if (keys[GLFW_KEY_ENTER] == GL_TRUE)
		keysNewState[GLFW_KEY_ENTER] = GLFW_PRESS;
	if (keysNewState[GLFW_KEY_ENTER] == GLFW_RELEASE && keysOldState[GLFW_KEY_ENTER] == GLFW_PRESS)
	{
		stateManager.push();
		if(stateManager.getGameState() == State::PAUSE)
			cam->showMap();
	}
	if (keysNewState[GLFW_KEY_ESCAPE] == GLFW_RELEASE && keysOldState[GLFW_KEY_ESCAPE] == GLFW_PRESS)
	{
		stateManager.pop();
		if (stateManager.getGameState() == State::GAME)
			cam->hideMap();
	}

	if (stateManager.getGameState() == State::GAME)
	{
		if (keys[GLFW_KEY_SPACE] == GL_TRUE)
			cam->lockCamera();
		if (keys[GLFW_KEY_Y] == GL_TRUE)
			cam->freeCamera();

		/*
		* Tässä bugi, aiheuttaa crashin
		* 
		if (leftMouseClicked())
		{
			if(world->getTileAtCursor(player) != nullptr)
				world->getTileAtCursor(player)->setTile(TileType::TORCH); // chunkien välillä nullptr
		}
		*/

		//if (keys[GLFW_KEY_F] == GL_TRUE)
		//	keysNewState[GLFW_KEY_F] = GLFW_PRESS;
		//if (keysNewState[GLFW_KEY_F] == GLFW_RELEASE && keysOldState[GLFW_KEY_F] == GLFW_PRESS)
		//	world->getPlayerPositionTopBlock(player)->setTile(TileType::TORCH);

		if (keys[GLFW_KEY_W] == GL_TRUE && !keys[GLFW_KEY_S])
			player->setDirection(glm::vec2(player->direction.x, -player->getSpeed()));
		if (keys[GLFW_KEY_S] == GL_TRUE && !keys[GLFW_KEY_W])
			player->setDirection(glm::vec2(player->direction.x, player->getSpeed()));
		if (keys[GLFW_KEY_A] == GL_TRUE && !keys[GLFW_KEY_D])
			player->setDirection(glm::vec2(-player->getSpeed(), player->direction.y));
		if (keys[GLFW_KEY_D] == GL_TRUE && !keys[GLFW_KEY_A])
			player->setDirection(glm::vec2(player->getSpeed(), player->direction.y));
	}

	for (int i = 0; i < 1024; i++)
		keysOldState[i] = keysNewState[i];
}

void Game::update(float dt)
{
	if (stateManager.getGameState() == State::GAME)
	{
		player->update(dt);
		world->update(player);
	}

	cam->update(player);

	//std::cout << "x: " << cursorPos.x << " y: " << cursorPos.y << std::endl;
}

void Game::render(float dt)
{
	if (stateManager.getGameState() == State::GAME)
	{
		world->render(renderer);
		renderer.render(player->position, player->texture);
	}
	else if (stateManager.getGameState() == State::PAUSE)
	{
		world->renderMap(renderer);
		renderer.render(player->position, player->texture, glm::vec3(1.0f, 1.0f, 1.0f), false, player->size);
	}
}

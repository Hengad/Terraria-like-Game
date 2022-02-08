#include "World.h"
#include "../game/Game.h"

World::World(const glm::i32vec2 chunkSize, float blockSize)
	: chunkSize(chunkSize), blockSize(blockSize)
{
	playerChunkLocX = 0;
	playerChunkLocY = 0;
	playerChunkQuarter = Quarter::BOTTOM_RIGHT;

	heightMap = new float*[worldSize * chunkSize.x];
	for (int i = 0; i < worldSize * chunkSize.x; i++)
		heightMap[i] = new float[worldSize * chunkSize.y];

	for (int i = 0; i < worldSize; i++)
	{
		for (int j = 0; j < worldSize; j++)
		{
			chunks[j][i] = new Chunk(glm::vec2(j*chunkSize.x*blockSize, i*chunkSize.y*blockSize), chunkSize, blockSize);
		}
	}
	
	generateHeightMap();
}

void World::generateHeightMap()
{
	FastNoise noise; // Create a FastNoise object
	noise.SetNoiseType(FastNoise::PerlinFractal); // Set the desired noise type
	noise.SetSeed(43634675);
	
	for (int y = 0; y < worldSize*chunkSize.y; y++)
	{
		for (int x = 0; x < worldSize*chunkSize.x; x++)
		{
			heightMap[x][y] = noise.GetNoise(x, y);
		}
	}
	
	for (int cY = 0; cY < worldSize; cY++)
	{
		for (int cX = 0; cX < worldSize; cX++)
		{
			for (int y = 0; y < chunkSize.y; y++)
			{
				for (int x = 0; x < chunkSize.x; x++)
				{
					//heightmap conversion
					if (heightMap[cX*chunkSize.x + x][cY*chunkSize.y + y] < -0.08) // simplexfractal -0.2
						this->chunks[cX][cY]->tiles[x][y][0]->setTile(TileType::WATER);
					else if (heightMap[cX*chunkSize.x + x][cY*chunkSize.y + y] < 0.0) // simplexfractal -0.05 
						this->chunks[cX][cY]->tiles[x][y][0]->setTile(TileType::SAND);
					else
						this->chunks[cX][cY]->tiles[x][y][0]->setTile(TileType::GRASS);
				}
			}
		}
	}
}

void World::update(Player *player)
{
	timerEnd = (float)glfwGetTime();

	timer += timerEnd - timerBegin;
	timerBegin = timerEnd;

	if (timer > 1.0)
	{
		int playerX = (player->position.x + player->size.x / 2 - playerChunkLocX*chunkSize.x*blockSize) / blockSize;
		int playerY = (player->position.y + player->size.y / 2 - playerChunkLocY*chunkSize.y*blockSize) / blockSize;
		//std::cout << "[" << playerChunkLocX << "] [" << playerChunkLocY << "] " << playerX << " " << playerY << std::endl;
		timer = 0.0;
	}

	playerChunkLocX = (player->position.x + player->size.x / 2) / (chunkSize.x * blockSize);
	playerChunkLocY = (player->position.y + player->size.y / 2) / (chunkSize.y * blockSize);

	float playerPosInChunkX = player->position.x + player->size.x / 2 - playerChunkLocX*chunkSize.x*blockSize; //0-1300
	float playerPosInChunkY = player->position.y + player->size.y / 2 - playerChunkLocY*chunkSize.y*blockSize; // 0-750

	if (playerPosInChunkX < chunkSize.x*blockSize / 2 && playerPosInChunkY < chunkSize.y*blockSize / 2)
		playerChunkQuarter = Quarter::TOP_LEFT;
	else if (playerPosInChunkX > chunkSize.x*blockSize / 2 && playerPosInChunkY < chunkSize.y*blockSize / 2)
		playerChunkQuarter = Quarter::TOP_RIGHT;
	else if (playerPosInChunkX < chunkSize.x*blockSize / 2 && playerPosInChunkY > chunkSize.y*blockSize / 2)
		playerChunkQuarter = Quarter::BOTTOM_LEFT;
	else if (playerPosInChunkX > chunkSize.x*blockSize / 2 && playerPosInChunkY > chunkSize.y*blockSize / 2)
		playerChunkQuarter = Quarter::BOTTOM_RIGHT;

	if (getPlayerPositionBlock(player)->tileType != TileType::WATER)
		player->setSpeed(400.0f);
	else if (getPlayerPositionBlock(player)->tileType == TileType::WATER)
		player->setSpeed(250.0f);
}

Tile* World::getPlayerPositionBlock(Player* player)
{
	int playerX = (player->position.x + player->size.x / 2 - playerChunkLocX*chunkSize.x*blockSize) / blockSize;
	int playerY = (player->position.y + player->size.y / 2 - playerChunkLocY*chunkSize.y*blockSize) / blockSize;
	if (this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY] != nullptr)
	{
		if (this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY][1]->tileType == TileType::NONE)
			return this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY][0];
		else
			return this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY][1];
	}
}

Tile* World::getPlayerPositionTopBlock(Player* player)
{
	int playerX = (player->position.x + player->size.x / 2 - playerChunkLocX*chunkSize.x*blockSize) / blockSize;
	int playerY = (player->position.y + player->size.y / 2 - playerChunkLocY*chunkSize.y*blockSize) / blockSize;
	if (this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY] != nullptr)
	{
			return this->chunks[playerChunkLocX][playerChunkLocY]->tiles[playerX][playerY][1];
	}
}

Tile* World::getTileAtCursor(Player *player)
{
	//int X = (player->position.x - playerChunkLocX*chunkSize.x*blockSize - Window::getWinWidth()/2 + Game::cursorPos.x) / blockSize;
	//int Y = (player->position.y - playerChunkLocY*chunkSize.y*blockSize - Window::getWinHeight()/2 + Game::cursorPos.y) / blockSize;
	int x = player->position.x + (Game::cursorPos.x - Window::getWinWidth() / 2);
	int y = player->position.y + (Game::cursorPos.y - Window::getWinHeight() / 2);

	int cX = x / chunkSize.x * blockSize;
	int cY = y / chunkSize.y * blockSize;
	int tX = x % chunkSize.x * blockSize;
	int tY = y % chunkSize.y * blockSize;

	if (this->chunks[cX][cY]->tiles[tX][tY] != nullptr)
	{
		return this->chunks[cX][cY]->tiles[tX][tY][1];
	}
	return nullptr;
}

void World::renderMap(Renderer &renderer)
{
	if (playerChunkLocX >= 1 && playerChunkLocY >= 1 && playerChunkLocX <= worldSize - 2 && playerChunkLocY <= worldSize - 1)
	{
		for (int i = 0; i < worldSize; i++)
			for (int j = 0; j < worldSize; j++)
				chunks[j][i]->render(renderer);
	}
}

void World::render(Renderer &renderer)
{
	if (playerChunkLocX >= 1 && playerChunkLocY >= 1 && playerChunkLocX <= worldSize-2 && playerChunkLocY <= worldSize-1)
	{
		if (playerChunkQuarter == Quarter::TOP_LEFT)
		{
			chunks[playerChunkLocX][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX - 1][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX][playerChunkLocY - 1]->render(renderer);
			chunks[playerChunkLocX - 1][playerChunkLocY - 1]->render(renderer);
		}

		else if (playerChunkQuarter == Quarter::TOP_RIGHT)
		{
			chunks[playerChunkLocX][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX][playerChunkLocY - 1]->render(renderer);
			chunks[playerChunkLocX + 1][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX + 1][playerChunkLocY - 1]->render(renderer);
		}

		else if (playerChunkQuarter == Quarter::BOTTOM_LEFT)
		{
			chunks[playerChunkLocX][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX - 1][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX][playerChunkLocY + 1]->render(renderer);
			chunks[playerChunkLocX - 1][playerChunkLocY + 1]->render(renderer);
		}

		else if (playerChunkQuarter == Quarter::BOTTOM_RIGHT)
		{
			chunks[playerChunkLocX][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX + 1][playerChunkLocY]->render(renderer);
			chunks[playerChunkLocX][playerChunkLocY + 1]->render(renderer);
			chunks[playerChunkLocX + 1][playerChunkLocY + 1]->render(renderer);
		}
	}

	/*
	for (int y = 0; y < worldSize; y++)
	{
		for (int x = 0; x < worldSize; x++)
		{
			chunks[x][y]->render(renderer);
		}
	}
	*/
}

/*
std::mt19937 rng;
rng.seed(std::random_device()());
std::uniform_int_distribution<std::mt19937::result_type> r(230, 280);

for (int y = 0; y < 50; y++) // 15
{
	for (int x = 0; x < 100; x++) // 26
	{
		if (y>y*y + x*x - 26 * x - 13 * y + 195)
			gameObjects.push_back(new GameObject(ResourceManager::getShaderLocation("shader"), glm::vec2(50.0f*(float)x, 50.0f*(float)y), glm::vec3(r(rng) / 255.0f*0.0f, r(rng) / 255.0f*153.0f, r(rng) / 255.0f*255.0f)));
		else if (y>y*y + x*x - 26 * x - 13 * y + 185 && y < (y*y + x*x - 26 * x - 13 * y + 195))
			gameObjects.push_back(new GameObject(ResourceManager::getShaderLocation("shader"), glm::vec2(50.0f*(float)x, 50.0f*(float)y), glm::vec3(r(rng) / 255.0f*255.0f, r(rng) / 255.0f*198.0f, r(rng) / 255.0f*26.0f)));
		else
			gameObjects.push_back(new GameObject(ResourceManager::getShaderLocation("shader"), glm::vec2(50.0f*(float)x, 50.0f*(float)y), glm::vec3(r(rng) / 255.0f*25.0f, r(rng) / 255.0f*77.0f, r(rng) / 255.0f*25.0f)));
	}
}*/
#pragma once
#include <random>
#include <iostream>

#include "..\vendor\noise\FastNoise.h"
#include "Chunk.h"
#include "..\player\Player.h"

enum class Quarter {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

class World
{
private:
	float timer = 0.0f, timerEnd = 0.0f, timerBegin = 0.0f; // clock
	int playerChunkLocX, playerChunkLocY;
	Quarter playerChunkQuarter;

	void generateHeightMap();
public:
	static const int worldSize = 40; // privateks
	const glm::i32vec2 chunkSize; // privateks
	const float blockSize; // privateks

	World(glm::i32vec2 chunkSize, float blockSize);
	float** heightMap;
	Chunk *chunks[worldSize][worldSize];

	void update(Player *player);
	Tile* getPlayerPositionBlock(Player* player);
	Tile* getPlayerPositionTopBlock(Player *player);
	Tile* getTileAtCursor(Player *player);
	void renderMap(Renderer &renderer);
	void render(Renderer &renderer);
};
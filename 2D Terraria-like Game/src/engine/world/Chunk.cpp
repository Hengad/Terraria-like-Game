#include "Chunk.h"

Chunk::Chunk(glm::i32vec2 position, const glm::i32vec2 chunkSize, float blockSize)
	: chunkSize(chunkSize)
{
	//this->chunkSize = chunkSize;

	for (int y = 0; y < chunkSize.y; y++)
	{
		for (int x = 0; x < chunkSize.x; x++)
		{
			tiles[x][y][0] = new Tile(glm::vec2(blockSize*x + position.x, blockSize*y + position.y), TileType::GRASS, glm::vec2(blockSize, blockSize));
			tiles[x][y][1] = new Tile(glm::vec2(blockSize*x + position.x, blockSize*y + position.y), TileType::NONE, glm::vec2(blockSize, blockSize));
		}
	}
}

void Chunk::render(Renderer &renderer)
{
	for (int y = 0; y < chunkSize.y; y++)
	{
		for (int x = 0; x < chunkSize.x; x++)
		{
			if(tiles[x][y][1]->tileType != TileType::NONE)
			{
				tiles[x][y][0]->render(renderer);
				tiles[x][y][1]->render(renderer);
			}
			else
				tiles[x][y][0]->render(renderer);
		}
	}
}

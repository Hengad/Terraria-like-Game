#pragma once
#include <stack>
#include "Tile.h"

class Chunk
{
private:
	const glm::i32vec2 chunkSize;
public:
	Chunk(glm::i32vec2 position, const glm::i32vec2 chunkSize, float blockSize);
	Tile *tiles[29][18][2];
	// purkka ^^ koodaa vec2 chunkSize -> blocks[x][y]

	void render(Renderer &renderer);
};
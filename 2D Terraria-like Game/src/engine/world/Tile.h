#pragma once
#include <iostream>
#include <random>
#include <glm/gtc/type_precision.hpp>

#include "..\..\graphics\Renderer.h"
#include "..\..\graphics\GameObject.h"
#include "../management/ResourceManager.h"

enum class TileType { GRASS, DIRT, SAND, WATER, WOOD, TORCH, NONE };

class Tile : public GameObject
{
public:
	static int numOfTorches;
	TileType tileType;

	Tile(glm::i32vec2 pos, TileType tileType, glm::vec2 size = glm::vec2(50.0f, 50.0f));
	virtual void setTile(TileType tileType);
	void render(Renderer &renderer);
};
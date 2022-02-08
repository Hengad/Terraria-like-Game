#include "Tile.h"
#include <string>

int Tile::numOfTorches;

Tile::Tile(glm::i32vec2 pos, TileType tileType, glm::vec2 size)
	: GameObject(pos, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), size)
{
	this->size = size;
	this->position = pos;
	this->tileType = tileType;
	this->lightSource = false;
	numOfTorches = 0;

	this->setTile(this->tileType);
}

void Tile::setTile(TileType tileType)
{
	this->tileType = tileType;
	this->size = glm::vec2(50.0f, 50.0f);

	switch (tileType)
	{
	case TileType::NONE:
		this->texture = ResourceManager::getTexture("none");
		break;
	case TileType::GRASS:
		this->texture = ResourceManager::getTexture("grass");
		break;
	case TileType::DIRT:
		this->texture = ResourceManager::getTexture("dirt");
		break;
	case TileType::SAND:
		this->texture = ResourceManager::getTexture("sand");
		break;
	case TileType::WATER:
		this->texture = ResourceManager::getTexture("water");
		break;
	case TileType::WOOD:
		this->texture = ResourceManager::getTexture("wood");
		break;
	// top layer:
	case TileType::TORCH:
		this->texture = ResourceManager::getTexture("torch");
		this->lightSource = true;
		std::string num = std::to_string(numOfTorches);
		ResourceManager::getShader("shader").setVector2f(("lightPositions[" + num + "]").c_str(), glm::vec2(position.x + 25.0f, position.y + 25.0f));
		ResourceManager::getShader("shader").setInteger("numOfLights", numOfTorches);
		//ResourceManager::getShader("shader").setVector2f(("lightPositions[0]"), this->position);
		numOfTorches++;
		std::cout << "numOfTorches: " << numOfTorches << std::endl;
		break;
	}
}

void Tile::render(Renderer &renderer)
{
	renderer.render(this->position, this->texture, glm::vec3(1.0f, 1.0f, 1.0f), this->lightSource);
}

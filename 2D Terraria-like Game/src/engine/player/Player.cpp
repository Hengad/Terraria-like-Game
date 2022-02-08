#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec4 color, glm::vec2 size, float speed)
	: GameObject(pos, color, size)
{
	this->position = pos;
	//this->color = color;
	this->size = size;
	this->speed = speed;
	this->texture = ResourceManager::getTexture("player");
	direction = glm::vec2(0.0f, 0.0f);
}

void Player::update(float dt)
{
	this->position.x += direction.x * dt;
	this->position.y += direction.y * dt;
	direction = glm::vec2(0.0f, 0.0f);
}

void Player::setDirection(glm::vec2 direction)
{
	this->direction.x = direction.x;
	this->direction.y = direction.y;
}
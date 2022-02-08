#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
{
	this->position = pos;
	this->size = size;
	this->velocity = velocity;
}
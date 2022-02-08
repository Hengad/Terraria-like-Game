#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "..\vendor\Shader\Shader.h"
#include "..\vendor\Texture\Texture.h"

class GameObject
{
public:
	GameObject(glm::vec2 pos, glm::vec2 size = glm::vec2(50.0f, 50.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	Texture* texture;
	glm::vec2 position, size, velocity;
	bool lightSource;
};

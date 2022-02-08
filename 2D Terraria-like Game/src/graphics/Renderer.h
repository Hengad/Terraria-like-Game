#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>

#include "Texture\Texture.h"
#include "GameObject.h"

class Renderer
{
private:
	void initRenderData();
	unsigned int VAO, VBO, EBO;
	unsigned int lightVAO;
public:
	Renderer() {};
	void init(Shader shader, Shader lightShader);

	void render(glm::vec2 pos, Texture* texture, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), bool lightSource = false,  glm::vec2 size = glm::vec2(50.0f, 50.0f));
	void renderLight(glm::vec2 pos, Texture* texture, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2 size = glm::vec2(50.0f, 50.0f));

	//void finishRendering();

	Shader shader;
	Shader lightShader;
};
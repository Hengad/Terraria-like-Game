#include "Renderer.h"
#include "..\management\ResourceManager.h"

/* ---------------------------------------- NO INSTANCING ----------------------------------------
void Renderer::initRenderData()
{
	float positions[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Renderer::render(Shader *shader, glm::vec2 pos, glm::vec3 color, glm::vec2 size)
{
	shader->use();

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	ResourceManager::getShader("shader").setMatrix4("model", model);
	ResourceManager::getShader("shader").setVector3f("color", color);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
*/


void Renderer::initRenderData()
{
	float vertices[] =
	{
		//pos & texcord //colors
		0.0f, 0.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,		1.0f, 1.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// normal VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // pos

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float))); // color

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // tex coord

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// light VAO
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); // color

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // tex coord

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Renderer::init(Shader shader, Shader lightShader)
{
	initRenderData();
	this->shader = shader;
	this->lightShader = lightShader;

	ResourceManager::getShader("shader").setInteger("texSampler", 0);
	ResourceManager::getShader("lightShader").setInteger("texSampler", 0);
}

void Renderer::renderLight(glm::vec2 pos, Texture* texture, glm::vec3 color, glm::vec2 size)
{
	this->lightShader.use();

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	ResourceManager::getShader("lightShader").setMatrix4("model", model);

	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glBindVertexArray(lightVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Renderer::render(glm::vec2 pos, Texture* texture, glm::vec3 color, bool lightSource, glm::vec2 size)
{
	if (lightSource)
	{
		renderLight(pos, texture, color, size);
	}
	else
	{
		this->shader.use();

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(pos, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		ResourceManager::getShader("shader").setMatrix4("model", model);
		//ResourceManager::getShader("shader").setVector3f("color", color);

		glBindTexture(GL_TEXTURE_2D, texture->ID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

/*
void Renderer::finishRendering()
{
	glBindVertexArray(VAO);
	modelMatrices = new glm::mat4[renderCallsAmount];

	//matriisien ja värien alustus
	for (int i = 0; i < gameObjectsGrass.size(); i++)
	{
		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(gameObjectsGrass.at(i)->position, 0.0f));
		model = glm::scale(model, glm::vec3(gameObjectsGrass.at(i)->size, 1.0f));

		modelMatricesGrass[i] = model;
	}

	for (int i = 0; i < gameObjectsSand.size(); i++)
	{
		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(gameObjectsSand.at(i)->position, 0.0f));
		model = glm::scale(model, glm::vec3(gameObjectsSand.at(i)->size, 1.0f));

		modelMatricesSand[i] = model;
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, renderCallsAmount * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW); // muunna yhdeksi matriksiksi modelMatrices

	//glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	//glBufferData(GL_ARRAY_BUFFER, renderCallsAmount * sizeof(glm::vec4), &modelColors[0], GL_DYNAMIC_DRAW);

	shader.use();

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, renderCallsAmount); // what is gl_triangle_strip?	

	glBindVertexArray(0);

	delete modelMatrices;
	//delete modelColors;

	renderCallsAmount = 0;
	gameObjectsGrass.clear();
	gameObjectsSand.clear();
	gameObjectsWater.clear();
}
*/
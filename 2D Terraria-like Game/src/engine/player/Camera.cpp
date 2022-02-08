#include "Camera.h"

Camera::Camera()
{
	glm::mat4 view(1.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	ResourceManager::getShader("shader").use();
	ResourceManager::getShader("shader").setMatrix4("view", view);
	cameraLocked = true;
	mapVisible = false;
}

void Camera::lockCamera()
{
	cameraLocked = true;
}

void Camera::freeCamera()
{
	cameraLocked = false;
}

void Camera::showMap()
{
	mapVisible = true;
	freeCamera();
}

void Camera::hideMap()
{
	mapVisible = false;
	lockCamera();
}

void Camera::update(GameObject* player)
{
	glm::mat4 view(1.0f);
	if (mapVisible)
	{
		//view = glm::translate(view, glm::vec3(500.0f, 0.0f, 0.0f));
		//view = glm::lookAt(glm::vec3(-400.0f, 0.0f, 1.0f), glm::vec3(-400.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::scale(view, glm::vec3(0.022f, 0.0199f, 0.0f));
	}

	else if (cameraLocked)
	{
		view = glm::lookAt(
			glm::vec3(player->position.x - Window::getWinWidth() / 2 + player->size.x,
			player->position.y - Window::getWinHeight() / 2 + player->size.y, 1.0f),
			glm::vec3(player->position.x - Window::getWinWidth() / 2 + player->size.x,
			player->position.y - Window::getWinHeight() / 2 + player->size.y, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}

	cameraPosition = glm::vec2(player->position.x - Window::getWinWidth() / 2 + player->size.x,
		player->position.y - Window::getWinHeight() / 2 + player->size.y);

	ResourceManager::getShader("shader").use();
	ResourceManager::getShader("shader").setMatrix4("view", view);

	ResourceManager::getShader("lightShader").use();
	ResourceManager::getShader("lightShader").setMatrix4("view", view);
}
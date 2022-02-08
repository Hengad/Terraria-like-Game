
#include "engine\game\Game.h"

Game* App;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main()
{
	GLFWwindow* window;
	App = new Game();

	if (!glfwInit())
		std::cout << "Could not initialize GLFW." << std::endl;

	window = glfwCreateWindow(App->getWinWidth(), App->getWinHeight(), "2D Game Project", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//unsigned char cursorPixels[16 * 16 * 4];
	//memset(cursorPixels, 0xff, sizeof(cursorPixels));

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
		std::cout << "Could not initialize GLEW." << std::endl;

	float timer = 0.0f, timerEnd = 0.0f, timerBegin = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float currentFrame = (float)glfwGetTime();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	App->init();

	GLFWimage cursorImage;
	cursorImage.width = 24;
	cursorImage.height = 24;
	cursorImage.pixels = ResourceManager::getImage("cursor");
	
	GLFWcursor* cursor = glfwCreateCursor(&cursorImage, 0, 0);
	glfwSetCursor(window, cursor);

	while (!glfwWindowShouldClose(window))
	{
		currentFrame = (float)glfwGetTime();
		timerEnd = (float)glfwGetTime();


		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		timer += timerEnd - timerBegin;
		timerBegin = timerEnd;

		if (timer > 1.0)
		{
			std::cout << "FPS: " << 1.0 / deltaTime << std::endl;
			timer = 0.0;
		}

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		App->processInput();
		App->update(deltaTime);

		App->render(deltaTime);
		//App->renderer.finishRendering();

		glfwSwapBuffers(window);

		if (App->stateManager.gameShouldClose)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			App->keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			App->keys[key] = GL_FALSE;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	App->cursorPos.x = xpos;
	App->cursorPos.y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		App->rightMousePressed = GL_TRUE;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		App->rightMousePressed = GL_FALSE;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		App->leftMousePressed = GL_TRUE;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		App->leftMousePressed = GL_FALSE;
}
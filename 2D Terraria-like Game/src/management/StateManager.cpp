#include "StateManager.h"

StateManager::StateManager()
{
	gameState.push(State::MENU);
	gameShouldClose = false;
}

void StateManager::push()
{
	if(gameState.top() == State::MENU)
		gameState.push(State::GAME);
	else if (gameState.top() == State::GAME)
		gameState.push(State::PAUSE);

	if (gameState.top() == State::MENU)
		std::cout << "MENU" << std::endl;
	else if (gameState.top() == State::GAME)
		std::cout << "GAME" << std::endl;
	else if (gameState.top() == State::PAUSE)
		std::cout << "PAUSE" << std::endl;
}

void StateManager::pop()
{
	if (gameState.top() != State::MENU)
		gameState.pop();
	else
		gameShouldClose = true;
	if (gameState.top() == State::MENU)
		std::cout << "MENU" << std::endl;
	else if (gameState.top() == State::GAME)
		std::cout << "GAME" << std::endl;
	else if (gameState.top() == State::PAUSE)
		std::cout << "PAUSE" << std::endl;
}

State StateManager::getGameState()
{
	return gameState.top();
}

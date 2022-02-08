#pragma once

#include <iostream>
#include <stack>

enum class State { MENU, GAME, PAUSE };

class StateManager
{
private:
	std::stack<State> gameState;
public:
	StateManager();

	bool gameShouldClose;

	void push();
	void pop();

	State getGameState();
};
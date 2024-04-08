#ifndef GAME_H
#define GAME_H

#include <vector>

class Game
{
	//enum to represent the current Game Phase
	enum GamePhase { ORBITING, LANDING };

public:
	Game();

private:
	int balance, cargoValue, quota;
	MoonManager moonManager;
	ItemManager itemManager;
	GamePhase gamePhase;
	std::Vector<Employee*> aliveEmployees;

	void newGame();

	

}

#endif
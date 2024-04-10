#ifndef GAME_H
#define GAME_H

#include <vector>
#include "MoonManager.h"
#include "ItemManager.h"
#include "Employee.h"

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
	std::vector<Employee*> aliveEmployees;

	void newGame();



};

#endif
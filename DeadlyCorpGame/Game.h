#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include "MoonManager.h"
#include "ItemManager.h"
#include "Employee.h"
#include "AbstractMoon.h"
#include "CorporationMoon.h"
#include "GenericMoon.h"


class Game
{
	//enum to represent the current Game Phase
	enum GamePhase { ORBITING, LANDING };

public:
	Game();

	//initialising new game
	void newGame();
	
	/// <summary>
	/// Initialises the moons for the game
	/// </summary>
	bool initialiseMoons();//create new moons
	
	/// <summary>
	/// Initialises the items for the game
	/// </summary>
	bool initialiseItems();//create new items

	//manager game cycle - 4 day loops
	void gameCycle();
	//read, parse dispatch commands


private:
	int balance, cargoValue, quota;
	int dayCount;
	MoonManager moonManager;
	ItemManager itemManager;
	std::weak_ptr<AbstractMoon> currentMoon;
	GamePhase gamePhase;
	std::vector<Employee*> aliveEmployees;
};

#endif
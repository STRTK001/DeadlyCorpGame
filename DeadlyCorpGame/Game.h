#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <format>

#include "MoonManager.h"
#include "ItemManager.h"
#include "AbstractMoon.h"
#include "SellableMoon.h"
#include "SendableMoon.h"
#include "util.h"
#include "Logger.h"


class Game
{
	//enum to represent the current Game Phase
	enum GamePhase { ORBITING, LANDING };
	enum OptionMode {MAIN,MOONS};

public:
	Game();

	//initialising new game
	void play();
	
	/// <summary>
	/// Initialises the moons for the game
	/// </summary>
	bool initialiseMoons();//create new moons
	
	/// <summary>
	/// Initialises the items for the game
	/// </summary>
	bool initialiseItems();//create new items

	//read, parse dispatch commands


private:
	int balance, cargoValue, quota;
	int dayCount;
	MoonManager moonManager;
	ItemManager itemManager;
	std::weak_ptr<AbstractMoon> currentMoon;
	GamePhase gamePhase;
	int employeeCount;

	//brute forcing a delegate into c++
	//this is a delegate to change the current mode based on the user input
	std::unique_ptr<void(Game::*)()> currentMode;

	void simulation();

	void displayTitle();


	void displayStats();

	void displayOrbitInfo();

	void parseInput(std::string& line, std::vector<std::string>& args);

	void processCommand(std::string& line, std::vector<std::string>& args);

	// --- Mode methods ---

	void orbitMode();
	void landMode();
	void sendMode();
	void sellMode();
	void moonMode();

};

#endif
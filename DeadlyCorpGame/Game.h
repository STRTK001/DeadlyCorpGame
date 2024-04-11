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
	int balance, cargoValue, initalQuota, currentQuota;
	int dayCount, deadline;
	MoonManager moonManager;
	ItemManager itemManager;
	std::weak_ptr<AbstractMoon> currentMoon;
	GamePhase gamePhase;
	int employeeCount;

	bool isPlaying;

	//brute forcing a delegate into c++
	//this is a delegate to change the current mode based on the user input
	std::unique_ptr<void(Game::*)(std::string& line,std::vector<std::string>& args)> currentMode;

	void simulation();

	void checkDeadline();

	void displayTitle();

	void displayGameOver();
	
	void displaySuccess();

	void displayStats();

	void displayOrbitInfo();

	void getInput(std::string& line, std::vector<std::string>& args);

	void parseInput(std::string& line, std::vector<std::string>& args);

	void processCommand(std::string& line, std::vector<std::string>& args);

	// --- Mode methods ---

	void orbitMode(std::string& line, std::vector<std::string>& args);
	void landMode(std::string& line, std::vector<std::string>& args); //can send or sell	

};

#endif
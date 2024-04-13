#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <format>
#include <random>

#include "MoonManager.h"
#include "ItemManager.h"
#include "AbstractMoon.h"
#include "SellableMoon.h"
#include "SendableMoon.h"
#include "PremiumMoon.h"
#include "util.h"
#include "Logger.h"
#include "MoonWeather.h"

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

class Game
{
	/// <summary>
	/// Enum for managing the state of the game.
	/// </summary>
	enum GamePhase { ORBITING, LANDING };

public:
	Game();

	/// <summary>
	/// starts a new game
	/// </summary>
	void play();
	
	/// <summary>
	/// Initialises the moons for the game
	/// </summary>
	bool initialiseMoons();//create new moons
	
	/// <summary>
	/// Initialises the items for the game
	/// </summary>
	bool initialiseItems();//create new items

	/// <summary>
	/// getter for the weak_ptr that points at the current moon.
	/// </summary>
	std::shared_ptr<AbstractMoon> getCurrentMoon();

	/// <summary>
	/// sets the currentMoon to target moon
	/// </summary>
	void setCurrentMoon(std::shared_ptr<AbstractMoon>& targetMoon);

	/// <summary>
	/// getter for the balance
	/// </summary>
	int& getBalance();

	/// <summary>
	/// getter for the current quota effort
	/// </summary>
	/// <returns></returns>
	int& getCurrentQuotaEffort();
	
	/// <summary>
	/// getter for the current cargo value
	/// </summary>
	int& getCargoValue();

	///<summary>
	/// getter for the current number of alive employees
	///<summary>
	int& getAliveEmployees();

	/// <summary>
	/// getter for the initial quota
	/// </summary>
	int& getInitialQuota();

	/// <summary>
	/// getter for the random number generator
	/// </summary>
	std::mt19937& getRandomGenerator() ;

	///<summary>
	/// calculates the simulation parameters of the current bought items
	///<summary>
	void calculateSimulationParameters
	(
		float& scrapValueMutli, float& explorerSurvivalChanceMulti,
		float& operatorSurvivalChanceMulti, float& explorerSaveChance,
		float& lootRecoveryMulti
	);


private:

	/// <summary>
	/// random number generator
	/// </summary>
	std::mt19937 _randomGenerator;

	/// <summary>
	/// balance -> the current balance
	/// cargoValue -> the current cargo value
	/// initialQuota -> the initital quota to meet
	/// currentQuotaEffort -> the current effort towards the initial quota
	/// </summary>
	int _balance, 
		_cargoValue, 
		_initialQuota, 
		_currentQuotaEffort;

	/// <summary>
	/// dayCount -> the number of days passed.
	/// deadline -> the number of days until quota needs to be reached
	/// </summary>
	int 
		_dayCount, 
		_deadline;

	/// <summary>
	/// the number of alive employees
	/// </summary>
	int _aliveEmployees;

	/// <summary>
	/// the manager for moons
	/// </summary>
	MoonManager _moonManager;

	/// <summary>
	/// the manager for items
	/// </summary>
	ItemManager _itemManager;
	
	/// <summary>
	/// the weak ptr for pointing at the current moon
	/// </summary>
	std::weak_ptr<AbstractMoon> _currentMoon;

	/// <summary>
	/// the current state of the game either ORBITING or LANDING
	/// </summary>
	GamePhase _gamePhase;

	/// <summary>
	/// bool for checking if the game is still active
	/// </summary>
	bool _isPlaying;
	
	/// <summary>
	/// a method pointer (delegate) that points at the method for the current mode that the game is in.
	/// 
	/// This was my attempt to brute force a delegate in c++. I made this as a way of potentially extending the commands
	/// that a user could do but then after making landMode() and OrbitMode(); I realised there was no point having a 
	/// separate method for each command so I stubbornly worked the game around using those two methods using this delegate
	/// to switch behaviours.
	/// </summary>
	std::unique_ptr<void(Game::*)(std::string& line,std::vector<std::string>& args)> _currentMode;

	/// <summary>
	/// checks if the player has meet the quota by the deadline
	/// </summary>
	void checkDeadline();

	/// <summary>
	/// displays the game title
	/// </summary>
	void displayTitle();

	/// <summary>
	/// displays the game over msg
	/// </summary>
	void displayGameOver();
	
	/// <summary>
	/// displays the quota meet msg
	/// </summary>
	void displaySuccess();
	
	/// <summary>
	/// displays the cargo value, balance and quota
	/// </summary>
	void displayStats();

	/// <summary>
	/// displays the orbit info
	/// </summary>
	void displayOrbitInfo();

	/// <summary>
	/// captures the users input
	/// </summary>
	/// <param name="line">The command</param>
	/// <param name="args">The arguments</param>
	void getInput(std::string& line, std::vector<std::string>& args);

	/// <summary>
	/// parses the input and splits the line creating a command and multiple args
	/// </summary>
	void parseInput(std::string& line, std::vector<std::string>& args);

	/// <summary>
	/// processes the command and distributes it to the responsible manager
	/// </summary>
	void processCommand(std::string& line, std::vector<std::string>& args);
	
	/// <summary>
	/// runs the behaviour for being in orbit mode
	/// </summary>
	void orbitMode(std::string& line, std::vector<std::string>& args);

	/// <summary>
	/// runs the behaviour for being in orbit mode
	/// </summary>
	void landMode(std::string& line, std::vector<std::string>& args);
};

#endif
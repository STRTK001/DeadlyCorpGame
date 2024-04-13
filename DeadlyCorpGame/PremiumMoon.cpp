#include "PremiumMoon.h"
#include "Game.h"

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

bool PremiumMoon::onNavigate(Game& game)
{
	//print notice msg
	std::cout << std::format("The cost of going to {} is ${}\n", _name,_price);
	//print purchase query
	std::cout << std::format("You have ${}. Confirm destination? [Yes/No]\n",game.getBalance());
	//the specs dont have it but lets put the test cursor in
	std::cout << "> ";
	//capture user input
	std::string input;
	std::getline(std::cin, input);
	//apply new line
	std::cout << std::endl;
	//lower input
	util::lower(input);
	//parse input
	if (input == "yes")
	{
		//not in specs but check if they can afford the purchase
		if (game.getBalance() - _price < 0)
		{
			//print poor msg
			std::cout << std::format("You cannot afford to route to {}.\n", _name);
			return false;
		}
		//make transaction
		game.getBalance() -= _price;
		//print balance
		std::cout << std::format("New Balance: ${}\n", game.getBalance());
		return true;
	}
	//cancel trip
	std::cout << "Trip cancelled.\n";
	return false;
}

void PremiumMoon::sell(Game& game, int amount)
{
	std::cout << "This command is not available on this moon.\n\n";
}

void PremiumMoon::send(Game& game, int count)
{
	//init the explorer and operater vars
	int explorers = count;
	int operators = game.getAliveEmployees() - explorers;

	//simulation param declarations
	float
		scrapValueMuliplier = 1,
		explorerSurvialChanceMultiplier = 1,
		operatorSurvivalChanceMultiplier = 1,
		explorerSaveChance = 0,
		lootRecoveryMultiplier = 0.5;

	//apply weather calculations
	switch (_weather)
	{
	case MoonWeather::FLOODED:
		explorerSurvialChanceMultiplier *= 0.7;
		break;
	case MoonWeather::STORMY:
		scrapValueMuliplier *= 0.75;
		break;
	case MoonWeather::ECLIPSED:
		explorerSurvialChanceMultiplier *= 0.9;
		operatorSurvivalChanceMultiplier *= 0.7;
		break;
	default:
		break;
	}
	//apply item calculations
	game.calculateSimulationParameters
	(
		scrapValueMuliplier, explorerSurvialChanceMultiplier,
		operatorSurvivalChanceMultiplier, explorerSaveChance,
		lootRecoveryMultiplier
	);
	//final survival chances
	float explorerSurvivalChance = _baseSurvivalChance * explorerSurvialChanceMultiplier;
	float operatorSurvivalChance = 1.0 * operatorSurvivalChanceMultiplier;
	//
	int totalRevenue = 0;
	//
	int deadExplorers = 0;
	int deadOperators = 0;

	std::uniform_real_distribution<float> survivalRandom(0, 1);

	//explorer survival calculations
	for (int explorer = 0; explorer < explorers; explorer++)
	{
		//random scrap value beteen the min and max scrap values * the multiplier
		std::uniform_real_distribution<float> revenueValue
		(
			_minimumScrapValue * scrapValueMuliplier,
			_maximumScrapValue * scrapValueMuliplier
		);
		float revenue = revenueValue(game.getRandomGenerator());
		//explorer survival calculations
		float survivalValue = survivalRandom(game.getRandomGenerator());
		if (survivalValue < explorerSurvivalChance)
		{
			//employee survived
			totalRevenue += revenue;
		}
		else if (survivalValue >= explorerSaveChance)
		{
			//employee died
			deadExplorers += 1;
			totalRevenue += revenue * lootRecoveryMultiplier;
		}
	}
	//operator survival calculations
	for (int operatorI = 0; operatorI < operators; operatorI++)
	{
		//get random value for operator survival
		float survivalValue = survivalRandom(game.getRandomGenerator());
		if (survivalValue >= operatorSurvivalChance)
		{
			//operater died
			deadOperators += 1;
		}
	}

	//calculate the death toll of both explorers and operators
	explorers -= deadExplorers;
	operators -= deadOperators;

	//substract the dead from the living
	game.getAliveEmployees() -= deadExplorers;
	game.getAliveEmployees() -= deadOperators;

	//print how many explorers made it back 
	if (explorers > 0)
	{
		std::cout
			<< std::format("{} employees made it back to the ship, bringing ${} worth of scrap. {} died\n",
				explorers, totalRevenue, deadExplorers);
	}
	else
	{
		std::cout
			<< std::format("None of the employees managed to make it back. {} employees left\n",
				game.getAliveEmployees());
	}
	if (deadOperators > 0)
	{
		std::cout << std::format("In the meantime, {} employees left on the ship died.\n", deadOperators);
	}
	//line break
	std::cout << std::endl;

	//if all employees are deceased
	if (game.getAliveEmployees() < 1)
	{
		std::cout
			<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
			<< "All the employees died and the scrap is lost.\n"
			<< "Autopilot will now bring the ship back to orbit.\n"
			<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
		game.getCargoValue() = 0;
		return;
	}

	//some, if not all, made it back so give them their cargo
	game.getCargoValue() += totalRevenue;
}

void PremiumMoon::print()
{
	std::cout
		<< "Type SEND followed by the number of employees you wish to send "
		<< "inside the facility. All the other employees will stay on the ship. "
		<< "Type LEAVE to leave the planet.\n\n";
}

void PremiumMoon::onDayBegin(Game& game)
{
	//get the random int
	std::uniform_int_distribution<int> intDistribution(0, 3);
	int randomInt = intDistribution(game.getRandomGenerator());
	//set the weather
	_weather = static_cast<MoonWeather>(randomInt);
	Logger::logDebug(std::format("Random weather on {} is {}.", _name, randomInt));
}
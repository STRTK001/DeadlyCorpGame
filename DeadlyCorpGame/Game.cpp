#include "Game.h"

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

Game::Game()
{
	Logger::logDebug("initalising Game!");

	Logger::logDebug("initalising balance!");
	//set the balance
	_balance = 5000;

	Logger::logDebug("initalising cargovalue!");
	//we dont start with cargo
	_cargoValue = 0;

	Logger::logDebug("initalising quotas!");
	//the first quota starts at 150
	_initialQuota = 150;
	//set the current quota
	_currentQuotaEffort = 0;

	Logger::logDebug("initalising day count!");
	//set day count
	_dayCount = 1;

	//set deadline
	Logger::logDebug("intiallising deadline");
	_deadline = 4;

	Logger::logDebug("initalising items!");
	//add items
	bool itemsInit = initialiseItems();

	Logger::logDebug("initalising Moons!");
	//add moons
	bool moonsInit = initialiseMoons();

	Logger::logDebug("initalising current moon!");
	//set current moon to corp
	_currentMoon = _moonManager.getMoon("corporation");
	if (!_currentMoon.expired())
	{
		Logger::logDebug((*_currentMoon.lock()).name());
	}
	else
	{
		Logger::logError("couldnt set the current moon to corp");
	}

	Logger::logDebug("initalising game phase!");
	//set game phase to orbiting corp
	_gamePhase = GamePhase::ORBITING;

	Logger::logDebug("Initalising currentMode delegate");
		
	_currentMode = std::make_unique<void(Game::*)
		(std::string & line, std::vector<std::string>&args)>(&Game::orbitMode);

	Logger::logDebug("Initalising isPlaying");
	_isPlaying = true;

	Logger::logDebug("initialise rng");
	_randomGenerator.seed(std::random_device{}());

	Logger::logDebug("Completed game intialisation!");
}


bool Game::initialiseMoons()
{
	// -- add normal moons
	//create corporation moon
	Logger::logDebug("__creating corporation moon__");
	std::shared_ptr<AbstractMoon> corporation = std::make_shared<SellableMoon>(SellableMoon("Corporation", 0, 0, 0, 1));
	if (!_moonManager.addMoon(corporation))
	{
		return false;
	}
	//create prototyping moon
	Logger::logDebug("__creating prototyping moon__");
	std::shared_ptr<AbstractMoon> prototyping = std::make_shared<SendableMoon>(SendableMoon("Prototyping", 0, 3, 30, 0.5));
	if (!_moonManager.addMoon(prototyping))
	{
		return false;
	}
	//create insurance moon
	Logger::logDebug("__creating insurance moon__");
	std::shared_ptr<AbstractMoon> insurance = std::make_shared<SendableMoon>(SendableMoon("Insurance", 0, 5, 50, 0.45));
	if (!_moonManager.addMoon(insurance))
	{
		return false;
	}
	//create pledge moon
	Logger::logDebug("__creating pledge moon__");
	std::shared_ptr<AbstractMoon> pledge = std::make_shared<SendableMoon>(SendableMoon("Pledge", 0, 30, 50, 0.4));
	if (!_moonManager.addMoon(pledge))
	{
		return false;
	}
	//create defence moon
	Logger::logDebug("__creating defence moon__");
	std::shared_ptr<AbstractMoon> defence = std::make_shared<SendableMoon>(SendableMoon("Defence", 0, 10, 70,0.35));
	if (!_moonManager.addMoon(defence))
	{
		return false;
	}
	//--- add premium moons
	//create april moon
	Logger::logDebug("__creating april moon__");
	std::shared_ptr<AbstractMoon> april = std::make_shared<PremiumMoon>(PremiumMoon("April", 550, 20, 120, 0.3));
	if (!_moonManager.addMoon(april))
	{
		return false;
	}
	//create tore moon
	Logger::logDebug("__creating tore moon__");
	std::shared_ptr<AbstractMoon> tore = std::make_shared<PremiumMoon>(PremiumMoon("Tore", 700, 100, 130, 0.25));
	if (!_moonManager.addMoon(tore))
	{
		return false;
	}
	//create hyperion moon
	Logger::logDebug("__creating hyperion moon__");
	std::shared_ptr<AbstractMoon> hyperion = std::make_shared<PremiumMoon>(PremiumMoon("Hyperion", 900, 100, 150, 0.2));
	if (!_moonManager.addMoon(hyperion))
	{
		return false;
	}

	return true;
}

bool Game::initialiseItems()
{
	//create flashlight
	Logger::logDebug("__creating flashlight item__");
	std::shared_ptr<Item> flashlight = std::make_shared<Item>("Flashlight", 60, 1, 1.05, 1, 1, 1);
	if(!_itemManager.addItem(flashlight))
	{
		return false;
	}
	//create Shovel
	Logger::logDebug("__creating Shovel item__");
	std::shared_ptr<Item> shovel = std::make_shared<Item>("Shovel", 100, 1, 1.05, 1, 1, 1);
	if(!_itemManager.addItem(shovel))
	{
		return false;
	}
	//create pro-flashlight
	Logger::logDebug("__creating pro-flashlight item__");
	std::shared_ptr<Item> pro_flashlight = std::make_shared<Item>("Pro-Flashlight", 200, 1, 1.1, 1, 1, 1);
	if(!_itemManager.addItem(pro_flashlight))
	{
		return false;
	}
	//create teleporter
	Logger::logDebug("__creating teleporter item__");
	std::shared_ptr<Item> teleporter = std::make_shared<Item>("Teleporter", 300, 1, 1, 1, 0.33, 1);
	if(!_itemManager.addItem(teleporter))
	{
		return false;
	}
	//create inverse-teleporter
	Logger::logDebug("__creating inverse-teleporter item__");
	std::shared_ptr<Item> inverse_teleporter = std::make_shared<Item>("Inverse-Teleporter", 400, 1.1, 0.8, 1 , 1, 1);
	if(!_itemManager.addItem(inverse_teleporter))
	{
		return false;
	}
	//create backpack
	Logger::logDebug("__creating backpack item__");
	std::shared_ptr<Item> backpack = std::make_shared<Item>("Backpack", 500, 1, 1, 1, 1, 1.25);
	if(!_itemManager.addItem(backpack))
	{
		return false;
	}
	//create hydraulics mk2
	Logger::logDebug("__creating hydraulics mk2 item__");
	std::shared_ptr<Item> hydraulics_mk2 = std::make_shared<Item>("Hydraulics-Mk2", 1000, 1, 1, 1.25, 1, 1);
	if (!_itemManager.addItem(hydraulics_mk2))
	{
		return false;
	}
		
	
	return true;
}


void Game::play()
{
	//display title
	displayTitle();
	//init input 
	std::string line;
	//and args
	std::vector<std::string> args;

	//gameplay loop
	do
	{
		//if we have a valid delegate
		if (_currentMode)
		{
			//execute the delegate by deferencing it and calling its method
			(this->*(*_currentMode))(line, args);
		}
		else
		{
			Logger::logError("panic as we have no menu right now!");
		}
	}while(_isPlaying);
	
}

void Game::getInput(std::string& line, std::vector<std::string>& args)
{
	//print little arrow thing to console
	std::cout << "> ";
	//wait for input
	std::getline(std::cin, line);
	//parse input
	parseInput(line, args);
	//create new lines
	std::cout << "\n";
}

void Game::parseInput(std::string& line, std::vector<std::string>& args)
{
	//lower all characters
	util::lower(line);
	//spilt the line into command and arguments
	util::splitArguments(line, args);
}

void Game::processCommand(std::string& line, std::vector<std::string>& args)
{
	//proccess the command
	if (line == "land")
	{
		//if not in orbit phase
		if (_gamePhase != GamePhase::ORBITING)
		{
			//cmd invalid
			if (!_currentMoon.expired())
			{
				std::cout << std::format("Already landed on {}\n\n", (*_currentMoon.lock()).name());
			}
			else
			{
				std::cout << "Already landed on NONE\n\n";
			}
			return;
		}
		//set the phase to landing
		_gamePhase = GamePhase::LANDING;
		//change mode to land mode
		_currentMode = std::make_unique<void(Game::*)
			(std::string & line, std::vector<std::string>&args)>(&Game::landMode);
		return;
	}
	else if (line == "leave")
	{
		//check if not in landing phase
		if (_gamePhase != GamePhase::LANDING)
		{
			//cmd is invalid
			std::cout << "This command is not available at this time.\n\n";
			return;
		}
		//set the phase to orbiting
		_gamePhase = GamePhase::ORBITING;
		//change mode to orbit mode
		_currentMode = std::make_unique<void(Game::*)
			(std::string & line, std::vector<std::string>&args)>(&Game::orbitMode);

	}
	else if (line == "exit")
	{
		_isPlaying = false;
	}
	else if (line == "inventory")
	{
		//call inventory method in the item manager
		_itemManager.inventory();
		//print balance and quota
		std::cout << std::format("Balance: ${} (quota is ${})\n",_balance, _initialQuota);
		//print cargo val
		std::cout << std::format("Cargo value: ${}\n\n", _cargoValue);
	}
	else if (line == "store")
	{
		//call store method in the item manager
		_itemManager.store();
		std::cout << std::format("Balance: ${}\n\n", _balance);
	}
	else if (line == "buy")
	{
		if (args.size() < 1)
		{
			std::cout << "Bad command; the syntax is: \"buy itemName\"\n\n";
			return;
		}
		//call purchase method in item manager
		_itemManager.buy(*this, args[0]);
	}
	else if (line == "route")
	{
		//check if we're in orbit
		if (_gamePhase != GamePhase::ORBITING)
		{
			//cmd invalid
			std::cout << "This command is not available at this time.\n\n";
			return;
		}

		//check if args[0] ie moonName exists
		if (args.size() < 1)
		{
			std::cout << "Bad command; the syntax is: \"route moonName\"\n\n";
			return;
		}
		//call route method in moon manager
		_moonManager.route(*this,args[0]);
	}
	else if (line == "moons")
	{
		//call moons method in moon manager
		_moonManager.moons();
		//print balance
		std::cout << std::format("Balance: ${}\n\n",_balance);
	}
	else if (line == "send")
	{
		//check if we are landed
		if (_gamePhase != GamePhase::LANDING)
		{
			std::cout << "This command is not available at this time.\n\n";;
			return;
		}
		//check that the first arg exists 
		if (args.size() < 1)
		{
			//cmd invalid
			std::cout << "Bad command; the syntax is: \"send numberOfEmployees\".\n\n";
			return;
		}
		//check if the first arg is an int
		int arg = util::parsePositiveInt(args[0]);
		if (arg == -1)
		{
			//arg invalid
			std::cout << std::format("Invalid employee count \"{}\".\n\n",args[0]);
			return;
		}
		//check if the arg is > than the sum of alive employees
		if (arg > _aliveEmployees)
		{
			//arg invalid
			std::cout << std::format("Only {} employees are left.\n\n", _aliveEmployees);
			return;
		}
		//call the send method of the current moon
		_currentMoon.lock().get()->send(*this, arg);
	}
	else if (line == "sell")
	{
		//check if we are landed
		if (_gamePhase != GamePhase::LANDING)
		{
			std::cout << "This command is not available at this time.\n\n";;
			return;
		}
		//check if there arent any args
		if (args.size() < 1 || args[0] == "")
		{
			_currentMoon.lock().get()->sell(*this, -1);
			return;
		}
		//check if first arg is an int
		int arg = util::parsePositiveInt(args[0]);
		if (arg == -1)
		{
			//arg invalid
			std::cout << std::format("Invalid amount \"{}\".\n\n", args[0]);
			return;
		}
		//call the send method of the current moon
		_currentMoon.lock().get()->sell(*this, arg);
		//this will enable the user to sell cargo.
	}
	else
	{
		std::cout << "Unknown command.\n\n";
	}
	
}

void Game::checkDeadline()
{
	//check if we have approached the deadline
	if (_dayCount < _deadline+1)
	{
		return;
	}
	//check if we have met the quota at the deadline
	if (_currentQuotaEffort < _initialQuota)
	{
		displayGameOver();
		_isPlaying = false;
		return;
	}
	_deadline += 4;
	_initialQuota += _initialQuota * 0.50;
	_currentQuotaEffort = 0;
	displaySuccess();
}

void Game::displayGameOver()
{
	std::cout
		<< "-------------------------------------\n"
		<< ">>>>>>>>>>>>> GAME OVER <<<<<<<<<<<<<\n"
		<< "-------------------------------------\n\n"
		<< "You did not meet quota in time, and your employees have been fired.\n"
		<< std::format("You kept them alive for {} days.\n\n",_dayCount-1);
}

void Game::displaySuccess()
{
	std::cout
		<< "-------------------------------------\n"
		<< "CONGRATULATIONS ON MAKING QUOTA!\n"
		<< std::format("New quota : ${}\n", _initialQuota)
		<< "-------------------------------------\n\n";
}

void Game::displayTitle()
{
	//print ascii art
	std::cout
		<< "    ___               _ _           ___                 \n" <<
		"   /   \\___  __ _  __| | |_   _    / __\\___  _ __ _ __  \n" <<
		"  / /\\ / _ \\/ _` |/ _` | | | | |  / /  / _ \\| '__| '_ \\ \n" <<
		" / /_//  __/ (_| | (_| | | |_| | / /__| (_) | |  | |_) |\n" <<
		"/___,' \\___|\\__,_|\\__,_|_|\\__, | \\____/\\___/|_|  | .__/ \n" <<
		"                          |___/                  |_|    \n\n";
	//print welcome text
	std::cout << "Welcome!\n" << "We trust you will be a great asset to the corporation!\n\n";
}


void Game::displayOrbitInfo()
{
	//check if we have a current moon or not
	if (!_currentMoon.expired())
	{
		std::cout << std::format("Currently orbiting: {}\n\n", (*_currentMoon.lock()).name());
	}
	else
	{
		std::cout << "Currently orbiting: NONE!!\n\n";
	}
		
}

void Game::displayStats()
{
	std::cout
		<< std::format("Current cargo value: ${}\n", _cargoValue)
		<< std::format("Current balance: ${}\n", _balance)
		<< std::format("Current quota: ${} ({} days left to meet quota)\n",
			_initialQuota, _deadline - _dayCount);
}


void Game::orbitMode(std::string& line, std::vector<std::string>& args)
{
	//display day header
	std::cout
		<< std::format("============= DAY {} =============\n", _dayCount);
	//display stats
	displayStats();
	//display orbit info
	displayOrbitInfo();
	//display options
	std::cout
		<< ">MOONS\nTo see the list of moons the autopilot can route to.\n\n"
		<< ">STORE\nTo see the company store's selection of useful items.\n\n"
		<< ">INVENTORY\nTo see the list of items you've already bought.\n\n";

	//warn player that the deadline is today
	if (_dayCount == _deadline)
	{
		std::cout
			<< "NOTE: 0 days left to meet quota. Type \"route corporation\""
			<< " to go to the corp's moon and sell the scrap you collected for cash.\n\n";
	}

	//its a new day when this is called
	_moonManager.onDaybegin(*this);
	//get user input
	do
	{
		getInput(line, args);
		processCommand(line, args);
	} while (_gamePhase == GamePhase::ORBITING);
}

void Game::landMode(std::string& line, std::vector<std::string>& args)
{
	//display welcome notice
	if (!_currentMoon.expired())
	{
		std::cout << std::format("WELCOME to {}!\n\n", (*_currentMoon.lock()).name());
	}
	else
	{
		std::cout << "WELCOME to NONE!!\n\n";
	}
	//display stats
	displayStats();
	//reset the number of employees
	_aliveEmployees = 4;
	//display number of employees
	std::cout << std::format("Number of employees: {}\n", _aliveEmployees);
	
	//display weather
	_currentMoon.lock().get()->displayWeather();

	//probably shouldnt go here but get moon behaviour notes (SEND/SELL)
	//display the behaviour notes
	_currentMoon.lock().get()->print();

	//get user input
	do
	{
		getInput(line, args);
		processCommand(line, args);
	} while (_gamePhase == GamePhase::LANDING && _aliveEmployees > 0);
	
	//if all employees are dead
	if (_aliveEmployees < 1)
	{
		line = "leave";
		processCommand(line, args);
	}

	//increment day as we are leaving
	_dayCount++;
	checkDeadline();
}

int& Game::getBalance() 
{
	return _balance;
}

int& Game::getCurrentQuotaEffort() 
{
	return _currentQuotaEffort;
}

int& Game::getCargoValue() 
{
	return _cargoValue;
}

int& Game::getInitialQuota() 
{
	return _initialQuota;
}

void Game::setCurrentMoon(std::shared_ptr<AbstractMoon>& targetMoon)
{
	_currentMoon = targetMoon;
}

std::shared_ptr<AbstractMoon> Game::getCurrentMoon()
{
	return _currentMoon.lock();
}

std::mt19937& Game::getRandomGenerator() 
{
	return _randomGenerator;
}

int& Game::getAliveEmployees()
{
	return _aliveEmployees;
}

void Game::calculateSimulationParameters
(
	float& scrapValueMutli, float& explorerSurvivalChanceMulti,
	float& operatorSurvivalChanceMulti, float& explorerSaveChance,
	float& lootRecoveryMulti
)
{
	_itemManager.calculateSimulationParameters
	(
		scrapValueMutli, explorerSurvivalChanceMulti,
		operatorSurvivalChanceMulti, explorerSaveChance,
		lootRecoveryMulti
	);
}
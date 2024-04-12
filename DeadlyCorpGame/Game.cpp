#include "Game.h"


Game::Game()
{
	//log that we are creating game
	Logger::logDebug("initalising Game!");

	Logger::logDebug("initalising balance!");
	//set the balance
	balance = 5000;

	Logger::logDebug("initalising cargovalue!");
	//we dont start with cargo
	cargoValue = 220;

	Logger::logDebug("initalising quotas!");
	//the first quota starts at 150
	initialQuota = 150;
	//set the current quota
	currentQuotaEffort = 0;

	Logger::logDebug("initalising day count!");
	//set day count
	dayCount = 1;

	//set deadline
	Logger::logDebug("intiallising deadline");
	deadline = 4;

	Logger::logDebug("initalising items!");
	//add items
	bool itemsInit = initialiseItems();

	Logger::logDebug("initalising Moons!");
	//add moons
	bool moonsInit = initialiseMoons();

	Logger::logDebug("initalising current moon!");
	//set current moon to corp
	currentMoon = moonManager.getMoon("corporation");
	if (!currentMoon.expired())
		Logger::logDebug((*currentMoon.lock()).name());
	else
		Logger::logError("couldnt set the current moon to corp");

	Logger::logDebug("initalising game phase!");
	//set game phase to orbiting corp
	gamePhase = GamePhase::ORBITING;

	Logger::logDebug("Initalising currentMode delegate");
		
	currentMode = std::make_unique<void(Game::*)
		(std::string & line, std::vector<std::string>&args)>(&Game::orbitMode);

	Logger::logDebug("Initalising isPlaying");
	isPlaying = true;

	Logger::logDebug("Completed game intialisation!");
}


bool Game::initialiseMoons()
{
	// -- add normal moons
	//create corporation moon
	Logger::logDebug("__creating corporation moon__");
	std::shared_ptr<AbstractMoon> corporation = std::make_shared<SellableMoon>(SellableMoon("Corporation", 0));
	if (!moonManager.addMoon(corporation))
		return false;
	//create prototyping moon
	Logger::logDebug("__creating prototyping moon__");
	std::shared_ptr<AbstractMoon> prototyping = std::make_shared<SendableMoon>(SendableMoon("Prototyping", 0));
	if (!moonManager.addMoon(prototyping))
		return false;
	//create insurance moon
	Logger::logDebug("__creating insurance moon__");
	std::shared_ptr<AbstractMoon> insurance = std::make_shared<SendableMoon>(SendableMoon("Insurance", 0));
	if (!moonManager.addMoon(insurance))
		return false;
	//create pledge moon
	Logger::logDebug("__creating pledge moon__");
	std::shared_ptr<AbstractMoon> pledge = std::make_shared<SendableMoon>(SendableMoon("Pledge", 0));
	if (!moonManager.addMoon(pledge))
		return false;
	//create defence moon
	Logger::logDebug("__creating defence moon__");
	std::shared_ptr<AbstractMoon> defence = std::make_shared<SendableMoon>(SendableMoon("Defence", 0));
	if (!moonManager.addMoon(defence))
		return false;

	//--- add premium moons
	//create april moon
	Logger::logDebug("__creating april moon__");
	std::shared_ptr<AbstractMoon> april = std::make_shared<PremiumMoon>(PremiumMoon("April", 550));
	if (!moonManager.addMoon(april))
		return false;
	//create tore moon
	Logger::logDebug("__creating tore moon__");
	std::shared_ptr<AbstractMoon> tore = std::make_shared<PremiumMoon>(PremiumMoon("Tore", 700));
	if (!moonManager.addMoon(tore))
		return false;
	//create hyperion moon
	Logger::logDebug("__creating hyperion moon__");
	std::shared_ptr<AbstractMoon> hyperion = std::make_shared<PremiumMoon>(PremiumMoon("Hyperion", 900));
	if (!moonManager.addMoon(hyperion))
		return false;

	return true;
}

bool Game::initialiseItems()
{
	//create flashlight
	Logger::logDebug("__creating flashlight item__");
	std::shared_ptr<Item> flashlight = std::make_shared<Item>("Flashlight", 60);
	if(!itemManager.addItem(flashlight))
		return false;
	//create Shovel
	Logger::logDebug("__creating Shovel item__");
	std::shared_ptr<Item> shovel = std::make_shared<Item>("Shovel", 100);
	if(!itemManager.addItem(shovel))
		return false;
	//create pro-flashlight
	Logger::logDebug("__creating pro-flashlight item__");
	std::shared_ptr<Item> pro_flashlight = std::make_shared<Item>("Pro-Flashlight", 200);
	if(!itemManager.addItem(pro_flashlight))
		return false;
	//create teleporter
	Logger::logDebug("__creating teleporter item__");
	std::shared_ptr<Item> teleporter = std::make_shared<Item>("Teleporter", 300);
	if(!itemManager.addItem(teleporter))
		return false;
	//create inverse-teleporter
	Logger::logDebug("__creating inverse-teleporter item__");
	std::shared_ptr<Item> inverse_teleporter = std::make_shared<Item>("Inverse-Teleporter", 400);
	if(!itemManager.addItem(inverse_teleporter))
		return false;
	//create backpack
	Logger::logDebug("__creating backpack item__");
	std::shared_ptr<Item> backpack = std::make_shared<Item>("Backpack", 500);
	if(!itemManager.addItem(backpack))
		return false;
	//create hydraulics mk2
	Logger::logDebug("__creating hydraulics mk2 item__");
	std::shared_ptr<Item> hydraulics_mk2 = std::make_shared<Item>("Hydraulics-Mk2", 1000);
	if(!itemManager.addItem(hydraulics_mk2))
		return false;
	
	return true;
}


void Game::play()
{
	displayTitle();
	//gameplay loop
	
	//init input 
	std::string line;
	//and args
	std::vector<std::string> args;

	do
	{
		//if we have a valid delegate
		if (currentMode)
			//execute the delegate by deferencing it and calling its method
			(this->*(*currentMode))(line,args);
		else
			Logger::logError("panic as we have no menu right now!");
	}while(isPlaying);
	
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
		if (gamePhase != GamePhase::ORBITING)
		{
			//cmd invalid
			if (!currentMoon.expired())
				std::cout << std::format("Already landed on {}\n\n", (*currentMoon.lock()).name());
			else
				std::cout << "Already landed on NONE\n\n";
			return;
		}
		//set the phase to landing
		gamePhase = GamePhase::LANDING;
		//change mode to land mode
		currentMode = std::make_unique<void(Game::*)
			(std::string & line, std::vector<std::string>&args)>(&Game::landMode);
		return;
	}
	else if (line == "leave")
	{
		//check if not in landing phase
		if (gamePhase != GamePhase::LANDING)
		{
			//cmd is invalid
			std::cout << "This command is not available at this time.\n\n";
			return;
		}
		//set the phase to orbiting
		gamePhase = GamePhase::ORBITING;
		//change mode to orbit mode
		currentMode = std::make_unique<void(Game::*)
			(std::string & line, std::vector<std::string>&args)>(&Game::orbitMode);

	}
	else if (line == "exit")
	{
		isPlaying = false;
	}
	else if (line == "inventory")
	{
		//call inventory method in the item manager
		itemManager.inventory();
		//print balance and quota
		std::cout << std::format("Balance: ${} (quota is ${})\n",balance, initialQuota);
		//print cargo val
		std::cout << std::format("Cargo value: ${}\n\n", cargoValue);
	}
	else if (line == "store")
	{
		//call store method in the item manager
		itemManager.store();
		std::cout << std::format("Balance: ${}\n\n", balance);
	}
	else if (line == "buy")
	{
		if (args.size() < 1)
		{
			std::cout << "Bad command; the syntax is: \"buy itemName\"\n\n";
			return;
		}
		//call purchase method in item manager
		itemManager.buy(*this, args[0]);
	}
	else if (line == "route")
	{
		//check if we're in orbit
		if (gamePhase != GamePhase::ORBITING)
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
		moonManager.route(*this,args[0]);
	}
	else if (line == "moons")
	{
		//call moons method in moon manager
		moonManager.moons();
		//print balance
		std::cout << std::format("Balance: ${}\n\n",balance);
	}
	else if (line == "send")
	{
		//check if we are landed
		if (gamePhase != GamePhase::LANDING)
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
		//check if any args exist
		if (args.size() < 1)
		{
			//cmd invalid
			std::cout << "Bad command; the syntax is: \"send numberOfEmployees\"\n\n";
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
		//call the send method of the current moon
		currentMoon.lock().get()->send(*this, arg);
		//send will run the simulation

		std::cout << "---  sending kinda ---\n\n";
	}
	else if (line == "sell")
	{
		//check if we are landed
		if (gamePhase != GamePhase::LANDING)
		{
			std::cout << "This command is not available at this time.\n\n";;
			return;
		}
		//check if there arent any args
		if (args.size() < 1 || args[0] == "")
		{
			currentMoon.lock().get()->sell(*this, -1);
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
		currentMoon.lock().get()->sell(*this, arg);
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
	if (dayCount < deadline+1)
	{
		return;
	}
	//check if we have met the quota at the deadline
	if (currentQuotaEffort < initialQuota)
	{
		displayGameOver();
		isPlaying = false;
		return;
	}
	deadline += 4;
	initialQuota += initialQuota * 0.50;
	currentQuotaEffort = 0;
	displaySuccess();
}

void Game::displayGameOver()
{
	std::cout
		<< "-------------------------------------\n"
		<< ">>>>>>>>>>>>> GAME OVER <<<<<<<<<<<<<\n"
		<< "-------------------------------------\n\n"
		<< "You did not meet quota in time, and your employees have been fired.\n"
		<< std::format("You kept them alive for {} days.\n\n",dayCount-1);
}

void Game::displaySuccess()
{
	std::cout
		<< "-------------------------------------\n"
		<< "CONGRATULATIONS ON MAKING QUOTA!\n"
		<< std::format("New quota : ${}\n", initialQuota)
		<< "-------------------------------------\n\n";
}

void Game::simulation()
{

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
	if (!currentMoon.expired())
		std::cout << std::format("Currently orbiting: {}\n\n", (*currentMoon.lock()).name());
	else
		std::cout << "Currently orbiting: NONE!!\n\n";
}

void Game::displayStats()
{
	std::cout
		<< std::format("Current cargo value: ${}\n", cargoValue)
		<< std::format("Current balance: ${}\n", balance)
		<< std::format("Current quota: ${} ({} days left to meet quota)\n",
			initialQuota, deadline - dayCount);
}


void Game::orbitMode(std::string& line, std::vector<std::string>& args)
{
	//display day header
	std::cout
		<< std::format("============= DAY {} =============\n", dayCount);
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
	if (dayCount == deadline)
		std::cout 
			<< "NOTE: 0 days left to meet quota. Type \"route corporation\""
			<< " to go to the corp's moon and sell the scrap you collected for cash.\n\n";

	//get user input
	do
	{
		getInput(line, args);
		processCommand(line, args);
	} while (gamePhase == GamePhase::ORBITING);
}

void Game::landMode(std::string& line, std::vector<std::string>& args)
{
	//display welcome notice
	if (!currentMoon.expired())
		std::cout << std::format("WELCOME to {}!\n\n", (*currentMoon.lock()).name());
	else
		std::cout << "WELCOME to NONE!!\n\n";
	//display stats
	displayStats();
	//reset the number of employees
	employeeCount = 4;
	//display number of employees
	std::cout << std::format("Number of employees: {}\n\n", employeeCount);
	
	//do something with the weather 
	//display weather
	std::cout << "--- weather info goes here ---\n\n";
	
	//probably shouldnt go here but get moon behaviour notes (SEND/SELL)
	//display the behaviour notes
	currentMoon.lock().get()->print();

	//get user input
	do
	{
		getInput(line, args);
		processCommand(line, args);
	} while (gamePhase == GamePhase::LANDING);
	
	//increment day as we are leaving
	dayCount++;
	checkDeadline();
}

int& Game::getBalance() 
{
	return balance;
}

int& Game::getCurrentQuotaEffort() 
{
	return currentQuotaEffort;
}

int& Game::getCargoValue() 
{
	return cargoValue;
}

const int& Game::getInitialQuota() 
{
	return initialQuota;
}

void Game::setCurrentMoon(std::shared_ptr<AbstractMoon>& targetMoon)
{
	currentMoon = targetMoon;
}

std::shared_ptr<AbstractMoon> Game::getCurrentMoon()
{
	return currentMoon.lock();
}



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
	cargoValue = 0;

	Logger::logDebug("initalising quota!");
	//the first quota starts at 150
	quota = 150;

	Logger::logDebug("initalising day count!");
	//
	dayCount = 1;

	Logger::logDebug("initalising items!");
	//add items
	bool itemsInit = initialiseItems();

	Logger::logDebug("initalising Moons!");
	//add moons
	bool moonsInit = initialiseMoons();

	Logger::logDebug("initalising current moon!");
	//set current moon to corp
	currentMoon = moonManager.getMoon("Corporation");
	if (!currentMoon.expired())
		Logger::logDebug((*currentMoon.lock()).name());
	else
		Logger::logError("couldnt set the current moon to corp");

	Logger::logDebug("initalising game phase!");
	//set game phase to orbiting corp
	gamePhase = GamePhase::ORBITING;

	Logger::logDebug("Initalising currentMode delegate");
		
	currentMode = std::make_unique<void(Game::*)()>(&Game::orbitMode);

	Logger::logDebug("Completed game intialisation!");
}


bool Game::initialiseMoons()
{
	//create corporation moon
	Logger::logDebug("__creating corporation moon__");
	std::shared_ptr<AbstractMoon> corporation = std::make_shared<SellableMoon>(SellableMoon("Corporation"));
	if (!moonManager.addMoon(corporation))
		return false;
	//create prototyping moon
	Logger::logDebug("__creating prototyping moon__");
	std::shared_ptr<AbstractMoon> prototyping = std::make_shared<SendableMoon>(SendableMoon("Prototyping"));
	if (!moonManager.addMoon(prototyping))
		return false;
	//create insurance moon
	Logger::logDebug("__creating insurance moon__");
	std::shared_ptr<AbstractMoon> insurance = std::make_shared<SendableMoon>(SendableMoon("Insurance"));
	if (!moonManager.addMoon(insurance))
		return false;
	//create pledge moon
	Logger::logDebug("__creating pledge moon__");
	std::shared_ptr<AbstractMoon> pledge = std::make_shared<SendableMoon>(SendableMoon("Pledge"));
	if (!moonManager.addMoon(pledge))
		return false;
	//create defence moon
	Logger::logDebug("__creating defence moon__");
	std::shared_ptr<AbstractMoon> defence = std::make_shared<SendableMoon>(SendableMoon("Defence"));
	if (!moonManager.addMoon(defence))
		return false;
	
	return true;
}

bool Game::initialiseItems()
{
	//create flashlight
	Logger::logDebug("__creating flashlight item__");
	std::shared_ptr<Item> flashlight = std::make_shared<Item>("Flashlight");
	if(!itemManager.addItem(flashlight))
		return false;
	//create Shovel
	Logger::logDebug("__creating Shovel item__");
	std::shared_ptr<Item> shovel = std::make_shared<Item>("Shovel");
	if(!itemManager.addItem(shovel))
		return false;
	//create pro-flashlight
	Logger::logDebug("__creating pro-flashlight item__");
	std::shared_ptr<Item> pro_flashlight = std::make_shared<Item>("Pro-Flashlight");
	if(!itemManager.addItem(pro_flashlight))
		return false;
	//create teleporter
	Logger::logDebug("__creating teleporter item__");
	std::shared_ptr<Item> teleporter = std::make_shared<Item>("Teleporter");
	if(!itemManager.addItem(teleporter))
		return false;
	//create inverse-teleporter
	Logger::logDebug("__creating inverse-teleporter item__");
	std::shared_ptr<Item> inverse_teleporter = std::make_shared<Item>("Inverse-Teleporter");
	if(!itemManager.addItem(inverse_teleporter))
		return false;
	//create backpack
	Logger::logDebug("__creating backpack item__");
	std::shared_ptr<Item> backpack = std::make_shared<Item>("Backpack");
	if(!itemManager.addItem(backpack))
		return false;
	//create hydraulics mk2
	Logger::logDebug("__creating hydraulics mk2 item__");
	std::shared_ptr<Item> hydraulics_mk2 = std::make_shared<Item>("Hydraulics-Mk2");
	if(!itemManager.addItem(hydraulics_mk2))
		return false;
	
	return true;
}


void Game::play()
{
	displayTitle();
	//gameplay loop
	
	while (true)
	{
		//if we have a valid delegate
		if (currentMode)
			//execute the delegate by deferencing it
			(this->*(*currentMode))();
		else
			Logger::logError("panic as we have no menu right now!");

		//init input 
		std::string line;
		//and args
		std::vector<std::string> args;
		//print little arrow thing to console
		std::cout << "> ";
		//wait for input
		std::getline(std::cin,line);
		//parse input
		parseInput(line,args);
		//create new lines
		std::cout << "\n\n";
		//process input
		processCommand(line, args);

		if(line == "quit")
			break;
	}
	
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
	//c++ doesnt have decent switch statements
	//this conditional chain acts like one for the value of `line`
	if (line == "land")
	{
		//if not in orbit phase
		if (gamePhase != GamePhase::ORBITING)
		{
			//cmd invalid
			std::cout << "This command is not available at this time.\n";
			return;
		}
		//set the phase to landing
		gamePhase = GamePhase::LANDING;
		//change mode to base menu
		currentMode = std::make_unique<void(Game::*)()>(&Game::landMode);
		return;
	}
	else if (line == "leave")
	{
		std::cout << "option 2 is: " << line << std::endl;
	}
	else if (line == "exit")
	{
		std::cout << "option 3 is: " << line << std::endl;
	}
	else if (line == "inventory")
	{
		std::cout << "option 4 is: " << line << std::endl;
	}
	else if (line == "store")
	{
		std::cout << "option 5 is: " << line << std::endl;
	}
	else if (line == "buy")
	{
		std::cout << "option 6 is: " << line << std::endl;
	}
	else if (line == "route")
	{
		std::cout << "option 7 is: " << line << std::endl;
	}
	else if (line == "moons")
	{
		std::cout << "option 8 is: " << line << std::endl;
	}
	else if (line == "send")
	{
		std::cout << "option 9 is: " << line << std::endl;
	}
	else if (line == "sell")
	{
		std::cout << "option 10 is: " << line << std::endl;
	}
	
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


void Game::orbitMode()
{
	//display day header
	std::cout
		<< std::format("============= DAY {} =============\n", dayCount);
	//display stats
	std::cout
		<< std::format("Current cargo value: ${}\n", cargoValue)
		<< std::format("Current balance: ${}\n", balance)
		<< std::format("Current quota: ${} ({} days left to meet quota)\n", quota,4-dayCount);
	//display orbit info
	displayOrbitInfo();
	//display options
	std::cout
		<< ">MOONS\nTo see the list of moons the autopilot can route to.\n\n"
		<< ">STORE\nTo see the company store's selection of useful items.\n\n"
		<< ">INVENTORY\nTo see the list of items you've already bought.\n\n";
}

void Game::landMode()
{
	//display welcome notice
	if (!currentMoon.expired())
		std::cout << std::format("WELCOME to {}!\n\n", (*currentMoon.lock()).name());
	else
		std::cout << "WELCOME to NONE!!\n\n";
	//display stats
	std::cout
		<< std::format("Current cargo value: ${}\n", cargoValue)
		<< std::format("Current balance: ${}\n", balance)
		<< std::format("Current quota: ${} ({} days left to meet quota)\n", quota, 4 - dayCount);
	
	//reset the number of employees
	employeeCount = 4;
	//display number of employees
	std::cout << std::format("Number of employees: {}\n\n", employeeCount);
	
	//do something with the weather 
	//display weather
	std::cout << "--- weather info goes here ---\n\n";
	
	//probably shouldnt go here but get moon behaviour notes (SEND/SELL)
	//display the behaviour notes
	std::cout << "--- stuff about sending/selling goes here ---\n\n";
}




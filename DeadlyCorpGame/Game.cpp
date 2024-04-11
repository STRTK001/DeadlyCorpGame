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
	if (auto ptr = currentMoon.lock())
		Logger::logDebug(ptr.get()->name());
	else
		Logger::logError("couldnt set the current moon to corp");

	//Logger::logDebug("initalising game phase!");
	//set game phase to orbiting corp

	Logger::logDebug("Completed game intialisation!");
}

void Game::newGame()
{
	
}


bool Game::initialiseMoons()
{
	//create corporation moon
	Logger::logDebug("__creating corporation moon__");
	std::shared_ptr<AbstractMoon> corporation = std::make_shared<CorporationMoon>(CorporationMoon("Corporation"));
	if (!moonManager.addMoon(corporation))
		return false;
	//create prototyping moon
	Logger::logDebug("__creating prototyping moon__");
	std::shared_ptr<AbstractMoon> prototyping = std::make_shared<GenericMoon>(GenericMoon("Prototyping"));
	if (!moonManager.addMoon(prototyping))
		return false;
	//create insurance moon
	Logger::logDebug("__creating insurance moon__");
	std::shared_ptr<AbstractMoon> insurance = std::make_shared<GenericMoon>(GenericMoon("Insurance"));
	if (!moonManager.addMoon(insurance))
		return false;
	//create pledge moon
	Logger::logDebug("__creating pledge moon__");
	std::shared_ptr<AbstractMoon> pledge = std::make_shared<GenericMoon>(GenericMoon("Pledge"));
	if (!moonManager.addMoon(pledge))
		return false;
	//create defence moon
	Logger::logDebug("__creating defence moon__");
	std::shared_ptr<AbstractMoon> defence = std::make_shared<GenericMoon>(GenericMoon("Defence"));
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
	std::shared_ptr<Item> hydraulics_mk2 = std::make_shared<Item>("Hydraulics Mk2");
	if(!itemManager.addItem(hydraulics_mk2))
		return false;
	
	return true;
}

void Game::gameCycle()
{

}





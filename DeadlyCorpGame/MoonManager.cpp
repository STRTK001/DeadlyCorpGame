#include "MoonManager.h"
#include <iostream>

#include "Game.h"

bool MoonManager::addMoon(std::shared_ptr<AbstractMoon> moon)
{
	moonVec.push_back(moon);
	return true;
}

std::shared_ptr<AbstractMoon> MoonManager::getMoon(std::string name) const
{
	for (std::shared_ptr<AbstractMoon> moon : moonVec)
	{
		Logger::logDebug(moon.get()->name());
		if (moon.get() != nullptr)
		{
			std::string moonName = moon.get()->name();
			//lower the name
			util::lower(moonName);
			if (moonName == name)
				return moon;
		}
	}

	return nullptr;
}

void MoonManager::moons() const
{
	//display welcome msg
	std::cout
		<< "Welcom to the exomoons catalogue.\n"
		<< "To route the autopilot to a moob, use the word ROUTE.\n"
		<< "---------------------------------------\n\n";
	//for each moon in our moon vec
	for (std::shared_ptr<AbstractMoon> moon : moonVec)
	{
		//print the moon name
		std::cout << std::format("* {}", moon.get()->name());
		//check if this moon costs money to route to
		if (moon.get()->price() > 0)
			std::cout << std::format(": ${}\n", moon.get()->price());
		else
			std::cout << std::endl;
	}
}

void MoonManager::route(Game& game, std::string moonName)
{
	//get the moon
	std::shared_ptr<AbstractMoon> targetMoon = getMoon(moonName);
	//check if the moon exists
	if (targetMoon == nullptr)
	{
		//print error msg
		std::cout << std::format("Unknown moon \"{}\"\n\n", moonName);
		//*** print weather as well once we've worked that out
		return;
	}
	//check if we already orbiting the moon
	if (game.getCurrentMoon().get() == targetMoon.get())
	{
		//print msg
		std::cout << std::format("Already orbiting {}.\n\n", targetMoon.get()->name());
		return;
	}
	//call onNavigate()
	if (targetMoon->onNavigate(game))
	{
		//set the games current moon to the target moon
		game.setCurrentMoon(targetMoon);
		//print orbit msg
		std::cout << std::format("Now orbiting {}. Use the LAND command to land.\n\n", game.getCurrentMoon()->name());
		return;
	}
	//print orbit msg
	std::cout << std::format("Still orbiting {}.\n\n", game.getCurrentMoon()->name());
}





#include "MoonManager.h"
#include <iostream>


bool MoonManager::addMoon(std::shared_ptr<AbstractMoon> moon)
{
	moonVec.push_back(moon);
	return true;
}

std::shared_ptr<AbstractMoon> MoonManager::getMoon(std::string name)
{
	std::cout << "vec size is " << moonVec.size() << "!\n";
	Logger::logDebug(""+moonVec.size());
	for (std::shared_ptr<AbstractMoon> moon : moonVec)
	{
		Logger::logDebug(moon.get()->name());
		if (moon.get() != nullptr && moon.get()->name() == name)
			return moon;
	}

	return nullptr;
}


void MoonManager::helloWorld()
{

}

// ---- map methods ---- *before i read that we cant use maps
/*
bool MoonManager::addMoon(std::shared_ptr<AbstractMoon> moon)
{
	//check if either the ptr or moon are valid
	if (!moon || moon.get() == nullptr)
	{
		Logger::logError("the moon is not a valid object or ptr\n");
		return false;
	}
		

	//get the moons name
	std::string name = moon.get()->name();
	//check if the a moon with the same name exists
	
	if (contains(name))
	{
		Logger::logError("allegedly the moon: " + name + " exists\n");
		return false;
	}
		

	//add moon to our moon map
	moonMap[name] = moon;
	Logger::logDebug("shouldve added the moon: " + name + "\n");
	return true;
}
*/

/*
std::shared_ptr<AbstractMoon> MoonManager::getMoon(std::string name)
{
	if (!contains(name))
		return nullptr;

	return moonMap[name];
}
*/

/*
bool MoonManager::contains(std::string key)
{
	auto iter = moonMap.find(key);
	if (iter != moonMap.end())
	{
		return true;
	}
	return false;
}
*/


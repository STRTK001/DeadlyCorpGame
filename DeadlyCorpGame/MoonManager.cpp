#include "MoonManager.h"
#include <iostream>


bool MoonManager::addMoon(std::shared_ptr<AbstractMoon> moon)
{
	moonVec.push_back(moon);
	return true;
}

std::shared_ptr<AbstractMoon> MoonManager::getMoon(std::string name)
{
	Logger::logDebug(""+moonVec.size());
	for (std::shared_ptr<AbstractMoon> moon : moonVec)
	{
		Logger::logDebug(moon.get()->name());
		if (moon.get() != nullptr && moon.get()->name() == name)
			return moon;
	}

	return nullptr;
}



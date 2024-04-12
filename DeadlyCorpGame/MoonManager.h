#ifndef MOONMANAGER_H
#define MOONMANAGER_H

//#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <format>

#include "AbstractMoon.h"
#include "Logger.h"
#include "PremiumMoon.h"
#include "util.h"
class Game;

class MoonManager
{
public:
	
	MoonManager() {};

	bool addMoon(std::shared_ptr<AbstractMoon> moon);
	std::shared_ptr<AbstractMoon> getMoon(std::string name) const;
	
	void moons() const;
	void route(Game& game, std::string moonName);

private:
	std::vector<std::shared_ptr<AbstractMoon>> moonVec;


	 
};
#endif
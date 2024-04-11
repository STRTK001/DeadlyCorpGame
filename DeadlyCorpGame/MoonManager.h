#ifndef MOONMANAGER_H
#define MOONMANAGER_H

//#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AbstractMoon.h"
#include "Logger.h"

class MoonManager
{
public:
	
	bool addMoon(std::shared_ptr<AbstractMoon> moon);
	std::shared_ptr<AbstractMoon> getMoon(std::string name);

	MoonManager() {};
	void helloWorld();
	

private:
	std::vector<std::shared_ptr<AbstractMoon>> moonVec;


	 
};
#endif
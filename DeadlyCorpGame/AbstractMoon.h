#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H

#include <string>

class Game;

class AbstractMoon
{

public:
	AbstractMoon(std::string name) : name_(name) {};

	const std::string& name() const { return name_;};

	virtual void onDayBegin(Game& g) {};

	virtual void sellCargo(Game& g, int amount) = 0;

	virtual void sendEmployees(Game& g, int count) = 0;

protected:
	std::string name_;
	float
		minimumScrapValue,
		maximumScrapValue,
		baseSurvivalChance;


};

#endif
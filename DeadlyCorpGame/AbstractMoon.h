#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H

#include <string>

class Game;

class AbstractMoon
{

public:
	// --- vars
	

	// --- methods

	AbstractMoon(std::string name,int price) : 
		name_(name), price_(price) {};

	const std::string& name() const { return name_;};

	const int& price() const { return price_; };

	virtual void onDayBegin(Game& g) {};

	virtual void sellCargo(Game& g, int amount) = 0;

	virtual void sendEmployees(Game& g, int count) = 0;

	virtual bool onNavigate(Game& game) { return true; };


protected:
	std::string name_;

	int price_;

	float
		minimumScrapValue,
		maximumScrapValue,
		baseSurvivalChance;


};

#endif
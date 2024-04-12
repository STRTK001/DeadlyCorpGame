#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H

#include <string>

class Game;

class AbstractMoon
{

public:
	AbstractMoon(std::string name,int price) : 
		name_(name), price_(price) {};

	const std::string& name() const { return name_;};

	const int& price() const { return price_; };

	virtual void onDayBegin(Game& game) {};

	virtual void sell(Game& game, int amount) = 0;

	virtual void send(Game& game, int count) = 0;

	virtual bool onNavigate(Game& game) { return true; };

	virtual void print() = 0;;


protected:
	std::string name_;

	int price_;

	float
		minimumScrapValue,
		maximumScrapValue,
		baseSurvivalChance;


};

#endif
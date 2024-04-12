#ifndef IPREMIUMMOON_H
#define IPREMIUMMOON_H

#include <string>
#include <iostream>
#include <format>

#include "AbstractMoon.h"
#include "util.h"


class Game;

class PremiumMoon : public AbstractMoon
{
public:
	PremiumMoon(std::string name, int price) : AbstractMoon(name, price) {};
	
	bool onNavigate(Game& game) override;

	virtual void sellCargo(Game& g, int amount) override {};

	virtual void sendEmployees(Game& g, int count) override {};
};

#endif
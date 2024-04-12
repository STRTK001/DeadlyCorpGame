#ifndef SELLABLEMOON_H
#define SELLABLEMOON_H

#include <string>

#include "AbstractMoon.h"

class SellableMoon : public AbstractMoon
{

public:
	SellableMoon(std::string name,int price) : AbstractMoon(name,price) {};

	virtual void sellCargo(Game& g, int amount) override {};

	virtual void sendEmployees(Game& g, int count) override {};
};

#endif
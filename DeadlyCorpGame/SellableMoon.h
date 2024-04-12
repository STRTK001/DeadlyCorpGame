#ifndef SELLABLEMOON_H
#define SELLABLEMOON_H

#include <string>
#include <iostream>
#include <format>

#include "AbstractMoon.h"

class SellableMoon : public AbstractMoon
{

public:
	SellableMoon(std::string name,int price) : AbstractMoon(name,price) {};

	virtual void sell(Game& game, int amount) override;

	virtual void send(Game& game, int count) override;

	virtual void print();
};

#endif
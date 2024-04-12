#ifndef SENDABLEMOON_H
#define SENDABLEMOON_H

#include <iostream>
#include <format>

#include "AbstractMoon.h"

class SendableMoon : public AbstractMoon
{
public:
	SendableMoon(std::string name, int price) : AbstractMoon(name, price) {};

	virtual void sell(Game& game, int amount) override;

	virtual void send(Game& game, int count) override;

	virtual void print() override;
};

#endif
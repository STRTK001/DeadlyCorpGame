#ifndef SENDABLEMOON_H
#define SENDABLEMOON_H

#include "AbstractMoon.h"

class SendableMoon : public AbstractMoon
{
public:
	SendableMoon(std::string name) : AbstractMoon(name) {};

	virtual void sellCargo(Game& g, int amount) override {};

	virtual void sendEmployees(Game& g, int count) override {};
};

#endif
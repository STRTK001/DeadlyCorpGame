#ifndef CORPORATIONMOON_H
#define CORPORATIONMOON_H

#include <string>

#include "AbstractMoon.h"

class CorporationMoon : public AbstractMoon
{

public:
	CorporationMoon(std::string name) : AbstractMoon(name) {};

	void moonCommand(std::string moonCommand) const override {};
};

#endif
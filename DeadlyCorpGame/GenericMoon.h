#ifndef GENERICMOON_H
#define GENERICMOON_H

#include "AbstractMoon.h"

class GenericMoon : public AbstractMoon
{
public:
	GenericMoon(std::string name) : AbstractMoon(name) {};

	void moonCommand(std::string moonCommand) const override {};
};

#endif
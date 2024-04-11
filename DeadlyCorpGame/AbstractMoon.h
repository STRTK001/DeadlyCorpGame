#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H

#include <string>

class AbstractMoon
{

public:
	AbstractMoon(std::string name) : name_(name) {};

	std::string name() const { return name_;};

	virtual void moonCommand(std::string moonCommand) const = 0;

protected:
	std::string name_;
	float
		minimumScrapValue,
		maximumScrapValue,
		baseSurvivalChance;
};

#endif
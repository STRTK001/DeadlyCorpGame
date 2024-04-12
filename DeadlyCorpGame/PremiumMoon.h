#ifndef IPREMIUMMOON_H
#define IPREMIUMMOON_H

#include <string>
#include <format>

#include "AbstractMoon.h"
#include "util.h"


class Game;

class PremiumMoon : public AbstractMoon
{
public:
	PremiumMoon(std::string name, int price) : AbstractMoon(name, price) {};
	
	bool onNavigate(Game& game) override;

	virtual void sell(Game& game, int amount) override;

	virtual void send(Game& game, int count) override;

	virtual void print() override;
};

#endif
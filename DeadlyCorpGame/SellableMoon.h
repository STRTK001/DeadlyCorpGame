#ifndef SELLABLEMOON_H
#define SELLABLEMOON_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include <string>
#include <iostream>
#include <format>

#include "AbstractMoon.h"

/// <summary>
/// moon class that can sell cargo but doesnt allow for expeditions
/// </summary>
class SellableMoon : public AbstractMoon
{

public:
	SellableMoon
	(
		std::string name, int price, float minScrapVal, float maxScrapVal,
		float baseSurvChance
	) : AbstractMoon(name,price,minScrapVal,maxScrapVal,baseSurvChance) {};

	/// <summary>
	/// sells the users cargo.
	/// sells all if the user doesnt specify an amount "-1".
	/// sells a portion if the user specifies and amount.
	/// </summary>
	virtual void sell(Game& game, int amount) override;

	/// <summary>
	/// this moon doesnt do expeditions so it displays a "command not available" msg.
	/// </summary>
	virtual void send(Game& game, int count) override;

	/// <summary>
	/// changes this moons weather via randomly generated numbers when the day begins
	/// </summary>
	virtual void onDayBegin(Game& game) override;

	/// <summary>
	/// prints this moons msg
	/// </summary>
	virtual void print();
};

#endif
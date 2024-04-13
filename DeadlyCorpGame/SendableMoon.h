#ifndef SENDABLEMOON_H
#define SENDABLEMOON_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include <iostream>
#include <format>

#include "AbstractMoon.h"

/// <summary>
/// class for basic moons that can send employees out on an expedition.
/// </summary>
class SendableMoon : public AbstractMoon
{
public:
	SendableMoon
	(
		std::string name, int price, float minScrapVal, float maxScrapVal,
		float baseSurvChance
	) : AbstractMoon(name, price, minScrapVal, maxScrapVal, baseSurvChance) {};

	/// <summary>
	/// this moon cant sell so just prints an "unavailable command" msg
	/// </summary>
	virtual void sell(Game& game, int amount) override;

	/// <summary>
	/// method for sending employees out on an expedition.
	/// Runs the whole expedition simulation
	/// </summary>
	virtual void send(Game& game, int count) override;

	/// <summary>
	/// changes this moons weather via randomly generated numbers when the day begins
	/// </summary>
	virtual void onDayBegin(Game& game) override;

	/// <summary>
	/// prints this moons msg
	/// </summary>
	virtual void print() override;
};

#endif
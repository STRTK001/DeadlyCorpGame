#ifndef IPREMIUMMOON_H
#define IPREMIUMMOON_H


///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///
/// 
#include <string>
#include <format>

#include "AbstractMoon.h"
#include "util.h"


class Game;


/// <summary>
/// class for moons that can be bought
/// </summary>
class PremiumMoon : public AbstractMoon
{
public:
	PremiumMoon
	(
		std::string name, int price, float minScrapVal, float maxScrapVal,
		float baseSurvChance
	) : AbstractMoon(name, price, minScrapVal, maxScrapVal, baseSurvChance) {};
	
	/// <summary>
	/// method that is called when the user attemps to route to this moon. 
	/// prompts the user if they want to purchase it.
	/// </summary>
	bool onNavigate(Game& game) override;
	
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
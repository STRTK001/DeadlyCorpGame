#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include <string>
#include <format>
#include <random>

#include "MoonWeather.h"
#include "Logger.h"

class Game;

class AbstractMoon
{

public:
	
	AbstractMoon
	(
		std::string name,int price,float minScrapVal,float maxScrapVal,
		float baseSurvChance
	) : 
		_name(name), _price(price),_minimumScrapValue(minScrapVal),
		_maximumScrapValue(maxScrapVal),_baseSurvivalChance(baseSurvChance){};


	/// <summary>
	/// getter for name
	/// </summary>
	const std::string& name() const { return _name;};

	/// <summary>
	/// getter for price
	/// </summary>
	/// <param name="game"></param>
	/// <param name="amount"></param>
	const int& price() const { return _price; };

	/// <summary>
	/// getter for weather
	/// </summary>
	const MoonWeather& weather() { return _weather; };
	
	/// <summary>
	/// method to invoke behaviour when a new day begins
	/// </summary>
	virtual void onDayBegin(Game& game) {};

	/// <summary>
	/// method for selling cargo
	/// </summary>
	/// <param name="game"></param>
	/// <param name="count"></param>
	virtual void sell(Game& game, int amount) = 0;

	/// <summary>
	/// method for sending employees out
	/// </summary>
	virtual void send(Game& game, int count) = 0;

	/// <summary>
	/// method to invoke behaviour when the moon is navigated to
	/// </summary>
	virtual bool onNavigate(Game& game) { return true; };

	/// <summary>
	/// displays weather infomation to console
	/// </summary>
	virtual void displayWeather();

	/// <summary>
	/// displays a message about the moon to console
	/// </summary>
	virtual void print() = 0;

	


protected:

	/// <summary>
	/// name of the moon
	/// </summary>
	std::string _name;

	/// <summary>
	/// price of the mooon
	/// </summary>
	int _price;
		
	/// <summary>
	/// baseSurvivalChance -> the base survival chance of explorers
	/// minimumScrapValue -> the minimum value for scrap grabbed in an expedition
	/// maximumScrapValue -> the maximum value for scrap grabbed in an expedition
	/// </summary>
	float
		_baseSurvivalChance,
		_minimumScrapValue,
		_maximumScrapValue;

	/// <summary>
	/// the current weather of the moon
	/// </summary>
	MoonWeather _weather;


};

#endif
#ifndef MOONMANAGER_H
#define MOONMANAGER_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

//#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <format>

#include "AbstractMoon.h"
#include "Logger.h"
#include "PremiumMoon.h"
#include "util.h"
#include "MoonWeather.h"


class Game;

/// <summary>
/// manager of the games moons
/// </summary>
class MoonManager
{
public:
	
	MoonManager() {};

	/// <summary>
	/// adds a new moon to the moon vector
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool addMoon(std::shared_ptr<AbstractMoon> moon);
	/// <summary>
	/// getter for retriving a copy of the shared ptr of the selected moon
	/// </summary>
	/// <param name="game"></param>
	const std::shared_ptr<AbstractMoon> getMoon(std::string name) const;
	
	/// <summary>
	/// displays the current routable moons
	/// </summary>
	void moons() const;

	/// <summary>
	/// routes the to the selected moon.
	/// </summary>
	/// <param name="game"></param>
	/// <param name="moonName"></param>
	void route(Game& game, std::string moonName);
	/// <summary>
	/// triggers the onDayBegin methods of each moon
	/// </summary>
	void onDaybegin(Game& game);

private:
	/// <summary>
	/// the collection of moons
	/// </summary>
	std::vector<std::shared_ptr<AbstractMoon>> _moonVec; 
};
#endif
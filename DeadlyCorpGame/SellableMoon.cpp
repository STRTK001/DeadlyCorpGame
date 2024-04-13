#include "SellableMoon.h"
#include "Game.h"

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

void SellableMoon::sell(Game& game, int amount) 
{
	if (amount == -1)
	{
		//check if the cargo value is less than 1
		if (game.getCargoValue() < 1)
		{
			//we have nothing to sell
			std::cout << "Nothing to sell.\n\n";
			return;
		}
		//add cargo value to the quota effort
		game.getCurrentQuotaEffort() += game.getCargoValue();
		//increase the balance by the cargo value
		game.getBalance() += game.getCargoValue();
		//reset the cargo value
		game.getCargoValue() = 0;
	}
	else
	{
		//check if the amount is > than cargoValue
		if (amount > game.getCargoValue())
		{
			std::cout << std::format("Only ${} available in cargo.\n\n", game.getCargoValue());
			return;
		}
		//add the amount to the quota effort
		game.getCurrentQuotaEffort() += amount;
		//subtract the amount from the cargo val
		game.getCargoValue() -= amount;
		//increase the balance by the amount
		game.getBalance() += amount;

	}
	//print msg
	std::cout << "Your service is invaluable to the corporation.\n";
	//print balance and quota
	std::cout << std::format("New balance: ${} (quota is ${}).\n",
		game.getBalance(),game.getInitialQuota());
	//print cargo val
	std::cout << std::format("New cargo value: ${}\n\n",game.getCargoValue());
}


void SellableMoon::send(Game& g, int count) 
{
	std::cout << "This command is not available on this moon {SA}.\n\n";
}

void SellableMoon::print()
{
	std::cout
		<< "Type SELL to sell your cargo contents and increase your "
		<< "balance and achieve quota.\nSpecify the amount to sell after "
		<< "the SELL word to only sell a portion of your cargo.\n"
		<< "Type LEAVE to leave the planet.\n\n";
}

void SellableMoon::onDayBegin(Game& game)
{
	//set weather to clear
	_weather = MoonWeather::CLEAR;
}
#include "PremiumMoon.h"
#include "Game.h"

bool PremiumMoon::onNavigate(Game& game)
{
	//print notice msg
	std::cout << std::format("The cost of going to {} is ${}\n", name_,price_);
	//print purchase query
	std::cout << std::format("You have ${}. Confirm destination? [Yes/No]\n",game.getBalance());
	//the specs dont have it but lets put the test cursor in
	std::cout << "> ";
	//capture user input
	std::string input;
	std::getline(std::cin, input);
	//apply new line
	std::cout << std::endl;
	//lower input
	util::lower(input);
	//parse input
	if (input == "yes")
	{
		//not in specs but check if they can afford the purchase
		if (game.getBalance() - price_ < 0)
		{
			//print poor msg
			std::cout << std::format("You cannot afford to route to {}.\n", name_);
			return false;
		}
		//make transaction
		game.getBalance() -= price_;
		//print balance
		std::cout << std::format("New Balance: ${}\n", game.getBalance());
		return true;
	}
	//cancel trip
	std::cout << "Trip cancelled.\n";
	return false;
}
#include "SendableMoon.h"
#include "Game.h"

void SendableMoon::sell(Game& game, int amount) 
{
	std::cout << "This command is not available on this moon.\n\n";
}

void SendableMoon::send(Game& game, int count) 
{
	std::cout << std::format("you wouldve sent {} employees out\n\n", count);
};

void SendableMoon::print()
{
	std::cout
		<< "Type SEND followed by the number of employees you wish to send "
		<< "inside the facility.\nAll the other employees will stay on the ship.\n"
		<< "Type LEAVE to leave the planet.\n\n";
}
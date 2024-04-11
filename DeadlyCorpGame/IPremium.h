#ifndef IPREMIUM_H
#define IPREMIUM_H

class Game;

interface IPremium
{
	/// <summary>
	/// prompts the user if they want to purchase this
	/// </summary>
	virtual void payPremium(Game& game) = 0;
};

#endif
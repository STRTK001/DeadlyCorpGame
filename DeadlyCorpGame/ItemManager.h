#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include <memory>
#include <vector>
#include <string>


#include "Item.h"
#include "Logger.h"
#include "util.h"

class Game;

/// <summary>
/// Class for managing items in the players store and inventory.
/// </summary>
class ItemManager
{
public:
	ItemManager() {};
	
	/// <summary>
	/// adds the item to the store items vector
	/// </summary>
	/// <param name="itemName"></param>
	/// <returns></returns>
	bool addItem(std::shared_ptr<Item> item);

	/// <summary>
	/// getter for the shared_ptr that points to the item we want
	/// </summary>
	/// <param name="game"></param>
	/// <param name="itemName"></param>
	std::shared_ptr<Item> getItem(std::string itemName);

	///<summary>
	/// method for buying the item of choice
	///<summary>
	void buy(Game& game, std::string itemName);

	/// <summary>
	/// displays all the items in the store that can be bought
	/// </summary>
	void store();

	///<summary>
	/// displays all the items that the user has bought
	///<summary>
	void inventory();

	///<summary>
	/// calculates the simulation parameters of the current bought items
	///<summary>
	void calculateSimulationParameters
	(
		float& scrapValueMutli, float& explorerSurvivalChanceMulti,
		float& operatorSurvivalChanceMulti, float& explorerSaveChance,
		float& lootRecoveryMulti
	);


private:
	/// <summary>
	/// the vector for storing items in our "store"
	/// </summary>
	std::vector<std::shared_ptr<Item>> _storeItems;
	/// <summary>
	/// the vector for storing items the the user has bought
	/// </summary>
	std::vector<std::shared_ptr<Item>> _boughtItems;

	/// <summary>
	/// checks if the user has bought the item matching item name
	/// </summary>
	bool hasBought(std::string itemName);
};

#endif
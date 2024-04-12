#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <vector>
#include <string>


#include "Item.h"
#include "Logger.h"
#include "util.h"

class Game;

class ItemManager
{
public:
	ItemManager() {};
	
	bool addItem(std::shared_ptr<Item> item);
	std::shared_ptr<Item> getItem(std::string itemName);

	void buy(Game& game, std::string itemName);

	void store();

	void inventory();

private:
	std::vector<std::shared_ptr<Item>> storeItems;
	std::vector<std::shared_ptr<Item>> boughtItems;

	bool hasBought(std::string itemName);
};

#endif
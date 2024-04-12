#include "ItemManager.h"
#include "Game.h"

bool ItemManager::addItem(std::shared_ptr<Item> item)
{
	storeItems.push_back(item);
	return true;
}

std::shared_ptr<Item> ItemManager::getItem(std::string itemName)
{
	for (std::shared_ptr<Item> item : storeItems)
	{
		Logger::logDebug(item.get()->name());
		if (item.get() != nullptr)
		{
			//get target item name
			std::string targetName = item.get()->name();
			//lower target name
			util::lower(targetName);
			if(targetName == itemName)
				return item;
		}
			
	}

	return nullptr;
}


void ItemManager::buy(Game& game, std::string itemName)
{
	//check if the item is in the store
	std::shared_ptr<Item> targetItem = getItem(itemName);
	if (targetItem == nullptr)
	{
		//print error msg
		std::cout << std::format("Unknown item \"{}\".\n\n", itemName);
		//*** print weather as well once we've worked that out
		return;
	}
	//check if we have already bought the item
	if (hasBought(itemName))
	{
		//print error msg
		std::cout << std::format("You already own a {}.\n\n", itemName);
		return;
	}
	//add item to bought items
	boughtItems.push_back(targetItem);
	//make transaction
	game.getBalance() -= targetItem.get()->price();
	//print sucess msg
	std::cout << std::format("Successfully bought {}.\n",itemName);
	//print balance
	std::cout << std::format("Balance is now ${}\n\n", game.getBalance());
}

bool ItemManager::hasBought(std::string itemName)
{
	for (std::shared_ptr<Item> item : boughtItems)
	{
		//get target item name
		std::string targetName = item.get()->name();
		//lower target name
		util::lower(targetName);
		if (targetName == itemName)
			return true;
	}
	return false;
}

void ItemManager::store()
{
	//display welcome msg
	std::cout
		<< "Welcome to the Corporation store.\n"
		<< "Use the word BUY on any item.\n"
		<< "---------------------------------------\n\n";
	//for each moon in our moon vec
	for (std::shared_ptr<Item> item : storeItems)
	{
		//print the moon name and price
		std::cout << std::format("* {} // Price: ${}\n", 
			item.get()->name(), item.get()->price());
	}
	//line break
	std::cout << std::endl;
}

void ItemManager::inventory()
{
	//display msg
	std::cout
		<< "The following items are available.\n"
		<< "---------------------------------------\n\n";
	//check if we have bought items
	if (boughtItems.size() == 0)
	{
		//print empty
		std::cout << "(empty)\n\n";
		return;
	}

	//for each moon in our moon vec
	for (std::shared_ptr<Item> item : boughtItems)
	{
		//print the moon name and price
		std::cout << std::format("* {}\n", item.get()->name());
	}
	//line break
	std::cout << std::endl;
}
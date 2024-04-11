#include "ItemManager.h"


bool ItemManager::addItem(std::shared_ptr<Item> item)
{
	//check if either the ptr or item are valid
	if (!item || item.get() == nullptr)
	{
		Logger::logError("the item is not a valid object or ptr\n");
		return false;
	}
		
	//get the item name
	std::string name = item.get()->name;
	
	//check if the a item with the same name exists
	if (contains(name))
	{
		Logger::logError("allegedly the item: " + name + " exists\n");
		return false;
	}

	//add item to our item map
	itemMap[name] = item;
	Logger::logDebug("shouldve added the item: " + name + "\n");
	return true;
}


std::shared_ptr<Item> ItemManager::getItem(std::string name)
{
	if (!contains(name))
		return nullptr;

	return itemMap[name];
}

bool ItemManager::contains(std::string key)
{
	auto iter = itemMap.find(key);
	if (iter != itemMap.end())
	{
		return true;
	}
	return false;
}

void ItemManager::helloWorld()
{

}
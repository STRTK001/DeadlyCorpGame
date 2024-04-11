#include "ItemManager.h"


bool ItemManager::addItem(std::shared_ptr<Item> item)
{
	itemVec.push_back(item);
	return true;
}

std::shared_ptr<Item> ItemManager::getItem(std::string name)
{
	for (std::shared_ptr<Item> item : itemVec)
	{
		Logger::logDebug(item.get()->name());
		if (item.get() != nullptr && item.get()->name() == name)
			return item;
	}

	return nullptr;
}
#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <vector>

#include "Item.h"
#include "Logger.h"


class ItemManager
{
public:
	ItemManager() {};
	
	bool addItem(std::shared_ptr<Item> item);
	std::shared_ptr<Item> getItem(std::string name);

private:
	std::vector<std::shared_ptr<Item>> itemVec;
};
#endif
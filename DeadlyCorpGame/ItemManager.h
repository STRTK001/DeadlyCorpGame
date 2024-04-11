#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <map>

#include "Item.h"
#include "Logger.h"


class ItemManager
{
public:
	ItemManager() {};
	
	bool addItem(std::shared_ptr<Item> item);
	
	std::shared_ptr<Item> getItem(std::string name);
	
	void helloWorld();


private:
	std::map<std::string, std::shared_ptr<Item>> itemMap;


	bool contains(std::string key);
};
#endif
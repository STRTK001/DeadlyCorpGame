#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(std::string name) : name_(name) {};
	std::string name() const { return name_; };
private:
	std::string name_;

	int price;
	float
		scrapValueMultiplier,
		explorerSurvivalChanceMultiplier,
		operatorSurvivalChanceMultiplier,
		explorerSaveChance,
		lootRecoveryMultiplier;

};

#endif
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(std::string name, int price) : name_(name), price_(price) {};

	std::string name() const { return name_; };
	int price() const { return price_; };
private:
	std::string name_;

	int price_;
	float
		scrapValueMultiplier,
		explorerSurvivalChanceMultiplier,
		operatorSurvivalChanceMultiplier,
		explorerSaveChance,
		lootRecoveryMultiplier;

};

#endif
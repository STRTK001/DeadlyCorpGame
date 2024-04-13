#ifndef ITEM_H
#define ITEM_H

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include <string>

class Item
{
public:
	Item(
		std::string name, int price,float scrapValMulti,float exSurvChance,
		float opSurvChance, float exSaveChance,float lootRecovMulti
		) : 
		_name(name), _price(price), _scrapValueMultiplier(scrapValMulti),
		_explorerSurvivalChanceMultiplier(exSurvChance),
		_operatorSurvivalChanceMultiplier(opSurvChance), _explorerSaveChance(exSaveChance),
		_lootRecoveryMultiplier(lootRecovMulti) {};

	std::string name() const { return _name; };
	int price() const { return _price; };

	void calculateSimulationParameters
	(
		float& scrapValueMutli, float& explorerSurvivalChanceMulti,
		float& operatorSurvivalChanceMulti, float& explorerSaveChance,
		float& lootRecoveryMulti
	)
	{ 
		scrapValueMutli *= _scrapValueMultiplier;
		explorerSurvivalChanceMulti *= _explorerSurvivalChanceMultiplier;
		operatorSurvivalChanceMulti *= _operatorSurvivalChanceMultiplier;
		explorerSaveChance *= _explorerSaveChance;
		lootRecoveryMulti *= _lootRecoveryMultiplier;
	}

private:
	std::string _name;

	int _price;
	float
		_scrapValueMultiplier,
		_explorerSurvivalChanceMultiplier,
		_operatorSurvivalChanceMultiplier,
		_explorerSaveChance,
		_lootRecoveryMultiplier;



};

#endif
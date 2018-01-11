#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "Inventory.h"

#define NOT_DEFINED -999999

namespace core
{
	enum class CONTROLLER;
}

struct Stats
{
	int maxHp;
	int hp;
	unsigned int agility;
	unsigned int luck;
	unsigned int wisdom;
	unsigned int accuracy;
	unsigned int attack;
	std::string name;
	std::string race;
	std::vector<std::string> perks;
};

class Character
{
public:
	Character();
	~Character();

	std::string Name(std::string name = "");
	std::string Race(std::string race = "");
	std::vector<std::string> Perks(std::string perk = "");
	int Hp(int hp = NOT_DEFINED);
	unsigned int Agility(int agility = NOT_DEFINED);
	unsigned int Luck(int luck = NOT_DEFINED);
	unsigned int Wisdom(int wisdom = NOT_DEFINED);
	unsigned int Accuracy(int accuracy = NOT_DEFINED);
	unsigned int Attack(int attack = NOT_DEFINED);

	void IncreaseHp(int hp);
	void IncreaseAgility(int agility);
	void IncreaseLuck(int luck);
	void IncreaseWisdom(int wisdom);
	void IncreaseAccuracy(int accuracy);
	void IncreaseAttack(int attack);
	void SetMaxHp(int maxHp);
	
	void SetController(core::CONTROLLER controller);
	core::CONTROLLER GetController();

	Inventory inventory;
private:
	Stats m_stats;
	core::CONTROLLER m_controller;
};



#endif
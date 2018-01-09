#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "Inventory.h"

namespace core
{
	enum class CONTROLLER;
}

struct Stats
{
	std::string name;
	std::string race;
	std::vector<std::string> perks;
	unsigned int hp;
	unsigned int agility;
	unsigned int luck;
	unsigned int wisdom;
	unsigned int accuracy;
	unsigned int attack;
};

class Character
{
public:
	Character();
	~Character();

	std::string Name(std::string name = "");
	std::string Race(std::string race = "");
	std::vector<std::string> Perks(std::string perk = "");
	unsigned int Hp(int hp = -1);
	unsigned int Agility(int agility = -1);
	unsigned int Luck(int luck = -1);
	unsigned int Wisdom(int wisdom = 0);
	unsigned int Accuracy(int accuracy = 0);
	unsigned int Attack(int attack = 0);

	void IncreaseHp(int hp);
	void IncreaseAgility(int agility);
	void IncreaseLuck(int luck);
	void IncreaseWisdom(int wisdom);
	void IncreaseAccuracy(int accuracy);
	void IncreaseAttack(int attack);
	
	void SetController(core::CONTROLLER controller);
	core::CONTROLLER GetController();

	Inventory inventory;
private:
	Stats stats;
	core::CONTROLLER m_controller;
};



#endif
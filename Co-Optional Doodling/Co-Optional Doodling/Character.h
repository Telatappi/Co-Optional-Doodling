#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

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
private:
	Stats stats;
	Inventory inventory;
};



#endif
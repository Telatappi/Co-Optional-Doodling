#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item();
	~Item();
	void SetName(std::string name);
	void SetHp(unsigned int hp);
	void SetAgility(unsigned int agility);
	void SetLuck(unsigned int luck);
	void SetWisdom(unsigned int wisdom);
	void SetAccuracy(unsigned int accuracy);
	void SetAttack(unsigned int attack);
	void SetType(std::string type);
	
	std::string GetName();
	unsigned int GetHp();
	unsigned int GetAgility();
	unsigned int GetLuck();
	unsigned int GetWisdom();
	unsigned int GetAccuracy();
	unsigned int GetAttack();
	std::string GetType();
private:
	std::string m_name;
	unsigned int m_hp;
	unsigned int m_agility;
	unsigned int m_luck;
	unsigned int m_wisdom;
	unsigned int m_accuracy;
	unsigned int m_attack;
	std::string m_type;
};
#endif
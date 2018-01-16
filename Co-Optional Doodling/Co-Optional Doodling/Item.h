#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item();
	~Item();
	void SetName(std::string name);
	void SetHp(int hp);
	void SetAgility(int agility);
	void SetLuck(int luck);
	void SetWisdom(int wisdom);
	void SetAccuracy(int accuracy);
	void SetAttack(int attack);
	void SetType(std::string type);
	
	std::string GetName();
	int GetHp();
	int GetAgility();
	int GetLuck();
	int GetWisdom();
	int GetAccuracy();
	int GetAttack();
	std::string GetType();
private:
	std::string m_name;
	int m_hp;
	int m_agility;
	int m_luck;
	int m_wisdom;
	int m_accuracy;
	int m_attack;
	std::string m_type;
};
#endif
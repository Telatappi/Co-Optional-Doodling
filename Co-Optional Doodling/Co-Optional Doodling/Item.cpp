#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::SetName(std::string _name)
{
	m_name = _name
}

void Item::SetHp(unsigned int _hp)
{
	m_hp = _hp;
}

void Item::SetAgility(unsigned int _agility)
{
	m_agility = _agility;
}

void Item::SetLuck(unsigned int _luck)
{
	m_luck = _luck;
}

void Item::SetWisdom(unsigned int _wisdom)
{
	m_wisdom = _wisdom;
}

void Item::SetAccuracy(unsigned int _accuracy)
{
	m_accuracy = _accuracy;
}

void Item::SetAttack(unsigned int _attack)
{
	m_attack = _attack
}

void Item::SetType(std::string _type)
{
	m_type = _type;
}

std::string Item::GetName()
{
	return m_name;
}

unsigned int Item::GetHp()
{
	return m_hp;
}

unsigned int Item::GetAgility()
{
	return m_agility;
}

unsigned int Item::GetLuck()
{
	return m_luck;
}

unsigned int Item::GetWisdom()
{
	return m_wisdom;
}

unsigned int Item::GetAccuracy()
{
	return m_accuracy;
}

unsigned int Item::GetAttack()
{
	return m_attack;
}

std::string Item::GetType()
{
	return m_type;
}

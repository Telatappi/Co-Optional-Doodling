#include "Item.h"

Item::Item()
	:m_name(""),
	m_hp(0),
	m_agility(0),
	m_luck(0),
	m_wisdom(0),
	m_accuracy(0),
	m_attack(0),
	m_type("")
{
}

Item::~Item()
{
}

void Item::SetName(std::string _name)
{
	m_name = _name;
}

void Item::SetHp(int _hp)
{
	m_hp = _hp;
}

void Item::SetAgility(int _agility)
{
	m_agility = _agility;
}

void Item::SetLuck(int _luck)
{
	m_luck = _luck;
}

void Item::SetWisdom(int _wisdom)
{
	m_wisdom = _wisdom;
}

void Item::SetAccuracy(int _accuracy)
{
	m_accuracy = _accuracy;
}

void Item::SetAttack(int _attack)
{
	m_attack = _attack;
}

void Item::SetType(std::string _type)
{
	m_type = _type;
}

std::string Item::GetName()
{
	return m_name;
}

int Item::GetHp()
{
	return m_hp;
}

int Item::GetAgility()
{
	return m_agility;
}

int Item::GetLuck()
{
	return m_luck;
}

int Item::GetWisdom()
{
	return m_wisdom;
}

int Item::GetAccuracy()
{
	return m_accuracy;
}

int Item::GetAttack()
{
	return m_attack;
}

std::string Item::GetType()
{
	return m_type;
}

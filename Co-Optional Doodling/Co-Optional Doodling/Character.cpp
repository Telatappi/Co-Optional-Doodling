#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

std::string Character::Name(std::string _name)
{
	//if name was provided
	//we want to change current name
	if (_name != "")
	{
		m_stats.name = _name;
	}

	//return current name
	return m_stats.name;
}

std::string Character::Race(std::string _race)
{
	if (_race != "")
	{
		m_stats.race = _race;
	}
	return m_stats.race;
}

std::vector<std::string> Character::Perks(std::string _perk)
{
	if (_perk != "")
	{
		m_stats.perks.push_back(_perk);
	}
	return m_stats.perks;
}

int Character::Hp(int _hp)
{
	if (_hp != NOT_DEFINED)
	{
		m_stats.hp = _hp;
	}
	return m_stats.hp;
}

unsigned int Character::Agility(int _agility)
{
	if (_agility != NOT_DEFINED)
	{
		m_stats.agility = _agility;
	}
	return m_stats.agility;
}

unsigned int Character::Luck(int _luck)
{
	if (_luck != NOT_DEFINED)
	{
		m_stats.luck = _luck;
	}
	return m_stats.luck;
}

unsigned int Character::Wisdom(int _wisdom)
{
	if (_wisdom != NOT_DEFINED)
	{
		m_stats.wisdom = _wisdom;
	}
	return m_stats.wisdom;
}

unsigned int Character::Accuracy(int _accuracy)
{
	if (_accuracy != NOT_DEFINED)
	{
		m_stats.accuracy = _accuracy;
	}
	return m_stats.accuracy;
}

unsigned int Character::Attack(int _attack)
{
	if (_attack != NOT_DEFINED)
	{
		m_stats.attack = _attack;
	}
	return m_stats.attack;
}

void Character::IncreaseHp(int _hp)
{
	m_stats.hp += _hp;

	if (m_stats.hp > m_stats.maxHp)
	{
		m_stats.hp = m_stats.maxHp;
	}
}

void Character::IncreaseAgility(int _agility)
{
	m_stats.agility += _agility;
}

void Character::IncreaseLuck(int _luck)
{
	m_stats.agility += _luck;
}

void Character::IncreaseWisdom(int _wisdom)
{
	m_stats.wisdom += _wisdom;
}

void Character::IncreaseAccuracy(int _accuracy)
{
	m_stats.accuracy += _accuracy;
}

void Character::IncreaseAttack(int _attack)
{
	m_stats.attack += _attack;
}

void Character::SetMaxHp(int _maxHp)
{
	m_stats.maxHp = _maxHp;
}

void Character::SetController(core::CONTROLLER _controller)
{
	m_controller = _controller;
}

core::CONTROLLER Character::GetController()
{
	return m_controller;
}

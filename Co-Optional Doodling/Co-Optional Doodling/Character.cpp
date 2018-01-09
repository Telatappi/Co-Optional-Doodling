#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

std::string Character::Name(std::string _name)
{
	if (_name != "")
	{
		stats.name = _name;
	}
	return stats.name;
}

std::string Character::Race(std::string _race)
{
	if (_race != "")
	{
		stats.race = _race;
	}
	return stats.race;
}

std::vector<std::string> Character::Perks(std::string _perk)
{
	if (_perk != "")
	{
		stats.perks.push_back(_perk);
	}
	return stats.perks;
}

unsigned int Character::Hp(int _hp)
{
	if (_hp != -1)
	{
		stats.hp = _hp;
	}
	return stats.hp;
}

unsigned int Character::Agility(int _agility)
{
	if (_agility != -1)
	{
		stats.agility = _agility;
	}
	return stats.agility;
}

unsigned int Character::Luck(int _luck)
{
	if (_luck != -1)
	{
		stats.luck = _luck;
	}
	return stats.luck;
}

unsigned int Character::Wisdom(int _wisdom)
{
	if (_wisdom != -1)
	{
		stats.wisdom = _wisdom;
	}
	return stats.wisdom;
}

unsigned int Character::Accuracy(int _accuracy)
{
	if (_accuracy != -1)
	{
		stats.accuracy = _accuracy;
	}
	return stats.accuracy;
}

unsigned int Character::Attack(int _attack)
{
	if (_attack != -1)
	{
		stats.attack = _attack;
	}
	return stats.attack;
}

void Character::IncreaseHp(int _hp)
{
	stats.hp += _hp;
}

void Character::IncreaseAgility(int _agility)
{
	stats.agility += _agility;
}

void Character::IncreaseLuck(int _luck)
{
	stats.agility += _luck;
}

void Character::IncreaseWisdom(int _wisdom)
{
	stats.wisdom += _wisdom;
}

void Character::IncreaseAccuracy(int _accuracy)
{
	stats.accuracy += _accuracy;
}

void Character::IncreaseAttack(int _attack)
{
	stats.attack += _attack;
}

void Character::SetController(core::CONTROLLER _controller)
{
	m_controller = _controller;
}

core::CONTROLLER Character::GetController()
{
	return m_controller;
}

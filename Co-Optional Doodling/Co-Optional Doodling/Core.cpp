#include "Core.h"
#include <iostream>

void core::InitGame()
{
	std::cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				"          Game Title Screen\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"PLACEHOLDER TEXT PLACEHOLDER TEXT PLACE\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				"PRESS A KEY TO ENTER THE GERMAN DUNGEON\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	fflush(stdin);
	getchar();
}

void core::CharacterCreation()
{
	std::cout << "Character Creation" << std::endl;
	std::cout << "Enter Name:" << std::endl;
	std::cin >>
}

int core::Rand(int x, int y)
{
	std::uniform_int_distribution<int> randomNumber(x, y);
	return randomNumber(rng);
}

void core::PrintInventoryFooter()
{

}

void core::EnterInventory()
{
}

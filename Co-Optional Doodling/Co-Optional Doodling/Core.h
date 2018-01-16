#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <random>
#include "SceneManager.h"
#include "Character.h"
#include "Item.h"

//used for RNG no need to touch this
static std::random_device rd;

//used for RNG no need to touch this
static std::mt19937 rng(rd());

namespace core
{
	enum class COMBAT_OUTCOME
	{
		PLAYER_VICTORY,
		PLAYER_DEATH,
		PLAYER_ESCAPE
	};

	enum class CONTROLLER
	{
		PLAYER,
		ENEMY
	};

	COMBAT_OUTCOME Combat(std::vector<Character>& playerCharacters,
		std::vector<Character>& enemies);

	COMBAT_OUTCOME Combat(Character& player, Character& enemy);
	COMBAT_OUTCOME Combat(Character& player, std::vector<Character>& enemies);
	COMBAT_OUTCOME Combat(std::vector<Character>& playerCharacters, Character& enemy);

	//game core stuff
	void InitGame();
	Character CreateCharacter();
	
	void ClearScreen();
	void PrintCharacterStats(Character& character);

	//get a string of text from input
	std::string GetText();
	//get a single character from input
	int GetKey();
	//char GetKey();
		
	void ClearScreen();

	//utility functions
	int Rand(int min, int max);

	void EnterInventory();

	void Pause();

	Location GetRandomLocation();

	//variables
	extern SceneManager sceneManager;
	extern Character player;
	
	enum ITEMS
	{
		NO_ITEM_SELECTED,
		ITEM_SELECTED
	};
}



#endif
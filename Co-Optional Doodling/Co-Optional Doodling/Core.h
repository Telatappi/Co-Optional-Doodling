#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <random>
#include "SceneManager.h"
#include "Character.h"

//used for RNG no need to touch this
static std::random_device rd;

//used for RNG no need to touch this
static std::mt19937 rng(rd());

//this will be 
static std::string textBuffer;
static std::string longTermTextBuffer;

namespace core
{
	//game core stuff
	void InitGame();
	void PlayerCreation();
	Character CreateCharacter();
	
	void Print(bool clearScreen = false);
	void PrintLongTerm(bool clearScreen = true);

	std::string Input();

	void Text(std::string text);

	void ClearLongTermTextBuffer();

	void ClearScreen();

	//utility functions		


	int Rand(int min, int max);

	void EnterInventory();

	void Pause();

	//variables
	extern SceneManager sceneManager;
	extern Character player;

	class coreDetails
	{
	private:
		struct details
		{

		};
	};
}



#endif
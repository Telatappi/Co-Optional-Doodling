#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <random>
#include "SceneManager.h"
#include "Scene.h"
#include "Character.h"

//used for RNG no need to touch this
static std::random_device rd;

//used for RNG no need to touch this
static std::mt19937 rng(rd());



namespace core
{
	//game core stuff
	void InitGame();
	void CharacterCreation();
	
	//utility functions		
	int Rand(int x, int y);
	void PrintInventoryFooter();
	void EnterInventory();

	//variables
	SceneManager sceneManager;
	Character player;
}



#endif
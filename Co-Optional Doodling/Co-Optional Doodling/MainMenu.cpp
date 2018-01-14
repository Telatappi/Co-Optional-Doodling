#include "MainMenu.h"
#include <iostream>
#include "Core.h"

MainMenu::MainMenu(SceneManager* _sceneManager, std::string _name, core::Location _location)
	:Scene(_sceneManager, _name, _location)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
}

bool MainMenu::Loop(bool exit)
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
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
	core::Pause();
	PlayerCreation();
	return false;
}

void MainMenu::Uninit()
{
}

void MainMenu::PlayerCreation()
{
	core::ClearScreen();

	Character character;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"          Character Creation\n"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Enter Name:" << std::endl;
	std::string name;
	std::cin >> name;
	character.Name(name);

	std::cout << "Enter Race:" << std::endl;
	std::cout << "Gnome | Elf | Merman | Cat Woman | Werebear";
	do
	{
		std::string race;
		std::cin >> race;
		character.Race(race);
	} while (character.Race() != "gnome"
		&& character.Race() != "elf"
		&& character.Race() != "merman"
		&& character.Race() != "cat woman"
		&& character.Race() != "werebear");

	character.Hp(core::Rand(90, 100));
	character.SetMaxHp(character.Hp());
	character.Agility(core::Rand(8, 12));
	character.Luck(core::Rand(8, 12));
	character.Wisdom(core::Rand(8, 12));
	character.Accuracy(core::Rand(85, 95));
	character.Attack(core::Rand(8, 12));

	if (character.Race() == "gnome")
	{
		int hpMod;
		hpMod = core::Rand(-10, 0);
		character.IncreaseHp(hpMod);
		character.IncreaseAgility(1);
		character.IncreaseLuck(2);
		character.IncreaseWisdom(-1);
		character.IncreaseAccuracy(-5);
		character.Perks("greedy");
	}
	else if (character.Race() == "elf")
	{
		int hpMod;
		hpMod = core::Rand(-5, 0);
		character.IncreaseHp(hpMod);
		character.IncreaseAgility(1);
		character.IncreaseLuck(0);
		character.IncreaseWisdom(1);
		character.IncreaseAccuracy(3);
		character.Perks("night eye");
	}
	else if (character.Race() == "merman")
	{
		int hpMod;
		hpMod = core::Rand(-10, 0);
		character.IncreaseHp(hpMod);
		character.IncreaseAgility(-2);
		character.IncreaseLuck(1);
		character.IncreaseWisdom(0);
		character.IncreaseAccuracy(5);
		character.Perks("slippery");
	}
	else if (character.Race() == "cat woman")
	{
		int hpMod;
		hpMod = core::Rand(-15, 0);
		character.IncreaseHp(hpMod);
		character.IncreaseAgility(2);
		character.IncreaseLuck(-1);
		character.IncreaseWisdom(1);
		character.IncreaseAccuracy(5);
		character.Perks("hips don't lie");
	}
	else if (character.Race() == "werebear")
	{
		int hpMod;
		hpMod = core::Rand(-25, 0);
		character.IncreaseHp(hpMod);
		character.IncreaseAgility(-3);
		character.IncreaseLuck(-1);
		character.IncreaseWisdom(0);
		character.IncreaseAccuracy(-5);
		character.Perks("nature's reserve");
	}

	std::cout << "\nCurrent Character: ";
	std::cout << "\nName: " + character.Name();
	std::cout << "\nRace: " + character.Race();
	std::cout << "\n\n Are you happy with the character?";
	std::cout << "\n y) yes | n) no\n";

	std::string input;
	do
	{
		input = core::GetText();
	} while (input != "y" && input != "yes"
		&& input != "n" && input != "no");

	if (input == "y" || input == "yes")
	{
		core::player = character;
		core::sceneManager.NextRandomScene(core::Location::TRAVELING, core::Location::TEMPPELINRAUNIOT);
		//once all locations have at least one scene use the one below instead
		//core::sceneManager.NextRandomScene(core::Location::TRAVELING, core::GetRandomLocation());
	}
}

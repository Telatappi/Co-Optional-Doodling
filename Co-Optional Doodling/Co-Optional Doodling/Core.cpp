#include "Core.h"
#include <iostream>

Character core::player;
SceneManager core::sceneManager;

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
	Pause();
}

void core::PlayerCreation()
{
	ClearScreen();

	Character character;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				 "          Character Creation\n"
				 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Enter Name:" << std::endl;
	std::cin >> character.Name();
	std::cout << "Enter Race:" << std::endl;
	do
	{
		std::string race;
		std::cin >> race;
		character.Race(race);
	} 
	while (character.Race() != "gnome"
		|| character.Race() != "elf"
		|| character.Race() != "merman"
		|| character.Race() != "cat woman"
		|| character.Race() != "werebear");

	character.Hp(core::Rand(90, 100));
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
	else if(character.Race() == "cat woman")
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

	std::string text;
	text = "\nCurrent Character: ";
	text += "\nName: " + character.Name();
	text += "\nRace: " + character.Race();
	text += "\n\n Are you happy with the character?";
	text += "\n y) yes | n) no";
	core::Text(text);

	std::string input;
	do
	{
		input = core::Input();
	} while (input == "y" || input == "yes"
		|| input == "n" || input == "no");

	if(input == "y" || input == "yes")
	{
		player = character;
		core::sceneManager.NextRandomScene(Location::TRAVELING, Location::AAVIKKO);
	}
	else if (input == "n" || input == "no")
	{
		core::PlayerCreation();
	}
}

Character core::CreateCharacter()
{
	return Character();
}

void core::Print(bool _clearScreen)
{
	if (_clearScreen) // same as if(_clearScreen == true)
	{
		system("cls");
	}

	std::cout << textBuffer;
}

void core::PrintLongTerm(bool _clearScreen)
{
	if (_clearScreen) // same as if(_clearScreen == true)
	{
		system("cls");
	}

	std::cout << longTermTextBuffer;
}

std::string core::Input()
{
	std::string text;
	std::cin >> text;
	
	//check for predetermined commands
	if (text == "!inv") //open inventory
	{
		EnterInventory();
	}
	else if (text == "!help") //get help
	{
		text = "\nthe text you were looking for is in another castle\n";
	}

	//\n means new line, the same way as std::endl;
	//we automatically add new lines so user input 
	// is on it's own line below the possible text
	textBuffer += ("\n" + text + "\n");
	longTermTextBuffer += textBuffer;

	return text;
}

void core::Text(std::string text)
{
	textBuffer += text;
	longTermTextBuffer += text;
}

void core::ClearLongTermTextBuffer()
{
	longTermTextBuffer = "";
}

void core::ClearScreen()
{
	system("cls");
}

int core::Rand(int min, int max)
{
	std::uniform_int_distribution<int> randomNumber(min, max);
	return randomNumber(rng);
}

void core::EnterInventory()
{
	bool exit = false;
	while (exit)
	{
		int counter = 0;
		int page = 0;

		//top of the screen
		Text("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			"				Inventory\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		if (page == 0)
		{
			Text("Equipped:");
			std::string helmet = "Helmet:\nname:" + player.inventory.Slot("helmet").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("helmet").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("helmet").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("helmet").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("helmet").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("helmet").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("helmet").GetAttack())
				+ "typ: " + player.inventory.Slot("helmet").GetType() + "\n";
			core::Text(helmet);

			std::string armor = "Armor:\nname:" + player.inventory.Slot("armor").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("armor").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("armor").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("armor").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("armor").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("armor").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("armor").GetAttack())
				+ "typ: " + player.inventory.Slot("armor").GetType() + "\n";
			core::Text(armor);

			std::string mHand = "main hand:\nname:" + player.inventory.Slot("main hand").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("main hand").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("main hand").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("main hand").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("main hand").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("main hand").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("main hand").GetAttack())
				+ "typ: " + player.inventory.Slot("mHand").GetType() + "\n";
			core::Text(mHand);

			std::string oHand = "off hand:\nname:" + player.inventory.Slot("off hand").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("off hand").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("off hand").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("off hand").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("off hand").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("off hand").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("off hand").GetAttack())
				+ "typ: " + player.inventory.Slot("oHand").GetType() + "\n";
			core::Text(oHand);

			std::string misc1 = "misc1:\nname:" + player.inventory.Slot("misc1").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("misc1").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("misc1").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("misc1").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("misc1").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("misc1").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("misc1").GetAttack())
				+ "typ: " + player.inventory.Slot("misc1").GetType() + "\n";
			core::Text(misc1);

			std::string misc2 = "misc2:\nname:" + player.inventory.Slot("misc2").GetName()
				+ "hp : " + std::to_string(player.inventory.Slot("misc2").GetHp())
				+ "agi: " + std::to_string(player.inventory.Slot("misc2").GetAgility())
				+ "lck: " + std::to_string(player.inventory.Slot("misc2").GetLuck())
				+ "wsd: " + std::to_string(player.inventory.Slot("misc2").GetWisdom())
				+ "acc: " + std::to_string(player.inventory.Slot("misc2").GetAccuracy())
				+ "atk: " + std::to_string(player.inventory.Slot("misc2").GetAttack())
				+ "typ: " + player.inventory.Slot("misc2").GetType() + "\n";
			core::Text(misc2);

			Text("\n\n Items in the inventory");
			for(unsigned int i = 0; (i < player.inventory.GetItems().size() && i < 2); ++i)
			{
				std::string item = "\nItem:\nname:" + player.inventory.GetItems()[i].GetName()
					+ "hp : " + std::to_string(player.inventory.GetItems()[i].GetHp())
					+ "agi: " + std::to_string(player.inventory.GetItems()[i].GetAgility())
					+ "lck: " + std::to_string(player.inventory.GetItems()[i].GetLuck())
					+ "wsd: " + std::to_string(player.inventory.GetItems()[i].GetWisdom())
					+ "acc: " + std::to_string(player.inventory.GetItems()[i].GetAccuracy())
					+ "atk: " + std::to_string(player.inventory.GetItems()[i].GetAttack())
					+ "typ: " + player.inventory.GetItems()[i].GetType() + "\n";
				core::Text(item);
			}

			std::string text = Input();
			++page;
		}
		else
		{
			//top of the screen
			Text("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				"				Inventory\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			Text("\n\n Items in the inventory");
			for (int i = 0; i < page * 8; ++i)
			{
				std::string item = "\nItem:\nname:" + player.inventory.GetItems()[i].GetName()
					+ "hp : " + std::to_string(player.inventory.GetItems()[i].GetHp())
					+ "agi: " + std::to_string(player.inventory.GetItems()[i].GetAgility())
					+ "lck: " + std::to_string(player.inventory.GetItems()[i].GetLuck())
					+ "wsd: " + std::to_string(player.inventory.GetItems()[i].GetWisdom())
					+ "acc: " + std::to_string(player.inventory.GetItems()[i].GetAccuracy())
					+ "atk: " + std::to_string(player.inventory.GetItems()[i].GetAttack())
					+ "typ: " + player.inventory.GetItems()[i].GetType() + "\n";
				core::Text(item);
				
				if ((i + 1) % 8 == 0)
				{
					page++;
				}
			}
		}
	}
	
}

void core::Pause()
{
	fflush(stdin);
	getchar();
}

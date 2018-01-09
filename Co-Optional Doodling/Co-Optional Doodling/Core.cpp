#include "Core.h"
#include <iostream>
#include <algorithm>

Character core::player;
SceneManager core::sceneManager;

const int NO_ITEM_SELECTED = 0;
const int ITEM_SELECTED = 1;

core::COMBAT_OUTCOME core::Combat(std::vector<Character> playerCharacters, std::vector<Character> enemyCharacters)
{
	return core::COMBAT_OUTCOME::PLAYER_VICTORY;
}

core::COMBAT_OUTCOME core::Combat(Character player, Character enemy)
{
	return core::COMBAT_OUTCOME();
}

core::COMBAT_OUTCOME core::Combat(Character player, std::vector<Character> enemies)
{
	
	//int = owner of the unit
	//Character = unit itself
	std::vector<Character> units;

	std::vector<Character*> playerUnits;

	//init combat
	{
		bool sorted = false;

		std::vector<Character>::const_iterator enemiesIt = enemies.begin();
		for (; enemiesIt != enemies.end(); ++enemiesIt)
		{
			units.push_back((*enemiesIt));
		}

		units.push_back(player);
		playerUnits.push_back(&units.back());

		//sort units by their agility, fastest go first
		std::vector<Character>::iterator nextUnitIt = units.begin();
		std::vector<Character>::iterator unitIt = units.begin();		
		do
		{
			sorted = true;
			for (; unitIt != units.end();)
			{
				nextUnitIt = unitIt;
				++nextUnitIt;

				if (nextUnitIt != units.end())
				{
					if ((*unitIt).Agility() < (*nextUnitIt).Agility())
					{
						std::iter_swap(unitIt, nextUnitIt);
						sorted = false;
					}
					else
					{
						++unitIt;
					}
				}
				else
				{
					break;
				}
			}
		} while (!sorted);
	}
	
	//actual combat
	bool combatOver = false;
	
	while (!combatOver)
	{
		//clear screen
		core::ClearScreen();

		//list your character
		std::string text = "Player Units:";
		std::vector<Character>::iterator unitIt = units.begin();
		for (; unitIt != units.end(); ++unitIt)
		{
			if ((*unitIt).GetController() == core::CONTROLLER::PLAYER)
			{
				core::PrintCharacterStats((*unitIt));
			}
		}

		//list enemies
		text = "Enemy Units:";
		unitIt = units.begin();
		for (; unitIt != units.end(); ++unitIt)
		{
			if ((*unitIt).GetController() == core::CONTROLLER::ENEMY)
			{
				core::PrintCharacterStats((*unitIt));
			}
		}

		std::cout << "\nQ) Hit an enemy\n";

		//perform actions
		unitIt = units.begin();
		for (; unitIt != units.end(); ++unitIt)
		{
			if ((*unitIt).GetController() == core::CONTROLLER::PLAYER)
			{
				core::GetKey();
				const int damage = (*unitIt).Attack();
				//add item damage

				std::vector<Character>::iterator enemyIt = units.begin();
				for (; enemyIt != units.end(); ++enemyIt)
				{
					if ((*enemyIt).GetController() == core::CONTROLLER::ENEMY)
					{
						(*enemyIt).IncreaseHp(-damage);
						break;
					}
				}
			}
		}
		
		//delete dead characters
		unitIt = units.begin();
		for (; unitIt != units.end();)
		{
			if ((*unitIt).Hp() < 0)
			{
				unitIt = units.erase(unitIt);
				continue;
			}

			++unitIt;
		}

		//
		int amountOfPlayers = 0;
		int amountOfEnemies = 0;

		unitIt = units.begin();
		for (; unitIt != units.end(); ++unitIt)
		{
			if ((*unitIt).GetController() == core::CONTROLLER::PLAYER)
			{
				++amountOfPlayers;
			}
			else if ((*unitIt).GetController() == core::CONTROLLER::ENEMY)
			{
				++amountOfEnemies;
			}			
		}

		if (amountOfPlayers < 1)
		{
			return core::COMBAT_OUTCOME::PLAYER_DEATH;
		}
		else if (amountOfEnemies < 1)
		{
			return core::COMBAT_OUTCOME::PLAYER_VICTORY;
		}
	}
}

core::COMBAT_OUTCOME core::Combat(std::vector<Character> playerCharacters, Character enemy)
{
	return core::COMBAT_OUTCOME();
}

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
	PlayerCreation();
}

void core::PlayerCreation()
{
	ClearScreen();

	Character character;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				 "          Character Creation\n"
				 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Enter Name:" << std::endl;
	std::string name;
	std::cin >> name;
	character.Name(name);

	std::cout << "Enter Race:" << std::endl;
	do
	{
		std::string race;
		std::cin >> race;
		character.Race(race);
	} 
	while (character.Race() != "gnome"
		&& character.Race() != "elf"
		&& character.Race() != "merman"
		&& character.Race() != "cat woman"
		&& character.Race() != "werebear");

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

	if(input == "y" || input == "yes")
	{
		player = character;
		core::sceneManager.NextRandomScene(Location::TRAVELING, Location::TEMPPELINRAUNIOT);
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

void core::ClearScreen()
{
#ifdef _WIN32
	system("cls");
#elif __linux__

#endif
}

void core::PrintCharacterStats(Character _character)
{
	if (_character.GetController() == core::CONTROLLER::PLAYER)
	{
		std::cout << "\nName: " << _character.Name()
			<< " | Race: " << _character.Race()
			<< "\nHp: " << _character.Hp()
			<< " | Agi: " << _character.Agility()
			<< " | Lck: " << _character.Luck()
			<< "\nWis: " << _character.Wisdom()
			<< " | Acc: " << _character.Accuracy()
			<< " | Atk: " << _character.Attack()
			<< "\n";
	}
	else
	{
		std::cout << "\nName: " << _character.Name();
		std::cout << " | Race: " << _character.Race();
		std::cout << "\nHp: " << _character.Hp();
	}
}

std::string core::GetText()
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
	// is shown on it's own line
	std::cout << "\n" + text + "\n";
	return text;
}

int core::GetKey()
{
	int key;
	key = getchar();
	fflush(stdin);

	if (key == EOF)
	{
		return 0;
	}
	return key;
}

int core::Rand(int min, int max)
{
	std::uniform_int_distribution<int> randomNumber(min, max);
	return randomNumber(rng);
}

void core::EnterInventory()
{
	bool exit = false;
	int counter = 0;
	int page = 0;
	int depth = 0;
	int selectedItem = -1;

	while (exit)
	{
		//top of the screen
		std::cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				  <<"				Inventory\n"
				  <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		switch (depth)
		{
			case NO_ITEM_SELECTED:
			{
				if (page == 0)
				{
					std::cout << "Equipped:\n";
					std::cout <<  "Helmet:"
						<< "\nname:" + player.inventory.Slot("helmet").GetName()
						<< "\nhp : " + std::to_string(player.inventory.Slot("helmet").GetHp())
						<< "\nagi: " + std::to_string(player.inventory.Slot("helmet").GetAgility())
						<< "\nlck: " + std::to_string(player.inventory.Slot("helmet").GetLuck())
						<< "\nwsd: " + std::to_string(player.inventory.Slot("helmet").GetWisdom())
						<< "\nacc: " + std::to_string(player.inventory.Slot("helmet").GetAccuracy())
						<< "\natk: " + std::to_string(player.inventory.Slot("helmet").GetAttack())
						<< "\ntyp: " + player.inventory.Slot("helmet").GetType() + "\n";

					std::cout << "Armor:\n"
						<<"name:" + player.inventory.Slot("armor").GetName()
						<< "hp : " + std::to_string(player.inventory.Slot("armor").GetHp())
						<< "agi: " + std::to_string(player.inventory.Slot("armor").GetAgility())
						<< "lck: " + std::to_string(player.inventory.Slot("armor").GetLuck())
						<< "wsd: " + std::to_string(player.inventory.Slot("armor").GetWisdom())
						<< "acc: " + std::to_string(player.inventory.Slot("armor").GetAccuracy())
						<< "atk: " + std::to_string(player.inventory.Slot("armor").GetAttack())
						<< "typ: " + player.inventory.Slot("armor").GetType() + "\n";

					std::cout << "main hand:\n"
						<< "name:" + player.inventory.Slot("main hand").GetName()
						<< "hp : " + std::to_string(player.inventory.Slot("main hand").GetHp())
						<< "agi: " + std::to_string(player.inventory.Slot("main hand").GetAgility())
						<< "lck: " + std::to_string(player.inventory.Slot("main hand").GetLuck())
						<< "wsd: " + std::to_string(player.inventory.Slot("main hand").GetWisdom())
						<< "acc: " + std::to_string(player.inventory.Slot("main hand").GetAccuracy())
						<< "atk: " + std::to_string(player.inventory.Slot("main hand").GetAttack())
						<< "typ: " + player.inventory.Slot("mHand").GetType() + "\n";

					std::cout << "off hand:\n"
						<< "name:" + player.inventory.Slot("off hand").GetName()
						<< "hp : " + std::to_string(player.inventory.Slot("off hand").GetHp())
						<< "agi: " + std::to_string(player.inventory.Slot("off hand").GetAgility())
						<< "lck: " + std::to_string(player.inventory.Slot("off hand").GetLuck())
						<< "wsd: " + std::to_string(player.inventory.Slot("off hand").GetWisdom())
						<< "acc: " + std::to_string(player.inventory.Slot("off hand").GetAccuracy())
						<< "atk: " + std::to_string(player.inventory.Slot("off hand").GetAttack())
						<< "typ: " + player.inventory.Slot("oHand").GetType() + "\n";

					std::cout << "misc1:\n"
						<< "name:" + player.inventory.Slot("misc1").GetName()
						<< "hp : " + std::to_string(player.inventory.Slot("misc1").GetHp())
						<< "agi: " + std::to_string(player.inventory.Slot("misc1").GetAgility())
						<< "lck: " + std::to_string(player.inventory.Slot("misc1").GetLuck())
						<< "wsd: " + std::to_string(player.inventory.Slot("misc1").GetWisdom())
						<< "acc: " + std::to_string(player.inventory.Slot("misc1").GetAccuracy())
						<< "atk: " + std::to_string(player.inventory.Slot("misc1").GetAttack())
						<< "typ: " + player.inventory.Slot("misc1").GetType() + "\n";

					std::cout <<"misc2:\n"
						<< "name:" + player.inventory.Slot("misc2").GetName()
						<< "hp : " + std::to_string(player.inventory.Slot("misc2").GetHp())
						<< "agi: " + std::to_string(player.inventory.Slot("misc2").GetAgility())
						<< "lck: " + std::to_string(player.inventory.Slot("misc2").GetLuck())
						<< "wsd: " + std::to_string(player.inventory.Slot("misc2").GetWisdom())
						<< "acc: " + std::to_string(player.inventory.Slot("misc2").GetAccuracy())
						<< "atk: " + std::to_string(player.inventory.Slot("misc2").GetAttack())
						<< "typ: " + player.inventory.Slot("misc2").GetType() + "\n";

					std::cout << "\n\n Items in the inventory";
					for (unsigned int i = 0; (i < player.inventory.GetItems().size() && i < 2); ++i)
					{
						std::cout << "\nItem:\n"
							<< "name:" + player.inventory.GetItems()[i].GetName()
							<< "hp : " + std::to_string(player.inventory.GetItems()[i].GetHp())
							<< "agi: " + std::to_string(player.inventory.GetItems()[i].GetAgility())
							<< "lck: " + std::to_string(player.inventory.GetItems()[i].GetLuck())
							<< "wsd: " + std::to_string(player.inventory.GetItems()[i].GetWisdom())
							<< "acc: " + std::to_string(player.inventory.GetItems()[i].GetAccuracy())
							<< "atk: " + std::to_string(player.inventory.GetItems()[i].GetAttack())
							<< "typ: " + player.inventory.GetItems()[i].GetType() + "\n";
					}
					std::string text = GetText();
					++page;
				}
				else
				{
					std::cout << "\n\n Items in the inventory";
					for (unsigned int i = 0; (i + 2) < player.inventory.GetItems().size() && i < 8; ++i)
					{
						std::cout << "\nItem:"
							<< "\nname:" + player.inventory.GetItems()[(8 * page) + (2 + i)].GetName()
							<< "hp : " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetHp())
							<< "agi: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAgility())
							<< "lck: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetLuck())
							<< "wsd: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetWisdom())
							<< "acc: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAccuracy())
							<< "atk: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAttack())
							<< "typ: " + player.inventory.GetItems()[(8 * page) + (2 + i)].GetType() + "\n";

						if (i % 7 == 0)
						{
							page++;

						}
					}
				}
				break;
			}
			case ITEM_SELECTED:
			{
				std::cout << "\nItem:"
					<< "\nname:" + player.inventory.GetItems()[selectedItem].GetName()
					<< "hp : " + std::to_string(player.inventory.GetItems()[selectedItem].GetHp())
					<< "agi: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAgility())
					<< "lck: " + std::to_string(player.inventory.GetItems()[selectedItem].GetLuck())
					<< "wsd: " + std::to_string(player.inventory.GetItems()[selectedItem].GetWisdom())
					<< "acc: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAccuracy())
					<< "atk: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAttack())
					<< "typ: " + player.inventory.GetItems()[selectedItem].GetType() + "\n";
				break;
			}
			default:
				break;
		}

		std::cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << "1) Back";
		for (int i = 0; i < 6; ++i)
		{
			std::cout << " | " << i << ")" << player.inventory.GetItems()[i].GetName();
		}
		if (player.inventory.GetItems().size() > 6)
		{
			std::cout << " 0) next page\n";
		}
		
		switch (depth)
		{
		case NO_ITEM_SELECTED:
			{
				//input
				int input;
				input = GetKey();
				switch (input)
				{
					case 1:
					{
						if (page == 0)
						{
							//exit inventory
						}
						else
						{
							--page;
						}
						break;
					}
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
					{
						selectedItem = input;
						depth = ITEM_SELECTED;
						break;
					}
					case 0:
					{
						//next page of items
						break;
					}
				default:
					break;
				}
				
				break;
			}
			case ITEM_SELECTED:
			{
				break;
			}
			default:
				break;
		}
	}
	
	core::ClearScreen();
}

void core::Pause()
{
	fflush(stdin);
	getchar();
}

#include "Core.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <iostream>

Character core::player;
SceneManager core::sceneManager;

const int NO_ITEM_SELECTED = 0;
const int ITEM_SELECTED = 1;

core::COMBAT_OUTCOME core::Combat(std::vector<Character>& playerCharacters, std::vector<Character>& enemyCharacters)
{
	return core::COMBAT_OUTCOME::PLAYER_VICTORY;
}

core::COMBAT_OUTCOME core::Combat(Character& player, Character& enemy)
{
	return core::COMBAT_OUTCOME();
}

core::COMBAT_OUTCOME core::Combat(Character& player, std::vector<Character>& enemies)
{
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

		//sort units by their agility, fastest goes first
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

		//TODO: SELECT ENEMY TO HIT
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
						(*enemyIt).IncreaseHp((-damage));
						break;
					}
				}
			}
		}

		//delete dead characters
		unitIt = units.begin();
		for (; unitIt != units.end();)
		{ 
			if ((*unitIt).Hp() < 1)
			{
				//units.erase returns next unit from the vector
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

	return core::COMBAT_OUTCOME::PLAYER_VICTORY;
}

core::COMBAT_OUTCOME core::Combat(std::vector<Character>& playerCharacters, Character& enemy)
{
	return core::COMBAT_OUTCOME();
}

void core::InitGame()
{
	std::string menuName = "MainMenu";
	sceneManager.LoadScene(menuName);
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

void core::PrintCharacterStats(Character& _character)
{
	if (_character.GetController() == core::CONTROLLER::PLAYER)
	{
		std::cout << "\nName: " << _character.Name();
		std::cout << " | Race: " << _character.Race();
		std::cout << "\nHp: " << _character.Hp();
		std::cout << " | Agi: " << _character.Agility();
		std::cout << " | Lck: " << _character.Luck();
		std::cout << "\nWis: " << _character.Wisdom();
		std::cout << " | Acc: " << _character.Accuracy();
		std::cout << " | Atk: " << _character.Attack();
		std::cout << "\n";
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
	std::cout << "type !help for help\n";
	std::string text;
	std::cin >> text;
	
	//check for predetermined commands
	if (text == "!inv") //open inventory
	{
		EnterInventory();
	}
	else if (text == "!help") //get help
	{
		std::cout <<"[!inv] = Enter Inventory\n";
	}

	return text;
}

int core::GetKey()
{
	int key;
	do
	{
		std::cin.sync();
		key = getchar();
	} while (key == EOF || key == '\n');

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

	while (!exit)
	{
		//top of the screen
		system("cls");
		std::cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				  <<"               Inventory               \n"
				  <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		switch (depth)
		{
			case NO_ITEM_SELECTED:
			{
				if (page == 0)
				{
					std::cout << "Equipped:\n";
					std::cout <<  "Helmet:\n"
						<< "[Name:" + player.inventory.Slot("helmet").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("helmet").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("helmet").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("helmet").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("helmet").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("helmet").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("helmet").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("helmet").GetType() + "]\n";

					std::cout << "Armor:\n"
						<< "[Name:" + player.inventory.Slot("armor").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("armor").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("armor").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("armor").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("armor").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("armor").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("armor").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("armor").GetType() + "]\n";

					std::cout << "Main hand:\n"
						<< "[Name:" + player.inventory.Slot("main hand").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("main hand").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("main hand").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("main hand").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("main hand").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("main hand").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("main hand").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("mHand").GetType() + "]\n";

					std::cout << "Off hand:\n"
						<< "[Name:" + player.inventory.Slot("off hand").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("off hand").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("off hand").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("off hand").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("off hand").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("off hand").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("off hand").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("oHand").GetType() + "]\n";

					std::cout << "Misc 1:\n"
						<< "[Name:" + player.inventory.Slot("misc1").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("misc1").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("misc1").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("misc1").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("misc1").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("misc1").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("misc1").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("misc1").GetType() + "]\n";

					std::cout <<"Misc 2:\n"
						<< "[Name:" + player.inventory.Slot("misc2").GetName() << "]"
						<< "[Hp : " + std::to_string(player.inventory.Slot("misc2").GetHp()) << "]"
						<< "[Agi: " + std::to_string(player.inventory.Slot("misc2").GetAgility()) << "]"
						<< "[Lck: " + std::to_string(player.inventory.Slot("misc2").GetLuck()) << "]"
						<< "[Wsd: " + std::to_string(player.inventory.Slot("misc2").GetWisdom()) << "]"
						<< "[Acc: " + std::to_string(player.inventory.Slot("misc2").GetAccuracy()) << "]"
						<< "[Atk: " + std::to_string(player.inventory.Slot("misc2").GetAttack()) << "]"
						<< "[Typ: " + player.inventory.Slot("misc2").GetType() + "]\n";

					std::cout << "\nItems in the inventory\n";
					for (unsigned int i = 0; (i < player.inventory.GetItems().size() && i < 5); ++i)
					{
						std::cout <<"[Name:" + player.inventory.GetItems()[i].GetName() << "]"
								  << "[Hp : " + std::to_string(player.inventory.GetItems()[i].GetHp()) << "]"
								  << "[Agi: " + std::to_string(player.inventory.GetItems()[i].GetAgility()) << "]"
								  << "[Lck: " + std::to_string(player.inventory.GetItems()[i].GetLuck()) << "]"
								  << "[Wsd: " + std::to_string(player.inventory.GetItems()[i].GetWisdom()) << "]"
								  << "[Acc: " + std::to_string(player.inventory.GetItems()[i].GetAccuracy()) << "]"
								  << "[Atk: " + std::to_string(player.inventory.GetItems()[i].GetAttack()) << "]"
								  << "[Typ: " + player.inventory.GetItems()[i].GetType() + "]\n";
					}
					std::string text = GetText();
					++page;
				}
				else
				{
					std::cout << "\nItems in the inventory: \n";
					for (unsigned int i = 0; (i + 2) < player.inventory.GetItems().size() && i < 8; ++i)
					{
					  std::cout << "[Name:" + player.inventory.GetItems()[(8 * page) + (2 + i)].GetName() << "]"
								<< "[Hp : " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetHp()) << "]"
								<< "[Agi: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAgility()) << "]"
								<< "[Lck: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetLuck()) << "]"
								<< "[Wsd: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetWisdom()) << "]"
								<< "[Acc: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAccuracy()) << "]"
								<< "[Atk: " + std::to_string(player.inventory.GetItems()[(8 * page) + (2 + i)].GetAttack()) << "]"
								<< "[Typ: " + player.inventory.GetItems()[(8 * page) + (2 + i)].GetType() + "]\n";

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
				std::cout << "\nItem:\n"
					<< "[Name:" + player.inventory.GetItems()[selectedItem].GetName() << "]"
					<< "[Hp : " + std::to_string(player.inventory.GetItems()[selectedItem].GetHp()) << "]"
					<< "[Agi: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAgility()) << "]"
					<< "[Lck: " + std::to_string(player.inventory.GetItems()[selectedItem].GetLuck()) << "]"
					<< "[Wsd: " + std::to_string(player.inventory.GetItems()[selectedItem].GetWisdom()) << "]"
					<< "[Acc: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAccuracy()) << "]"
					<< "[Atk: " + std::to_string(player.inventory.GetItems()[selectedItem].GetAttack()) << "]"
					<< "[Typ: " + player.inventory.GetItems()[selectedItem].GetType() + "]\n";
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
	std::cout << "Press enter to continue\n";
	int c = 0;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

core::Location core::GetRandomLocation()
{
	core::Location location = static_cast<core::Location>(
		Rand(0, static_cast<int>(core::Location::NUMBEROFLOCATIONS)));

	switch (location)
	{
		case core::Location::BLACKRIVER:
		{
			return core::Location::BLACKRIVER;
			break;
		}
		case core::Location::DUSSELDWARF:
		{
			return core::Location::DUSSELDWARF;
			break;
		}
		case core::Location::TEMPPELINRAUNIOT:
		{
			return core::Location::TEMPPELINRAUNIOT;
			break;
		}
		case core::Location::TASANKO:
		{
			return core::Location::TASANKO;
			break;
		}
		case core::Location::AAVIKKO:
		{
			return core::Location::AAVIKKO;
			break;
		}
		case core::Location::SAMMUNUTTULIVUORI:
		{
			return core::Location::SAMMUNUTTULIVUORI;
			break;
		}
		case core::Location::TRAVELING:
		{
			return core::Location::TRAVELING;
			break;
		}
		default:
			break;
	}

	return Location();
}

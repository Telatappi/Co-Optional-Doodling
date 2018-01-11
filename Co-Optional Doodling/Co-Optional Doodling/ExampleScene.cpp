#include "ExampleScene.h"
#include "Core.h"
#include <iostream>

ExampleScene::ExampleScene(SceneManager* _sceneManager, std::string _name, core::Location _location)
	:Scene(_sceneManager, _name, _location),
	m_scenePart(SCENEPART::BEGINNING),
	m_partDepth(PARTDEPTH::BEGINNING)
{
	
}

ExampleScene::~ExampleScene()
{
}

void ExampleScene::Init()
{
}

bool ExampleScene::Loop(bool exit)
{
	std::string answer;
	switch(m_scenePart)
	{
	case SCENEPART::BEGINNING:
		{
			switch (m_partDepth)
			{
				case PARTDEPTH::BEGINNING:
				{
					std::cout << "\nYou open your eyes as you feel something slimy on your cheek.";
					std::cout << "\nYou hit your back to ground as you fall from a tree.";
					std::cout << "\nAs you gather your lump body from the ground, two linen wrapped figures appear from the distance";
					std::cout << "\nYou decide to:\n";
					std::cout << "Q) Wait and see what happens\n";
					std::cout << "E) Run away\n";
					answer = core::GetText();
					if (answer == "Q" || answer == "q")
					{
						m_partDepth = PARTDEPTH::MIDDLE;
					}
					else if (answer == "E" || answer == "e")
					{
						m_partDepth = PARTDEPTH::BEGINNING;
						m_scenePart = SCENEPART::END;
					}
					break;
				}
				case PARTDEPTH::MIDDLE:
				{
					std::cout << "You decided to stand and wait for the creatures to come by.";
					std::cout << "\nAs they walk to you one of them unveils it's mouth which was covered in a linen wrap.";
					std::cout << "\n'Stop right there you criminal scum!' they yell.";
					std::cout << "\nYou decide to answer with:";
					std::cout << "\nQ) Unseath your weapon and get ready for battle.";
					std::cout << "\nE) Try to run away\n";
					answer = core::GetText();
					if (answer == "Q" || answer == "q")
					{
						m_partDepth = PARTDEPTH::BEGINNING;
						m_scenePart = SCENEPART::COMBAT;
					}
					else if (answer == "E" || answer == "e")
					{
						m_partDepth = PARTDEPTH::BEGINNING;
						m_scenePart = SCENEPART::END;
					}
					break;
				}
				default:
					break;
			}
			break;
		}
	case SCENEPART::COMBAT:
		{
			switch (m_partDepth)
			{
				case PARTDEPTH::BEGINNING:
				{
					for (int i = 0; i < 2; ++i)
					{
						Character enemy;
						enemy.Name("thug");
						enemy.Race("human");
						enemy.Hp(core::Rand(10, 100));
						enemy.SetMaxHp(enemy.Hp());
						enemy.Agility(core::Rand(1, 10));
						enemy.Luck(core::Rand(1, 10));
						enemy.Wisdom(core::Rand(1, 10));
						enemy.Accuracy(core::Rand(1, 10));
						enemy.Attack(core::Rand(1, 10));
						enemy.SetController(core::CONTROLLER::ENEMY);
						m_enemies.push_back(enemy);
					}
					m_partDepth = PARTDEPTH::MIDDLE;
					break;
				}
				case PARTDEPTH::MIDDLE:
				{
					m_combatOutcome = core::Combat(core::player, m_enemies);
					m_partDepth = PARTDEPTH::END;
					break;
				}
				case PARTDEPTH::END:
				{
					std::string endText;
					if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_VICTORY)
					{
						//TODO: pause
						std::cout << "\nYou won the combat.\n";
						//load next scene
					}
					else if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_DEATH
						|| m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_ESCAPE)
					{
						std::cout << "\nYou died.\n";
						//load next scene
					}
					break;
				}
				default:
					break;
			}
			break;
		}
	case SCENEPART::END:
		{
			switch (m_partDepth)
			{
				case PARTDEPTH::BEGINNING:
				{
					if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_VICTORY)
					{
						std::cout << "You slayed the puny mummiefied robbers!\n";
						std::cout << "You lean forward to enjoy the spoils of victory,";
						std::cout << "to gather what the robbers left.\n";
						std::cout << "You pick up a necklace with stone attached to it.\n";
						std::cout << "The stone shimmers with a dim blue light";
						std::cout << "As the neclace disappears into your pocket,\n";
						std::cout << "you first hear a silent hissing sound, followed by a cracking noise.\n";
						std::cout << "the pocket feels chill suddenly and as you pick up the necklace your eyes\n";
						std::cout << "lock onto the necklace. The stone is now a common grey stone.\n";
						std::cout << "Not only that, but you can see a large crack on it's surface.\n";
						std::cout << "It must have contained something to keep those foul beasts together.\n";
						std::cout << "No more of any value in the market, you throw it away frustrated.\n";
						std::cout << "As the common necklace hits ground, it doesn't even let out a satisfying clank.\n";
						std::cout << "Now, feeling insulted, you finally leave the scene.\n";
					}
					else if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_ESCAPE)
					{
						std::cout << "One of the creatures lunges forward with his arm straightened for a stab.\n";
						std::cout << "You dodge to its right. Unable to recover quickly enough,\n";
						std::cout << "you get an opportunity to strike. But as you've been looking for\n";
						std::cout << "an opportunity to esape, you waste no time to finish off the creature.\n";
						std::cout << "Instead you push some more momentum to the creature, toppling it over.\n";
						std::cout << "You hear a loud 'thump'. The other stands there, waiting for a strike,\n";
						std::cout << "but instead you sprint off. When it finally reacts, you've gained a safe distance.\n";
						std::cout << "You escape scared but alive.\n";
					}
					else if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_DEATH)
					{
						std::cout << "You see the oportunity to strike. Now is you time. You swing your weapon.\n";
						std::cout << "Sudden panic fills your mind as you feel your leg slip.\n";
						std::cout << "Your blood had covered a stone, making it all slippery.\n";
						std::cout << "As you start to fall down, you swing your sword from side to side,\n";
						std::cout << "trying to fend them off. But your clumsy strikes are easily cast aside.\n";
						std::cout << "You start to scream in panic as one of the living deads strikes with its sword.\n";
						std::cout << "You start coughing blood as the blade pushes deeper into your lung.\n";
						std::cout << "Your vision blurs,\n";
						std::cout << "your weapon falls off from your grip just as you feel another blade enter your body\n";
						std::cout << "Within seconds all the pain is gone. You're dead.";
					}
					break;
				}
				case PARTDEPTH::END:
				{
					break;
				}
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
	return exit;
}

void ExampleScene::Uninit()
{
}

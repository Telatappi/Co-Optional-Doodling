#include "ExampleScene.h"
#include "Core.h"
#include <iostream>

ExampleScene::ExampleScene(SceneManager* _sceneManager, std::string _name, core::Location _location)
	:Scene(_sceneManager, _name, _location),
	m_scenePart(SCENEPART::BEGINNING),
	m_partDepth(PARTDEPTH::BEGINNING),
	m_rng(0),
	m_used(false),
	m_escape(ESCAPE::DIDNT)
{
	
}

ExampleScene::~ExampleScene()
{
}

void ExampleScene::Init()
{
	Item item1;
	item1.SetName("Pointy Stick");
	item1.SetHp(0);
	item1.SetAgility(1);
	item1.SetLuck(2);
	item1.SetWisdom(0);
	item1.SetAccuracy(-5);
	item1.SetAttack(1);
	item1.SetType("Spear");
	core::player.inventory.AddItemToInventory(item1);

	Item item2;
	item2.SetName("Rock of Forgetfulness");
	item2.SetHp(0);
	item2.SetAgility(-2);
	item2.SetLuck(8);
	item2.SetWisdom(-2);
	item2.SetAccuracy(-8);
	item2.SetAttack(-2);
	item2.SetType("Amulet");
	core::player.inventory.AddItemToInventory(item2);

	Item item3;
	item3.SetName("Wooden shield");
	item3.SetHp(8);
	item3.SetAgility(-1);
	item3.SetLuck(0);
	item3.SetWisdom(0);
	item3.SetAccuracy(0);
	item3.SetAttack(-1);
	item3.SetType("Shield");
	core::player.inventory.AddItemToInventory(item3);

	Item item4;
	item4.SetName("Thumb Splatter");
	item4.SetHp(0);
	item4.SetAgility(-1);
	item4.SetLuck(0);
	item4.SetWisdom(0);
	item4.SetAccuracy(0);
	item4.SetAttack(2);
	item4.SetType("Hammer");
	core::player.inventory.AddItemToInventory(item4);

	Item item5;
	item5.SetName("Potion of Hobbler the Experimentalist");
	item5.SetHp(core::Rand(-5, 5));
	item5.SetAgility(core::Rand(-5, 5));
	item5.SetLuck(core::Rand(-5, 5));
	item5.SetWisdom(core::Rand(-5, 5));
	item5.SetAccuracy(core::Rand(-5, 5));
	item5.SetAttack(core::Rand(-5, 5));
	item5.SetType("Potion");
	core::player.inventory.AddItemToInventory(item5);

	Item item6;
	item6.SetName("Helmet of Hungry Weasels");
	item6.SetHp(0);
	item6.SetAgility(5);
	item6.SetLuck(2);
	item6.SetWisdom(-2);
	item6.SetAccuracy(-5);
	item6.SetAttack(1);
	item6.SetType("Helmet");
	core::player.inventory.AddItemToInventory(item6);

	Item item7;
	item7.SetName("Bag of Hurdledoo");
	item7.SetHp(core::Rand(0, 1));
	item7.SetAgility(core::Rand(0, 1));
	item7.SetLuck(core::Rand(0, 1));
	item7.SetWisdom(core::Rand(-5, 1));
	item7.SetAccuracy(core::Rand(0, 1));
	item7.SetAttack(1);
	item7.SetType("Bag");
	core::player.inventory.AddItemToInventory(item7);

	Item item8;
	item8.SetName("Armor of Sluggishness");
	item8.SetHp(20);
	item8.SetAgility(-2);
	item8.SetLuck(0);
	item8.SetWisdom(0);
	item8.SetAccuracy(0);
	item8.SetAttack(0);
	item8.SetType("Armor");
	core::player.inventory.AddItemToInventory(item8);
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
						m_escape = ESCAPE::RANAWAY;
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
						m_escape = ESCAPE::TRIED;
					}
					core::Pause();
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
					core::Pause();
					break;
				}
				case PARTDEPTH::END:
				{
					m_partDepth = PARTDEPTH::BEGINNING;
					m_scenePart = SCENEPART::END;
					break;
				}
				default:
					break;
			}
			break;
		}
		case SCENEPART::END:
		{
			core::ClearScreen();
			switch (m_partDepth)
			{
				case PARTDEPTH::BEGINNING:
				{
					if (m_combatOutcome == core::COMBAT_OUTCOME::PLAYER_VICTORY)
					{
						if (!m_used)
						{
							m_rng = core::Rand(0, 1);
							m_used = true;
						}
						if (m_rng == 0)
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
						else
						{
							std::cout << "Even when you're on your limits, the two creatures don't seem\n";
							std::cout << "even slightly fatigued. Before you can step futher in your thoughts\n";
							std::cout << "one of the decaying creatures goes for a swing.\n";
							std::cout << "You manage to deflect the strike and guide its blade on the side.\n";
							std::cout << "This is perhaps your only chance to land a good strike you think.\n";
							std::cout << "But even before the thought has completed in your mind you go for a strike.\n";
							std::cout << "Your blade cuts into its right shoulder. The situation surprises even you\n";
							std::cout << "as the resistant of the creatures body seems to be a lot less than that of a living body.\n";
							std::cout << "Even though the blade doesn't cut the limb clean the sword falls from the creature's grip.\n";
							std::cout << "The wreck of a creatures lets out a shrieking voice mimicing a creature in pain.\n";
							std::cout << "The one still fully functioning prepares for a strike, but you dodge right,\n";
							std::cout << "Leaving the disabled creture between you and the fully functioning one.\n";
							std::cout << "You prepare another strike. This time with the power of full body.\n";
							std::cout << "You rotate your body as you unleash your full rath on the creature.\n";
							std::cout << "Your blade rips its head right off, sending it towards the one behind.\n";
							std::cout << "The one in front falls apart as the magic is no more holding the body together.\n";
							std::cout << "The unattached head sprints through the air like a boulder from a trebuchet.\n";
							std::cout << "Remaining monster manages to take a step towards you before the head hits its chest\n";
							std::cout << "Loud cracking noises fill the air as the head penetrates creature's ribcase.\n";
							std::cout << "The creature collapses immediately as it's impaled by its comrade's head.\n";
							std::cout << "You look the bizarre sight for a second before turning away.\n";
						}

						core::Pause();
						//load next scene
						core::sceneManager.NextRandomScene(core::Location::TRAVELING, core::Location::TEMPPELINRAUNIOT);
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

						core::Pause();
						//load next scene
						core::sceneManager.NextRandomScene(core::Location::TRAVELING, core::Location::TEMPPELINRAUNIOT);
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

						core::Pause();
						//load next scene
						std::string menuText = "mainMenu";
						core::sceneManager.LoadScene(menuText);
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
	m_partDepth = PARTDEPTH::BEGINNING;
	m_scenePart = SCENEPART::BEGINNING;
}

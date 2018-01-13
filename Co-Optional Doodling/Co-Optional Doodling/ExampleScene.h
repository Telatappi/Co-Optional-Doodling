#ifndef EXAMPLESCENE_H
#define EXAMPLESCENE_H

#include "Scene.h"
#include <vector>

class Character;
namespace core
{
	enum class COMBAT_OUTCOME;
}

class ExampleScene : public Scene
{
public:
	ExampleScene(SceneManager* sceneManager, std::string name, core::Location location);
	~ExampleScene();
	//init this scene
	void Init();
	//This is where the action happens in a scene
	bool Loop(bool exit);
	//do something before the scene ends
	void Uninit();
private:	
	enum class SCENEPART
	{
		BEGINNING,
		COMBAT,
		END
	};

	enum class PARTDEPTH
	{
		BEGINNING,
		MIDDLE,
		END
	};

	enum class ESCAPE
	{
		RANAWAY,
		TRIED,
		DIDNT
	};

	SCENEPART m_scenePart;
	PARTDEPTH m_partDepth;
	std::vector<Character> m_enemies;
	core::COMBAT_OUTCOME m_combatOutcome;
	int m_rng;
	bool m_used;
	ESCAPE m_escape;
};

#endif
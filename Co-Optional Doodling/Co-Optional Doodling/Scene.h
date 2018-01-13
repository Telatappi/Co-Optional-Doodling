#ifndef SCENE_H
#define SCENE_H

#include <string>

class SceneManager;

namespace core
{
	enum class Location
	{
		BLACKRIVER,
		DUSSELDWARF,
		TEMPPELINRAUNIOT,
		TASANKO,
		AAVIKKO,
		SAMMUNUTTULIVUORI,
		TRAVELING,

		//NOTE! Add locations above!
		//the ones below are special ones 
		//and you should not add anything there
		NUMBEROFLOCATIONS,
		NOTALOCATION,
	};
}

class Scene
{
public:
	Scene(SceneManager* sceneManager, std::string name, core::Location location);
	~Scene();

	//init this scene
	virtual void Init() = 0;
	//This is where the action happens in a scene
	virtual bool Loop(bool exit = false) = 0;
	//do something before the scene ends
	virtual void Uninit() = 0;

	//get the name of this scene
	std::string GetName() const;

	//move to a new random scene
	//based on m_location and m_targetrLocation
	void NextRandomScene();

	//move to a new scene based on m_linkedSceneName
	void NextLinkedScene();

	//set scene that should follow this scene
	void SetLinkedScene(std::string linkedSceneName);

	//set how likely this scene is to happen
	//default value = 100
	void SetOccuringPropability(int& newPropability);

	//set where the player wants to travel from this scene.
	//needs to be set before we change the current scene
	void SetSceneTarget(core::Location targetLocation);

	//get how likely this scene is to happen
	int GetOccuringPropability() const;

	//get the location where this scene happens
	core::Location GetLocation() const;

private:
	std::string m_linkedSceneName;
	std::string m_name;
	core::Location m_location;
	core::Location m_targetLocation;
	SceneManager* m_sceneManager;
	int m_occuringPropability;
};



#endif
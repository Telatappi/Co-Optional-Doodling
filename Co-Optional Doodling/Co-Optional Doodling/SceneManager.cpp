#include <algorithm>
#include "SceneManager.h"
#include "Core.h"

//include your scene here
#include "ExampleScene.h"

SceneManager::SceneManager()
	:m_exit(false)
{
	InitScenes();
}

SceneManager::~SceneManager()
{
	std::vector<Scene*>::iterator scene = m_scenes.begin();
	for (; scene != m_scenes.end(); ++scene)
	{
		(*scene)->Uninit();
		delete (*scene);
		scene = m_scenes.erase(scene);
	}
}

bool SceneManager::LoopActiveScene()
{
	return m_activeScene->Loop(m_exit);
}

void SceneManager::NextRandomScene(core::Location _previousLocation, core::Location _targetLocation)
{
	//1st val = scene position in scenes array
	//2nd val = scene name
	std::vector<std::string> possibleScenesNames;
	//tracks individual values of random
	int* scenes = new int[m_scenes.size()];
	//fill scenes array with 0s
	std::fill_n(scenes, m_scenes.size(), 0);
	
	//tracks total value of random
	int randomTotal = 0;

	//Go through all the scenes and check which are accessible from current scenev.
	std::vector<Scene*>::const_iterator scene = m_scenes.begin();

	//get a scene from the same place
	unsigned int possibleSceneCounter = 0;
	for (; scene != m_scenes.end(); ++scene)
	{
		if (_previousLocation == _targetLocation)
		{
			//since location is the same we left from, there won't be traveling events
			if ((*scene)->GetLocation() == _targetLocation)
			{
				scenes[possibleSceneCounter] = (*scene)->GetOccuringPropability();
				++possibleSceneCounter;
				randomTotal += (*scene)->GetOccuringPropability();
				possibleScenesNames.push_back((*scene)->GetName());				
			}
		}
		else
		{
			//also accept all traveling events
			if ((*scene)->GetLocation() == _targetLocation || (*scene)->GetLocation() == core::Location::TRAVELING)
			{
				scenes[possibleSceneCounter] = (*scene)->GetOccuringPropability();
				++possibleSceneCounter;
				randomTotal += (*scene)->GetOccuringPropability();
				possibleScenesNames.push_back((*scene)->GetName());				
			}
		}
	}

	//Find the scene we selected
	int rng = core::Rand(0, randomTotal);
	for (unsigned int i = 0; i < m_scenes.size(); ++i)
	{
		if (scenes[i] == 0)
		{
			break;
		}

		rng -= scenes[i];
		if (rng <= 0)
		{
			LoadScene(possibleScenesNames[i]);
		}
	}
}

void SceneManager::NextLinkedScene(std::string& _name)
{
	LoadScene(_name);
}

void SceneManager::InitScenes()
{
	//enter scenes here
	//also main menu needs to be added
	m_scenes.push_back(new ExampleScene(this, "ExampleScene", core::Location::TEMPPELINRAUNIOT));
}

void SceneManager::LoadScene(std::string& _sceneName)
{
	std::vector<Scene*>::const_iterator scene = m_scenes.begin();
	for (; scene != m_scenes.end(); ++scene)
	{
		if ((*scene)->GetName() == _sceneName)
		{
			if (m_activeScene != nullptr)
			{
				m_activeScene->Uninit();
			}
			m_activeScene = (*scene);
			m_activeScene->Init();
			break;
		}
	}
}

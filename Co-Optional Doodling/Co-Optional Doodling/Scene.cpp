#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(SceneManager* _sceneManager, std::string _name, core::Location _location)
	:m_sceneManager(_sceneManager),
	m_name(_name),
	m_location(_location),
	m_linkedSceneName(""),
	m_occuringPropability(100)
{
}


Scene::~Scene()
{
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::NextRandomScene()
{
	//TODO: välispiikit
	m_sceneManager->NextRandomScene(m_location, m_targetLocation);
}

void Scene::NextLinkedScene()
{
	if (m_linkedSceneName != "")
	{
		m_sceneManager->NextLinkedScene(m_name);
	}
	//needs a backup for linked failure
}

void Scene::SetLinkedScene(std::string _linkedSceneName)
{
	m_linkedSceneName = _linkedSceneName;
}

void Scene::SetOccuringPropability(int & _newPropability)
{
	m_occuringPropability = _newPropability;
}

void Scene::SetSceneTarget(core::Location _targetLocation)
{
	m_targetLocation = _targetLocation;
}

int Scene::GetOccuringPropability() const
{
	return m_occuringPropability;
}

core::Location Scene::GetLocation() const
{
	return m_location;
}

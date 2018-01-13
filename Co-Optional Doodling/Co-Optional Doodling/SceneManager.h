#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <chrono>
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	bool LoopActiveScene();
	void NextRandomScene(core::Location previousLocation, core::Location targetLocation);
	void NextLinkedScene(std::string& name);

	//This should not be used
	//in normal in-game scenes
	//to load next scene
	void LoadScene(std::string& sceneName);

private:
	void InitScenes();

	Scene* m_activeScene;
	std::vector<Scene*> m_scenes;
	bool m_exit;
};

#endif
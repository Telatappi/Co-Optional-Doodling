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
	void LoopActiveScene();
	void NextRandomScene(core::Location previousLovation, core::Location targetLocation);
	void NextLinkedScene(std::string& name);
private:
	void LoadScene(std::string& sceneName);
	Scene* m_activeScene;
	std::vector<Scene*> m_scenes;
};

#endif
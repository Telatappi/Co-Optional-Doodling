#ifndef EXAMPLESCENE_H
#define EXAMPLESCENE_H

#include "Scene.h"

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
};

#endif
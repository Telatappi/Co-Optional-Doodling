#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu(SceneManager* sceneManager, std::string name, core::Location location);
	~MainMenu();
	//init this scene
	void Init();
	//This is where the action happens in a scene
	bool Loop(bool exit);
	//do something before the scene ends
	void Uninit();
private:
	void PlayerCreation();

};

#endif
#include "ExampleScene.h"

ExampleScene::ExampleScene(SceneManager* _sceneManager, std::string _name, core::Location _location)
	:Scene(_sceneManager, _name, _location)
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
	return exit;
}

void ExampleScene::Uninit()
{
}

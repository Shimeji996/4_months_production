#pragma once
#include <memory>
#include <Novice.h>
#include "Scene.h"
#include "Title.h"
#include "Stage1.h"
#include "Clear.h"
#include "Gameover.h"

class GameManager
{
private:
	std::unique_ptr<Scene> sceneArr_[4];

	int currentSceneNo_;
	int prevSceneNo_;

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

public:

	GameManager();
	~GameManager();

	int Run();

private:
	Scene* scene;
};


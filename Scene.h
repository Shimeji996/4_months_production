#pragma once

enum SCENE {
	TITLE,
	STAGE1,
	CLEAR,
	GAMEOVER
};

class Scene
{
protected:

	static int sceneNo_;

public:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual ~Scene();

	int GetSceneNo() { return sceneNo_; }

};


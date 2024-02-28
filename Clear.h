#pragma once
#include "Scene.h"
#include <Novice.h>

class Clear : public Scene
{
public:
	void Initialize() override;

	void Update() override;

	void Draw() override;

private:
	
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

};


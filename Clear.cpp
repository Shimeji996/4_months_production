#include "Clear.h"

void Clear::Initialize() {

}

void Clear::Update() {
	
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton10)) {
		sceneNo_ = TITLE;
	}
}

void Clear::Draw() {
	
}
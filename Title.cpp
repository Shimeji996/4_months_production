#include "Title.h"

void Title::Initialize() {

}

void Title::Update() {

	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	//スペースキーとAボタン
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton10)) {
		sceneNo_ = STAGE1;
	}

}

void Title::Draw() {
	Novice::ScreenPrintf(0, 0, "TITLE");
}

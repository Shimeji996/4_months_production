#pragma once
#include "Scene.h"
#include <Novice.h>
#include "Vector2.h"

#include "Player.h"

class Stage1 : public Scene
{
public:
	Stage1();
	~Stage1();

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	enum MapInfo {
		NONE,
		BLOCK
	};

	struct Block {
		MapInfo state; //ブロックの状態
		Vector2 pos; //座標
		Vector2 size; //画像の大きさ
		Vector2 imagePos; //読み込む画像の座標
	};

	int blockSize = 128;

	/*int mapHeight = 8;
	int mapWidth = 30;*/

	/*float posXtmp = 0.0f;
	float posYtmp = 0.0f;*/

	int gh1 = Novice::LoadTexture("./Resources/block.png");

	int map[8][15]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	//プレイヤーをステージ１に持たせる
	Player* player_ = nullptr;

	////スティック操作
	//int stickPosX = 0;
	//int stickPosY = 0;

	//int leftTopX;//左上のX座標
	//int leftTopY;//左上のY座標
	//int rightTopX;//右上のX座標
	//int rightTopY;//右上のY座標
	//int leftBottomX;//左下のX座標
	//int leftBottomY;//左下のY座標
	//int rightBottomX;//右下のX座標
	//int rightBottomY;//右下のY座標
	//int playerPosOldX;//Xに仮に進んだときの変数
	//int playerPosOldY;//Yに仮に進んだときの変数

};


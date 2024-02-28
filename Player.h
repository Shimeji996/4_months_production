#pragma once
#include "Vector2.h"
#include "Novice.h"
#include "Input.h"

class Player
{
public:

	void Initialize();

	void Update();

	void Draw();

private:

	//ブロックの状態
	enum MapInfo
	{
		NONE,
		BLOCK,
	};

	Input* input_ = nullptr;

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

	//プレイヤーのブロックサイズ
	int kBlockSize = 128;

	//プレイヤーの座標
	int PlayerPosX = 130; 
	int PlayerPosY = 832;
	int PlayerRadius = 32;
	const int kWitdth = 64;
	const int kHeight = 64;

	//プレイヤーの各頂点座標
	int PlayerRightTopX = 0; //右上Ｘ座標
	int PlayerRightTopY = 0; //右上Ｙ座標

	int PlayerLeftTopX = 0; //左上Ｘ座標
	int PlayerLeftTopY = 0; //左上Ｙ座標

	int PlayerRightBottomX = 0; //右下Ｘ座標
	int PlayerRightBottomY = 0; //右下Ｙ座標

	int PlayerLeftBottomX = 0; //左下Ｘ座標
	int PlayerLeftBottomY = 0; //左下Ｙ座標

	//プレイヤーが仮に進んだ時の移動量
	int PlayerSpeedTmp = 0;

	//プレイヤーがもし進んだ時の移動座標
	int PlayerSpeedX = 0;

};


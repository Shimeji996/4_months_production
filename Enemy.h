#pragma once
#include "Novice.h"
#include "Vector2.h"

class Enemy
{
public:

	//エネミ初期化関数
	void Initialize(Vector2 Pos);

	//エネミ更新関数
	void Update();

	//エネミ描画関数
	void Draw();

	//エネミーリセット
	void Reset(Vector2 Pos);

private:

	//エネミー死亡フラグ
	bool EnemyAlive;

	//エネミー初期位置
	Vector2 enemyPos;

	//エネミー大きさ
	float enemyRad;

	//エネミー速度
	float enemySpeed;
};


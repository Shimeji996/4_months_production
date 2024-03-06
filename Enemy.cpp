#include "Enemy.h"

void Enemy::Initialize(Vector2 Pos)
{
	enemyRad = 64.0f;
	enemySpeed = 0.5f;
	Reset(Pos);
}

void Enemy::Update()
{
	//enemyPos.x -= enemySpeed;
}

void Enemy::Draw()
{
	Novice::DrawBox((int)enemyPos.x, (int)enemyPos.y, (int)enemyRad, (int)enemyRad, 0.0f, RED, kFillModeSolid);
}

void Enemy::Reset(Vector2 Pos)
{
	enemyPos = Pos;
}

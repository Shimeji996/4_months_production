#include "Enemy.h"

void Enemy::Initialize()
{
	enemyRad = 64.0f;

	enemySpeed = 0.5f;

	Reset();
}

void Enemy::Update()
{
	enemyPos.x -= enemySpeed;
}

void Enemy::Draw()
{
	Novice::DrawBox((int)enemyPos.x, (int)enemyPos.y, (int)enemyRad, (int)enemyRad, 0.0f, WHITE, kFillModeSolid);
}

void Enemy::Reset()
{
	enemyPos = { 800.0f,832.0f };
}

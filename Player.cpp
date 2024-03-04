#include "Player.h"

//プレイヤー初期化
void Player::Initialize()
{
	//PlayerPosX = 128;
	//PlayerPosY = 832;

	input_ = Input::GetInstance();
}

//プレイヤー更新
void Player::Update()
{
	
	//プレイヤーの各頂点座標の計算
	PlayerRightTopX = (PlayerPosX + PlayerRadius - 1) / kBlockSize;
	PlayerRightTopY = (PlayerPosY - PlayerRadius) / kBlockSize;

	PlayerRightBottomX = (PlayerPosX + PlayerRadius - 1) / kBlockSize;
	PlayerRightBottomY = (PlayerPosY + PlayerRadius - 1) / kBlockSize;

	PlayerLeftTopX = (PlayerPosX - PlayerRadius) / kBlockSize;
	PlayerLeftTopY = (PlayerPosY - PlayerRadius) / kBlockSize;

	PlayerLeftBottomX = (PlayerPosX - PlayerRadius) / kBlockSize;
	PlayerLeftBottomY = (PlayerPosY + PlayerRadius - 1) / kBlockSize;

	//プレイヤーの移動速度初期化
	PlayerSpeedX = 0;
	//プレイヤーの移動処理

	//右
	if (input_->PushKey(DIK_D) == 1)	{

		PlayerRightTopX = (PlayerPosX + PlayerSpeedTmp + PlayerRadius) / kBlockSize;
		PlayerRightBottomX = (PlayerPosX + PlayerSpeedTmp + PlayerRadius) / kBlockSize;

		if (map[PlayerRightTopX][PlayerRightTopY] == NONE && map[PlayerRightBottomX][PlayerRightBottomY] == NONE) {
			
			PlayerSpeedX = 6;
		}
	}
	PlayerPosX += PlayerSpeedX;

	
	PlayerSpeedX = 0;

	//左
	if (input_->PushKey(DIK_A) == 1) {

		PlayerLeftTopX = (PlayerPosX -PlayerSpeedTmp - PlayerRadius) / kBlockSize;
		PlayerLeftBottomX = (PlayerPosX - PlayerSpeedTmp - PlayerRadius) / kBlockSize;

		if (map[PlayerLeftTopX][PlayerLeftTopY] == NONE && map[PlayerLeftBottomX][PlayerLeftBottomY] == NONE) {

			PlayerSpeedX = -6;
		}
	}
	PlayerPosX += PlayerSpeedX;

}

//プレイヤー描画
void Player::Draw()
{
	Novice::ScreenPrintf(0,50,"posX : %d", PlayerPosX);
	Novice::ScreenPrintf(0, 70, "sppedX : %d", PlayerSpeedX);
	Novice::ScreenPrintf(0, 90, "posY : %d", PlayerPosY);
	Novice::ScreenPrintf(0, 110, "LeftTopX : %d", PlayerLeftTopX);
	Novice::ScreenPrintf(0, 130, "LeftTopY : %d", PlayerLeftTopY);
	Novice::ScreenPrintf(0, 150, "RightTopX : %d", PlayerRightTopX);
	Novice::ScreenPrintf(0, 170, "RightTopY : %d", PlayerRightTopY);

	//プレイヤーの描画
	Novice::DrawBox(PlayerPosX - PlayerRadius, PlayerPosY, kWitdth, kHeight, 0.0f, RED, kFillModeSolid);
}

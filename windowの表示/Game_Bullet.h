#pragma once
/*==================================================================================================

	ゲームの弾制御[game_bullet.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "collision.h"

#define BULLET_MAX (128)


//弾の初期化
void GameBullet_Initialize(void);

//弾の終了処理
void GameBullet_Finalize(void);

//弾の更新
void GameBullet_Update(void);

//弾の描画
void GameBullet_Draw(void);

//弾の生成
void GameBullet_Create(float x, float y);

CollisionCircle Game_Bullet_GetCollision(int index);

void GameBullet_Disable(int index);

bool GameBullet_IsEnable(int index);

#endif // !GAME_BULLET_H


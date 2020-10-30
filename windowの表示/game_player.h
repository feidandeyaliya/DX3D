/*==================================================================================================

	ゲームのプレイヤー制御[game_player.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "collision.h"

//ゲームのプレイヤー初期化
void GamePlayer_Initialize(void);
//ゲームのプレイヤー終了処理
void GamePlayer_FinalIze(void);

//ゲームのプレイヤーの更新
void GamePlayer_Update(void);

//ゲームのプレイヤーの描画
void GamePlayer_Draw(void);

void GamePlayer_MoveUp(void);
void GamePlayer_MoveDown(void);
void GamePlayer_MoveLeft(void);
void GamePlayer_MoveRight(void);

//ゲームプレイヤーの弾の発射
void GamePlayer_shoot(void);
void GamePlayer_damage(void);
int GamePlayer_getHP(void);

CollisionCircle GamePlayer_Position(void);

#endif // GAME_PLAYER_H


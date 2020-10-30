/*==================================================================================================

	ゲームの敵制御[game_enemy.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "collision.h"


#define ENEMY_MAX (128)

//敵の初期化
void GameEnemy_Initialize(void);

//敵の終了処理
void GameEnemy_Finalize(void);

//敵の更新
void GameEnemy_Update(void);

//敵の描画
void GameEnemy_Draw(void);

//敵の生成
void GameEnemy_Spawn(float x, float y);
void GameBoss_Spawn(float x, float y);


CollisionCircle Game_Enemy_GetCollision(int index);

void GameEnemy_Disable(int index);

bool GameEnemy_IsEnable(int index);

void GameEnemy_damage(void);

CollisionCircle Game_Boss_GetCollision(void);

bool GameBoss_IsEnable(void);
int GameBoss_getHP(void);

#endif // !GAME_ENEMY_H
/*==================================================================================================

	ゲームのエフェクト制御[game_effect.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef GAME_EFFECT_H
#define GAME_EFFECT_H


//弾の初期化
void GameEffect_Initialize(void);

//弾の終了処理
void GameEffect_Finalize(void);

//弾の更新
void GameEffect_Update(void);

//弾の描画
void GameEffect_Draw(void);

//弾の生成
void GameEffect_Create(float x, float y);

#endif // !GAME_EFFECT_H

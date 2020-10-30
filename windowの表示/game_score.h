#pragma once
#ifndef GAME_SCORE_H
#define GAME_SCORE_H

//初期化
void GameScore_Initialize(int dig,bool zeroFill,bool left);

//終了処理
void GameScore_Finalize(void);

//更新
void GameScore_Update(void);

//描画
void GameScore_Draw(float x,float y);


void GameScore_AddScore(int score);
int GameScore_GetScore(void);
void GameScore_ConfirmScore(void);
#endif // !GAME_SCORE_H
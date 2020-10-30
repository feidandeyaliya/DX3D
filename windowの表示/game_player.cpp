/*==================================================================================================

	ゲームのプレイヤー制御[game_player.cpp]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include<stdio.h>
#include "KeyLogger.h"
#include "game_player.h"
#include "Game_Bullet.h"
#include "sound.h"
#include "scene.h"
#include "debug_font.h"

static int g_pTexturePlayer = TEXTURE_INVALID_ID;//テクスチャ管理番号
static D3DXVECTOR2 g_PlayerDirection(0.0f, 0.0f);//プレイヤー進行方向
static D3DXVECTOR2 g_PlayerPosition(0.0f, 0.0f);//プレイヤー座標
static float g_PlayerSpeed = 0.0f;
int g_PlayerHP = 0;

//ゲームのプレイヤー初期化
void GamePlayer_Initialize(void)
{
	g_pTexturePlayer = texture_SetTextureLoadFile("asset/texture/Player.tga");

	g_PlayerPosition = D3DXVECTOR2(600.0f, 620.0f);

	g_PlayerDirection = D3DXVECTOR2(0.0f, 0.0f);

	g_PlayerSpeed = 6.0f;

	g_PlayerHP = 3;
}
//ゲームのプレイヤー終了処理
void GamePlayer_FinalIze(void)
{
	texture_Release(&g_pTexturePlayer, 1);
}

//ゲームのプレイヤーの更新
void GamePlayer_Update(void)
{
	if (g_PlayerHP <= 0)
		Scene_Change(SCENE_RESULT);

	if (keylogger_Press(KL_UP))
	{
		GamePlayer_MoveUp();
	}
	if (keylogger_Press(KL_DOWN))
	{
		GamePlayer_MoveDown();
	}
	if (keylogger_Press(KL_LEFT))
	{
		GamePlayer_MoveLeft();
	}
	if (keylogger_Press(KL_RIGHT))
	{
		GamePlayer_MoveRight();
	}
	//進行方向の正規化
	D3DXVec2Normalize(&g_PlayerDirection, &g_PlayerDirection);

	//プレイヤー座標の更新
	g_PlayerPosition += g_PlayerDirection * g_PlayerSpeed;
	g_PlayerSpeed *= 0.85f;

	//g_PlayerDirection = D3DXVECTOR2(0.0f, 0.0f);


	if (g_PlayerPosition.y < 0.0f)
		g_PlayerPosition.y = 0.0f;

	if (g_PlayerPosition.y > 620.0f)
		g_PlayerPosition.y = 620.0f;

	if (g_PlayerPosition.x < 0.0f)
		g_PlayerPosition.x = 0.0f;

	if (g_PlayerPosition.x > 1206.0f)
		g_PlayerPosition.x = 1206.0f;
}

//ゲームのプレイヤーの描画
void GamePlayer_Draw(void)
{
	Sprite_Draw(g_pTexturePlayer, g_PlayerPosition.x,g_PlayerPosition.y,73.7f,99.3f,0.0f,0.0f,295.0f,397.0f);
	char hp[64];
	sprintf_s(hp, "PLAYER HP=%d", g_PlayerHP);
	DebugFont_Draw(900.0f, 650.0f, hp);
}



void GamePlayer_MoveUp(void)
{
	g_PlayerDirection.y = -1.0f;
	g_PlayerSpeed = 6.0f;
	
}
void GamePlayer_MoveDown(void)
{
	g_PlayerDirection.y = 1.0f;
	g_PlayerSpeed = 6.0f;
	
}
void GamePlayer_MoveLeft(void)
{
	g_PlayerDirection.x = -1.0f;
	g_PlayerSpeed = 6.0f;
	
}
void GamePlayer_MoveRight(void)
{
	g_PlayerDirection.x = 1.0f;
	g_PlayerSpeed = 6.0f;
	
}

//ゲームプレイヤーの弾の発射
void GamePlayer_shoot(void)
{
	//弾の発射
	if (keylogger_Trigger(KL_ATTACK))
	{
		GameBullet_Create(g_PlayerPosition.x, g_PlayerPosition.y);

		PlaySound(SOUND_LABEL_SE_SHOT);
	}
}

void GamePlayer_damage(void)
{
	g_PlayerHP--;
}

int GamePlayer_getHP(void)
{
	return g_PlayerHP;
}


CollisionCircle GamePlayer_Position(void)
{
	CollisionCircle GamePlayer;
	GamePlayer.center = g_PlayerPosition;
	GamePlayer.radius = 25.0f;
	return GamePlayer;
}
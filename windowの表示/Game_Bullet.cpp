/*==================================================================================================

	ゲームの弾制御[game_bullet.cpp]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include"collision.h"
#include"Game_Bullet.h"
#include"game_effect.h"

typedef struct Bullet_tag
{
	D3DXVECTOR2 position;
	bool enable;
}Bullet;

static int g_pTextureBullet = TEXTURE_INVALID_ID;//テクスチャ管理番号
static Bullet g_Bullets[BULLET_MAX];

//弾の初期化
void GameBullet_Initialize(void)
{
	g_pTextureBullet = texture_SetTextureLoadFile("asset/texture/Bullet.tga");

	
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].enable = false;
	}
}

//弾の終了処理
void GameBullet_Finalize(void)
{
	texture_Release(&g_pTextureBullet, 1);

}

//弾の更新
void GameBullet_Update(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾が有効か調べる
		if (g_Bullets[i].enable)
		{
			g_Bullets[i].position.y -= 10.0f;
			GameEffect_Create(g_Bullets[i].position.x-35.0f, g_Bullets[i].position.y+20.0f);

		}
		//弾が有効だったら↓
		//弾の座標の更新
		//何かの条件で弾を無効にする
		if (g_Bullets[i].position.y <= 0.0f)
			g_Bullets[i].enable = false;
	}
}

//弾の描画
void GameBullet_Draw(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾が有効か調べる
		if (g_Bullets[i].enable == true)
		{
			Sprite_Draw(g_pTextureBullet, g_Bullets[i].position.x, g_Bullets[i].position.y, 10.0f, 54.3f, 0.0f, 0.0f, 91.0f, 487.0f);

		}
		//弾が有効だったら↓
		//弾の座標に弾を描画する
	}
}

//弾の生成
void GameBullet_Create(float x, float y)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾を有効か調べる

		//弾が無効だったら↓
		//弾を有効する
		//弾の座標を設定する
		if (g_Bullets[i].enable == false)
		{
			g_Bullets[i].enable = true;
			g_Bullets[i].position.x = x;
			g_Bullets[i].position.y = y;
			break;
		}
	}
}


CollisionCircle Game_Bullet_GetCollision(int index)
{
	CollisionCircle g_Bullet;
	g_Bullet.center = g_Bullets[index].position;
	g_Bullet.radius = 25.0f;
	return g_Bullet;
}

void GameBullet_Disable(int index)
{
	g_Bullets[index].enable = false;
}

bool GameBullet_IsEnable(int index)
{
	return g_Bullets[index].enable;
}
/*==================================================================================================

	ゲームの敵制御[game_enemy.cpp]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/

#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include "config.h"
#include "collision.h"
#include "game_player.h"
#include "game_enemy.h"
#include "scene.h"
#include "explosion.h"
#include "sound.h"
#include "fade.h"
#include <stdio.h>
#include "debug_font.h"
#include "debug_primitive.h"

typedef struct Enemy_tag
{
	D3DXVECTOR2 position;
	bool enable;
	int hp;
	D3DXVECTOR2 aim;
}Enemy;

static int g_pTextureEnemy = TEXTURE_INVALID_ID;//テクスチャ管理番号
static int g_pTextureBoss = TEXTURE_INVALID_ID;//テクスチャ管理番号

static Enemy boss;
static Enemy g_Enemys[ENEMY_MAX];

int chae = 0;
int speed = 10;
int time=0;
int killTime = 0;
int step = 0;
float rad = 0;
float fangxiang = 0.1f;
int cishu = 0;

//弾の初期化
void GameEnemy_Initialize(void)
{
	g_pTextureEnemy = texture_SetTextureLoadFile("asset/texture/enemy.tga");
	g_pTextureBoss = texture_SetTextureLoadFile("asset/texture/space_kikansen.png");
	chae = 0;
	speed = 10;
	time = 0;
	killTime = 0;
	step = 0;
	rad = 0;
	fangxiang = 0.1f;
	cishu = 0;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemys[i].position= D3DXVECTOR2(0.0f, 0.0f);
		g_Enemys[i].enable = false;
		g_Enemys[i].hp = 1;
	}
	boss.position = D3DXVECTOR2(0.0f, 0.0f);
	boss.enable = false;
	boss.hp = 20;
	boss.aim.x = 10.0f;
}

//弾の終了処理
void GameEnemy_Finalize(void)
{
	texture_Release(&g_pTextureEnemy, 1);
	texture_Release(&g_pTextureBoss, 1);

}

//弾の更新
void GameEnemy_Update(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵が有効か調べる
		if (g_Enemys[i].enable == true)
		{
			if (g_Enemys[i].position.y < 500.0f)
			{
				chae = sqrt((GamePlayer_Position().center.y - g_Enemys[i].position.y)*(GamePlayer_Position().center.y - g_Enemys[i].position.y) +
					(GamePlayer_Position().center.x - g_Enemys[i].position.x)*(GamePlayer_Position().center.x - g_Enemys[i].position.x));

				g_Enemys[i].aim.x = speed * (GamePlayer_Position().center.x - g_Enemys[i].position.x) / chae;
				g_Enemys[i].aim.y = speed * (GamePlayer_Position().center.y - g_Enemys[i].position.y) / chae;
			}
			g_Enemys[i].position.x += g_Enemys[i].aim.x;
			g_Enemys[i].position.y += g_Enemys[i].aim.y;

		}
		//敵が有効だったら↓
		//敵の座標の更新
		//何かの条件で敵を無効にする

		if (g_Enemys[i].position.y >= SCREEN_HEIGHT|| g_Enemys[i].position.x>=SCREEN_WIDTH|| g_Enemys[i].position.y < -54.0f|| g_Enemys[i].position.x < 0.0f)
			g_Enemys[i].enable = false;
	}

	//boss行動パターン
	if (boss.enable == true)
	{
		if (step == 0)//下に二マス移動 デフォルト位置(500,100)
		{
			boss.position.y+=2.0f;
			if (boss.position.y >= 100.0f)
				step = 1;
		}
		if (step == 1)//(400,100)円心
		{
			boss.position.x = 400 + 100 * cosf(rad);
			boss.position.y = 100 + 100 * sinf(rad);
			rad += 0.1f;
			if (rad >= 2 * 3.14)
			{
				step = 2;
				rad = 3.14f;
			}
			
		}
		if (step == 2)//(600,100)円心
		{
			boss.position.x = 600 + 100 * cosf(rad);
			boss.position.y = 100 - 100 * sinf(rad);
			rad += 0.1f;
			if (rad >= 3 * 3.14)
			{
				step = 3;
				rad = 0.0f;
			}
		}
		if (step == 3)//平行移動
		{
			if (boss.aim.x >= 10.0f)
			{ 
				fangxiang = -0.1f;
				cishu++;
				}
			else if (boss.aim.x <= -10.0f)
			{
				fangxiang = 0.1f;
			}
			boss.aim.x += fangxiang;
			boss.position.x += boss.aim.x;
			if (cishu == 3)
			{
				step = 1;
				fangxiang = 0.1f;
				boss.aim.x = 10.0f;
				cishu = 0;
			}

		}

	}

	time++;
}

//弾の描画
void GameEnemy_Draw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//弾が有効か調べる
		if (g_Enemys[i].enable == true)
		{
			Sprite_Draw(g_pTextureEnemy, g_Enemys[i].position.x, g_Enemys[i].position.y, 10.0f, 54.3f, 0.0f, 0.0f, 91.0f, 487.0f);

		}
		//弾が有効だったら↓
		//弾の座標に弾を描画する

		//当たり判定のデバッグ表示
		DebugPrimitive_BatchDrawCircle(
			g_Enemys[i].position.x + 5.0f,
			g_Enemys[i].position.y + 27.0f,
			25.0f
		);
	}
	if (boss.enable == true)
	{
		Sprite_Draw(g_pTextureBoss, boss.position.x, boss.position.y, 200.0f, 168.5f, 0.0f, 0.0f, 400.0f, 337.0f);
	}
	if (boss.hp <= 0&&killTime==0)
	{
		killTime = time;
		Explosion_Set(boss.position.x + 50.0f, boss.position.y + 30.0f);
		Explosion_Set(boss.position.x + 150.0f, boss.position.y + 130.0f);
		Explosion_Set(boss.position.x + 130.0f, boss.position.y + 150.0f);
		Explosion_Set(boss.position.x + 100.0f, boss.position.y + 100.0f);
		boss.enable = false;
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);
	}
	if (killTime!=0 && time - killTime > 100)
	{
		Scene_Change(SCENE_RESULT);

	}
	char boss_hp[64];
	sprintf_s(boss_hp, "BOSS HP=%d", boss.hp);
	DebugFont_Draw(900.0f, 0.0f, boss_hp);
}

//弾の生成
void GameEnemy_Spawn(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//敵を有効か調べる

		//敵が無効だったら↓
		//敵を有効する
		//敵の座標を設定する
		if (g_Enemys[i].enable == false)
		{
			g_Enemys[i].enable = true;
			g_Enemys[i].position.x = x;
			g_Enemys[i].position.y = y;
			return;
		}
	}
}


void GameBoss_Spawn(float x, float y)
{
	if (boss.enable == false)
	{
		boss.enable = true;
		boss.position.x = x;
		boss.position.y = y;
	}
}

void GameEnemy_damage(void)
{
	boss.hp--;
	if (boss.hp < 0)
		boss.hp = 0;
	
}

CollisionCircle Game_Enemy_GetCollision(int index)
{
	CollisionCircle g_Enemy;
	g_Enemy.center = g_Enemys[index].position;
	g_Enemy.radius = 25.0f;
	return g_Enemy;
}
	
void GameEnemy_Disable(int index)
{
	g_Enemys[index].enable = false;
}

bool GameEnemy_IsEnable(int index)
{
	return g_Enemys[index].enable;
}

CollisionCircle Game_Boss_GetCollision(void)
{
	CollisionCircle g_Boss;
	g_Boss.center.x = boss.position.x+100.0f;
	g_Boss.center.y = boss.position.y + 84.0f;
	g_Boss.radius = 35.0f;
	return g_Boss;
}

bool GameBoss_IsEnable(void)
{
	return boss.enable;
}


int GameBoss_getHP(void)
{
	return boss.hp;
}
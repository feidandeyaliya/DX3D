#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include "explosion.h"

typedef struct Explosion_tag
{
	D3DXVECTOR2 position;
	bool enable;
}Explosion;

static int g_pTextureExplosion = TEXTURE_INVALID_ID;//テクスチャ管理番号
static Explosion g_Explosions[Explosion_MAX];
int animetion = 0;
int count = 0;

//爆発の初期化
void Explosion_Initialize(void)
{
	g_pTextureExplosion = texture_SetTextureLoadFile("asset/texture/exp.png");
	for (int i = 0; i < Explosion_MAX; i++)
	{
		g_Explosions[i].position = D3DXVECTOR2(0.0f, 0.0f);
		g_Explosions[i].enable = false;
	}
}

//爆発の終了処理
void Explosion_Finalize(void)
{
	texture_Release(&g_pTextureExplosion, 1);
}

//爆発の更新
void Explosion_Update(void)
{
	for (int i = 0; i < Explosion_MAX; i++)
	{
		if (g_Explosions[i].enable == true)
		{
			count++;
			animetion = count / 3;
			if (count > 21)
			{
				count = 0;
				g_Explosions[i].enable = false;
			}
		}
	}
}

//爆発の描画
void Explosion_Draw(void)
{
	for (int i = 0; i < Explosion_MAX; i++)
	{
		if (g_Explosions[i].enable == true)
		{
			Sprite_Draw(g_pTextureExplosion, g_Explosions[i].position.x, g_Explosions[i].position.y, 32.0f, 32.0f, 32.0f*(animetion % 4) - 0.1f, 32.0f*(animetion / 4) - 0.1f, 32.0f, 32.0f);
		}
	}
}

//爆発の生成
void Explosion_Set(float x, float y)
{
	for (int i = 0; i < Explosion_MAX; i++)
	{
		if (g_Explosions[i].enable == false)
		{
			g_Explosions[i].position.x = x;
			g_Explosions[i].position.y = y;
			g_Explosions[i].enable = true;
			return;
		}
	}
}
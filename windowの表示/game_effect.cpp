#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include "mydirect3d.h"

#define EFFECT_MAX (2048)

typedef struct Effect_tag
{
	D3DXVECTOR2 position;
	//color
	//size
	D3DXVECTOR2 size;
	//alpha
	//type
	//along time
	int timeLength;
	int birthFrame;
	bool enable;
}Effect;


static int g_pTextureId = TEXTURE_INVALID_ID;//テクスチャ管理番号
static Effect g_Effects[EFFECT_MAX];
static int g_FrameCount = 0;


void GameEffect_Initialize(void)
{
	g_pTextureId= texture_SetTextureLoadFile("asset/texture/effect000.jpg");

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effects[i].enable = false;
	}
	g_FrameCount = 0;
}


void GameEffect_Finalize(void)
{
	texture_Release(&g_pTextureId, 1);
}


void GameEffect_Update(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effects[i].enable) continue;

		int age = g_FrameCount - g_Effects[i].birthFrame;

		if (age >= 30)
		{
			g_Effects[i].enable = false;
		}
	}
	g_FrameCount++;
}


void GameEffect_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effects[i].enable) continue;

		int age = g_FrameCount - g_Effects[i].birthFrame;

		float a = 1.0f - ((1.0f / 30.0f)*age);

		D3DXCOLOR color(1.0f, 0.1f, 0.1f, a);

		Sprite_Setcolor(color);

		Sprite_Draw(g_pTextureId, g_Effects[i].position.x, g_Effects[i].position.y);
	}
	Sprite_Setcolor(D3DCOLOR_RGBA(255, 255, 255, 255));

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


void GameEffect_Create(float x, float y)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effects[i].enable) continue;

		g_Effects[i].enable = true;
		g_Effects[i].position = D3DXVECTOR2(x, y);
		g_Effects[i].birthFrame = g_FrameCount;

		break;
	}
}

#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>

static int g_pTextureBG = TEXTURE_INVALID_ID;//テクスチャ管理番号
float x;

void GameBG_Initialize(void)
{
	g_pTextureBG  = texture_SetTextureLoadFile("asset/texture/sky.jpg");
	x = 0.0f;
}

void GameBG_Finalize(void)
{
	texture_Release(&g_pTextureBG, 1);

}

void GameBG_Update(void)
{
	x++;
	if (x >= 2560.0f)
		x = 0.0f;
}

void GameBG_Draw(void)
{
	if (x < 1840.0f)
	{
		Sprite_Draw(g_pTextureBG, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1840.0f - x, 1280.0f, 720.f);
	}
	if (x >= 1840.0f)
	{
		Sprite_Draw(g_pTextureBG, 0.0f, 0.0f, 1280.0f, x - 1840.0f, 0.0f, 4400.0f - x, 1280.0f, x - 1840.0f);
		Sprite_Draw(g_pTextureBG, 0.0f, x - 1840.0f, 1280.0f, 2560.0f-x, 0.0f, 0.0f, 1280.0f, 2560.0f - x);

	}

	//Sprite_Draw(g_pTextureBG, 0.0f, x, 1280.0f, 720.0f-x, 0.0f, 0.0f, 1280.0f, 720.0f-x);

}
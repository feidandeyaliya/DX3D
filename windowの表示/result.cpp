#include"texture.h"
#include"sprite.h"
#include"KeyLogger.h"
#include"scene.h"
#include"fade.h"

static int g_pTextureClear = TEXTURE_INVALID_ID;//テクスチャ管理番号
static int g_pTextureId = TEXTURE_INVALID_ID;//テクスチャ管理番号
static int  player_hp = 0;

void Result_Initialize(void)
{
	g_pTextureId = texture_SetTextureLoadFile("asset/texture/result_gameover.tga");
	g_pTextureClear = texture_SetTextureLoadFile("asset/texture/result_clear.tga");
	texture_Load();

	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 40);
}

void Result_Update(void)
{
	if (keylogger_Trigger(KL_UP))
	{
		//next scene
		Scene_Change(SCENE_TITLE);
	}
}

void Result_Draw(void)
{
	if(player_hp>0)
		Sprite_Draw(g_pTextureClear, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1280.0f, 960.0f);
	else
		Sprite_Draw(g_pTextureId, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1280.0f, 960.0f);
}

void Result_Finalize(void)
{
	texture_Release(&g_pTextureId, 1);
	texture_Release(&g_pTextureClear, 1);
}
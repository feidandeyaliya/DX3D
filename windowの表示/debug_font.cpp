#if defined (_DEBUG)||defined(DEBUG)
/*==================================================================================================

    デバッグフォントモジュール[debug_font.cpp]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include "texture.h"
#include <string.h>
#include "sprite.h"

#define DEBUG_FONT_WIDTH (32)
#define DEBUG_FONT_HEIGHT (64)
#define DEBUG_FONT_START_CHAR_CODE (32)
#define DEBUG_FONT_ONE_LINE_CHAR_COUNT (16)


static int g_TextureId = TEXTURE_INVALID_ID;
//デバッグフォントモジュールの初期化
void DebugFont_Initialize(void)
{
	g_TextureId = texture_SetTextureLoadFile("asset/texture/debug_font_32x64.png");

	if (texture_Load() > 0)
	{
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
	}
}

//デバッグフォントモジュールの終了処理
void DebugFont_Finalize(void)
{
	texture_Release(&g_TextureId, 1);
}

//デバッグフォントの表示
//
//引数：dx,dy    デバッグ文字列への描画座標
//      pSting   デバッグ文字列へのポインタ
//
void DebugFont_Draw(float dx, float dy, const char* pString)
{
	for (unsigned int i = 0; i < strlen(pString); i++)
	{
		int tcx = (pString[i] % DEBUG_FONT_ONE_LINE_CHAR_COUNT)*DEBUG_FONT_WIDTH;
		int tcy = (pString[i] / DEBUG_FONT_ONE_LINE_CHAR_COUNT - 2)*DEBUG_FONT_HEIGHT;

		Sprite_Draw(g_TextureId, dx+i*DEBUG_FONT_WIDTH, dy, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
	}
}

#endif
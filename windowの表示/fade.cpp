#include"texture.h"
#include"sprite.h"
#include"fade.h"
#include<d3dx9.h>
#include"config.h"

static FadeMode g_FadeMode = FADE_NONE;
static D3DXCOLOR g_color;
static float g_Prop = 0.0f;
static int g_FadeFrame = 0;
static int g_FrameCount = 0;
static int g_FadeStartFrame = 0;
static int g_TextureId = TEXTURE_INVALID_ID;

void Fade_Initialize(void)
{
	g_FadeMode = FADE_NONE;
	g_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Prop = 0.0f;
	g_FadeFrame = 0;
	g_FrameCount = 0;
	g_FadeStartFrame = 0;
	g_TextureId = TEXTURE_INVALID_ID;

	g_TextureId = texture_SetTextureLoadFile("asset/texture/fade.tga");
}
void Fade_Finalize(void)
{
	texture_Release(&g_TextureId, 1);

}
void Fade_Update(void)
{
	g_FrameCount++;
	if (g_FadeMode == FADE_NONE) 
		return;

	int frame = g_FrameCount - g_FadeStartFrame;
	g_Prop = (float)frame / g_FadeFrame;

	if (g_Prop > 1.0f)
		g_FadeMode = FADE_NONE;
}
void Fade_Draw(void)
{
	if (g_FadeMode == FADE_IN)
		g_color.a = 1.0f - g_Prop;
	if(g_FadeMode == FADE_OUT)
		g_color.a = g_Prop;

	if (g_color.a <= 0.001f)
		return;
	Sprite_Setcolor(g_color);
	Sprite_Draw(g_TextureId, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,0,0,8,8);

	Sprite_Setcolor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

void Fade_Start(FadeMode mode, float r, float g, float b, int frame)
{
	g_FadeMode = mode;
	g_color = D3DXCOLOR(r, g, b, 0.0f);
	g_Prop = 0.0f;
	g_FadeFrame = frame;
	g_FadeStartFrame = g_FrameCount;
}
bool Fade_IsFade(void)
{
	return g_FadeMode != FADE_NONE;
}
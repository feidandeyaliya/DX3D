#include"texture.h"
#include"sprite.h"
#include"KeyLogger.h"
#include"scene.h"
#include"fade.h"
#include<math.h>

#define rate (2.0f)
#define speed (5.0f)

static int g_pTextureId = TEXTURE_INVALID_ID;//テクスチャ管理番号
static int g_pTextureId_title = TEXTURE_INVALID_ID;

float i;
float y;

typedef enum TitleMode
{
	TITLE_FADE_IN,
	TITLE_SHOW,
	TITLE_FADE_OUT
};
TitleMode g_TitleMode;
void Title_Initialize(void)
{

	g_TitleMode = TITLE_FADE_IN;
	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 60 * 3);

	i = 0;
	y = 0.0f;
}

void Title_Update(void)
{
	switch (g_TitleMode)
	{
	case TITLE_FADE_IN:
		if (!Fade_IsFade())
			g_TitleMode = TITLE_SHOW;
		break;
	case TITLE_SHOW:
		if (keylogger_Trigger(KL_UP))
		{
			g_TitleMode = TITLE_FADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 100);

		}
		break;
	case TITLE_FADE_OUT:
		if (!Fade_IsFade())
			Scene_Change(SCENE_GAME);
		
		break;
	default:
		break;
	}
	//if (keylogger_Trigger(KL_DECISION))
	//{
	//	//next scene
	//	Scene_Change(SCENE_GAME);
	//}
}

void Title_Draw(void)
{
	//Sprite_Draw(g_pTextureId, 0.0f, 0.0f, 1280.0f, 720.0f, 0, 0, 1920, 1080);

	if (g_TitleMode!= TITLE_FADE_OUT)
	{

		//Sprite_Draw(g_pTextureId_title,950.0f, 100.0f, 78.0f, 500.0f,0, 0, 125, 800);


	}
	else
	{
		for (float i = 0.0f; i < 200.0f; i++)
		{
			//Sprite_Draw(g_pTextureId_title,40.0f*sinf((i*rate + y) / 180.0f*3.14f) + 950.0f, 2.5f * i + 100.0f, 78.0f, 2.5f,0, 4*i, 125, 4);
		}

		y += speed;
	}
}

void Title_Finalize(void)
{
	//texture_Release(&g_pTextureId, 1);
	//texture_Release(&g_pTextureId_title, 1);
}
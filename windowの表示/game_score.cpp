#include "texture.h"
#include "sprite.h"
#include "game_score.h"

#define NUMBER_WIDTH  (32)
#define NUMBER_HEIGHT (32)

static int  g_Score = 0;
static int  g_DrawScore = 0;
static int  g_Digits = 0;
static bool g_ZeroFill = true;
static bool g_Left = false;
static int  g_pTextureId = TEXTURE_INVALID_ID;

void drawNumber(int n, float x, float y);

void GameScore_Initialize(int dig, bool zeroFill, bool left)
{
	g_Score = 0;
	g_DrawScore = 0;
	g_Digits = dig;
	g_ZeroFill = zeroFill;
	g_Left = left;

	g_pTextureId = texture_SetTextureLoadFile("asset/texture/number.tga");
}

//終了処理
void GameScore_Finalize(void)
{
	texture_Release(&g_pTextureId, 1);
}

//更新
void GameScore_Update(void)
{
	if (g_DrawScore < g_Score)
	{
		g_DrawScore++;
	}
	else if (g_DrawScore > g_Score)
	{
		g_DrawScore--;
	}

	//カウントストップ
	if (g_DrawScore < 0)
	{
		g_DrawScore = 0;
	}
	int maxDrawScore = 1;
	for (int i = 0; i < g_Digits; i++)
	{
		maxDrawScore *= 10;
	}
	maxDrawScore--;
	if (g_DrawScore > maxDrawScore)
	{
		g_DrawScore = maxDrawScore;
	}
}

//描画
void GameScore_Draw(float x, float y)
{
	/*if (g_Left)
	{
		char buf[256];
		g_Digits=sprintf()
	}*/

	int score = g_DrawScore;
	float dx = x + ((g_Digits - 1)*NUMBER_WIDTH);

	for (int i = 0; i < g_Digits; i++)
	{
		int n = score % 10;
		drawNumber(n, dx, y);
		dx -= NUMBER_WIDTH;
		score /= 10;

		if (!g_ZeroFill)
		{
			if (score == 0)
				break;
		}
	}
}


void GameScore_AddScore(int score)
{
	GameScore_ConfirmScore();
	g_Score += score;
}
int GameScore_GetScore(void)
{
	return g_Score;
}
void GameScore_ConfirmScore(void)
{
	g_DrawScore = g_Score;
}
void drawNumber(int n, float x, float y)
{
	if (n < 0 || n>9)return;

	Sprite_Draw(g_pTextureId, x, y,
		n*NUMBER_WIDTH, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
}

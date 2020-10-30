/*==================================================================================================

	ゲームの敵出現制御[game_EnemySpawner.cpp]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include "game_enemy.h"
#include "config.h"

//構造体宣言
typedef struct EnemySpawn_tag
{
	int spawn_frame;
	float x, y;
}EnemySpawn;

//グローバル変数宣言
static EnemySpawn g_EnemySpawnData[] = 
{
	{ 0,SCREEN_WIDTH*0.5f,-54.0f},
	{ 90,SCREEN_WIDTH*0.5f,-54.0f},
	{90,SCREEN_WIDTH*0.2f,-54.0f},
	{90,SCREEN_WIDTH*0.8f,-54.0f},
	{200,SCREEN_WIDTH*0.1f,-54.0f},
	{200,SCREEN_WIDTH*0.9f,-54.0f},
	{200,SCREEN_WIDTH*0.3f,-54.0f},
	{200,SCREEN_WIDTH*0.5f,-54.0f},
	{200,SCREEN_WIDTH*0.7f,-54.0f},
	{270,SCREEN_WIDTH*0.3f,-54.0f},
	{270,SCREEN_WIDTH*0.7f,-54.0f},
	{300,SCREEN_WIDTH*0.2f,-54.0f},
	{300,SCREEN_WIDTH*0.5f,-54.0f},
	{300,SCREEN_WIDTH*0.8f,-54.0f},
	{400,SCREEN_WIDTH*0.2f,-54.0f},
	{400,SCREEN_WIDTH*0.5f,-54.0f},
	{400,SCREEN_WIDTH*0.8f,-54.0f},
	{500,SCREEN_WIDTH*0.2f,-54.0f},
	{500,SCREEN_WIDTH*0.5f,-54.0f},
	{500,SCREEN_WIDTH*0.8f,-54.0f},
	{610,SCREEN_WIDTH*0.9f,-54.0f},
	{620,SCREEN_WIDTH*0.8f,-54.0f},
	{630,SCREEN_WIDTH*0.7f,-54.0f},
	{640,SCREEN_WIDTH*0.6f,-54.0f},
	{650,SCREEN_WIDTH*0.5f,-54.0f},
	{660,SCREEN_WIDTH*0.4f,-54.0f},
	{670,SCREEN_WIDTH*0.3f,-54.0f},
	{680,SCREEN_WIDTH*0.2f,-54.0f},
	{690,SCREEN_WIDTH*0.1f,-54.0f},
	{700,SCREEN_WIDTH*0.2f,-54.0f},
	{710,SCREEN_WIDTH*0.3f,-54.0f},
	{720,SCREEN_WIDTH*0.4f,-54.0f},
	{730,SCREEN_WIDTH*0.5f,-54.0f},
	{740,SCREEN_WIDTH*0.6f,-54.0f},
	{750,SCREEN_WIDTH*0.7f,-54.0f},
	{760,SCREEN_WIDTH*0.8f,-54.0f},
	{770,SCREEN_WIDTH*0.9f,-54.0f},
	{-1,0,0},
};

static int g_FrameCount = 0;
static int g_SpawnIndex = 0;

void GameEnemySpawner_Initialize(void)
{
	g_FrameCount = 0;
	g_SpawnIndex = 0;
}
void GameEnemySpawner_Finalize(void)
{

}
void GameEnemySpawner_Update(void)
{
	
	
	while(g_EnemySpawnData[g_SpawnIndex].spawn_frame <= g_FrameCount)
	{
		if (g_EnemySpawnData[g_SpawnIndex].spawn_frame < 0)
		{
			break;
		}
		GameEnemy_Spawn(g_EnemySpawnData[g_SpawnIndex].x, g_EnemySpawnData[g_SpawnIndex].y);
		g_SpawnIndex++;
	}
	if (g_FrameCount > 300)
		GameBoss_Spawn(500.0f,-170.0f);
	g_FrameCount++;

	if (g_SpawnIndex >= 37)
	{
		g_SpawnIndex = 0;
		g_FrameCount = 0;
	}

}

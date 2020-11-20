#include<d3dx9.h>
#include"texture.h"
#include"sprite.h"
#include"debug_font.h"
#include "config.h"
#include "explosion.h"
#include "KeyLogger.h"
#include "sound.h"
#include "fade.h"
#include "Cube.h"
#include "grid.h"
#include "camera.h"
#include "meshfield.h"
#include "model_x.h"

static float g_Angle = 0.0f;
static float g_Value = 0.f;
float g_Var = 0.01f;
D3DXVECTOR3 camera;
static int g_xmodel_id = MODEL_X_INVALID_ID;
void Game_Initialize(void)
{
	//Explosion_Initialize();
	Camera_Initialize();
	MeshField_Initialize(15,15);
	Cube_Initialize();
	Model_x_Initialize();

	g_xmodel_id = Model_x_Load("asset/model/Robo/Robo.x");
	if (texture_Load()>0)
	{
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
	}
	//keylogger_RecordLoad();
	//keylogger_RecordPlay();

	//PlaySound(SOUND_LABEL_BGM000);

	//Grid_Initialize(1.0f, 10, D3DCOLOR_RGBA(152, 10, 10, 255));

	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 60);

}

void Game_Update(void)
{
	g_Value += g_Var;
	//GameEnemy_Spawn(rand()%SCREEN_WIDTH, -54.0f);
	//Explosion_Update();
	Cube_Update();
	Camera_Update();

	Camera_SetMatrixToDevice();
}

void Game_Draw(void)
{
	//Grid_Draw();
	MeshField_Draw();
	//Explosion_Draw();

	//ワールド座標変換行列の作成
	D3DXMATRIX mtxWorld, mtxS, mtxR, mtxT;

	//単位行列の作成
	D3DXMatrixIdentity(&mtxWorld);//rtxWorld=1
	//回転行列の作成
	D3DXMatrixRotationY(&mtxWorld, -g_Value);
	//D3DXMatrixRotationYawPitchRoll(&mtxWorld, g_Angle, g_Angle, g_Angle);
	//平行移動行列の作成
	//D3DXMatrixTranslation(&mtxT, Camera_GetAt()->x, Camera_GetAt()->y, Camera_GetAt()->z);
	//拡大行列の作成
	//D3DXMatrixScaling(&mtxS, sin(g_Value)*0.5f+1.0f, 1.0f, sin(g_Value)*0.5f + 1.0f);

	//mtxWorld = mtxWorld * mtxS;
	//D3DXMatrixMultiply(&mtxWorld, &mtxS, &mtxR);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxT);
	Cube_Draw(&mtxWorld);

	/*for (float i = 0; i < 500; i += 2.0f)
	{
		for (float j = 0; j < 500; j += 2.0f)
		{

			D3DXMatrixRotationY(&mtxWorld, -g_Value);

			D3DXMatrixTranslation(&mtxT, i, j, 0.0f);
			mtxWorld = mtxWorld * mtxT;
			Cube_Draw(&mtxWorld);
		}
	}*/

	D3DXMatrixTranslation(&mtxT, 5.0f, 0.5f, 5.0f);
	Model_x_Draw(g_xmodel_id, &mtxT);
}

void Game_Finalize(void)
{
	//Grid_Finalize();
	//Explosion_Finalize();
	Cube_Finalize();
	MeshField_Finalize();
	Model_x_Finalize();
}
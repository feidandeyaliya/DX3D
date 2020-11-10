/*==================================================================================================

	3Dキューブ[Cube.cpp]
																					Author:
																					Date  :2020/10/09
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include<d3dx9.h>
#include"mydirect3d.h"
#include"config.h"
#include"camera.h"
#include"texture.h"
#include"sprite.h"


typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE|D3DFVF_TEX1)

//頂点データ配列（3Dキューブ）
Vertex3D g_CubeVertex[] = {
	//front
	{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f}},
	{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f}},
	{{-0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f}},
	//{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f}},
	{{ 0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	//{{-0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f}},
	//right
	{{0.5f, 0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f}},
	{{0.5f, 0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.0f}},
	{{0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	//{{0.5f, 0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.0f}},
	{{0.5f,-0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.25f}},
	//{{0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	//up
	{{-0.5f, 0.5f, 0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.0f}},
	{{ 0.5f, 0.5f, 0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.0f}},
	{{-0.5f, 0.5f,-0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.25f}},
	//{{ 0.5f, 0.5f, 0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.0f}},
	{{ 0.5f, 0.5f,-0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.25f}},
	//{{-0.5f, 0.5f,-0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.25f}},
	//back				 				
	{{ 0.5f, 0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.0f}},
	{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{1.0f,0.0f}},
	{{ 0.5f,-0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.25f}},
	//{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{1.0f,0.0f}},
	{{-0.5f,-0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{1.0f,0.25f}},
	//{{ 0.5f,-0.5f, 0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.75f,0.25f}},
	//left				 
	{{-0.5f, 0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f}},
	{{-0.5f, 0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	{{-0.5f,-0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.5f}},
	//{{-0.5f, 0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	{{-0.5f,-0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.5f}},
	//{{-0.5f,-0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.5f}},
	//bottom			 				 
	{{-0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
	{{ 0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.25f}},
	{{-0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.5f}},
	//{{ 0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.25f}},
	{{ 0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.5f,0.5f}},
	//{{-0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.5f}},
};

//テクスチャ管理番号
static int g_TextureId = TEXTURE_INVALID_ID;

//頂点バッファインターフェース
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
//インデックスバッファインターフェース
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

void Cube_Initialize(void)
{

	g_TextureId = texture_SetTextureLoadFile("asset/texture/spice_and_wolf.png");
	texture_Load();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	pDevice->CreateVertexBuffer(
		sizeof(Vertex3D) * 24,	//頂点バッファの量(バイト)
		D3DUSAGE_WRITEONLY,		//使い方
		FVF_VERTEX3D,			//FVF
		D3DPOOL_MANAGED,		//メモリの管理方法
		&g_pVertexBuffer,		//取得したインターフェースのアドレスを記録するためのポインタ
		NULL
	);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);

	Vertex3D* pV;
	g_pVertexBuffer->Lock(0,0,(void**)&pV,0);
	memcpy(pV, g_CubeVertex, sizeof(g_CubeVertex));
	g_pVertexBuffer->Unlock();

	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	
	for (int i = 0, j = 0; i < 36; i += 6, j += 4)//0-3,4-7,8-11
	{
		pIndex[i] = j + 0;
		pIndex[i + 1] = j + 1;
		pIndex[i + 2] = j + 2;
		pIndex[i + 3] = j + 1;
		pIndex[i + 4] = j + 3;
		pIndex[i + 5] = j + 2;
	}
	g_pIndexBuffer->Unlock();
}

void Cube_Finalize(void)
{
	texture_Release(&g_TextureId, 1);

	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

void Cube_Update(void)
{
	
}

void Cube_Draw(const D3DXMATRIX* pMtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//ライト(平行光源)の設定
	D3DLIGHT9 light = {};//0に初期化   //memset(&light, 0, sizeof(light));     //ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDirLight(3.0f, -2.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirLight);

	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 0.3f;
	light.Ambient.g = 0.3f;
	light.Ambient.b = 0.3f;
	light.Ambient.a = 1.0f;

	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);
	
	//ディフューズマテリアルを設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	//アンビエントライトの設定
	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(50, 50, 50, 255));

	//ディフューズマテリアルを設定
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//デバイスにワールド変換行列を設定
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorld);


	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, texture_GetTexture(g_TextureId));

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_CubeVertex,sizeof(Vertex3D));

	// デバイスにインデックスバッファの利用を設定
	pDevice->SetIndices(g_pIndexBuffer);

	//デバイスに頂点バッファの利用を設定
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex3D));

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

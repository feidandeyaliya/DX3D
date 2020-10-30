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
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE|D3DFVF_TEX1)

//頂点データ配列（3Dキューブ）
Vertex3D g_CubeVertex[] = {
	//front
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR3( 0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3( 0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	{D3DXVECTOR3( 0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	//right
	{D3DXVECTOR3(0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f)},
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	{D3DXVECTOR3(0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	//up
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.0f)},
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	{D3DXVECTOR3(0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	//back
	{D3DXVECTOR3( 0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.0f)},
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR3(0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR3(-0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.25f)},
	{D3DXVECTOR3(0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75f,0.25f)},
	//left
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f)},
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	{D3DXVECTOR3(-0.5f, 0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3(-0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.5f)},
	//bottom
	{D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3( 0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3(-0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
	{D3DXVECTOR3( 0.5f,-0.5f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.25f)},
	{D3DXVECTOR3( 0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.5f,0.5f)},
	{D3DXVECTOR3(-0.5f,-0.5f, 0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.5f)},
};

//テクスチャ管理番号
static int g_TextureId = TEXTURE_INVALID_ID;

void Cube_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	g_TextureId = texture_SetTextureLoadFile("asset/texture/spice_and_wolf.png");
	texture_Load();
}

void Cube_Finalize(void)
{
	texture_Release(&g_TextureId, 1);
}

void Cube_Update(void)
{
	
}

void Cube_Draw(const D3DXMATRIX* pMtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();


	//デバイスにワールド変換行列を設定
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorld);


	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, texture_GetTexture(g_TextureId));

	//ライトを無効(練習用)
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_CubeVertex,sizeof(Vertex3D));
}

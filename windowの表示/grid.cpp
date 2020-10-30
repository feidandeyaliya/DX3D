#include<d3dx9.h>
#include"mydirect3d.h"
#include"config.h"
#include <malloc.h>
#include "camera.h"

typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR Color;
	//D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

static Vertex3D* g_pVertex = NULL;
static int g_VertexCount = 0;
static int g_LineCount = 0;

void Grid_Initialize(float size, int count, D3DCOLOR color)
{
	g_LineCount = (count + 1) * 2;
	g_VertexCount = g_LineCount * 2;

	g_pVertex = (Vertex3D*)malloc(g_VertexCount * sizeof(Vertex3D));

	float length = size * count;
	float start = -length * 0.5f;
	float end = length * 0.5f;
	int n = g_LineCount;

	for (int i = 0; i < count + 1; i++)
	{		

		g_pVertex[    i * 2    ].Position = D3DXVECTOR3(start + size * i, 0.0f, start);
		g_pVertex[    i * 2 + 1].Position = D3DXVECTOR3(start + size * i, 0.0f, end);
		g_pVertex[n + i * 2    ].Position = D3DXVECTOR3(start, 0.0f, start + size * i);
		g_pVertex[n + i * 2 + 1].Position = D3DXVECTOR3(end, 0.0f, start + size * i);

	}	
	
	for (int i = 0; i < g_VertexCount; i++)
	{
		g_pVertex[i].Color = color;


	}

}

void Grid_Finalize(void)
{
	free(g_pVertex);
}

void Grid_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//ワールド座標変換行列の作成
	D3DXMATRIX mtxWorld;

	//単位行列の作成
	D3DXMatrixIdentity(&mtxWorld);//rtxWorld=1
	//デバイスにワールド変換行列を設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);


	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, NULL);
	//ライトを無効(練習用)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, g_LineCount, g_pVertex, sizeof(Vertex3D));
}

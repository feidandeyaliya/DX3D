#include<d3dx9.h>
#include"mydirect3d.h"
#include"config.h"
#include"camera.h"
#include"texture.h"
#include"sprite.h"
#include"KeyLogger.h"

typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ |D3DFVF_NORMAL| D3DFVF_DIFFUSE|D3DFVF_TEX1)

//頂点データ配列（3Dキューブ）
//Vertex3D g_MeshfieldVertex[64] = {
//	{{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{2.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{0.0f,0.0f,1.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{1.0f,0.0f,1.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{2.0f,0.0f,1.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{0.0f,0.0f,2.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{1.0f,0.0f,2.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{2.0f,0.0f,2.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//	{{2.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255) },
//};

Vertex3D* g_MeshfieldVertex = NULL;


//頂点バッファインターフェース
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
//インデックスバッファインターフェース
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
//テクスチャ管理番号
static int g_TextureId = TEXTURE_INVALID_ID;
bool mode = false;
int x_count;
int y_count;

void MeshField_Initialize(int xx, int yy)
{
	g_MeshfieldVertex = new Vertex3D[(xx + 1)*(yy + 1)];
	g_TextureId = texture_SetTextureLoadFile("asset/texture/grass.tga");
	texture_Load();
	x_count = xx;
	y_count = yy;

	for (int i = 0; i <= yy; i++)
	{
		for (int j = 0; j <= xx; j++)
		{
			g_MeshfieldVertex[i * (xx+1) + j].Position = { 1.0f*j-(float)xx/2,0.0f,1.0f*i- (float)yy/2 };
			g_MeshfieldVertex[i * (xx+1) + j].Normal = { 0.0f,1.0f,0.0f };
			g_MeshfieldVertex[i * (xx+1) + j].Color = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_MeshfieldVertex[i * (xx+1) + j].TexCoord = { 1.0f*j,1.0f*i };
		}
	}



	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	pDevice->CreateVertexBuffer(
		sizeof(Vertex3D) * (xx+1)*(yy+1),	//頂点バッファの量(バイト)
		D3DUSAGE_WRITEONLY,		//使い方
		FVF_VERTEX3D,			//FVF
		D3DPOOL_MANAGED,		//メモリの管理方法
		&g_pVertexBuffer,		//取得したインターフェースのアドレスを記録するためのポインタ
		NULL
	);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((xx+1)*2*yy+2*(yy-1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);

	Vertex3D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, g_MeshfieldVertex, sizeof(Vertex3D)*(xx + 1)*(yy + 1));
	g_pVertexBuffer->Unlock();

	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	
	for (int k = 0; k < yy; k++)
	{
		for (int l = 0; l < (xx+2)*2-1; l++)
		{
			
				if (l % 2 == 0)
				{
					pIndex[k*(xx + 2) * 2 + l] = l / 2 + (xx + 1)*k;
				}
				else
				{
					pIndex[k*(xx + 2) * 2 + l] = (l - 1) / 2 + (xx + 1) + (xx + 1)*k;
				}
			
			if (k == yy - 1 && l >= k * (xx + 2) * 2 + (xx + 1) * 2-1)
				break;
			
			
			if (k > 0 && l == 0)
			{
				pIndex[k*(xx + 2) * 2 - 1] = pIndex[k*(xx + 2) * 2];
				pIndex[k*(xx + 2) * 2 - 2] = pIndex[k*(xx + 2) * 2 - 3];
			}
		}
	}
	g_pIndexBuffer->Unlock();
	delete[] g_MeshfieldVertex;
}



void MeshField_Finalize(void)
{
	//texture_Release(&g_TextureId, 1);

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



void MeshField_Draw(void)
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
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);


	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, texture_GetTexture(g_TextureId));

	/*if (keylogger_Trigger(KL_MODE))
	{
		mode = !mode;
	}
	if (mode)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0,2);

		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	else
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);*/
	pDevice->SetIndices(g_pIndexBuffer);

	//デバイスに頂点バッファの利用を設定
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex3D));
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
	if (keylogger_Trigger(KL_MODE))
	{
		mode = !mode;
	}
	if (mode)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (x_count + 1)*(y_count + 1), 0, 2 * x_count*y_count + (y_count - 1) * 4);

		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	else
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (x_count + 1)*(y_count + 1), 0, 2 * x_count*y_count + (y_count - 1) * 4);

}
/*==================================================================================================

	モデル描画(Xファイル)[model_x.cpp]
																					Author:
																					Date  :2020/11/20
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#include "model_x.h"
#include "mydirect3d.h"

struct Model_X
{
	LPD3DXMESH pMesh; //メッシュ
	//LPD3DXBUFFER pAdjacency; //隣接情報バッファ
	DWORD materialCount; //マテリアル数
	//マテリアル情報
	//テクスチャId
};

#define MODEL_X_MAX (64)

static Model_X g_XModels[MODEL_X_MAX] = {};

void Model_x_Initialize(void)
{
	Model_x_ReleaseAll();
}

void Model_x_Finalize(void)
{
	Model_x_ReleaseAll();
}

//xファイルの読み込み
//
//戻り値：モデル整理番号
//
int Model_x_Load(const char* pFileName)
{
	int id = MODEL_X_INVALID_ID;
	for (int i = 0; i < MODEL_X_MAX; i++)
	{
		if (g_XModels[i].pMesh == NULL)
			id = i;
			break;
	}
	if (id == MODEL_X_INVALID_ID)
		return MODEL_X_INVALID_ID;//未使用領域がなかった場合

	HRESULT hr;
	PDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	LPD3DXBUFFER pAdjacency;
	LPD3DXMESH pTempMesh;
	hr = D3DXLoadMeshFromX(
		pFileName,							//ファイル名
		D3DXMESH_SYSTEMMEM,					//オプション(メインメモリに情報を作成)
		pDevice,							//Direct3Dデバイス
		&pAdjacency,						//隣接情報
		NULL,								//マテリアル情報(取得)
		NULL,								//エフェクト(シェーダー)(取得)
		&g_XModels[id].materialCount,		//マテリアル数(取得)
		&pTempMesh							//メッシュ(取得)
		);
	if (FAILED(hr))
	{
		//エラーチェック
		return MODEL_X_INVALID_ID;
	}

	//D3DXMATERIAL* pD3DXMateria=(D3DXMATERIAL*)pMaterial->get
	//pMaterial->Release();

	//メッシュの最適化をする
	pTempMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);

	//高速で面倒を見てくれる頂点バッファを取り扱うメッシュとしてクローンを作成する
	pTempMesh->CloneMeshFVF(
		D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
		pTempMesh->GetFVF(),
		pDevice,
		&g_XModels[id].pMesh
		);

	pAdjacency->Release();
	pTempMesh->Release();
	return id;
}

//モデルの解放
//
//引数 pIDs   解放したいモデル整理番号が入ったメモリ領域の先頭アドレス
//     count　解放したいモデル整理番号の個数
//
void Model_x_Release(const int* pIDs, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!g_XModels[pIDs[i]].pMesh)
			continue;
		g_XModels[pIDs[i]].pMesh->Release();
		g_XModels[pIDs[i]].pMesh = NULL;
	}
}

//モデルの全解放
void Model_x_ReleaseAll(void)
{
	for (int i = 0; i < MODEL_X_MAX; i++)
	{
		Model_x_Release(&i, 1);
	}
}

//モデルの描画
void Model_x_Draw(int id, const D3DXMATRIX* mtxModel)
{
	if (!g_XModels[id].pMesh)
		return;

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, mtxModel);


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

	
	for (DWORD i = 0; i < g_XModels[id].materialCount; i++)
	{
		pDevice->SetTexture(0, 0);
		g_XModels[id].pMesh->DrawSubset(i);			//FVFの設定、頂点バッファとインデックスバッファの設定ー＞DrawIndexedPrimitive()
	}
}
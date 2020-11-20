#include<d3dx9.h>

#include"mydirect3d.h"
#include"texture.h"

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//FVF フレキシブルバーテックスフォーマット
//RHW = 1...座標変換済み頂点

//グローバル変数宣言
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;	//頂点バッファ
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;	//インデックスバッファインターフェース
static D3DCOLOR g_Color = 0xffffffff;					//ポリゴンカラー

void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	pDevice->CreateVertexBuffer(
		sizeof(Vertex2D) * 4,	//頂点バッファの量(バイト)
		D3DUSAGE_WRITEONLY,		//使い方
		FVF_VERTEX2D,			//FVF
		D3DPOOL_MANAGED,		//メモリの管理方法
		&g_pVertexBuffer,		//取得したインターフェースのアドレスを記録するためのポインタ
		NULL
		);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
}

void Sprite_Finalaize(void)
{
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

//カラー設定
//
//引数：color　ポリゴンカラー
//
void Sprite_Setcolor(D3DCOLOR color)
{
	g_Color = color;
}



//スプライトの描画(シンプル)
//テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId 　テクスチャ管理番号
//      dx　　　　　描画座標ｘ（左上座標
//      dy　　　　　描画座標ｙ（左上座標
//
void Sprite_Draw(int textureId, float dx, float dy)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Deviceの取得に失敗しました", "エラー", MB_OK);
		return;
	}
	//デバイスにFVFの設定をする
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//デバイスにテクスチャの設定をする
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);



	//頂点データ
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx    - 0.5f,dy   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR4(dx +w - 0.5f,dy   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR4(dx    - 0.5f,dy+h - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR4(dx+w  - 0.5f,dy+h - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(1.0f,1.0f)},
	};

	//頂点バッファをロックしてデータを書き込み
	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);

	//データを書き込み
	memcpy(pV, v, sizeof(v));

	g_pVertexBuffer->Unlock();
	//インデックスバッファをロックしてデータを書き込み
	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 2;
	pI[3] = 1;
	pI[4] = 3;
	pI[5] = 2;
	
	g_pIndexBuffer->Unlock();

	//デバイスに頂点バッファの利用を設定
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//デバイスにインデックスバッファの利用を設定
	g_pDevice->SetIndices(g_pIndexBuffer);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);


	//ポリゴン描画(完全版)
	//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2,pI,D3DFMT_INDEX16, v, sizeof(Vertex2D));

	//ポリゴン描画(簡易版)
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}




//スプライトの描画(等倍サイズ)
//テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId 　テクスチャ管理番号
//      dx　　　　　描画座標ｘ（左上座標
//      dy　　　　　描画座標ｙ（左上座標
//　　　tcx　　　　 テクスチャの切り取り座標ｘ
//　　　tcy　　　　 テクスチャの切り取り座標y
//　　　tcw　　　　 テクスチャの切り取り幅
//　　　tch　　　　 テクスチャの切り取り幅
//
void Sprite_Draw(int textureId, float dx, float dy, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Deviceの取得に失敗しました", "エラー", MB_OK);
		return;
	}
	//デバイスにFVFの設定をする
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//デバイスにテクスチャの設定をする
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//ポリコンのサイズはテクスチャサイズ
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//テクスチャ切り取りUV座標
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	//頂点データ
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx - 0.5f,       dy - 0.5f,      0.0f,1.0f), g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy - 0.5f,      0.0f,1.0f), g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f,       dy + tch - 0.5f,0.0f,1.0f), g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f, dy + tch - 0.5f,0.0f,1.0f), g_Color,D3DXVECTOR2(u1,v1)},
	};

	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);

	//データを書き込み
	memcpy(pV, v, sizeof(v));

	g_pVertexBuffer->Unlock();

	//デバイスに利用する頂点バッファを指定する
	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}



//スプライトの描画(サイズ調整)
//テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId 　テクスチャ管理番号
//      dx　　　　　描画座標ｘ（左上座標
//      dy　　　　　描画座標ｙ（左上座標
//      dw          ポリコンサイズの幅
//      dh　　　　　ポリコンサイズの高さ
//　　　tcx　　　　 テクスチャの切り取り座標ｘ
//　　　tcy　　　　 テクスチャの切り取り座標y
//　　　tcw　　　　 テクスチャの切り取り幅
//　　　tch　　　　 テクスチャの切り取り幅
//
void Sprite_Draw(int textureId, float dx, float dy,float dw,float dh, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Deviceの取得に失敗しました", "エラー", MB_OK);
		return;
	}
	//デバイスにFVFの設定をする
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//デバイスにテクスチャの設定をする
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//ポリコンのサイズはテクスチャサイズ
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//テクスチャ切り取りUV座標
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	//頂点データ
	Vertex2D v[] =
	{
		{D3DXVECTOR4(dx - 0.5f,  dy - 0.5f,1.0f,1.0f),        g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx + dw - 0.5f, dy - 0.5f,1.0f,1.0f),    g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(dx - 0.5f,dy + dh - 0.5f,1.0f,1.0f),     g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx + dw - 0.5f,dy + dh - 0.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(u1,v1)},
	};




	//ポリゴン描画(簡易版)
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}


//スプライトの描画(+回転)
//テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId 　テクスチャ管理番号
//      dx　　　　　描画座標ｘ（左上座標
//      dy　　　　　描画座標ｙ（左上座標
//      dw          ポリコンサイズの幅
//      dh　　　　　ポリコンサイズの高さ
//　　　tcx　　　　 テクスチャの切り取り座標ｘ
//　　　tcy　　　　 テクスチャの切り取り座標y
//　　　tcw　　　　 テクスチャの切り取り幅
//　　　tch　　　　 テクスチャの切り取り幅
//      cx          回転の中心座標ｘ
//      cy          回転の中心座標ｙ
//      angle       回転角度(ラジアン)
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,float cx,float cy,float angle)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Deviceの取得に失敗しました", "エラー", MB_OK);
		return;
	}
	//デバイスにFVFの設定をする
	g_pDevice->SetFVF(FVF_VERTEX2D);

	//デバイスにテクスチャの設定をする
	g_pDevice->SetTexture(0, texture_GetTexture(textureId));

	//ポリコンのサイズはテクスチャサイズ
	unsigned long w = texture_GetTextureWidth(textureId);

	unsigned long h = texture_GetTextureHeight(textureId);

	//テクスチャ切り取りUV座標
	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	

	//頂点データ
	Vertex2D v[] =
	{
		{D3DXVECTOR4(   - 0.5f,   - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dw - 0.5f,   -0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v0)},
		{D3DXVECTOR4(-0.5f,dh - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dw - 0.5f,dh - 0.5f,1.0f,1.0f), g_Color,D3DXVECTOR2(u1,v1)},
	};

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	//戻る移動行列
	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx+dx, cy+dy, 0.0f);

	//回転行列
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	//拡大行列
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 2.0f, 2.0f, 1.0f);

	//行列の合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation * mtxTranslationI;

	//座標変換
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	

	//ポリゴン描画(簡易版)
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
}
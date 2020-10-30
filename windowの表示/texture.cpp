#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include "debugPrintf.h"

#include <d3dx9.h>
#include <string.h>
#include "mydirect3d.h"

#define TEXTURE_MAX (1024) //テクスチャ管理最大数

//テクスチャ管理テーブル構造体
typedef struct Texture_tag
{
	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long width;
	unsigned long height;
	char filename[TEXTURE_FILENAME_MAX];
}Texture;

//グローバル変数宣言
//テクスチャ管理テーブル
static Texture g_Texture[TEXTURE_MAX];


//テクスチャ管理モジュールの初期化
void texture_Initialize(void)
{
	//テクスチャ管理テーブルの初期化
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i].pTexture = NULL;
		g_Texture[i].width = 0;
		g_Texture[i].height = 0;
		g_Texture[i].filename[0] = 0;
	}
}

//テクスチャ管理モジュールの終了処理
void texture_Finalize(void)
{

}

//テクスチャファイルの読み込み予約
//
//引数：pFileName...ファイル名
//
//戻り値：テクスチャ管理番号
//　　　　最大管理数を超えていた場合はINVALID_TEXTURE_ID
//
int texture_SetTextureLoadFile(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//テーブルが空いていたらスキップ
		if (g_Texture[i].filename[0] == 0)
		{
			continue;
		}
		if (strcmp(pFileName, g_Texture[i].filename) == 0)
		{
			//予約されている
			return i;
		}
	}

	//新規予約
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//テーブルが使用中だったらスキップ
		if (g_Texture[i].filename[0] != 0)
		{
			continue;
		}
		strcpy(g_Texture[i].filename, pFileName);

		return i;
	}
	return TEXTURE_INVALID_ID;
}

//テクスチャの読み込み
//
//予約がされているファイルを読み込みます
//
//戻り値：読み込めなかったファイル数
//        
int texture_Load(void)
{
	int err_count = 0;


	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return -1;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i].filename[0] == 0)
		{
			//空のテーブルなのでスキップ
			continue;
		}
		if (g_Texture[i].pTexture != NULL)
		{
			//すでに読み込まれている
			continue;
		}

		//テクスチャの読み込み
		HRESULT hr = D3DXCreateTextureFromFile(g_pDevice, g_Texture[i].filename, &g_Texture[i].pTexture);
		if (FAILED(hr))
		{
			DebugPrintf("読み込めなかったテクスチャファイル:[%s}\n", g_Texture[i].pTexture);
			err_count++;
		}
		else
		{
			//テクスチャの解像度（幅、高さ）の調査
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Texture[i].filename, &info);
			g_Texture[i].height = info.Height;
			g_Texture[i].width = info.Width;
		}
	}
	return err_count;//読み込めなかった数
}

//テクスチャの部分解放
//
//引数：textureIds[]…解放したいtextureIdが入ったint型配列の先頭アドレス
//　　　count　　 　…解放するテクスチャの数
//
void texture_Release(int textureIds[], int count)//int textureIds[]=>int* pTextureIds
{
	for (int i = 0; i < count; i++)
	{
		if (g_Texture[textureIds[i]].pTexture)
		{
			g_Texture[textureIds[i]].pTexture->Release();
			g_Texture[textureIds[i]].pTexture = NULL;
		}
		g_Texture[textureIds[i]].filename[0] = 0;
		g_Texture[textureIds[i]].height = 0;
		g_Texture[textureIds[i]].width = 0;
	}
}

//テクスチャの全解放
void texture_AllRelease(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i].pTexture)
		{
			g_Texture[i].pTexture->Release();
			g_Texture[i].pTexture = NULL;
		}
		g_Texture[i].filename[0] = 0;
		g_Texture[i].height = 0;
		g_Texture[i].width = 0;
	}

}

//テクスチャの幅の取得
//
//引数：テクスチャの管理番号
//
//戻り値：テクスチャの幅
//
unsigned long texture_GetTextureWidth(int textureId)
{
	return g_Texture[textureId].width;
}

//テクスチャの高さの取得
//
//引数：テクスチャの管理番号
//
//戻り値：テクスチャの高さ
//
unsigned long texture_GetTextureHeight(int textureId)
{
	return g_Texture[textureId].height;
}

//テクスチャインターフェースのポインタ取得
//
//引数：テクスチャ管理番号
//
//戻り値：テクスチャインターフェースポインタ
//        読み込めていないまたは不正な管理番号だった場合NULL
//
LPDIRECT3DTEXTURE9 texture_GetTexture(int textureId)
{
	return g_Texture[textureId].pTexture;
}
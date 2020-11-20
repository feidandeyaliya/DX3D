/*==================================================================================================

	モデル描画(Xファイル)[model_x.h]
																					Author:
																					Date  :2020/11/20
----------------------------------------------------------------------------------------------------

===================================================================================================*/
#ifndef MODEL_X_H_
#define MODEL_X_H_

#include <d3dx9.h>

#define MODEL_X_INVALID_ID   (-1)//無効なXモデル管理番号

void Model_x_Initialize(void);

void Model_x_Finalize(void);

//xファイルの読み込み
//
//戻り値：モデル整理番号
//
int Model_x_Load(const char* pFileName);

//モデルの解放
//
//引数 pIDs   解放したいモデル整理番号が入ったメモリ領域の先頭アドレス
//     count　解放したいモデル整理番号の個数
//
void Model_x_Release(const int* pIDs, int count);

//モデルの全解放
void Model_x_ReleaseAll(void);

//モデルの描画
void Model_x_Draw(int id, const D3DXMATRIX* mtxModel);

#endif // MODEL_X_H_

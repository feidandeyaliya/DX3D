#include<d3d9.h>
#include<d3dx9.h>

#include"config.h"



static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3Dデバイスインターフェース

//direct3D関連の初期化

bool MyDirect3D_Initialize(HWND hWnd)
{
	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		MessageBox(NULL, "Direct3Dインターフェースの取得に失敗しました", "エラー", MB_OK);
		return false;
	}
	//デバイスの取得
	//デバイスの取得に必要な情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					//バックバッファの横幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				//バックバッファの縦幅
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				//バックバッファのフォーマット
	d3dpp.BackBufferCount = 1;							//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//スワップ方法の設定
	d3dpp.Windowed = TRUE;							//ウィンドウ　orフリスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE;							//深度バッファ　ステンシルバッファの使用
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//深度バッファ　ステンシルバッファのフォーマット
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//フルスクリーン時のリフレッシュレートの指定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//リフレッシュレートとpresent処理の関係
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//リフレッシュレートとpresent処理の関係(上より性能の要求)

	//Direct3Dデバイスの取得
	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if ((FAILED(hr)))
	{
		MessageBox(NULL, "Direct3Dデバイスの取得に失敗しました", "エラー", MB_OK);
		return false;
	}
	//UVアドレッシングモードの設定
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//テクスチャファイルダリングの設定
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//背景透明
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	return true;
}

//↑の終了処理

void MyDirect3D_Finalize(void)
{
	if (g_pDevice)
	{
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void)
{
	return g_pDevice;
}
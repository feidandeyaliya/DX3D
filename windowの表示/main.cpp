#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<stdio.h>

#include"config.h"
#include"mydirect3d.h"
#include"system_timer.h"
#include"texture.h"
#include"sprite.h"
#include"keyboard.h"
#include"KeyLogger.h"
#include"sound.h"
#include"scene.h"
#include"fade.h"
#include"debug_font.h"
#include"debug_primitive.h"


//ウインドウプロシージャ（コールバック関数）
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//ゲームの初期化関数
//戻り値：初期化に失敗したときfalse
static bool Initialize(HWND hWnd);
//更新処理
static void Update(void);
//描画処理
static void Draw(void);
//終了処理
static void Finalize(void);

//グローバル変数宣言
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;



//メイン
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)  
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	

	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);
	//ウィンドウスタイル
	const DWORD window_style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME^WS_MAXIMIZEBOX;
	//WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME|WS_MAXIMIZEBOX)

	//都合のいいウインドウサイズの算出
	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, window_style, FALSE);


	//ウィンドウの矩形から幅と高さを求める
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	//

	////デスクトップの矩形を取得
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);

	////デスクトップの幅と高さを算出
	//int desktop_width = desktop_rect.right - desktop_rect.left;
	//int desktop_height = desktop_rect.bottom - desktop_rect.top;

	////プライマリモニターの画面解像度取得
	//int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	//int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	//仮想画面の解像度取得
	int virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//仮想画面の左上座標
	int virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int virtual_desktop_y = GetSystemMetrics(SM_YVIRTUALSCREEN);


	int window_x = virtual_desktop_x + max((virtual_desktop_width - window_width) / 2, 0);
	int window_y = virtual_desktop_y + max((virtual_desktop_height - window_height) / 2, 0);

	MyDirect3D_GetDevice();
	HWND hWnd = CreateWindow
	(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		//サーズと初期位置	
		window_x, window_y, window_width, window_height,
		//ｘ　　　　　ｙ　　　　　　长            宽
		NULL,//親ウインドウハンドル
		NULL,//メニューハンドル
		hInstance,//インスタンスハンドル
		NULL//追加のアプリケーションデータ
	);
	if (hWnd == NULL)
	{
		return 0;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	
	
	

	//ゲームの初期化
	if (!Initialize(hWnd))
	{
		MessageBox(hWnd, "初期化失敗、プログラムを再起動してください。", "エラー", MB_OK);
		return 0;
	}

	MSG msg = {};

	//PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//ここがゲーム処理
			double time = SystemTimer_GetTime();
			if ((time - g_ReserveTime) < 1.0f / 60.0f)
			{
				Sleep(0);
				continue;
			}
			g_ReserveTime = time;

			//画面処理
			//更新
			Update();

			//描画
			Draw();

			//シーンの切り替え処理
			Scene_ExecuteChange();
		}
	}
	
	//ゲームの終了処理
	Finalize();
	
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {

		
		case WM_ACTIVATEAPP:
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) 
			{
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		    Keyboard_ProcessMessage(uMsg, wParam, lParam);
		    break;
		
		case WM_CLOSE:
			if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) 
			{
				DestroyWindow(hWnd);
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//初期化関数
//戻り値：初期化に失敗したときfalse
bool Initialize(HWND hWnd)
{
	Keyboard_Initialize();

	keylogger_Initialize();

	//InitSound(hWnd);

	if (!MyDirect3D_Initialize(hWnd))
	{
		MessageBox(NULL, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		return false;
	}

	//デバッグ図形描画モジュール
	DebugPrimitive_Initialize();

	texture_Initialize();

	Sprite_Initialize();

	DebugFont_Initialize();

	
	SystemTimer_Initialize();

	g_ReserveTime = g_BaseTime + SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;
	

	Fade_Initialize();

	Scene_Initialize();



	return true;
}

//更新処理
void Update(void)
{
	keylogger_Update();

	Scene_Update();
	Fade_Update();

	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0)
	{
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}

	g_FrameCount++;
}

//描画処理
void Draw(void)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		MessageBox(NULL, "Deviceの取得に失敗しました", "エラー", MB_OK);
		return;
	}
	
	//画面のクリア配列番号，範囲，クリアフラグ　　　　　　　　　，targetのあたえ　　　　　　　　，zbufferのあたえ
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 200, 255, 255), 1.0f, 0);

	//描画バッチ命令の開始
	g_pDevice->BeginScene();

	//デバッグ図形描画命令の受付開始
	DebugPrimitive_BatchBegin();

	//ゲームの描画
	Scene_Draw();

	Fade_Draw();
#if defined (_DEBUG)||defined(DEBUG)
	//FPS表示
	char buf[64];
	sprintf_s(buf, "FPS=%.2f", g_FPS);
	DebugFont_Draw(0.0f, 0.0f, buf);
#endif

	//デバッグ図形描画命令の受付実行
	DebugPrimitive_BatchRun();

	//描画バッチ命令の終了
	g_pDevice->EndScene();

	//バックバッファをフリップ(タイミングはD3DPRESENT_PARAMETERSの設定による)
	g_pDevice->Present(NULL, NULL, NULL, NULL);


	
}

//終了処理
void Finalize(void)
{

	Fade_Finalize();
	
	Scene_Finalize();

	DebugFont_Finalize();

	Sprite_Finalaize();

	texture_Finalize();

	DebugPrimitive_Finalize();

	MyDirect3D_Finalize();

	//UninitSound();

	keylogger_Finalize();
}
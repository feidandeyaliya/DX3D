#define _CRT_SECURE_NO_WARNINGS
/*==================================================================================================

	キー入力の記録制御[keylogger.h]
																					Author:
																					Date  :
----------------------------------------------------------------------------------------------------

===================================================================================================*/

#include "KeyLogger.h"
#include "keyboard.h"



static unsigned long g_CurrentKeyState = 0;//そのフレイムでのキーの状態
static unsigned long g_PrevKeyState = 0;//前のフレイムでのキーの状態
static unsigned long g_TriggerKeyState = 0;
static unsigned long g_ReleaseKeyState = 0;

static int g_KeyloggerMode = 0;//0-通常　1-記録　2-再生
static unsigned long* g_pRecordCurrentData = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

static const Keyboard_Keys g_KKs[KL_MAX]=
{
	KK_W,
	KK_S,
	KK_A,
	KK_D,
	KK_E,
	KK_Q,
	KK_LEFT,
	KK_RIGHT,
	KK_UP,
	KK_DOWN,
	KK_Z,
	KK_X,
	KK_SPACE,
	KK_L,
};

void keylogger_Initialize(void)
{
	g_CurrentKeyState = 0;
	g_PrevKeyState = 0;
	g_TriggerKeyState = 0;
	g_ReleaseKeyState = 0;

	static int g_KeyloggerMode = 0;
	static unsigned char* g_pRecordCurrentData = NULL;
	static int g_RecordFrame = 0;
	static int g_RecordPlayFrame = 0;
	static int g_RecordFrameMax = 0;
}

void keylogger_Finalize(void)
{
	if(g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}

void keylogger_Update(void)
{
	//前フレイムのキー状態を保存しておく
	g_PrevKeyState = g_CurrentKeyState;
	g_CurrentKeyState = 0;
	
	if (g_KeyloggerMode <= 1)
	{
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
				g_CurrentKeyState |= 1u << i;
		}

		if (g_KeyloggerMode == 1)
		{
			if (g_RecordFrame < g_RecordFrameMax)
			{
				g_pRecordCurrentData[g_RecordFrame] = g_CurrentKeyState;
				g_RecordFrame++;
			}
		}
	}
	else
	{
		//再生モード

		//安全処置
		if (g_RecordPlayFrame < g_RecordFrame)
		{			
			g_CurrentKeyState = g_pRecordCurrentData[g_RecordFrame++];
		}
		else
		{
			g_RecordPlayFrame = 0;
			g_KeyloggerMode = 0;
		}

	}
	
	g_TriggerKeyState = (g_PrevKeyState^g_CurrentKeyState)&g_CurrentKeyState;
	g_ReleaseKeyState = (g_PrevKeyState^g_CurrentKeyState)&g_PrevKeyState;
}

//キー入力状態の取得
//
//引数：
//
//戻り値：押されたらtrue
//
bool keylogger_Press(KeyloggerKey kl)
{
	return g_CurrentKeyState & (1u << kl);
}

//キー入力状態の取得(押した瞬間)
//
//引数：
//
//戻り値：押した瞬間true
//
bool keylogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << kl);
}

//キー入力状態の取得(離した瞬間)
//
//引数：
//
//戻り値：離した瞬間true
//
bool keylogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u << kl);
}


void keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (unsigned long*)malloc(sizeof(unsigned long)*frame_max);
	g_KeyloggerMode = 1;//記録モード
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}

void keylogger_RecordEnd(void)
{
	FILE*fp = fopen("keylogger.dat", "wb");
	//ファイルの先頭にデータ量を記録
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	//ファイルへデータを保存
	fwrite(g_pRecordCurrentData, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0;
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}

void keylogger_RecordLoad(void)
{
	FILE*fp = fopen("keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}
	g_pRecordCurrentData = (unsigned long*)malloc(sizeof(unsigned long)*g_RecordFrame);
	fread(g_pRecordCurrentData, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

}

void keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2;
}

bool keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2)
	{
		return true;
	}
	return false;
}
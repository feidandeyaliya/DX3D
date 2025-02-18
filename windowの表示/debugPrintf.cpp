#include<Windows.h>
#include "debugPrintf.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	DebugPrintf("hInstance = %p\n", hInstance);
	DebugPrintf("ポインタ型の大きさ= %dByte\n", (int)sizeof(void*));
	DebugPrintf("int型の大きさ = %dByte\n", (int)sizeof(int));
	DebugPrintf("long long型の大きさ = %dByte\n", (int)sizeof(long long));
	DebugPrintf("__int64型の大きさ = %dByte\n", (int)sizeof(__int64));

	return 0;
}
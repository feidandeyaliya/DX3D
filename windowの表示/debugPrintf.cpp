#include<Windows.h>
#include "debugPrintf.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	DebugPrintf("hInstance = %p\n", hInstance);
	DebugPrintf("ƒ|ƒCƒ“ƒ^Œ^‚Ì‘å‚«‚³= %dByte\n", (int)sizeof(void*));
	DebugPrintf("intŒ^‚Ì‘å‚«‚³ = %dByte\n", (int)sizeof(int));
	DebugPrintf("long longŒ^‚Ì‘å‚«‚³ = %dByte\n", (int)sizeof(long long));
	DebugPrintf("__int64Œ^‚Ì‘å‚«‚³ = %dByte\n", (int)sizeof(__int64));

	return 0;
}
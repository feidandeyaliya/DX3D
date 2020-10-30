#include<Windows.h>
#include "debugPrintf.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	DebugPrintf("hInstance = %p\n", hInstance);
	DebugPrintf("�|�C���^�^�̑傫��= %dByte\n", (int)sizeof(void*));
	DebugPrintf("int�^�̑傫�� = %dByte\n", (int)sizeof(int));
	DebugPrintf("long long�^�̑傫�� = %dByte\n", (int)sizeof(long long));
	DebugPrintf("__int64�^�̑傫�� = %dByte\n", (int)sizeof(__int64));

	return 0;
}
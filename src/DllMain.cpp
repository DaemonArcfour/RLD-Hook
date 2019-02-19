#include "g_Include.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DLL_Entry, NULL, NULL, NULL);

	}
	return TRUE;
}
#ifndef __SPPNDEFS_H__
#define __SPPNDEFS_H__
//-----------------------------------------------
//-@@@@@@@@@@@ Made by Daemon (2017) @@@@@@@@@@@-
//-----------------------------------------------
//Make your life easier.

#include "g_Include.h"


#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
namespace StaticPatcher {
	class InfoGathering {
	public:
		//Get INT from a specific address
		static int GetIntegerFromAddress(DWORD Address);
		//Get FLOAT from a specific address
		static float GetFloatFromAddress(DWORD Address);
		//GET STRING from a specific address
		static char* GetStringFromAddress(DWORD Address);

	};
	class SetInfo {
	public:
		//Assign INT to a specific address
		static void AssignIntegerToAddress(int val, DWORD Address);
		//Assign FLOAT to a specific address
		static void AssignFloatToAddress(float val, DWORD Address);
		//Assign CHAR* to a specific address
		static void AssignStringToAddress(char* str, DWORD Address);
	};
	class Patching {
	public:
		//Overwrite bytes at a specific address
		static void WriteBytes(BYTE Bytes[], DWORD Address, int size);
		//Place a JMP at a specific address
		static void CreateWarp(BYTE *Address, DWORD WarpTo, DWORD Length);
		//Detours a function (UNSAFE)
		static void *DetourFunction(BYTE *Source, const BYTE *Destination, const int Length);
	};
	class SearchOffset {
	public:
		// CMP Bytes
		static bool Compare(const BYTE* pData, const BYTE* bMask, const char* szMask);
		//Search for a byte pattern in memory
		static DWORD BytePattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask);

	};

	class Freeze {
	public:
		//Freeze integer permanently (UNSAFE)
		static void FreezeInteger(int val, DWORD Address);
		//Freeze float permanently (UNSAFE)
		static void FreezeFloat(float val, DWORD Address);
	};
	class Miscellaneous {
	public:
		static void OpenConsole();
	};
}
#endif
#pragma once
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <iterator>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <intrin.h>
//OpenGL
#include <gl\\GL.h>
#include <gl\\GLU.h>


#include "dirent.h"

#include "sp_NamespaceDefs.h" // StaticPatcher (By Daemon)
#include "MSDetour\detours.h" // MSDetours (By Microsoft) (Currently not used.) 
#include "MinHook\include\MinHook.h"  // MinHook

#include "RLD_OpenGL.h"
#include "RLD_PacketRecorder.h"
#include "RLD_Hooks.h"
#include "RLD_Namespace.h"
#include "RLD_ASM.h"
#include "RLD_PseudoPlayer.h"
#include "RLD_Threads.h"
#include "RLD_CVars.h"
#include "RLD_Autoshoot.h"

#pragma comment(lib, "MSDetour\\detours.lib")
#pragma comment(lib, "StaticPatcher\\StaticPatcher.lib")
#pragma comment(lib, "MinHook\\lib\\libMinHook-x86-v140-md.lib")
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLu32.lib")
void __fastcall hkCHAT_PrintChatString(int ulPlayer, int ulMode, const char *pszString);

//int __fastcall AimLineAttack(int AActor, unsigned int angle, signed int distance, DWORD *pLineTarget, int vrange, int flags, int target);
typedef int(__fastcall *func_AimLineAttack)(unsigned int, unsigned __int32, signed int, void*, int,int,int, unsigned int);
//typedef int(__fastcall *func_AimLineAttack)(unsigned int, unsigned __int32, signed int);

typedef void(__fastcall *CHAT_PrintChatString)(int, int, const char *);
typedef void(__fastcall *AddCommandString)(const char*,int);
typedef int(__thiscall *NET_SendPacket)(const void **edx, int pBuffer, int pAddress);
typedef void(__thiscall *CLAuth)(void *_this);
typedef int(__fastcall *func_GetMD5)(void *, size_t);
typedef int(*CPrint)(const char* msg, ...);
typedef int(__stdcall *o_sendTo)(unsigned int s, const char *buf, int len, int, const void*, int);
typedef int(__fastcall *FindCVar)(const char* name, void *unk1);
typedef int(*CLReqSnap)(void);
CLAuth extern cl_auth;
FindCVar extern _FindCVar;
CPrint extern CPrintf;
extern CHAT_PrintChatString orgCHAT_PrintChatString;
extern AddCommandString orgAddCommandString;
extern func_AimLineAttack orgAimLineAttack;
#endif
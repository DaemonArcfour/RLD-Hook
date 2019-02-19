#ifndef RLD_HOOKS
#define RLD_HOOKS
#include "g_Include.h"
void DLL_Entry();
void **getFBaseCVar_String(const char* CVarName);
int RequestSnapshot();
void __fastcall AttemptAuthentication(void *_this);
struct ASpace {
	DWORD EImage = 0x00400000;
	DWORD SLen = 0x0;
	BYTE pName[2] = { 0xEB, 0x1B };
	BYTE pDrop[2] = { 0xEB, 0x0F };
	BYTE remWHp_1[2] = { 0xEB,0x12 };
	BYTE remWHp_2[2] = { 0xEB, 0x0D };
};
//TODO: Remove this shit, use patterns instead, they are way more stable.
class unstableOffsets {
public:
	DWORD pointer_mapname = 0x8B4AF0;
	DWORD pointer_serverip = 0x122EC88;
	DWORD pointer_clientlag = 0x986C89;
	DWORD pointer_conprintf = 0x419070;
	DWORD pointer_cheats = 0x97FA30; // Tried creating pattern for this, didn't work. TODO: recode everything that uses this
	DWORD pointer_playerid = 0x11EDFB8;
	DWORD pointer_playername = 0x11F0A40;
	DWORD pointer_playerhealth = 0x11F0AC8;
	DWORD pointer_sendpacket = 0x489F20;

};
class patternClass {
public:
	char* pDrop[2] = { "\x73\x0F\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\x5E\xC3\x85\xF6", "xxx????x????xxxxxxx" };
	char* pName[2] = { "\x73\x1B\x68", "xxx" };
	char* pLamb[2] = { "\x7C\x05\xB8\x00\x00\x00\x00\x5F\x5E", "xxx????xx" };
	char* pCrosshair[2] = { "\x0F\x85\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x74\x2F", "xx????xx?????xx" };
	char* pCInfo[2] = { "\x0F\x85\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\xA8\x01\x75\x17", "xx????x????xxx????xxxx" };
	char* pITarget[2] = { "\x0F\x85\x00\x00\x00\x00\x85\xC0\x74\x11\x84\x50\x10","xx????xxxxxxx" };
	char* pCoopSpy[2] = { "\x0F\x84\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x75\x69\xE8\x00\x00\x00\x00\x84\xC0\x75\x5A\x8B\x00\x00\x00\x00\x00\x8B\xD1\x69\x00\x00\x00\x00\x00\x38\x00\x00\x00\x00\x00\x75\x4A\xE8\x00\x00\x00\x00\x83\xF8\x02\x75\x3A\x80\x3D\x00\x00\x00\x00\x00\x75\x31\x80\x3D\x00\x00\x00\x00\x00\x75\x28", "xx????xx?????xxx????xxxxx?????xxx?????x?????xxx????xxxxxxx?????xxxx?????xx" }; // Confirmed unstable
	//char* varConsolePlayer[2] = { "\x8B\x00\x00\x00\x00\x00\x69\x00\x00\x00\x00\x00\x81\xC7\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xF8\x02\x74\x1F\xD9\x87\x00\x00\x00\x00\x83\xEC\x08\xDD\x1C\x24\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x0C\x5F\x5E\x59\xC2\x04\x00\xF7\x05","x?????x?????xx????x????xxxxxxx????xxxxxxx????x????xxxxxxxxxxx" };
	char* frcAngle[2] = { "\x89\x00\x00\x00\x00\x00\x8B\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x10\x89\x00\x00\x00\x00\x00\x59\xC2\x04\x00\xCC\xCC\xCC","x?????x?????x????xxx?????xxxxxxx" };
	char* aAngle[2] = { "\x03\x05\x00\x00\x00\x00\x83\x7E\x04\xFF", "xx????xxxx" };
	char* funcPrintChatMsg[2] = { "\x6A\xFF\x68\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x50\x83\xEC\x08\x53\x55\x56\x57\xA1\x00\x00\x00\x00\x33\xC4\x50\x8D\x44\x24\x1C\x00\x00\x00\x00\x00\x00\x8B\xD9\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x33\xFF\x89\x4C\x24\x14\x83\xC0\x01\x83\xC0\x01","xxx??????????xxxxxxxxx????xxxxxxx??????xxx????x????xxxxxxxxxxxx" };
	char* funcAddCommandString[2] = { "\x6A\xFF\x68\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x50\x51\x53\x55\x56\x57\xA1\x00\x00\x00\x00\x33\xC4\x50\x8D\x44\x24\x18\x00\x00\x00\x00\x00\x00\x89\x54\x24\x14\x8B\xF9\x85\xFF\x0F\x84\x00\x00\x00\x00\x80\x3F\x00\x0F\x84\x00\x00\x00\x00\xB3\x5C\x8B\xFF\x80\x3F\x3B\x8B\xF7", "xxx??????????xxxxxxx????xxxxxxx??????xxxxxxxxxx????xxxxx????xxxxxxxxx" };
	char* funcFindCVar[2] = { "\x51\x53\x8B\xD9\x85\xDB", "xxxxxx" };
	char* funcConPrintf[2] = { "\x8B\x54\x24\x04\x8D\x44\x24\x08\x50\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC3","xxxxxxxxxx????x????x" }; //Confirmed unstable
	char* funcSendPacket[2] = { "\x83\xEC\x24\xA1\x00\x00\x00\x00\x33\xC4\x89\x44\x24\x20\x8B\x44\x24\x28", "xxxx????xxxxxxxxxx" };
	char* funcAuthClient[2] = { "\x83\x3D\x00\x00\x00\x00\x00\x56\x8B\xF1\x74\x09\x83\x2D","xx?????xxxxxxx" };
	char* funcReqSnapshot[2] = { "\x83\x3D\x00\x00\x00\x00\x00\x74\x08\x83\x2D\x00\x00\x00\x00\x00\xC3\x68","xx?????xxxx?????xx" };
};

struct NOPs {
public:
	BYTE NOP_1B[1] = { 0x90 };
	BYTE NOP_2B[2] = { 0x90, 0x90 };
	BYTE NOP_3B[3] = { 0x90,0x90,0x90 };
	BYTE NOP_4B[4] = { 0x90,0x90,0x90,0x90 };
	BYTE NOP_5B[5] = { 0x90,0x90,0x90,0x90,0x90 };
	BYTE NOP_6B[6] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
	BYTE NOP_7B[7] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
	BYTE NOP_8B[8] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
	BYTE NOP_9B[9] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
	BYTE NOP_10B[10] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
};

extern ASpace aSpace;
extern patternClass PatternClass;
extern unstableOffsets UnstableOffsets;
extern NOPs Nops;
extern int Spinhack;
extern bool laghack;
extern bool speedhack;
extern char* mapname;
extern bool* ptrCLAG;
extern char* serverip;

#endif
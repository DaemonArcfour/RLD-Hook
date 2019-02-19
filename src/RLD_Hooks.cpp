#include "RLD_Hooks.h"
#define CRASHLEN 21845
//Initialize structures
ASpace aSpace;
patternClass PatternClass;
unstableOffsets UnstableOffsets;

//Initialize functions
CHAT_PrintChatString	orgCHAT_PrintChatString =	nullptr;
AddCommandString		orgAddCommandString =		nullptr;
func_GetMD5				orgGetMD5 =					nullptr;
NET_SendPacket			orgSendPacket =				nullptr;
FindCVar				_FindCVar =					nullptr;
o_sendTo				org_sendTo =				nullptr;
func_AimLineAttack		orgAimLineAttack =			nullptr;
CLReqSnap cl_reqsnap = nullptr;
CLAuth cl_auth = nullptr;
CPrint CPrintf = NULL;

// Unstable stuff. Recode when have time.
char* mapname = (char*)UnstableOffsets.pointer_mapname;
char* serverip = (char*)UnstableOffsets.pointer_serverip;
bool* ptrCLAG = (bool*)UnstableOffsets.pointer_clientlag; // Currently not used anywhere

bool speedhack = false;
int twice = 0;
int Spinhack = 0;
bool laghack = false;


void __fastcall AttemptAuthentication(void *_this);
int RequestSnapshot(void);
int __stdcall hijacked_sendTo(SOCKET s, const char *buf, int len, int flags, const void* to, int tolen) 
{
	static char* mapnameold = new char[64];
	
	//Server crasher
		//Nope
	//Worst method to detect a map change. Hook changemap/map later.
	if (strcmp(mapnameold, mapname) != 0) {
		memset(mapnameold, 0, sizeof(mapnameold));
		memcpy(mapnameold, mapname, std::string(mapname).length());
		printf("Packet recorder: created a rec dir \"%s\" Possible Errors:\"%d\"\n", mapnameold, SetRecEnv());
	}

	if (gRLD_CVars.rld_start_packet_saving_sequence == 1 && gNet_Packet_Backup_Quantity != 0) {
		saveSequence();
		CPrintf("\\cvSequence saved, setting the CVar to 0.\n");
		orgAddCommandString("rld_start_packet_saving_sequence 0", 0);
	}
	if (gRLD_CVars.rld_start_packet_loading_sequence == 1) {
		CPrintf("\\cvSequence loaded, setting the CVar to 0.\n");
		loadSequence();
		
		orgAddCommandString("rld_start_packet_loading_sequence 0", 0);
	}

	if (gRLD_CVars.rld_record_packets == 1) {
		pr_record(buf, len);
	}
	else
		gNet_Packet_Quantity = 0;

	if (gRLD_CVars.rld_play_packets == true) {
		if (gNet_Packet_Played == gNet_Packet_Backup_Quantity) {
			orgAddCommandString("rld_play_packets 0",0);
			pr_clearbuf();
		}
		gNet_Packet_Played++;
		return org_sendTo(s, gNet_Buffer[gNet_Packet_Played], gNet_Buffer_len[gNet_Packet_Played], flags, to, tolen);
	}
	gNet_Packet_Played = 0;
	//printf("%s \n",buf);
	return org_sendTo(s, buf, len, flags, to, tolen);
}

void pCorder_hook() {
	auto dwAddress = reinterpret_cast<DWORD_PTR>(GetProcAddress(GetModuleHandleA("ws2_32.dll"), "sendto"));
	if (!dwAddress) {
		printf("Couldn't find sendTo address.\n");
	}
	if (MH_Initialize() != MH_OK)
	{
		printf("Bursted bagpipes! Oh dear, oh dear.\n");
	}
	if (MH_CreateHook((DWORD_PTR*)dwAddress, hijacked_sendTo, reinterpret_cast<void**>(&org_sendTo)) != MH_OK) {
		printf("MH_CreateHook fatal error:\n%s\n", MH_StatusToString(MH_CreateHook((DWORD_PTR*)dwAddress, hijacked_sendTo, reinterpret_cast<void**>(&org_sendTo))));
	}
	if (MH_EnableHook((DWORD_PTR*)dwAddress) != MH_OK) {
		printf("MH_EnableHook fatal error.\n");
	}
	std::cout << "SendTo found" << std::endl;
}

int __fastcall NETWORK_SendPacket(const void **edx,void * suck, int a2, int a3) {

	if (gRLD_CVars.rld_lag == true) {
		memset((void*)(bool*)0x986C89, 0, sizeof(bool));
		return 0;
	}

//	std::cout << (char*)*edx << std::endl;;
	return orgSendPacket(edx, a2, a3);
}

void DLL_Entry() {
	StaticPatcher::Miscellaneous::OpenConsole();
	aSpace.SLen = (DWORD)GetModuleHandle("fmodex");
	//orgAddCommandString = (AddCommandString)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcAddCommandString[0], PatternClass.funcAddCommandString[1]);
	orgAddCommandString = (AddCommandString)0x41D980;
	//std::cout << StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcAddCommandString[0], PatternClass.funcAddCommandString[1]) << std::endl;
	_FindCVar = (FindCVar)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcFindCVar[0], PatternClass.funcFindCVar[1]);
	CPrintf = (CPrint)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcConPrintf[0], PatternClass.funcConPrintf[1]);
	Patch::Coopinfo();
	Patch::Coopspy(); // Doesn't work with zcc
	Patch::Crosshair(); // Doesn't work with zcc
	Patch::Drop();
	Patch::FakeAngle(); // Doesn't work with zcc
	Patch::IdentifyTarget(); // Doesn't work with zcc
	//Patch::LightAmbient(); // Doesn't work with zcc
	Patch::Name();
	Patch::SetCheats();
	Patch::RemoveWallhackProtection();
	orgSendPacket = (NET_SendPacket)DetourFunction((PBYTE)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcSendPacket[0], PatternClass.funcSendPacket[1]), (PBYTE)NETWORK_SendPacket);
	orgCHAT_PrintChatString = (CHAT_PrintChatString)DetourFunction((PBYTE)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcPrintChatMsg[0], PatternClass.funcPrintChatMsg[1]),(PBYTE)hkCHAT_PrintChatString);
	cl_auth = (CLAuth)DetourFunction((PBYTE)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcAuthClient[0], PatternClass.funcAuthClient[1]), (PBYTE)AttemptAuthentication);
	cl_reqsnap = (CLReqSnap)DetourFunction((PBYTE)StaticPatcher::SearchOffset::BytePattern(aSpace.EImage, aSpace.SLen, (PBYTE)PatternClass.funcReqSnapshot[0], PatternClass.funcReqSnapshot[1]), (PBYTE)RequestSnapshot);
	printf("Speedhack loaded!\n");
	printf("Lag hack loaded!\n");
	pCorder_hook();
	setCVars();
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)tAutoHeal, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)tKeyChecker, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)tRefreshCVars, NULL, NULL, NULL);
	srand(time(NULL));
	HookGL();
	orgAimLineAttack = (func_AimLineAttack)0x4CD4A0;
	Sleep(1000);
	Greeting();
	/*while (1) {
		if (gRLD_CVars.rld_autoshoot) {
			autoshoot();
		}
		Sleep(1);

	}*/
}

void decolor(char *pszString)
{
	char	*p;
	char	c;
	char	*pszEnd;
	p = pszString;
	while ((c = *p)){
		if (c == '\034'){
			pszEnd = p + 1;
			switch (*pszEnd){
			case '[':
				while ((*pszEnd != ']') && (*pszEnd != 0))
					pszEnd++;
				break;
			default:
				break;
			}
			if (*pszEnd != 0)
				pszEnd++;
			const ULONG ulLength = strlen(pszEnd);
			for (ULONG i = 0; i < ulLength; ++i)
				p[i] = pszEnd[i];
			p[ulLength] = 0;
		}
		else
			p++;
	}
}
void __fastcall hkCHAT_PrintChatString(int ulPlayer, int ulMode, const char *pszString) {
	static char* nickdecolor = new char[124];
	std::string nick = StaticPatcher::InfoGathering::GetStringFromAddress(UnstableOffsets.pointer_playername + 0x55C * ulPlayer);
	nickdecolor = _strdup(nick.c_str());
	decolor(nickdecolor);
	printf("[%s] %s\n", nickdecolor, pszString);
orgCHAT_PrintChatString(ulPlayer, ulMode, pszString);
}

void __fastcall AttemptAuthentication(void *_this)
{
	if (gRLD_CVars.rld_send_auth)
		return cl_auth(_this);
	
}

int RequestSnapshot() {
	if (gRLD_CVars.rld_req_snapshot)
		return cl_reqsnap();
}
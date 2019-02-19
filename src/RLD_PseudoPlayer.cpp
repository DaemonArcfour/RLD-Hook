#include "RLD_PseudoPlayer.h"
pseudoPlayer PlayerClass[64];
DWORD VAR_Health = UnstableOffsets.pointer_playerhealth;
DWORD VAR_Name = UnstableOffsets.pointer_playername;
DWORD VAR_ConsolePlayer = UnstableOffsets.pointer_playerid;
DWORD ESC_PlayerClass = 0x55C;
int LocalPlayer = 0;
void findSelf() {
	PlayerClass[LocalPlayer].self = false;
	LocalPlayer = StaticPatcher::InfoGathering::GetIntegerFromAddress(VAR_ConsolePlayer);
	PlayerClass[LocalPlayer].self = true;
}

void update_LocalPlayerInfo() {
	
	for (int i = 0; i < 64; i++) {
		PlayerClass[i].Health = StaticPatcher::InfoGathering::GetIntegerFromAddress(VAR_Health + ESC_PlayerClass*i);
	}
	findSelf();
}
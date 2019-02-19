#include "RLD_Autoshoot.h"


void autoshoot() {
	DWORD32 *mo = (DWORD32*)0x11F09B8;
	if (mo)
	{
		void *_this = nullptr;
		unsigned int moPlayer = mo[343 * StaticPatcher::InfoGathering::GetIntegerFromAddress(UnstableOffsets.pointer_playerid) ];
		unsigned int moPlayerAngle = *(DWORD32 *)(moPlayer + 48);
		if (moPlayer && moPlayerAngle) {
			orgAimLineAttack(moPlayer, moPlayerAngle, 0x8000000, &_this,0,0,0,0);
			//std::cout << _this << " ";
			if (_this != NULL) {
				orgAddCommandString("autoshoot", 0);
			}
		}
	}
}

#include "RLD_ASM.h"
#define ANGLE_45		(0x20000000)
#define ANGLE_180		(0x80000000)
DWORD AnglePatchJMP = 0x5FEF65;
DWORD LightAmbientPatchJMP = 0x67C403;
int *ptrLightLevel = (int*)0x013FEB90;
int LightLevel = 0;

__declspec(naked) void ASM_LightAmbient() {
	LightLevel = *ptrLightLevel;
	_asm {
		mov eax, LightLevel
		JMP LightAmbientPatchJMP;
	}

}

__declspec(naked) void ASM_FakeAngle()
{
	_asm {
		CMP Spinhack, 1
		JE CV1
		JMP AnglePatchJMP
		CV1 :
		ADD EAX, ANGLE_180
			JMP AnglePatchJMP

	}
}
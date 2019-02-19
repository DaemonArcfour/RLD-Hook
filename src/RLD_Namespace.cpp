#include "RLD_Namespace.h"
NOPs Nops;
namespace Patch {
	void Drop() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pDrop[0], PatternClass.pDrop[1]);
		if (!Offset) {
			printf("Couldn't patch Drop CCMD\n");
			return;
		}
		printf("Drop patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(aSpace.pDrop, Offset, sizeof(aSpace.pDrop));
	}

	void Name() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pName[0], PatternClass.pName[1]);
		if (!Offset) {
			printf("Couldn't patch Name CCMD\n");
			return;
		}
		printf("Name patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(aSpace.pName, Offset, sizeof(aSpace.pName));
	}
	 
	void Crosshair() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pCrosshair[0], PatternClass.pCrosshair[1]);
		if (!Offset) {
			printf("Couldn't patch Crosshair DMFLAG\n");
			return;
		}
		printf("Crosshair patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(Nops.NOP_6B, Offset, sizeof(Nops.NOP_6B));
	}

	void Coopinfo() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pCInfo[0], PatternClass.pCInfo[1]);
		if (!Offset) {
			printf("Couldn't patch Coopinfo DMFLAG\n");
			return;
		}
		printf("Coopinfo patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(Nops.NOP_6B, Offset, sizeof(Nops.NOP_6B));
	}

	void IdentifyTarget() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pITarget[0], PatternClass.pITarget[1]);
		if (!Offset) {
			printf("Couldn't patch IdentifyTarget DMFLAG\n");
			return;
		}
		printf("Identify Target patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(Nops.NOP_6B, Offset, sizeof(Nops.NOP_6B));
	}

	void Coopspy() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pCoopSpy[0], PatternClass.pCoopSpy[1]);
		if (!Offset) {
			printf("Couldn't patch Coopspy DMFLAG\n");
			return;
		}
		printf("Coopspy patched! [0x%x]\n", Offset);
		StaticPatcher::Patching::WriteBytes(Nops.NOP_6B, Offset, sizeof(Nops.NOP_6B));
	}

	void LightAmbient() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.pLamb[0], PatternClass.pLamb[1]);
		StaticPatcher::Patching::CreateWarp((PBYTE)Offset, (DWORD)ASM_LightAmbient, 0x7);
		printf("Light Ambient patched! [0x%x]\n", Offset);
	}

	void FakeAngle() {
		DWORD Offset = StaticPatcher::SearchOffset::BytePattern(aSpace.EImage,
			aSpace.SLen, (PBYTE)PatternClass.aAngle[0], PatternClass.aAngle[1]);
		if (!Offset) {
			printf("Couldn't create a codecave for fake angles\n");
			return;
		}
		printf("Fake angles codecave created! [0x%x]\n", Offset);
		StaticPatcher::Patching::CreateWarp((PBYTE)Offset, (DWORD)ASM_FakeAngle, 0x6);
	}
	void SetCheats() {
		StaticPatcher::Freeze::FreezeInteger(1, UnstableOffsets.pointer_cheats);
		Sleep(10);
		printf("Forced sv_cheats: %d!\n", StaticPatcher::InfoGathering::GetIntegerFromAddress(UnstableOffsets.pointer_cheats));
	}
	void RemoveWallhackProtection() {
		StaticPatcher::Patching::WriteBytes(aSpace.remWHp_1, 0x6662F1, sizeof(aSpace.remWHp_1));
		StaticPatcher::Patching::WriteBytes(Nops.NOP_2B, 0x666358, sizeof(Nops.NOP_2B));
		StaticPatcher::Patching::WriteBytes(aSpace.remWHp_2, 0x66635F, sizeof(aSpace.remWHp_2));
		printf("Wallhack protection removed.\n");
	}
	
}
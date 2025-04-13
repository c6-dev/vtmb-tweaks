#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

UInt32 vampire_base = 0;

CGlobalVars* gpGlobals = nullptr;

// credits to davi aka funkkiy for the original implementation
void __fastcall AngularMoveHook(void* a1, void* edx, void* a2, float flSpeed)
{
	if (*(UInt32*)a1 == vampire_base + 0x454B94) { // CRotDoor only
		if (gpGlobals == nullptr)
		{
			gpGlobals = *(CGlobalVars**)(vampire_base + 0x70B228);
		}
		flSpeed *= (1.0f / gpGlobals->frametime) / 60.0f;
	}
	ThisCall(vampire_base + 0x1C17E0, a1, a2, flSpeed);
}

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;
		SafeWriteBuf(vampire_base + 0xF3A66, (void*)"\xB9\x02\x00\x00\x00\x90\x90", 7);
		WriteRelJump(vampire_base + 0xDAB2, (UInt32)AngularMoveHook);
		SafeWriteBuf(vampire_base + 0xF08B6, (void*)"\x6A\x00\x90\x90\x90", 5); // stops doors from auto-closing
	}
}

#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

UInt32 vampire_base = 0;
void __fastcall DropAllWeaponsHook(void* a1)
{
	for (int i = 0; i < 224; i++)
	{
		void* weapon = ThisCall<void*>(vampire_base + 0x100B4, a1, i); // CBaseCombatCharacter::GetWeapon
		if (weapon)
		{
			ThisCall(vampire_base + 0x32D0C0, a1, weapon, 0, 0); // CBaseCombatCharacter::Weapon_Drop
		}
	}
}

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;
		WriteRelCall(vampire_base + 0x32BA84, (UInt32)DropAllWeaponsHook);
	}
}

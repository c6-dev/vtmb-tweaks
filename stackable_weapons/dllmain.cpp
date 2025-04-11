#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

UInt32 vampire_base = 0;
bool droppedActive = false;

bool __fastcall ShouldDropActive(CBaseCombatWeapon* weapon)
{
	droppedActive = (!weapon->IsStackable() || weapon->stackCount <= 1);
	return droppedActive;
}

__declspec(naked) void DropStackableActiveWeaponHook()
{
	__asm
	{
		mov ecx, esi
		call ShouldDropActive
		test al, al
		jz DROPONE
		mov eax, dword ptr ds:[edi]
		mov ecx, edi
		call dword ptr ds:[eax+0x608]
		mov eax, vampire_base
		add eax, 0x32D14C
		jmp eax
	DROPONE:
		mov eax, vampire_base
		add eax, 0x32D16F
		jmp eax
	}
}

bool __fastcall SwitchToNextBestWeaponHook(void* player, void* edx, void* weapon)
{
	if (droppedActive)
	{
		droppedActive = false;
		return ThisCall<bool>(vampire_base + 0x138D6, player, 0);
	}
	return true;
}

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;
		WriteRelJump(vampire_base + 0x32D142, (UInt32)DropStackableActiveWeaponHook);
		WriteRelCall(vampire_base + 0x17788C, (UInt32)SwitchToNextBestWeaponHook);
		SafeWrite8(vampire_base + 0x177227, 0xEB);
	}
}

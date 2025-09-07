#include "stackable_weapons.h"
#include "safewrite.h"
#include "calls.h"
#include "defs.h"

extern UInt32 vampire_base;

namespace {

	bool __fastcall ShouldDropActive(CBaseCombatWeapon* weapon)
	{
		return (!weapon->IsStackable() || weapon->stackCount <= 1);
	}

	__declspec(naked) void DropStackableActiveWeaponHook()
	{
		__asm
		{
			mov ecx, esi
			call ShouldDropActive
			test al, al
			jz DROPONE
			mov eax, dword ptr ds : [edi]
			mov ecx, edi
			call dword ptr ds : [eax + 0x608]
			mov eax, vampire_base
			add eax, 0x32D14C
			jmp eax
		DROPONE :
			mov eax, vampire_base
			add eax, 0x32D16F
			jmp eax
		}
	}

	bool __fastcall SwitchToNextBestWeaponHook(void* player, void* edx, void* weapon)
	{
		UInt32 hActiveWeapon = ThisCall<UInt32>(vampire_base + 0x7E19, player);
		if (hActiveWeapon == NULL) 
		{
			return ThisCall<bool>(vampire_base + 0x138D6, player, 0);
		}
		return true;
	}

	// if player is about to pick up a stackable weapon, return nullptr as if he doesn't own it to allow picking up
	CBaseCombatWeapon* __fastcall PickUpStackableHook(void* player, void* edx, char* weaponType, int a2)
	{
		CBaseCombatWeapon* weapon = ThisCall<CBaseCombatWeapon*>(vampire_base + 0x151B8, player, weaponType, a2); // OwnsThisType
		if (weapon != nullptr && weapon->IsStackable())
		{
			return nullptr;
		}
		return weapon;
	}

}

void stackable_weapons::InitVampireHooks()
{
	WriteRelJump(vampire_base + 0x32D142, (UInt32)DropStackableActiveWeaponHook);
	WriteRelCall(vampire_base + 0x17788C, (UInt32)SwitchToNextBestWeaponHook);
	WriteRelCall(vampire_base + 0x17724E, (UInt32)PickUpStackableHook);
}
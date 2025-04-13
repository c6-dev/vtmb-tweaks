#include "npcs_drop_all_weapons.h"
#include "safewrite.h"
#include "calls.h"
#include "defs.h"
extern UInt32 vampire_base;

namespace {
	void __fastcall DropAllWeaponsHook(void* a1)
	{
		for (int i = 0; i < 224; i++)
		{
			CBaseCombatWeapon* weapon = ThisCall<CBaseCombatWeapon*>(vampire_base + 0x100B4, a1, i); // CBaseCombatCharacter::GetWeapon
			if (weapon)
			{
				ThisCall(vampire_base + 0x32D0C0, a1, weapon, 0, 0); // CBaseCombatCharacter::Weapon_Drop
			}
		}
	}
}

void npcs_drop_all_weapons::InitVampireHooks()
{
	WriteRelCall(vampire_base + 0x32BA84, (UInt32)DropAllWeaponsHook);
}
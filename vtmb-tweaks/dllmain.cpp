#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "types.h"
#include "door_helper.h" 
#include "no_corpse_despawn.h"
#include "no_tracers.h"
#include "non_solid_ragdolls.h"
#include "npcs_drop_all_weapons.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

UInt32 vampire_base = 0;

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;
		no_corpse_despawn::InitVampireHooks();
		no_tracers::InitVampireHooks();
		npcs_drop_all_weapons::InitVampireHooks();
		non_solid_ragdolls::InitVampireHooks();
		door_helper::InitVampireHooks();	
	}
}

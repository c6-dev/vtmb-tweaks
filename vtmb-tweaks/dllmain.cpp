#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "types.h"
#include "door_helper.h" 
#include "no_corpse_despawn.h"
#include "no_tracers.h"
#include "non_solid_ragdolls.h"
#include "npcs_drop_all_weapons.h"
#include "stackable_weapons.h"

#include "SimpleIni.h"
#include "logging.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

UInt32 vampire_base = 0;
CSimpleIniA ini;
std::ofstream Log::LOG("vtmb-tweaks.log");
float tweaks_version = 0.9f;

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;
		ini.SetUnicode();
		ini.LoadFile("Bin\\loader\\vtmb-tweaks.ini");

		bool bNoCorpseDespawn = ini.GetBoolValue("MAIN", "bNoCorpseDespawn");
		if (bNoCorpseDespawn) no_corpse_despawn::InitVampireHooks();

		bool bNoTracers = ini.GetBoolValue("MAIN", "bNoTracers");
		if (bNoTracers)	no_tracers::InitVampireHooks();

		bool bNPCsDropAllWeapons = ini.GetBoolValue("MAIN", "bNPCsDropAllWeapons");
		if (bNPCsDropAllWeapons) npcs_drop_all_weapons::InitVampireHooks();

		bool bNonSolidRagdolls = ini.GetBoolValue("MAIN", "bNonSolidRagdolls");
		if (bNonSolidRagdolls) non_solid_ragdolls::InitVampireHooks();

		bool bStackableWeapons = ini.GetBoolValue("MAIN", "bStackableWeapons");
		if (bStackableWeapons) stackable_weapons::InitVampireHooks();

		door_helper::bFixDoorsAtHighFPS = ini.GetBoolValue("MAIN", "bFixDoorsAtHighFPS");
		door_helper::bNoDoorAutoclose = ini.GetBoolValue("MAIN", "bNoDoorAutoClose");
		door_helper::InitVampireHooks();

		Log() << "vtmb-tweaks loaded.";
		Log() << "vtmb-tweaks version: " << tweaks_version;
	}
}

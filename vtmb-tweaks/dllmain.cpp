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

UInt32 vampire_base = 0;
UInt32 client_base = 0;
CSimpleIniA ini;
std::ofstream Log::LOG("vtmb-tweaks.log");
float tweaks_version = 0.95f;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		ini.SetUnicode();
		ini.LoadFile("Bin\\loader\\vtmb-tweaks.ini");
		Log() << "Loading vtmb-tweaks, version: " << tweaks_version;
	}

	return TRUE;
	
}

extern "C" __declspec(dllexport) void loaded_vampire()
{
	HMODULE vampire = GetModuleHandleA("vampire.dll");
	if (vampire != NULL)
	{
		vampire_base = (UInt32)vampire;

		bool bNoCorpseDespawn = ini.GetBoolValue("MAIN", "bNoCorpseDespawn");
		if (bNoCorpseDespawn) no_corpse_despawn::InitVampireHooks();
		
		bool bNPCsDropAllWeapons = ini.GetBoolValue("MAIN", "bNPCsDropAllWeapons");
		if (bNPCsDropAllWeapons) npcs_drop_all_weapons::InitVampireHooks();

		bool bNonSolidRagdolls = ini.GetBoolValue("MAIN", "bNonSolidRagdolls");
		if (bNonSolidRagdolls) non_solid_ragdolls::InitVampireHooks();

		bool bStackableWeapons = ini.GetBoolValue("MAIN", "bStackableWeapons");
		if (bStackableWeapons) stackable_weapons::InitVampireHooks();

		door_helper::bFixDoorsAtHighFPS = ini.GetBoolValue("MAIN", "bFixDoorsAtHighFPS");
		door_helper::bNoDoorAutoclose = ini.GetBoolValue("MAIN", "bNoDoorAutoClose");
		door_helper::InitVampireHooks();

		Log() << "vampire.dll patches loaded.";
	}
}

extern "C" __declspec(dllexport) void loaded_client()
{
	HMODULE client = GetModuleHandleA("client.dll");
	if (client != NULL)
	{
		client_base = (UInt32)client;
		bool bNoTracers = ini.GetBoolValue("MAIN", "bNoTracers");
		if (bNoTracers)	no_tracers::InitClientHooks();
		Log() << "client.dll patches loaded.";
		
	}
}

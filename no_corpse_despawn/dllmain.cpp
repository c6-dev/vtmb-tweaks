#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"

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
		SafeWrite8(vampire_base + 0x32C402, 0xEB);
		PatchMemoryNop(vampire_base + 0x265D72, 5);
	}
}

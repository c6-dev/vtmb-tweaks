#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

extern "C" __declspec(dllexport) void loaded_client()
{
	HMODULE client = GetModuleHandleA("client.dll");
	if (client != NULL)
	{
		UInt32 addr = (UInt32)client + 0x4099A;
		SafeWrite32(addr, 0xB0E9);
	}
}

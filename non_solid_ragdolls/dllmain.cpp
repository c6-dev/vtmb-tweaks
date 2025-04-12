#define WIN32_LEAN_AND_MEAN
#include "..\common\defs.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}


extern "C" __declspec(dllexport) void loaded_vampire() {
    HMODULE vampire = GetModuleHandleA("vampire.dll");
    if (vampire != NULL) {
        UInt32 addr = (UInt32)vampire + 0x154E90;
        SafeWriteBuf(addr, (void*)"\xB9\x01\x00\x00\x00\x90", 6);
    }
}

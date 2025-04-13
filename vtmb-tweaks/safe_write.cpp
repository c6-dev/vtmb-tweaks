#include "safe_write.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void SafeWrite32(UInt32 addr, UInt32 data)
{
	UInt32 oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt32*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void SafeWrite8(UInt32 addr, UInt32 data)
{
	UInt32	oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt8*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void PatchMemoryNop(UInt32 Address, UInt32 Size)
{
	DWORD d = 0;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &d);

	for (UInt32 i = 0; i < Size; i++)
		*(volatile BYTE*)(Address + i) = 0x90;

	VirtualProtect((LPVOID)Address, Size, d, &d);

	FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
}

void WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// call rel32
	SafeWrite8(jumpSrc, 0xE8);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);
}

void WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// jmp rel32
	SafeWrite8(jumpSrc, 0xE9);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);
}

void SafeWriteBuf(UInt32 addr, void* data, UInt32 len)
{
	UInt32    oldProtect;

	VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)addr, data, len);
	VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
}
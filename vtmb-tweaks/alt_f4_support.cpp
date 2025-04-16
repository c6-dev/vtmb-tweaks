// makes pressing Alt+F4 dispatch "exit" from anywhere by hooking engine Key_Event
#include "alt_f4_support.h"
#include "calls.h"
#include "safewrite.h"

extern UInt32 engine_base;

namespace
{
	bool HandleAltF4()
	{
		int altDown = *(int*)(engine_base + 0xD5FF50 + 4 * 132);
		int f4Down = *(int*)(engine_base + 0xD5FF50 + 4 * 138);
		if (altDown && f4Down)
		{
			CdeclCall(engine_base + 0x2DCC0, "exit\n"); // CBuf::AddText
			return true;
		}
		return false;

	}

	__declspec(naked) void HandleAltF4Hook()
	{
		__asm
		{
			call HandleAltF4
			test al, al
			jz DONE
			pop esi
			pop ebx
			add esp, 0x400
			retn
			DONE :
			mov eax, engine_base
			add eax, 0xD63510
			mov eax, dword ptr ds : [eax]
			test eax, eax
			mov ecx, engine_base
			add ecx, 0xA38F5
			jmp ecx

		}
	}
}
void alt_f4_support::InitEngineHooks()
{
	WriteRelJump(engine_base + 0xA38EE, (UInt32)HandleAltF4Hook);
}

#include "fov_reset_fix.h"

#include <cstdlib>

#include "safewrite.h"
extern UInt32 vampire_base;
namespace
{
	int gFov = 0;

	int __cdecl SetFOVHook(const char* value)
	{
		gFov = atoi(value);
		return gFov;
	}

	__declspec(naked) void ZoomOutHook()
	{
		__asm
		{
			mov ebx, gFov
			mov dword ptr ds:[edi+0x1E78], ebx
			pop edi
			pop esi
			pop ebx
			ret
		}
	}
}
void fov_reset_fix::InitVampireHooks()
{
	WriteRelCall(vampire_base + 0xD2DC1, (UInt32)SetFOVHook);
	WriteRelJump(vampire_base + 0x239E01, (UInt32)ZoomOutHook);
}

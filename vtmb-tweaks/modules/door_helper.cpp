#include "door_helper.h"
#include "calls.h"
#include "defs.h"
#include "safewrite.h"
extern UInt32 vampire_base;

namespace {
	CGlobalVars* gpGlobals = nullptr;

	// credits to davi aka funkkiy for the original implementation
	void __fastcall AngularMoveHook(void* a1, void* edx, void* a2, float flSpeed)
	{
		if (*(UInt32*)a1 == vampire_base + 0x454B94) { // CRotDoor only
			if (gpGlobals == nullptr)
			{
				gpGlobals = *(CGlobalVars**)(vampire_base + 0x70B228);
			}
			flSpeed *= (1.0f / gpGlobals->frametime) / 60.0f;
		}
		ThisCall(vampire_base + 0x1C17E0, a1, a2, flSpeed);
	}

	bool __fastcall ShouldGoDown(CBaseToggle* door)
	{
		if (*(UInt32*)door == vampire_base + 0x454B94) { // CRotDoor only
			UInt32* g_pEntityList = *(UInt32**)(vampire_base + 0x566458);
			CBaseEntity* activator = ThisCall<CBaseEntity*>(vampire_base + 0x9C8C, g_pEntityList, &door->m_hActivator); // CBaseEntityList::LookupEntity
			if (!activator || !activator->IsPlayer()) // skip doors activated by player
			{
				return true;
			}
			return false;
		}
		return true;
	}
	__declspec(naked) void RotDoorGoDownHook()
	{
		__asm
		{
			mov ecx, esi
			call ShouldGoDown
			test al, al
			jz DONE
			mov eax, dword ptr ds:[esi]
			push 0x1
			mov ecx, esi
			call dword ptr ds: [eax+0x3D0]
			DONE:
			pop esi
			retn
		}
	}
}

void door_helper::InitVampireHooks()
{
	if (bFixDoorsAtHighFPS) {
		SafeWriteBuf(vampire_base + 0xF3A66, (void*)"\xB9\x02\x00\x00\x00\x90\x90", 7);
		WriteRelJump(vampire_base + 0xDAB2, (UInt32)AngularMoveHook);
	}
	if (bNoDoorAutoclose) {
		WriteRelJump(vampire_base + 0xF09EB, (UInt32)RotDoorGoDownHook);
	}
}
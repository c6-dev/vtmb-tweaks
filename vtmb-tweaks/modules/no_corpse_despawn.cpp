#include "no_corpse_despawn.h"
#include "calls.h"
#include "defs.h"
#include "safewrite.h"

extern UInt32 vampire_base;
namespace
{
	void __fastcall FadeOnDeathHook(CBaseEntity* entity)
	{
		if (*(UInt32*)entity == vampire_base + 0x4C558C) // CNPC_VRat only
		{
			ThisCall(vampire_base + 0x11667, entity);
		}
	}
}

void no_corpse_despawn::InitVampireHooks()
{
	SafeWrite8(vampire_base + 0x32C402, 0xEB);
	WriteRelCall(vampire_base + 0x265D72, (UInt32)FadeOnDeathHook);
}

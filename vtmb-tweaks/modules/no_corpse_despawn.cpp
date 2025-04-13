#include "no_corpse_despawn.h"
#include "safewrite.h"
extern UInt32 vampire_base;

void no_corpse_despawn::InitVampireHooks()
{
	SafeWrite8(vampire_base + 0x32C402, 0xEB);
	PatchMemoryNop(vampire_base + 0x265D72, 5);
}

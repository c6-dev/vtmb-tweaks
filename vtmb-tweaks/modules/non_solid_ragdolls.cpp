#include "non_solid_ragdolls.h"
#include "safewrite.h"
#include "types.h"
extern UInt32 vampire_base;

void non_solid_ragdolls::InitVampireHooks()
{
	SafeWriteBuf(vampire_base + 0x154E90, (void*)"\xB9\x01\x00\x00\x00\x90", 6);
}
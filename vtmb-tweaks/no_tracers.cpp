#include "no_tracers.h"
#include "safe_write.h"
extern UInt32 vampire_base;

void no_tracers::InitVampireHooks()
{
	SafeWrite32(vampire_base + 0x4099A, 0xB0E9);
}
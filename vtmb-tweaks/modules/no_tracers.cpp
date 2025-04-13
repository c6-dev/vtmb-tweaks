#include "no_tracers.h"
#include "safewrite.h"
extern UInt32 client_base;

void no_tracers::InitClientHooks()
{
	SafeWrite32(client_base + 0x4099A, 0xB0E9);
}
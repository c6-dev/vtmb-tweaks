#pragma once
#include "types.h"

void SafeWrite32(UInt32 addr, UInt32 data);
void SafeWrite8(UInt32 addr, UInt32 data);
void PatchMemoryNop(UInt32 Address, UInt32 Size);
void WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt);
void WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt);
void SafeWriteBuf(UInt32 addr, void* data, UInt32 len);

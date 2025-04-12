#pragma once
#include "windows.h"
#include <utility>
#define UInt32 unsigned long
#define UInt8 unsigned char

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

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret ThisCall(UInt32 _addr, void* _this, Args ...args) {
	class T {};
	union {
		UInt32  addr;
		T_Ret(T::* func)(Args...);
	} u = { _addr };
	return ((T*)_this->*u.func)(std::forward<Args>(args)...);
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
class CBaseCombatWeapon {
public:
	CBaseCombatWeapon();
	~CBaseCombatWeapon();
	virtual void Unk01();
	virtual void Unk02();
	virtual void Unk03();
	virtual void Unk04();
	virtual void Unk05();
	virtual void Unk06();
	virtual void Unk07();
	virtual void Unk08();
	virtual void Unk09();
	virtual void Unk10();
	virtual void Unk11();
	virtual void Unk12();
	virtual void Unk13();
	virtual void Unk14();
	virtual void Unk15();
	virtual void Unk16();
	virtual void Unk17();
	virtual void Unk18();
	virtual void Unk19();
	virtual void Unk20();
	virtual void Unk21();
	virtual void Unk22();
	virtual void Unk23();
	virtual void Unk24();
	virtual void Unk25();
	virtual void Unk26();
	virtual void Unk27();
	virtual void Unk28();
	virtual void Unk29();
	virtual void Unk30();
	virtual void Unk31();
	virtual void Unk32();
	virtual void Unk33();
	virtual void Unk34();
	virtual void Unk35();
	virtual void Unk36();
	virtual void Unk37();
	virtual void Unk38();
	virtual void Unk39();
	virtual void Unk40();
	virtual void Unk41();
	virtual void Unk42();
	virtual void Unk43();
	virtual void Unk44();
	virtual void Unk45();
	virtual void Unk46();
	virtual void Unk47();
	virtual void Unk48();
	virtual void Unk49();
	virtual void Unk50();
	virtual void Unk51();
	virtual void Unk52();
	virtual void Unk53();
	virtual void Unk54();
	virtual void Unk55();
	virtual void Unk56();
	virtual void Unk57();
	virtual void Unk58();
	virtual void Unk59();
	virtual void Unk60();
	virtual void Unk61();
	virtual void Unk62();
	virtual void Unk63();
	virtual void Unk64();
	virtual void Unk65();
	virtual void Unk66();
	virtual void Unk67();
	virtual void Unk68();
	virtual void Unk69();
	virtual void Unk70();
	virtual void Unk71();
	virtual void Unk72();
	virtual void Unk73();
	virtual void Unk74();
	virtual void Unk75();
	virtual void Unk76();
	virtual void Unk77();
	virtual void Unk78();
	virtual void Unk79();
	virtual void Unk80();
	virtual void Unk81();
	virtual void Unk82();
	virtual void Unk83();
	virtual void Unk84();
	virtual void Unk85();
	virtual void Unk86();
	virtual void Unk87();
	virtual void Unk88();
	virtual void Unk89();
	virtual void Unk90();
	virtual void Unk91();
	virtual void Unk92();
	virtual void Unk93();
	virtual void Unk94();
	virtual void Unk95();
	virtual void Unk96();
	virtual void Unk97();
	virtual void Unk98();
	virtual void Unk99();
	virtual void Unk100();
	virtual void Unk101();
	virtual void Unk102();
	virtual void Unk103();
	virtual void Unk104();
	virtual void Unk105();
	virtual void Unk106();
	virtual void Unk107();
	virtual void Unk108();
	virtual void Unk109();
	virtual void Unk110();
	virtual void Unk111();
	virtual void Unk112();
	virtual void Unk113();
	virtual void Unk114();
	virtual void Unk115();
	virtual void Unk116();
	virtual void Unk117();
	virtual void Unk118();
	virtual void Unk119();
	virtual void Unk120();
	virtual void Unk121();
	virtual void Unk122();
	virtual void Unk123();
	virtual void Unk124();
	virtual void Unk125();
	virtual void Unk126();
	virtual void Unk127();
	virtual void Unk128();
	virtual void Unk129();
	virtual void Unk130();
	virtual void Unk131();
	virtual void Unk132();
	virtual void Unk133();
	virtual void Unk134();
	virtual void Unk135();
	virtual void Unk136();
	virtual void Unk137();
	virtual void Unk138();
	virtual void Unk139();
	virtual void Unk140();
	virtual void Unk141();
	virtual void Unk142();
	virtual void Unk143();
	virtual void Unk144();
	virtual void Unk145();
	virtual void Unk146();
	virtual void Unk147();
	virtual void Unk148();
	virtual void Unk149();
	virtual void Unk150();
	virtual void Unk151();
	virtual void Unk152();
	virtual void Unk153();
	virtual void Unk154();
	virtual void Unk155();
	virtual void Unk156();
	virtual void Unk157();
	virtual void Unk158();
	virtual void Unk159();
	virtual void Unk160();
	virtual void Unk161();
	virtual void Unk162();
	virtual void Unk163();
	virtual void Unk164();
	virtual void Unk165();
	virtual void Unk166();
	virtual void Unk167();
	virtual void Unk168();
	virtual void Unk169();
	virtual void Unk170();
	virtual void Unk171();
	virtual void Unk172();
	virtual void Unk173();
	virtual void Unk174();
	virtual void Unk175();
	virtual void Unk176();
	virtual void Unk177();
	virtual void Unk178();
	virtual void Unk179();
	virtual void Unk180();
	virtual void Unk181();
	virtual void Unk182();
	virtual void Unk183();
	virtual void Unk184();
	virtual void Unk185();
	virtual void Unk186();
	virtual void Unk187();
	virtual void Unk188();
	virtual void Unk189();
	virtual void Unk190();
	virtual void Unk191();
	virtual void Unk192();
	virtual void Unk193();
	virtual void Unk194();
	virtual void Unk195();
	virtual void Unk196();
	virtual void Unk197();
	virtual void Unk198();
	virtual void Unk199();
	virtual void Unk200();
	virtual void Unk201();
	virtual void Unk202();
	virtual void Unk203();
	virtual void Unk204();
	virtual void Unk205();
	virtual void Unk206();
	virtual void Unk207();
	virtual void Unk208();
	virtual void Unk209();
	virtual void Unk210();
	virtual void Unk211();
	virtual void Unk212();
	virtual void Unk213();
	virtual void Unk214();
	virtual void Unk215();
	virtual void Unk216();
	virtual void Unk217();
	virtual void Unk218();
	virtual void Unk219();
	virtual void Unk220();
	virtual void Unk221();
	virtual void Unk222();
	virtual void Unk223();
	virtual void Unk224();
	virtual void Unk225();
	virtual void Unk226();
	virtual void Unk227();
	virtual void Unk228();
	virtual void Unk229();
	virtual void Unk230();
	virtual void Unk231();
	virtual void Unk232();
	virtual void Unk233();
	virtual void Unk234();
	virtual void Unk235();
	virtual void Unk236();
	virtual void Unk237();
	virtual void Unk238();
	virtual void Unk239();
	virtual void Unk240();
	virtual void Unk241();
	virtual void Unk242();
	virtual void Unk243();
	virtual void Unk244();
	virtual void Unk245();
	virtual void Unk246();
	virtual void Unk247();
	virtual void Unk248();
	virtual void Unk249();
	virtual void Unk250();
	virtual void Unk251();
	virtual void Unk252();
	virtual void Unk253();
	virtual void Unk254();
	virtual void Unk255();
	virtual void Unk256();
	virtual void Unk257();
	virtual void Unk258();
	virtual void Unk259();
	virtual void Unk260();
	virtual void Unk261();
	virtual void Unk262();
	virtual void Unk263();
	virtual void Unk264();
	virtual void Unk265();
	virtual void Unk266();
	virtual void Unk267();
	virtual void Unk268();
	virtual void Unk269();
	virtual void Unk270();
	virtual void Unk271();
	virtual void Unk272();
	virtual void Unk273();
	virtual void Unk274();
	virtual void Unk275();
	virtual void Unk276();
	virtual void Unk277();
	virtual void Unk278();
	virtual void Unk279();
	virtual void Unk280();
	virtual void Unk281();
	virtual void Unk282();
	virtual void Unk283();
	virtual void Unk284();
	virtual void Unk285();
	virtual void Unk286();
	virtual void Unk287();
	virtual void Unk288();
	virtual void Unk289();
	virtual void Unk290();
	virtual void Unk291();
	virtual void Unk292();
	virtual void Unk293();
	virtual void Unk294();
	virtual void Unk295();
	virtual void Unk296();
	virtual void Unk297();
	virtual void Unk298();
	virtual void Unk299();
	virtual void Unk300();
	virtual void Unk301();
	virtual void Unk302();
	virtual void Unk303();
	virtual void Unk304();
	virtual void Unk305();
	virtual void Unk306();
	virtual void Unk307();
	virtual void Unk308();
	virtual void Unk309();
	virtual void Unk310();
	virtual void Unk311();
	virtual void Unk312();
	virtual void Unk313();
	virtual void Unk314();
	virtual void Unk315();
	virtual void Unk316();
	virtual void Unk317();
	virtual void Unk318();
	virtual void Unk319();
	virtual void Unk320();
	virtual void Unk321();
	virtual void Unk322();
	virtual void Unk323();
	virtual void Unk324();
	virtual void Unk325();
	virtual void Unk326();
	virtual void Unk327();
	virtual void Unk328();
	virtual void Unk329();
	virtual void Unk330();
	virtual void Unk331();
	virtual void Unk332();
	virtual void Unk333();
	virtual void Unk334();
	virtual void Unk335();
	virtual void Unk336();
	virtual void Unk337();
	virtual void Unk338();
	virtual void Unk339();
	virtual void Unk340();
	virtual void Unk341();
	virtual void Unk342();
	virtual void Unk343();
	virtual void Unk344();
	virtual void Unk345();
	virtual void Unk346();
	virtual void Unk347();
	virtual void Unk348();
	virtual void Unk349();
	virtual void Unk350();
	virtual void Unk351();
	virtual void Unk352();
	virtual void Unk353();
	virtual void Unk354();
	virtual void Unk355();
	virtual void Unk356();
	virtual void Unk357();
	virtual void Unk358();
	virtual void Unk359();
	virtual void Unk360();
	virtual void Unk361();
	virtual void Unk362();
	virtual void Unk363();
	virtual void Unk364();
	virtual void Unk365();
	virtual void Unk366();
	virtual void Unk367();
	virtual void Unk368();
	virtual void Unk369();
	virtual void Unk370();
	virtual void Unk371();
	virtual bool IsStackable();

	UInt8 gap00[0x8CA];
	int stackCount;
};
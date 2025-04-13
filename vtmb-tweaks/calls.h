#pragma once
#include "types.h"
#include <utility>
template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret ThisCall(UInt32 _addr, void* _this, Args ...args) {
	class T {};
	union {
		UInt32  addr;
		T_Ret(T::* func)(Args...);
	} u = { _addr };
	return ((T*)_this->*u.func)(std::forward<Args>(args)...);
}

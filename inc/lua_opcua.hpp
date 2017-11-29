#pragma once

namespace lua_opcua {

#if defined _MSC_VER
	#define LUA_OPCUA_VC
#elif defined __GNUC__
	#define LUA_OPCUA_GCC
#elif defined __clang__
	#define LUA_OPCUA_CLANG
#endif

#if defined LUA_OPCUA_VC
	#if defined LUA_OPCUA_DLL
		#if defined LUA_OPCUA_BUILD
			#define LUA_OPCUA_API __declspec(dllexport)
		#else
			#define LUA_OPCUA_API __declspec(dllexport)
		#endif // LUA_OPCUA_BUILD - Building the Library vs. Using the Library
	#else
		#define LUA_OPCUA_API 
	#endif // Building a DLL vs. Static Library
#else // g++ / clang++
	#define LUA_OPCUA_API __attribute__ ((visibility ("default")))
#endif // LUA_OPCUA_BUILD

} // namespace lua_opcua 

extern "C" LUA_OPCUA_API int luaopen_opcua(lua_State *L);


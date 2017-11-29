#include "oolua.h"
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/**
	\file class_from_stack.cpp
	\brief Implement the non inline index_is_userdata functions and error generator
*/

/** \cond INTERNAL */
namespace OOLUA
{
	namespace INTERNAL
	{

#if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 1
#	if OOLUA_USERDATA_OPTIMISATION == 1
		bool index_is_userdata(lua_State* vm, int index, Lua_ud*& ud)
		{
#if defined LUA_VERSION_NUM && LUA_VERSION_NUM >= 502
/*lua_objlen may or may not be a macro for lua_rawlen in luaconfig.h for 5.2
 so lets just work regardless of the configuration used*/
#	define _oolua_len_ lua_rawlen
#else
#	define _oolua_len_ lua_objlen
#endif
			ud = static_cast<Lua_ud *>(lua_touserdata(vm, index));
			return ud && _oolua_len_(vm, index) == sizeof(Lua_ud) && OOLUA_CHECK_COOKIE(ud->flags);
#undef _oolua_len_
		}
#	else

		bool index_is_userdata(lua_State* vm, int index, Lua_ud*& ud)
		{
			ud = static_cast<Lua_ud *>(lua_touserdata(vm, index));
			if(!ud || !lua_getmetatable(vm, index)) return false;
			lua_pushlightuserdata(vm, lua_topointer(vm, LUA_REGISTRYINDEX));
			lua_rawget(vm, -2);
			bool result = lua_isnil(vm, -1) == 0;
			lua_pop(vm, 2);
			return result;
		}

#	endif

#endif

		void report_error_userdata_is_constant(lua_State* const vm, char const* pulling_class_type)
		{
			luaL_error(vm, "%s \"%s\" %s", "Tried to pull a none constant"
						, pulling_class_type
						, "pointer from a const pointer");
		} // LCOV_EXCL_LINE

	} // namespace INTERNAL //NOLINT
} // namespace OOLUA
/** \endcond  */
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

///////////////////////////////////////////////////////////////////////////////
///  @file oolua.cpp
///////////////////////////////////////////////////////////////////////////////

namespace OOLUA
{
	void set_global_to_nil(lua_State* vm, char const * name)
	{
		lua_pushnil(vm);
		lua_setglobal(vm, name);
	}

	bool set_global(lua_State* vm, char const* name, lua_CFunction instance)
	{
		lua_pushcclosure(vm, instance, 0);
		lua_setglobal(vm, name);
		return true;
	}

} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{
	namespace INTERNAL
	{
		bool protected_call_check_result(lua_State* vm, int pcall_result)
		{
			if (pcall_result == 0)return true;

#if OOLUA_STORE_LAST_ERROR == 1
			if (pcall_result != LUA_ERRMEM)set_error_from_top_of_stack_and_pop_the_error(vm);
#elif OOLUA_USE_EXCEPTIONS == 1
			if (pcall_result == LUA_ERRRUN)
				throw OOLUA::Runtime_error(vm, (OOLUA::ERROR::PopTheStack*)0);
			else if (pcall_result == LUA_ERRMEM) // LCOV_EXCL_LINE
				throw OOLUA::Memory_error(vm, (OOLUA::ERROR::PopTheStack*)0); //LCOV_EXCL_LINE
			else if (pcall_result == LUA_ERRERR)
				throw OOLUA::Runtime_error(vm, (OOLUA::ERROR::PopTheStack*)0);
#elif OOLUA_DEBUG_CHECKS == 1
			(void)vm;
			if (pcall_result == LUA_ERRRUN)
				assert(0 && "LUA_ERRRUN");
			else if (pcall_result == LUA_ERRMEM)
				assert(0 && "LUA_ERRMEM");
			else if (pcall_result == LUA_ERRERR)
				assert(0 && "LUA_ERRERR");
#else
			(void)vm;
#endif
			return false;
		}


		bool load_buffer_check_result(lua_State* vm, int result)
		{
			if (result == 0)return true;
#if OOLUA_STORE_LAST_ERROR == 1
			if (result != LUA_ERRMEM)set_error_from_top_of_stack_and_pop_the_error(vm);
#elif OOLUA_USE_EXCEPTIONS == 1
			if (result == LUA_ERRFILE)
				throw OOLUA::File_error(vm, (OOLUA::ERROR::PopTheStack*)0);
			else if (result == LUA_ERRSYNTAX)
				throw OOLUA::Syntax_error(vm, (OOLUA::ERROR::PopTheStack*)0);
			else if (result == LUA_ERRMEM ) // LCOV_EXCL_LINE
				throw OOLUA::Memory_error(vm, (OOLUA::ERROR::PopTheStack*)0); // LCOV_EXCL_LINE
#elif OOLUA_DEBUG_CHECKS == 1
			(void)vm;
			if (result == LUA_ERRSYNTAX)
				assert(0 && "syntax error");
			else if (result == LUA_ERRMEM)
				assert(0 && "memory error");
			else if (result == LUA_ERRFILE)
					assert(0 && "file error");
#else
			(void)vm;
#endif
			return false;
		}
	} // namespace INTERNAL //NOLINT
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{

	bool load_chunk(lua_State* vm, std::string const& chunk)
	{
#ifdef DEBUG
#	define chunk_name chunk.c_str()
#else
#	define chunk_name "userChunk"
#endif

		int res = luaL_loadbuffer(vm, chunk.c_str(), chunk.size(), chunk_name);
#undef chunk_name
		return INTERNAL::load_buffer_check_result(vm, res);
	}

	bool run_chunk(lua_State* vm, std::string const& chunk)
	{
		if( !load_chunk(vm, chunk) ) return false;
		int result = lua_pcall(vm, 0, LUA_MULTRET, 0);
		return INTERNAL::protected_call_check_result(vm, result);
	}

	bool run_file(lua_State* vm, std::string const & filename)
	{
		bool status = load_file(vm, filename);
		if(!status)return false;
		int result = lua_pcall(vm, 0, LUA_MULTRET, 0);
		return INTERNAL::protected_call_check_result(vm, result);
	}

	bool load_file(lua_State* vm, std::string const & filename)
	{
		int result = luaL_loadfile(vm, filename.c_str() );
		return INTERNAL::load_buffer_check_result(vm, result);;
	}

} //namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#if OOLUA_STORE_LAST_ERROR == 1


namespace OOLUA
{
	char const last_error_string[] = {"oolua_last_error"};
	void push_error_id_str(lua_State* vm)
	{
		lua_pushlstring(vm, last_error_string, (sizeof(last_error_string)/sizeof(char))-1);
	}
	void reset_error_value(lua_State* vm)
	{
		push_error_id_str(vm);
		lua_pushnil(vm);
		lua_settable(vm, LUA_REGISTRYINDEX);
	}
	std::string get_last_error(lua_State* vm)
	{
		push_error_id_str(vm);
		lua_gettable(vm, LUA_REGISTRYINDEX);
		std::string error;
		if ( lua_type(vm, -1) == LUA_TSTRING )
		{
			size_t len(0);
			char const* str = lua_tolstring(vm, -1, &len);
			error = std::string(str, len);
		}
		lua_pop(vm, 1);
		return error;
	}
	namespace INTERNAL
	{
		void set_error_from_top_of_stack_and_pop_the_error(lua_State* vm)
		{
			int error_index = lua_gettop(vm);
			push_error_id_str(vm);
			lua_pushvalue(vm, error_index);
			lua_settable(vm, LUA_REGISTRYINDEX);
			lua_pop(vm, 1);
		}
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA
#else
//default implementations
struct lua_State;

namespace OOLUA
{
	// LCOV_EXCL_START
	void reset_error_value(lua_State* /*vm*/) // NOLINT
	{}

	std::string get_last_error(lua_State* /*vm*/) // NOLINT
	{
		return std::string();
	}
	namespace INTERNAL
	{
		void set_error_from_top_of_stack_and_pop_the_error(lua_State* /*vm*/) // NOLINT
		{}
	} // namespace INTERNAL
	// LCOV_EXCL_STOP
} // namespace OOLUA

#endif
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#	if OOLUA_USE_EXCEPTIONS == 1

#	include <cstring>

namespace
{
	void copy_buffer(char* to, char const* from, size_t& sz)
	{
		sz = sz + 1 < OOLUA::ERROR::size ? sz : OOLUA::ERROR::size-2;
		memcpy(to, from, sz);
		to[sz < OOLUA::ERROR::size -2 ? sz : OOLUA::ERROR::size -1] = '\0';
	}
	size_t copy_buffer(char* to, char const* from)
	{
		size_t sz = strlen(from);
		copy_buffer(to, from, sz);
		return sz;
	}
} // namespace

namespace OOLUA
{
	Exception::Exception(lua_State* vm)
		: m_len(0) // LCOV_EXCL_LINE
	{
		char const* str = lua_tolstring(vm, -1, &m_len);
		copy_buffer(m_buffer, str, m_len);
	}

	Exception::Exception(lua_State* vm, ERROR::PopTheStack*)
		: m_len(0) // LCOV_EXCL_LINE
	{
		char const* str = lua_tolstring(vm, -1, &m_len);
		copy_buffer(m_buffer, str, m_len);
		lua_pop(vm, 1);
	}

	Exception::Exception(char const* msg)
		: m_len(0) // LCOV_EXCL_LINE
	{
		m_len = copy_buffer(m_buffer, msg);
	}

	Exception::Exception(Exception const& rhs)
		: std::exception(rhs)
		, m_len(rhs.m_len)
	{
		copy_buffer(m_buffer, rhs.m_buffer, m_len);
	}

	Exception& Exception::operator = (Exception const& rhs) throw()
	{
		m_len = rhs.m_len;
		copy_buffer(m_buffer, rhs.m_buffer, m_len);
		return *this;
	}

	char const* Exception::what() const throw()
	{
		return &m_buffer[0];
	}


	Syntax_error::Syntax_error(lua_State* vm, ERROR::PopTheStack* specialisation)
		: Exception(vm, specialisation)
	{}

	Runtime_error::Runtime_error(lua_State* vm, ERROR::PopTheStack* specialisation)
		: Exception(vm, specialisation)
	{}
	Runtime_error::Runtime_error(char const* msg)
		: Exception(msg)
	{}

	// LCOV_EXCL_START
	Memory_error::Memory_error(lua_State* vm, ERROR::PopTheStack* specialisation)
		: Exception(vm, specialisation)
	{}
	// LCOV_EXCL_STOP

	File_error::File_error(lua_State* vm, ERROR::PopTheStack* specialisation)
		: Exception(vm, specialisation)
	{}

	Type_error::Type_error(lua_State* vm, ERROR::PopTheStack* specialisation)
		:Exception(vm, specialisation)
	{}
} // namespace OOLUA

#endif //OOLUA_USE_EXCEPTIONS
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
Licence for int stack_trace(lua_State *vm) which is take from Lua 5.1

Copyright (C) 1994-2012 Lua.org, PUC-Rio.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


namespace
{
	// LCOV_EXCL_START
	const int LEVELS1 = 10;
	const int LEVELS2 = 20;

	lua_State *getthread(lua_State *vm, int *arg)
	{
		if(lua_isthread(vm, 1))
		{
			*arg = 1;
			return lua_tothread(vm, 1);
		}
		else
		{
			*arg = 0;
			return vm;
		}
	}

	int stack_trace(lua_State *vm)
	{
		int level;
		int firstpart = 1;  /* still before eventual `...' */
		int arg;
		lua_State *L1 = getthread(vm, &arg);
		lua_Debug ar;
		if (lua_isnumber(vm, arg+2)) {
			level = (int)lua_tointeger(vm, arg+2);//NOLINT
			lua_pop(vm, 1);
		}
		else
			level = (vm == L1) ? 1 : 0;  /* level 0 may be this own function */
		if (lua_gettop(vm) == arg)
			lua_pushliteral(vm, "");
		else if (!lua_isstring(vm, arg+1)) return 1;  /* message is not a string */
		else lua_pushliteral(vm, "\n");
		lua_pushliteral(vm, "stack traceback:");
		while (lua_getstack(L1, level++, &ar))
		{
			if (level > LEVELS1 && firstpart)
			{
				/* no more than `LEVELS2' more levels? */
				if (!lua_getstack(L1, level+LEVELS2, &ar))
					level--;  /* keep going */
				else
				{
					lua_pushliteral(vm, "\n\t...");  /* too many levels */
					while (lua_getstack(L1, level+LEVELS2, &ar))  /* find last levels */
						level++;
				}
				firstpart = 0;
				continue;
			}
			lua_pushliteral(vm, "\n\t");
			lua_getinfo(L1, "Snl", &ar);
			lua_pushfstring(vm, "%s:", ar.short_src);
			if(ar.currentline > 0)
				lua_pushfstring(vm, "%d:", ar.currentline);
			if(*ar.namewhat != '\0')  /* is there a name? */
				lua_pushfstring(vm, " in function " LUA_QS, ar.name);
			else
			{
				if(*ar.what == 'm')  /* main? */
					lua_pushfstring(vm, " in main chunk");
				else if (*ar.what == 'C' || *ar.what == 't')
					lua_pushliteral(vm, " ?");  /* C function or tail call */
				else
					lua_pushfstring(vm, " in function <%s:%d>",
									ar.short_src, ar.linedefined);
			}
			lua_concat(vm, lua_gettop(vm) - arg);
		}
		lua_concat(vm, lua_gettop(vm) - arg);
		return 1;
	}
	// LCOV_EXCL_STOP

	int set_error_callback(lua_State* vm, lua_CFunction func)
	{
#if OOLUA_DEBUG_CHECKS == 1
		lua_pushcfunction(vm, func);
		return lua_gettop(vm);
#else
		(void)vm;
		(void)func;
		return 0;
#endif
	}

} //namespace

namespace OOLUA
{
	void Lua_function::bind_script(lua_State* const vm)
	{
#if OOLUA_DEBUG_CHECKS == 1
		assert(vm); // LCOV_EXCL_LINE
#endif
		m_lua = vm;
	}

	Lua_function::Lua_function()
		:m_lua(0)
	{}
	Lua_function::Lua_function(lua_State* vm)
	{
		bind_script(vm);
	}
	bool Lua_function::call(int const nparams, int const error_index)
	{
		int result = lua_pcall(m_lua, nparams, LUA_MULTRET, error_index);
		if (error_index != 0)lua_remove(m_lua, error_index);
		return INTERNAL::protected_call_check_result(m_lua, result);
	}


#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
#	if OOLUA_USE_EXCEPTIONS == 1
#		define OOLUA_CHECK_STACK_IF_ENABLED(lvm, count) \
		if( !lua_checkstack(lvm, (count)) )throw OOLUA::Runtime_error("unable to grow the stack")
#	elif OOLUA_STORE_LAST_ERROR == 1
#		define OOLUA_CHECK_STACK_IF_ENABLED(lvm, count) \
		MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
		if( !lua_checkstack(lvm, (count)) ) \
		do \
		{ \
			if( lua_checkstack(lvm, 3) ) \
			{ \
				lua_pushliteral(lvm, "unable to grow the stack"); \
				OOLUA::INTERNAL::set_error_from_top_of_stack_and_pop_the_error(lvm); \
			} \
			/*else cant even grow the stack to add the error*/ \
			return false; \
		}while(0) \
		MSC_POP_COMPILER_WARNING_OOLUA
#	endif
#elif OOLUA_DEBUG_CHECKS == 1
#	define OOLUA_CHECK_STACK_IF_ENABLED(lvm, count) \
	if( !lua_checkstack(lvm, (count)) ) assert(0 && "unable to grow the stack")
#else
#	define OOLUA_CHECK_STACK_IF_ENABLED(lvm, count)(void)lvm
#endif


	/*
	 prep_function
	 If the given function is not actually a function (and the following exception does not apply)
	 then pcall will tell us this and it will be handled as specified by the configuration in use.
	 Exception : If it is a function reference then it can fail when the states are not related.
	 If this happens then this error is given not a pcall error, otherwise it would be confusing
	 as to why there was an error.
	 */

	bool Lua_function::prep_function(Lua_func_ref const& func, int const nparams, int& error_index)
	{
		OOLUA_CHECK_STACK_IF_ENABLED(m_lua, nparams+2); // LCOV_EXCL_LINE
		error_index = set_error_callback(m_lua, stack_trace);
		return func.push(m_lua);
	}

	bool Lua_function::prep_function(std::string const& func, int const nparams, int& error_index)
	{
		OOLUA_CHECK_STACK_IF_ENABLED(m_lua, nparams+2); // LCOV_EXCL_LINE
		error_index = set_error_callback(m_lua, stack_trace);
		lua_getglobal(m_lua, func.c_str());
		return true;
	}

	bool Lua_function::prep_function(int const func_index, int const nparams, int& error_index)
	{
		int const top = lua_gettop(m_lua);
#if OOLUA_DEBUG_CHECKS == 1
		assert(!(top == 0 || func_index == 0|| func_index > top || -func_index > top) && "Out of bounds index"); // LCOV_EXCL_LINE
#endif
		OOLUA_CHECK_STACK_IF_ENABLED(m_lua, nparams+2); // LCOV_EXCL_LINE
		error_index = set_error_callback(m_lua, stack_trace);
		lua_pushvalue(m_lua, func_index > 0 ? func_index : top + 1 + func_index);

		return true;
	}

#undef OOLUA_CHECK_STACK_IF_ENABLED

	int Lua_function::get_top()
	{
#if OOLUA_DEBUG_CHECKS == 1
		assert(m_lua && "No valid script is bound for the Lua_function caller"); // LCOV_EXCL_LINE
#endif
		return lua_gettop(m_lua);
	}

} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{

	bool idxs_equal(lua_State* vm, int idx0, int idx1)
	{
#	if LUA_VERSION_NUM < 502
		return !!lua_equal(vm, idx0, idx1);
#	else
		return !!lua_compare(vm, idx0, idx1, LUA_OPEQ);
#	endif
	}


	bool can_xmove(lua_State* vm0, lua_State* vm1)
	{
		if(!vm0 || !vm1 || vm0 == vm1) return false;

		/*
		Threads that are related share the same registry
		G(vm0)->l_registry == G(vm1)->l_registry
		*/
		return lua_topointer(vm0, LUA_REGISTRYINDEX) == lua_topointer(vm1, LUA_REGISTRYINDEX);
	}

} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
 //get_oolua_module
namespace
{
	void add_weaklookup_table(lua_State* vm)
	{
		lua_newtable(vm);//tb
		int weakTable = lua_gettop(vm);
		luaL_newmetatable(vm, "weak_mt");
		int weak_mt = lua_gettop(vm);

		lua_pushstring(vm, "__mode");//tb mt key
		lua_pushstring(vm, "v");//tb mt key value
		lua_settable(vm, weak_mt);//tb mt
		//weak_mt["__mode"]="v"

		lua_setmetatable(vm, weakTable);//tb
		//weakTable["__mt"]=weak_mt

		OOLUA::INTERNAL::Weak_table::setWeakTable(vm, -2);
		//registry[weak_lookup_name]=weakTable

		lua_pop(vm, 1);//empty
	}

	void add_collision_metatable(lua_State* vm)
	{
		lua_createtable(vm, 0, 1);
		lua_pushliteral(vm, "__mode");
		lua_pushliteral(vm, "kv");
		//collisionMetaTable['__mode'] = 'kv'
		lua_rawset(vm, -3); //collisionMetaTable
		OOLUA::INTERNAL::Weak_table::setCollisionMetatable(vm, -2);
		lua_pop(vm, 1);
	}

	void add_ownership_globals(lua_State* vm)
	{
		lua_pushinteger(vm, OOLUA::Cpp);//int
		lua_setglobal(vm, OOLUA::INTERNAL::cpp_owns_str);//globals[string]=int

		lua_pushinteger(vm, OOLUA::Lua);//int
		lua_setglobal(vm, OOLUA::INTERNAL::lua_owns_str);//globals[string]=int

		lua_pushcclosure(vm, OOLUA::INTERNAL::l_new_table, 0);
		lua_setglobal(vm, OOLUA::INTERNAL::lua_new_table);

		OOLUA::INTERNAL::get_oolua_module(vm);

		OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::cpp_owns_str);
		lua_pushinteger(vm, OOLUA::Cpp);//int
		lua_rawset(vm, -3);

		OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::lua_owns_str);
		lua_pushinteger(vm, OOLUA::Lua);//int
		lua_rawset(vm, -3);

		OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::lua_new_table);
		lua_pushcclosure(vm, OOLUA::INTERNAL::l_new_table, 0);
		lua_rawset(vm, -3);

		lua_pop(vm, 1);
	}

	void get_preload_table(lua_State* vm)
	{
#if LUA_VERSION_NUM < 502
		lua_getglobal(vm, "package");
		lua_getfield(vm, -1, "preload");
#else
		lua_getfield(vm, LUA_REGISTRYINDEX, "_PRELOAD");
#endif
		if( lua_type(vm, -1) != LUA_TTABLE )
			luaL_error(vm, "Lua %d get_preload_table failed to retrieve the preload table. Stack top is %s\n"
					   , LUA_VERSION_NUM
					   , lua_typename(vm, -1)); // LCOV_EXCL_LINE
	}

	void register_oolua_module(lua_State *vm)
	{
		int const top = lua_gettop(vm);
		get_preload_table(vm);

		OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::oolua_str);
		lua_pushcclosure(vm, OOLUA::INTERNAL::get_oolua_module, 0);
		lua_settable(vm, -3);

		OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::oolua_str);
		lua_createtable(vm, 0, 3);//starts with three entries cpp_own, lua_owns and new_table
		lua_rawset(vm, LUA_REGISTRYINDEX);

		lua_settop(vm, top);
	}
} // namespace

namespace OOLUA
{
	void setup_user_lua_state(lua_State* vm)
	{
		add_weaklookup_table(vm);
		add_collision_metatable(vm);
		register_oolua_module(vm);
		add_ownership_globals(vm);
	}
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/



namespace OOLUA
{
	bool push(lua_State* const vm, void * lightud)
	{
		lua_pushlightuserdata(vm, lightud);
		return true;
	}

	bool push(lua_State* const vm, bool const& value)
	{
		assert(vm); // LCOV_EXCL_LINE
		lua_pushboolean(vm, (value? 1 : 0));
		return true;
	}

	bool push(lua_State* const vm, char const * const& value)
	{
		assert(vm && value); // LCOV_EXCL_LINE
		lua_pushstring(vm, value);
		return true;
	}

	bool push(lua_State* const vm, char * const& value)
	{
		assert(vm && value); // LCOV_EXCL_LINE
		lua_pushstring(vm, value);
		return true;
	}

	bool push(lua_State* const vm, double const& value)
	{
		assert(vm); // LCOV_EXCL_LINE
		lua_pushnumber(vm, value);
		return true;
	}

	bool push(lua_State* const vm, float const&  value)
	{
		assert(vm); // LCOV_EXCL_LINE
		lua_pushnumber(vm, value);
		return true;
	}

	bool push(lua_State* const vm, lua_CFunction const &  value)
	{
		assert(vm); // LCOV_EXCL_LINE
		lua_pushcclosure(vm, value, 0);
		return true;
	}

	bool push(lua_State* const vm, Table const &  value)
	{
		assert(vm); // LCOV_EXCL_LINE
		return value.push_on_stack(vm);
	}

} //namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/



namespace OOLUA
{
	namespace INTERNAL
	{
		namespace PULL
		{
			void set_index_gc_value_to_false(lua_State* vm, int idx)
			{
				OOLUA::INTERNAL::userdata_gc_value(static_cast<INTERNAL::Lua_ud*>(lua_touserdata(vm, idx)), false);
			}
		}
		void handle_cpp_pull_fail(lua_State* vm, char const * expected_type)
		{
#	if OOLUA_USE_EXCEPTIONS == 1 || OOLUA_STORE_LAST_ERROR == 1
			lua_pushfstring(vm, "Stack type is not a %s, yet %s"
							, expected_type
							, lua_gettop(vm) ? lua_typename(vm, lua_type(vm, -1) ) : "empty stack");
#	endif
#	if OOLUA_USE_EXCEPTIONS == 1
			throw OOLUA::Type_error(vm, static_cast<ERROR::PopTheStack*>(0));
#	elif OOLUA_STORE_LAST_ERROR == 1
			OOLUA::INTERNAL::set_error_from_top_of_stack_and_pop_the_error(vm);
			return;
#	else
			(void)vm;
			(void)expected_type;
			return;
#	endif
		}

		bool cpp_runtime_type_check_of_top(lua_State* vm, int expected_lua_type, char const * expected_type)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
			if( lua_gettop(vm) == 0 || lua_type(vm, -1) != expected_lua_type )
			{
				handle_cpp_pull_fail(vm, expected_type);
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
				return false;//dependant on config if the flow can return through this path
#	endif
			}
#else
			(void)vm;
			(void)expected_lua_type;
			(void)expected_type;
#endif
			return true;
		}

		bool cpp_runtime_type_check_of_top(lua_State* vm, compare_lua_type_func_sig compareFunc, char const * expected_type)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
			if(!compareFunc(vm, -1))
			{
				handle_cpp_pull_fail(vm, expected_type);
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
				return false;//dependant on config if the flow can return through this path
#	endif
			}
#else
			(void)vm;
			(void)compareFunc;
			(void)expected_type;
#endif
			return true;
		}

	} // namespace INTERNAL //NOLINT

	bool pull(lua_State* const vm, void*& value)
	{
		if( !INTERNAL::cpp_runtime_type_check_of_top(vm, LUA_TLIGHTUSERDATA, "light userdata") ) return false;
		value = lua_touserdata(vm, -1);
		return true;
	}

	bool pull(lua_State* const vm, bool& value)
	{
		/*
		If it is allowed to pull a bool from an int, check for number instead of boolean
		if(! INTERNAL::cpp_runtime_type_check_of_top(s,lua_isnumber,"bool") ) return false;
		 */
		if( !INTERNAL::cpp_runtime_type_check_of_top(vm, LUA_TBOOLEAN, "bool") ) return false;
		value = lua_toboolean(vm, -1) ? true : false;
		lua_pop(vm, 1);
		return true;
	}

	bool pull(lua_State* const vm, double& value)
	{
		if( !INTERNAL::cpp_runtime_type_check_of_top(vm, LUA_TNUMBER, "double") ) return false;
		value = static_cast<double>(lua_tonumber(vm, -1));
		lua_pop(vm, 1);
		return true;
	}

	bool pull(lua_State* const vm, float& value)
	{
		if( !INTERNAL::cpp_runtime_type_check_of_top(vm, LUA_TNUMBER, "float") ) return false;
		value = static_cast<float>(lua_tonumber(vm, -1));
		lua_pop(vm, 1);
		return true;
	}

	bool pull(lua_State* const vm, lua_CFunction& value)
	{
		if( !INTERNAL::cpp_runtime_type_check_of_top(vm, lua_iscfunction, "lua_CFunction") ) return false;
		value = lua_tocfunction(vm, -1);
		lua_pop(vm, 1);
		return true;
	}

	bool pull(lua_State* const vm, Table& value)
	{
		return value.pull_from_stack(vm);
	}

} //namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{
	namespace INTERNAL
	{
		bool handle_unrelated_states(lua_State* const from, lua_State* const to)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
#	if OOLUA_USE_EXCEPTIONS ==1
			lua_pushfstring(to, "Can not push a valid Lua reference from lua_State(%p) to an unrelated lua_State(%p)", from, to);
			throw OOLUA::Runtime_error(to, (OOLUA::ERROR::PopTheStack*)0);
#	endif
#	if OOLUA_STORE_LAST_ERROR ==1
			lua_pushfstring(to, "Can not push a valid Lua reference from lua_State(%p) to an unrelated lua_State(%p)", from, to);
			OOLUA::INTERNAL::set_error_from_top_of_stack_and_pop_the_error(to);
#	endif
#	if OOLUA_DEBUG_CHECKS == 1
			//assert(0 && "Can not push a valid Lua reference from one lua_State to a different state");
#	endif
#	if OOLUA_USE_EXCEPTIONS == 0
			return false;
#	endif
#else
			(void)from;
			(void)to;
			return true;
#endif
		}


		void pull_handle_invalid(lua_State* const vm, int id)
		{
#if OOLUA_STORE_LAST_ERROR == 1 || 	OOLUA_USE_EXCEPTIONS == 1
			lua_pushfstring(vm
							, "pulling incorrect type from stack. This is a Lua registry reference to %s, stack contains %s"
							, lua_typename(vm, id)
							, lua_gettop(vm) ? lua_typename(vm, lua_type(vm, -1)) : "empty stack");
#	if OOLUA_USE_EXCEPTIONS == 1
			throw OOLUA::Runtime_error(vm, (OOLUA::ERROR::PopTheStack*)0);
#	else // OOLUA_STORE_LAST_ERROR == 1
			OOLUA::INTERNAL::set_error_from_top_of_stack_and_pop_the_error(vm);
#	endif
#elif OOLUA_DEBUG_CHECKS == 1
			assert(0 && "pulling incorrect type from stack");
#endif
		}

#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable: 4702) //warning C4702: unreachable code
#endif
		bool push_reference_if_possible(int const ref, lua_State* const from, lua_State* const to)
		{
			if (from == to || OOLUA::can_xmove(from, to) )
			{
				lua_rawgeti(to, LUA_REGISTRYINDEX, ref);
				return true;
			}
			return handle_unrelated_states(from, to);
		}
MSC_POP_COMPILER_WARNING_OOLUA
	} // namespace INTERNAL //NOLINT
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		int get_oolua_module(lua_State* vm)
		{
			lua_getfield(vm, LUA_REGISTRYINDEX, OOLUA::INTERNAL::oolua_str);
			return 1;
		}
		void register_oolua_type(lua_State* vm, char const* name, int const stack_index)
		{
			get_oolua_module(vm);
			lua_pushstring(vm, name);
			lua_pushvalue(vm, stack_index);
			lua_rawset(vm, -3);
			lua_pop(vm, 1);
		}

		void set_function_in_table_with_upvalue(lua_State* vm, char const * func_name, lua_CFunction func
													, int tableIndex, void* upvalue)
		{
			lua_pushstring(vm, func_name);
			lua_pushlightuserdata(vm, upvalue);
			lua_pushcclosure(vm, func, 1);
			lua_rawset(vm, tableIndex);
		}
		void set_function_in_table(lua_State* vm, char const* func_name, lua_CFunction func, int tableIndex)
		{
			lua_pushstring(vm, func_name);
			lua_pushcclosure(vm, func, 0);
			lua_rawset(vm, tableIndex);
		}

		void set_oolua_userdata_creation_key_value_in_table(lua_State* vm, int tableIndex)
		{
#if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 1 && OOLUA_USERDATA_OPTIMISATION == 0
			lua_pushlightuserdata(vm, lua_topointer(vm, LUA_REGISTRYINDEX));
			lua_pushboolean(vm, 1);
			lua_rawset(vm, tableIndex);
#else
			(void)vm;
			(void)tableIndex;
#endif
		}

		void set_key_value_in_table(lua_State* vm, char const* key_name, int valueIndex, int tableIndex)
		{
			lua_pushstring(vm, key_name);
			lua_pushvalue(vm, valueIndex);
			lua_rawset(vm, tableIndex);
		}

		int check_for_key_in_stack_top(lua_State* vm)
		{
			//on entry stack is : table keyString basetable
			lua_pushvalue(vm, -2);//table keyString baseTable keyString
			lua_gettable(vm, -2);//check for keyString in baseTable
			if( lua_isnil(vm, -1) == 1)//table string baseTable valueOrNil
			{
				lua_pop(vm, 2);//table keyString
				return 0;
			}

			lua_remove(vm, -2);//table keyString TheValueThatWeWereLookingFor
			return 1;
		}

		bool class_name_is_already_registered(lua_State* vm, char const* name)
		{
			lua_getfield(vm, LUA_REGISTRYINDEX, name);
			if( lua_isnil(vm, -1) == 0 )// entryOrNil
			{
				lua_pop(vm, 1);//pop the table
				return true;
			}

			lua_pop(vm, 1);//pop the null
			return false;
		}

		// LCOV_EXCL_START
		int info(lua_State* vm, int const index, int const id)
		{
			if(lua_getmetatable(vm, index))
			{
				lua_pushinteger(vm, id);
				lua_rawget(vm, -2);
				lua_CFunction func = lua_tocfunction(vm, -1);
				lua_pop(vm, 2);
				return func ? func(vm) : 0;
			}
			return 0;
		}
		// LCOV_EXCL_STOP
	} // namespace INTERNAL // NOLINT
	/**\endcond*/
} // namespace OOLUA

/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{

	Script::Script()
		:call(), m_lua(0)
	{
		m_lua = luaL_newstate();
		luaL_openlibs(m_lua);
		call.bind_script(m_lua);//bind the lua state to the function caller
		setup_user_lua_state(m_lua);
	}

	Script::~Script()
	{
		close_down();
	}

	void Script::gc()
	{
		lua_gc(m_lua, LUA_GCCOLLECT, 0);
	}

	void Script::close_down()
	{
		if(m_lua)
		{
			lua_gc(m_lua, LUA_GCCOLLECT, 0);
			lua_close(m_lua);
			m_lua = 0;
		}
	}

	bool Script::load_chunk(std::string const& chunk)
	{
		return OOLUA::load_chunk(m_lua, chunk);
	}

	bool Script::run_chunk(std::string const& chunk)
	{
		return OOLUA::run_chunk(m_lua, chunk);
	}

	bool Script::run_file(std::string const & filename)
	{
		return OOLUA::run_file(m_lua, filename);
	}

	bool Script::load_file(std::string const & filename)
	{
		return OOLUA::load_file(m_lua, filename);
	}

} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <iostream> //NOLINT
#include <string>

namespace OOLUA
{
// LCOV_EXCL_START
void lua_stack_dump(lua_State * const vm)
{
	int i;

	int top = lua_gettop(vm);
	std::cout <<"Lua stack dump - number of nodes: " <<top <<std::endl;

	for (i = 1; i <= top; i++)
	{  /* repeat for each level */
		int t = lua_type(vm, i);
		switch (t)
		{
		case LUA_TSTRING:
			{
				size_t len(0);
				char const* str = lua_tolstring(vm, -1, &len);
				std::string value(std::string(str, len) );
				std::cout <<"LUA_TSTRING :" <<value;
			}
			break;

		case LUA_TBOOLEAN:
			std::cout <<"LUA_TBOOLEAN :" <<(lua_toboolean(vm, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:
			std::cout <<"LUA_TNUMBER :" <<lua_tonumber(vm, i);
			break;

		default:
			std::cout <<lua_typename(vm, t);
			break;
		}
		std::cout <<"  ";
	}
	std::cout <<std::endl;
}
// LCOV_EXCL_STOP
} // namespace OOLUA

/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/



#include <string>

namespace OOLUA
{
	namespace STRING
	{
		template<>
		bool push<std::string>(lua_State* const vm, std::string const& value)
		{
			lua_pushlstring(vm, value.data(), value.size());
			return true;
		}

		template<>
		bool pull<std::string>(lua_State* const vm, std::string& value)
		{
			if( !INTERNAL::cpp_runtime_type_check_of_top(vm, LUA_TSTRING, "std::string") ) return false;
			size_t len(0);
			char const* str = lua_tolstring(vm, -1, &len);
			value = std::string(str, len);
			lua_pop(vm, 1);
			return true;
		}

#if OOLUA_STD_STRING_IS_INTEGRAL == 1
		template<>
		void get<std::string>(lua_State* const vm, int idx, std::string &  value)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
			if(lua_type(vm, idx) != LUA_TSTRING ) INTERNAL::LUA_CALLED::get_error(vm, idx, "std::string");
#endif
			size_t len(0);
			char const* str = lua_tolstring(vm, idx, &len);
			value = std::string(str, len);
		}
#endif

	} // namespace STRING //NOLINT(readability/namespace)
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{
	Table::Table()
	{}

	Table::Table(Lua_table_ref const& ref)
		:m_table_ref(ref)
	{}

	Table::Table(lua_State*  const vm, std::string const& name)
		:m_table_ref(vm)
	{
		set_table(name);
	}

	Table::Table(Table const& rhs)
		:m_table_ref(rhs.m_table_ref)
	{}

	Table& Table::operator = (Table const& rhs)
	{
		m_table_ref = rhs.m_table_ref;
		return *this;
	}

	void Table::bind_script(lua_State*  const vm)
	{
		if(m_table_ref.m_lua == vm)return;
		if(m_table_ref.valid() )
		{
			Lua_table_ref tempRef(vm);
			m_table_ref.swap(tempRef);
		}
		else m_table_ref.m_lua = vm;
	}

	void Table::set_table(std::string const& name)
	{
		if(name.empty())
		{
			Lua_table_ref t;
			m_table_ref.swap(t);
			return;
		}
		if(!m_table_ref.m_lua)return;

		lua_getglobal(m_table_ref.m_lua,  name.c_str() );
		if(lua_type(m_table_ref.m_lua, -1) != LUA_TTABLE)
		{
			lua_pop(m_table_ref.m_lua, 1);
			lua_getfield(m_table_ref.m_lua, LUA_REGISTRYINDEX, name.c_str() );
			if(lua_type(m_table_ref.m_lua, -1) != LUA_TTABLE)
			{
				lua_pop(m_table_ref.m_lua,  1);
				Lua_table_ref t;
				m_table_ref.swap(t);
				return;
			}
		}
		set_ref(m_table_ref.m_lua, luaL_ref(m_table_ref.m_lua, LUA_REGISTRYINDEX));
	}

	bool Table::valid()const
	{
		int const init_stack_top = initial_stack_size();
		bool result = get_table();
		restore_stack(init_stack_top);
		return result;
	}

	void Table::set_ref(lua_State* const vm, int const& ref)
	{
		m_table_ref.set_ref(vm, ref);
	}

	bool Table::get_table()const
	{
		bool result(false);
		if( !m_table_ref.valid() )return result;
		lua_rawgeti(m_table_ref.m_lua, LUA_REGISTRYINDEX, m_table_ref.ref() );
		return  lua_type(m_table_ref.m_lua, -1) == LUA_TTABLE;
	}

	bool Table::push_on_stack(lua_State* vm)const
	{
		return m_table_ref.push(vm);
	}

	bool Table::pull_from_stack(lua_State* vm)
	{
		return m_table_ref.pull(vm);
	}

	void Table::lua_get(lua_State* vm, int idx)
	{
		m_table_ref.lua_get(vm, idx);
	}

	void Table::restore_stack(int const & init_stack_size)const
	{
		//ok now we need to clean up the stack if there are left overs
		if(!m_table_ref.m_lua)return;
		int end_stack_size(lua_gettop(m_table_ref.m_lua));
		if(init_stack_size != end_stack_size)
		{
			lua_pop(m_table_ref.m_lua, end_stack_size - init_stack_size);
		}
	}

	int Table::initial_stack_size()const
	{
		return (!m_table_ref.m_lua) ? 0 : lua_gettop(m_table_ref.m_lua);
	}

	void Table::traverse(Table::traverse_do_function do_)
	{
		Table& t = *this;
		oolua_pairs(t)
		{
			(*do_)(lvm);
			lua_pop(lvm, 1);
		}
		oolua_pairs_end()
	}

	void Table::swap(Table & rhs)
	{
		m_table_ref.swap(rhs.m_table_ref);
	}

	void new_table(lua_State* vm, Table& t)
	{
		new_table(vm).swap(t);
	}

	Table new_table(lua_State* vm)
	{
		lua_newtable(vm);
		Table t;
		t.pull_from_stack(vm);
		return t;
	}
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		int l_new_table(lua_State* vm)
		{
			lua_createtable(vm, static_cast<int>(luaL_optinteger(vm, 1, 0)), static_cast<int>(luaL_optinteger(vm, 2, 0)));
			return 1;
		}
	} //namespace INTERNAL
	/** \endcond */

} // namespace OOLUA

/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/



#if OOLUA_DEBUG_CHECKS == 1
#	include <cassert>
#endif

namespace OOLUA
{

	/** \cond INTERNAL*/
	namespace INTERNAL
	{

		//pushes the weak table on top and returns its absolute index
		//The weak table is a table in the Lua registry specific to OOLua,
		//which has void pointer keys and values of userdata pointers.
		int push_weak_table(lua_State* vm)
		{
			Weak_table::getWeakTable(vm);
			return lua_gettop(vm);
		}

		//if found it is left on the top of the stack and returns true
		//else the stack is same as on entrance to the function and false returned
		bool is_there_an_entry_for_this_void_pointer(lua_State* vm, void* ptr)
		{
			int wt = push_weak_table(vm);
			bool result = is_there_an_entry_for_this_void_pointer(vm, ptr, wt);
			lua_remove(vm, wt);
			return result;
		}

		bool is_there_an_entry_for_this_void_pointer(lua_State* vm, void* ptr, int tableIndex)
		{
			lua_pushlightuserdata(vm, ptr);//weakTable ... ptr
			lua_rawget(vm, tableIndex);//weakTable .... (full user data or nil)
			if( !lua_isnil(vm, -1) )
			{
				return true;//leave ud on top
			}
			lua_pop(vm, 1);//pop nil
			return false;
		}

		void add_ptr_if_required(lua_State* const vm, void* ptr, int ud_index, int weak_index)
		{
			lua_pushlightuserdata(vm, ptr);//ptr
			lua_rawget(vm, weak_index);//(null, ud or table)
			switch(lua_type(vm, -1))
			{
				case LUA_TNIL:
				{
					lua_pop(vm, 1);//pop the null
					lua_pushlightuserdata(vm, ptr);//key
					lua_pushvalue(vm, ud_index);//key ud
					lua_rawset(vm, weak_index);//table[key] = ud
					break;
				}
				case LUA_TUSERDATA:
				{
					//(weak_index ... ud_index ...) ud
					if( lua_rawequal(vm, -1, ud_index) == 1)
						lua_pop(vm, 1);//pop the ud
					else
					{
						lua_createtable(vm, 0, 2);////(weak_index ... ud_index ...) foundUd, collision_table
						lua_pushlightuserdata(vm, ptr);//key //(weak_index ... ud_index ...) foundUd, collisionTable, lightUd
						//lua_createtable(vm, 0, 2);//value
						lua_pushvalue(vm, -2); //(weak_index ... ud_index ...) foundUd, collisionTable, lightUd, collisionTable

						Weak_table::getCollisionMetatable(vm);// foundUd, collisionTable, lightUd, collisionTable, collisionMetaTable

						//setmetatable(collisionTable, collisionMetaTable)
						lua_setmetatable(vm, -2); // foundUd, collisionTable, lightUd, collisionTable

						lua_pushvalue(vm, ud_index);//key
						lua_pushvalue(vm, ud_index);//value
						//collisionTable[newLightUd] = newLightUd
						lua_rawset(vm, -3); // foundUd, collisionTable, lightUd, collisionTable

						lua_pushvalue(vm, -4);//key // foundUd, collisionTable, lightUd, collisionTable, foundUd
						lua_pushvalue(vm, -5);//value // foundUd, collisionTable, lightUd, collisionTable, foundUd, foundUd
						//collisionTable[foundUd] = foundUd
						lua_rawset(vm, -3);// foundUd, collisionTable, lightUd, collisionTable

						//weakTable[lightUd] = collisionTable
						lua_rawset(vm, weak_index);// foundUd, collisionTable,

						lua_pushboolean(vm, 1);// foundUd, collisionTable, boolean
						lua_rawset(vm, weak_index);// foundUd,
						//weakTable[collisionTable] = 1

						userdata_ptr_collision(static_cast<Lua_ud*>(lua_touserdata(vm, ud_index)));
						userdata_ptr_collision(static_cast<Lua_ud*>(lua_touserdata(vm, -1)));
						lua_pop(vm, 1);//pop ud that was not this ptr
					}
					break;
				}
				case LUA_TTABLE:
				{
					lua_pushvalue(vm, ud_index);
					lua_rawget(vm, -2);
					if(lua_type(vm, -1) != LUA_TNIL)
						lua_pop(vm, 2);//pop found ud and the collision table
					else
					{
						lua_pushvalue(vm, ud_index);//collisionTable, nil, ud
						lua_pushvalue(vm, ud_index);//collisionTable, nil, ud, ud
						//collisionTable[ud] = ud
						lua_rawset(vm, -4);//collisionTable, nil
						lua_pop(vm, 2); //pop nil and the collision table
						userdata_ptr_collision(static_cast<Lua_ud*>(lua_touserdata(vm, ud_index)));
					}
				}
			}
		}

		bool ud_at_index_is_const(lua_State* vm, int index)
		{
			return INTERNAL::userdata_is_constant( static_cast<Lua_ud *>( lua_touserdata(vm, index) ) );
		}

		Lua_ud* new_userdata(lua_State* vm, void* ptr, bool is_const
							, oolua_function_check_base base_checker
							, oolua_type_check_function type_check
							, oolua_release_shared_ptr shared_release)
		{
			Lua_ud* ud = static_cast<Lua_ud*>(lua_newuserdata(vm, sizeof(Lua_ud)));
			ud->flags = 0;
			reset_userdata(ud, ptr, is_const, base_checker, type_check, shared_release);
#if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 1 && OOLUA_USERDATA_OPTIMISATION == 1
			OOLUA_SET_COOKIE(ud->flags);
#endif
			return ud;
		}

		void reset_userdata(Lua_ud* ud, void* ptr, bool is_const
							, oolua_function_check_base base_checker
							, oolua_type_check_function type_check
							, oolua_release_shared_ptr shared_release)
		{
			ud->void_class_ptr = ptr;
			ud->base_checker = base_checker;
			ud->type_check = type_check;
#if OOLUA_USE_SHARED_PTR == 1
			ud->shared_ptr_release = shared_release;
#else
			(void)shared_release;
#endif
			userdata_const_value(ud, is_const);
		}

	} // namespace INTERNAL //NOLINT
	/**\endcond*/
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
#if OOLUA_DEBUG_CHECKS == 1
		void if_check_enabled_check_type_is_registered(lua_State* vm, char const* name)
		{
			lua_getfield(vm, LUA_REGISTRYINDEX, name);
			if( lua_isnil(vm, -1) )
			{
				lua_pop(vm, 1);
				luaL_error(vm, "%s %s %s", "the type", name, "is not registered with this Lua State");
			}
			else lua_pop(vm, 1);
		}
#else
		void if_check_enabled_check_type_is_registered(lua_State* /*vm*/, char const* /*name*/){}
#endif

		void set_owner_if_change(Owner owner, Lua_ud* ud)
		{
			if(owner != No_change)
			{
				userdata_gc_value(ud, owner == Lua ? true : false);
			}
		}

	} // namespace INTERNAL //NOLINT
	/** \endcond*/
} // namespace OOLUA
/*
The MIT License

Copyright (c) 2009 - 2015 Liam Devine

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
//set_tops_gc_value_to_false

#include <string>

namespace OOLUA
{
	namespace INTERNAL
	{
		namespace LUA_CALLED
		{
			void get_class_type_error(lua_State* const vm, char const* expected_type)
			{
				luaL_error(vm, "%s %s %s", "tried to pull type"
							, expected_type
							, "which is not the type or a base of the type on the stack");
			} // LCOV_EXCL_LINE

			void get_error(lua_State* vm, int idx, char const* expected_type)
			{
				luaL_error(vm, "trying to pull %s when %s is on stack"
							, expected_type
							, lua_typename(vm, lua_type(vm, idx)) );
			} // LCOV_EXCL_LINE

			void get(lua_State* const vm, int idx, void*& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( lua_type(vm, idx) != LUA_TLIGHTUSERDATA ) get_error(vm, idx, "light userdata");
#endif
				value = lua_touserdata(vm, idx);
			}

			void get(lua_State* const vm, int idx, bool& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( !lua_isboolean(vm, idx) ) get_error(vm, idx, "bool");
#endif
				value = lua_toboolean(vm, idx) ? true : false;
			}

			void get(lua_State* const vm, int idx, char const*& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( lua_type(vm, idx) != LUA_TSTRING ) get_error(vm, idx, "char const*");
#endif
				value = lua_tolstring(vm, idx, 0);
			}

			void get(lua_State* const vm, int idx, double& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( !lua_isnumber(vm, idx) ) get_error(vm, idx, "double");
#endif
				value = static_cast<double>(lua_tonumber(vm, idx));
			}

			void get(lua_State* const vm, int idx, float& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( !lua_isnumber(vm, idx) ) get_error(vm, idx, "float");
#endif
				value = static_cast<float>(lua_tonumber(vm, idx));
			}

			void get(lua_State* const vm, int idx, lua_CFunction& value)
			{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if( !lua_iscfunction(vm, idx) ) get_error(vm, idx, "lua_CFunction");
#endif
				value = lua_tocfunction(vm, idx);
			}

			void get(lua_State* const vm, int idx, Table& value)
			{
				value.lua_get(vm, idx);
			}

		} // namespace LUA_CALLED //NOLINT
	} // namespace INTERNAL //NOLINT
} // namespace OOLUA

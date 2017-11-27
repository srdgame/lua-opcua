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
	\file lua_includes.h
	\brief Prevents name mangling and provides a potential location to enable
	compatibility when new Lua versions are released.
	\details No part of OOLua directly includes any Lua header files, instead
	when required they include this header. Contrary to what some people may think,
	this is by design. There is no way to know if a user's version of the Lua
	library was compiled as C++ or C.
*/

#ifndef LUA_INCLUDES_H_
#	define LUA_INCLUDES_H_

//Prevent name mangling
extern "C"
{
#	include "lua/lua.h"
#	include "lua/lauxlib.h"
#	include "lua/lualib.h"
}

#endif //LUA_INCLUDES_H_
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
///  @file platform_check.h
///  Preforms a check of platform defines and defines a macro
///  @remarks
///  Information available via http://predef.sourceforge.net/preos.html
///////////////////////////////////////////////////////////////////////////////

#ifndef PLATFORM_CHECK_H_
#	define PLATFORM_CHECK_H_

#	ifndef PLATFORM_CHECKED
#		define PLATFORM_CHECKED
#		if (defined(__CYGWIN__))
//#			error Cygwin is currently not supported
#			define UNIX_BUILD			1
#		else
			/// windows
#			if (defined(__WIN32__) || defined(_WIN32) || defined(WIN32))
#				define WINDOWS_BUILD	1
			/// os2
#			elif(defined(__OS2__) || defined(_OS2)  || defined(OS2) || defined(Macintosh) || \
				defined(macintosh) || defined(__MACOSX__) || defined(__APPLE__))
#				define MAC_BUILD		1
			/// nix
#			elif(defined(unix) || defined(_unix) || defined(__unix) || defined(__unix__) || \
				defined(linux) || defined(__linux))
#				define UNIX_BUILD		1

#			endif///! CYGWIN
#		endif///CYGWIN

#	endif///PLATFORM_CHECKED

#endif ///PLATFORM_CHECK_H_
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
	\file oolua_config.h
	\brief Configuration options for the OOLua library.
*/
#ifndef OOLUA_CONFIG_H_
#	define OOLUA_CONFIG_H_

/** \addtogroup OOLuaConfig
@{ */

	/** \addtogroup OOLuaErrorReporting Error Reporting
	@{
		\brief
		Defines how any errors are reported
		\details Errors can be reported either by using exceptions or storing
		a retrievable error string. Only one of these methods is allowed
		and this condition is enforced, yet also neither are required. If both
		options are disabled then it depends on \ref OOLUA_DEBUG_CHECKS as to
		whether any error will be reported.
	*/

	/**	\def OOLUA_USE_EXCEPTIONS
		\hideinitializer
		\brief \b Default: Disabled
		\details
		Throws exceptions from C++ code.
		This could be the return of a pcall, or from pulling an incorrect type
		off the stack when \ref OOLUA_RUNTIME_CHECKS_ENABLED is enabled. It also
		prevents exceptions escaping from functions proxied by the library, enabling
		calls to such functions to be caught with pcall in Lua code.
		\param 0 Disabled
		\param 1 Enabled
	*/
#	ifndef OOLUA_USE_EXCEPTIONS
#		define OOLUA_USE_EXCEPTIONS 0
#	endif


	/** \def OOLUA_STORE_LAST_ERROR
		\hideinitializer
		\brief \b Default: Enabled
		\details
		Stores an error message in the registry which overwrites any previously stored error.
		The last error to have occurred is retrievable via \ref OOLUA::get_last_error.
		\see OOLUA::get_last_error
		\see OOLUA::reset_error_value
		\param 0 Disabled
		\param 1 Enabled
	*/
//#define OOLUA_STORE_LAST_ERROR 0
#	ifndef OOLUA_STORE_LAST_ERROR
#		define OOLUA_STORE_LAST_ERROR 1
#	endif

#	if OOLUA_USE_EXCEPTIONS == 1 && OOLUA_STORE_LAST_ERROR == 1
#		error Only one of these settings can be on
#	endif

	/**@}*/


	/** \addtogroup OOLuaErrorChecking Error Checking
	@{
		\brief Defines the type of checks which will be performed
	*/

	/** \def OOLUA_RUNTIME_CHECKS_ENABLED
		\hideinitializer
		\brief \b Default: Enabled
		\details
		Checks that a type being pulled off the stack is of the correct type,
		if this is a proxy type, it also checks the userdata on the stack was
		created by OOLua
		\param 0 Disabled
		\param 1 Enabled
	*/
//#define OOLUA_RUNTIME_CHECKS_ENABLED 0
#	ifndef OOLUA_RUNTIME_CHECKS_ENABLED
#		define OOLUA_RUNTIME_CHECKS_ENABLED 1
#	endif

	/** \def OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
		\hideinitializer
		\brief \b Default: Enabled
		\details
		Does what it says on the tin, only valid when
		\ref OOLUA_RUNTIME_CHECKS_ENABLED is enabled
		\param 0 Disabled
		\param 1 Enabled
	 */
//define OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA 0
#	if OOLUA_RUNTIME_CHECKS_ENABLED == 1
#		ifndef OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
#			define OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA 1
#		endif
#	else
#		ifdef OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
#			undef OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
#		endif
#		define OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA  0
#	endif

	/** \def OOLUA_USERDATA_OPTIMISATION
		\hideinitializer
		\brief \b Default: Enabled
		\details
		Userdata optimisation which checks for a magic cookie to try and ensure
		it was created by OOLua, by default this is on when userdata checking
		is on. Turning this off by setting it to zero will use a slower yet
		correct (as correct as can be) method. \n
		Only meaningful when \ref OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA is
		enabled
		\param 0 Disabled
		\param 1 Enabled
	 */
#	if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 1
#		ifndef OOLUA_USERDATA_OPTIMISATION
#			define OOLUA_USERDATA_OPTIMISATION 1
#		endif
#	endif

	/** \def OOLUA_DEBUG_CHECKS
		\hideinitializer
		\brief \b Default: Enabled when DEBUG or _DEBUG is defined
		\details
		Provides the following
			\li asserts on NULL pointers
			\li adds a stack trace to errors reported by pcall
			\li asserts on errors if both \ref OOLUA_USE_EXCEPTIONS and
				\ref OOLUA_STORE_LAST_ERROR are both disabled

		\param 0 Disabled
		\param 1 Enabled
	*/
#	if defined DEBUG || defined _DEBUG
#		define OOLUA_DEBUG_CHECKS 1
#	else
#		define OOLUA_DEBUG_CHECKS 0
#	endif

	/** \def OOLUA_SANDBOX
		\hideinitializer
		\brief \b Default: Disabled
		\details check everything
		\param 0 Disabled
		\param 1 Enabled
	*/
#	define OOLUA_SANDBOX 0

#	if OOLUA_SANDBOX == 1
#		if defined OOLUA_RUNTIME_CHECKS_ENABLED && OOLUA_RUNTIME_CHECKS_ENABLED == 0
#			undef OOLUA_RUNTIME_CHECKS_ENABLED
#			define OOLUA_RUNTIME_CHECKS_ENABLED 1
#		endif

#		if defined OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA && OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 0
#			undef OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
#		endif

#		ifndef OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA
#			define OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA 1
#		endif

//if neither are set then default to storing errors
#		if defined OOLUA_USE_EXCEPTIONS && OOLUA_USE_EXCEPTIONS == 0 \
				&& defined OOLUA_STORE_LAST_ERROR && OOLUA_STORE_LAST_ERROR == 0
#			undef OOLUA_STORE_LAST_ERROR
#			define OOLUA_STORE_LAST_ERROR 1
#		endif
#	endif

	/**@}*/


	/** \addtogroup OOLuaStringConfig
	@{*/
	/** \def OOLUA_STD_STRING_IS_INTEGRAL
		\hideinitializer
		\brief \b Default: Enabled
		\details
		Allows std::string to be a parameter or a return type for a function.
		\note This is always by value
		\param 0 Disabled
		\param 1 Enabled
	 **/
#	ifndef OOLUA_STD_STRING_IS_INTEGRAL
#		define OOLUA_STD_STRING_IS_INTEGRAL 1
#	endif
	/**@}*/


	/** \addtogroup OOLuaSharedPtrSupport Shared Pointer
	@{
		\brief Enable and configure library support for a shared pointer type.
		\details
		Requirements for the shared pointer type.
		\li The type must be non intrusive to the underlying type
		\li Have a "get" member function which returns a raw pointer
		\li Be constructable from a more derived shared_ptr
		\li Have a constructor which enables construction of shared<foo const> from shared<foo>
		\li Be of uniform size
		\li Have a const cast template function
		<p>
		Defaults for the configuration options in this category only apply when shared pointer
		support is enabled.
	*/
/**
	\def OOLUA_USE_SHARED_PTR
		\hideinitializer
		\brief \b Default: Disabled
		\details
		Configuration option to enable or disable the support of a shared pointer type for
		OOLua proxies.

		When enabled the library supports:
		\li pushing a shared pointer to the stack
		\li pulling a shared pointer from the stack(only defined when it is a shared pointer)
		\li pulling a raw pointer from a stack that contains a shared pointer(It is
			up to the user of the library to ensure the type will not be garbage collected)
		\li functions that return a shared pointer
		\li functions that return a shared pointer and have the \ref OOLUA::maybe_null trait
		\li functions that take a shared pointer as a parameter
		\li decaying of a shared pointer to a raw pointer for functions parameters(The raw
			pointer is defined to be valid for the duration of the call)
		\note The \ref OOLUA::Shared and \ref OOLUA::No_shared tags maybe ignored, as they are
			dependent on the value of \ref OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE
		\param 0 Disabled
		\param 1 Enabled
*/

/**
	\def OOLUA_SHARED_HEADER
		\hideinitializer
		\brief \b Default: MSC: \<memory\> other compilers: \<tr1/memory\>
		\details <p>
		Header file for the shared pointer type, library code will include
		the header using :
		\code{.cpp}
		#include OOLUA_SHARED_HEADER
		\endcode
*/

/**
	\def OOLUA_SHARED_TYPE
		\hideinitializer
		\brief \b Default: std::tr1::shared_ptr
		\details
		The templated shared pointer type.
*/

/**
	\def OOLUA_SHARED_CONST_CAST
		\hideinitializer
		\brief \b Default: std::tr1::const_pointer_cast
		\details
		Templated function which casts away constness for the shared pointer type.
*/

/**
	\def OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE
		\hideinitializer
		\brief \b Default: Disabled
		\details
		When compiled with support for a shared pointer type (\ref OOLUA_USE_SHARED_PTR)
		and in a situation that requires the allocation of a proxy type, then how the
		situation is handled depends upon this configuration value and possibly
		\ref SharedTags defined for the proxy. The resulting pointer can either be a
		'Raw' pointer or a 'Shared' pointer that retains shared ownership . Allocation
		of a proxy occurs for functions and operators that return a non-integral on the
		C stack and constructors.

		| Configuration value | Has Shared tag | Has No_shared tag | Pointer type |
		| :-----------------: | :------------: | :---------------: | :----------: |
		|      Disabled       |       No       |         X         |      Raw     |
		|      Disabled       |      Yes       |         X         |    Shared    |
		|      Enabled        |       X        |        No         |    Shared    |
		|      Enabled        |       X        |        Yes        |      Raw     |

		\param 0 Disabled
		\param 1 Enabled
		\see OOLUA_USE_SHARED_PTR
		\see OOLUA::Shared
		\see OOLUA::No_shared
*/
	/*@}*/

#	ifndef OOLUA_USE_SHARED_PTR
#		define OOLUA_USE_SHARED_PTR 0
#	else
#		if OOLUA_USE_SHARED_PTR == 1
#ifdef _MSC_VER
#			define OOLUA_SHARED_HEADER <memory>
#else
#			define OOLUA_SHARED_HEADER <tr1/memory>
#endif
#			define OOLUA_SHARED_TYPE std::tr1::shared_ptr
#			define OOLUA_SHARED_CONST_CAST std::tr1::const_pointer_cast
#			ifndef OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE
#				define OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE 0
#			endif
#		endif
#	endif
/**@}*/

/** \cond INTERNAL */

#ifdef _MSC_VER
#	define MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
__pragma(warning(push)) /*NOLINT*/ \
__pragma(warning(disable : 4127)) /*NOLINT*/
#	define MSC_POP_COMPILER_WARNING_OOLUA \
__pragma(warning(pop)) /*NOLINT*/
#else
#	define MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA
#	define MSC_POP_COMPILER_WARNING_OOLUA
#endif


#ifdef __GNUC__
/*
From GCC version 4.6 onwards you are meant to be able to push and pop diagnostic
settings which would allow turning variadic macro warnings off per file.
This was previously achieved by using the pramga GCC system_header; yet this may
hide other warnings when compiled with a combination of -ansi, -pedantic and -wall
From version 4.2 you can use :
pragma GCC diagnostic ignored [option]
yet this can effect more than the file in which it wants supressing and could effect
a users code base which is far from ideal.

GCC suggests to compile with -fdiagnostics-show-option which results in the following
warning for vaargs

warning: anonymous variadic macros were introduced in C99 [-Wvariadic-macros]

It would therefore seem reasonable that the following code could be used to prevent
vaarg warnings in a limited scope without effecting a user's compile options:

#if defined __GNUC__ && defined __STRICT_ANSI__
#	if __GNUC__ >4  || ( __GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#		pragma GCC diagnostic push
#		pragma GCC diagnostic ignored "-Wvariadic-macros"
#	else
#		pragma GCC system_header
#	endif
#endif

 Code wanting to be protected here

#if defined __GNUC__ && defined __STRICT_ANSI__ && ( __GNUC__ >4  || ( __GNUC__ == 4 && __GNUC_MINOR__ >= 6) )
#	pragma GCC diagnostic push
#endif

However using a 4.6 version of GCC and the above code does not prevent the warnings

*/




#	define GCC_VERSION_OOLUA (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
//	SShhhhhhhhh stops gcc generating warnings about the variadic macros
#	define GCC_PRAGMA_DO(x) _Pragma(#x)
#	define GCC_PRAGMA(x) GCC_PRAGMA_DO(GCC x)

#	if GCC_VERSION_OOLUA >= 40600
#		define GCC_PUSH_DISABLE_VA_WARNINGS_OOLUA \
			GCC_PRAGMA(diagnostic push) \
			GCC_PRAGMA(diagnostic ignored "-Wvariadic-macros")
#		define GCC_POP_VA_WARNINGS_OOLUA GCC_PRAGMA(diagnostic pop)
#	else
//#		define GCC_PUSH_DISABLE_VA_WARNINGS_OOLUA GCC_PRAGMA_DO(system_header)
//#		define GCC_PUSH_DISABLE_VA_WARNINGS_OOLUA _Pragma("GCC system_header") //doesn't work boooooooooo
#		define GCC_POP_VA_WARNINGS_OOLUA
#	endif
#else
#	define GCC_PUSH_DISABLE_VA_WARNINGS_OOLUA
#	define GCC_POP_VA_WARNINGS_OOLUA
#endif

//prevents g++ warning about locally defined yet unused typedefs i.e. static asserts
#if GCC_VERSION_OOLUA >= 40800
#	define OOLUA_UNUSED __attribute__((unused))
#else
#	define OOLUA_UNUSED
#endif

#if OOLUA_USE_EXCEPTIONS == 1
#	if defined __GNUC__ && ( ( !defined __EXCEPTIONS) || (defined __EXCEPTIONS && __EXCEPTIONS != 1) )
#			error OOLua has been compiled with exceptions yet they have been disabled for this build
#	elif defined _MSC_VER //&& !defined _HAS_EXCEPTIONS
#		if defined(_HAS_EXCEPTIONS) && (_HAS_EXCEPTIONS == 0)
#			error OOLua has been compiled with exceptions yet they have been disabled for this build
#		endif
#	endif
#endif

/** \endcond */

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

#ifndef TYPELIST_STRUCTS_H_
#	define TYPELIST_STRUCTS_H_

///////////////////////////////////////////////////////////////////////////////
///  @file typelist_structs.h
///  @remarks This file was auto generated
///////////////////////////////////////////////////////////////////////////////

/** \cond INTERNAL*/

namespace TYPE
{
	struct Null_type{};
} // namespace TYPE

/// the compile time list, where a standard list with raw pointers uses NULL for no type
/// this list has Null_type, which is an empty struct
///a node in the lists
///like a classic list node it contains a value for this node and the next
template <typename T, typename N>
struct Type_node
{
	///the type of this entry
	typedef T This;
	///the type for the next entry which is normally a Type_node, or a Null_type
	typedef N Next;
};

template
<
typename T01 = TYPE::Null_type, typename T02 = TYPE::Null_type, typename T03 = TYPE::Null_type, typename T04 = TYPE::Null_type, typename T05 = TYPE::Null_type,
typename T06 = TYPE::Null_type, typename T07 = TYPE::Null_type, typename T08 = TYPE::Null_type, typename T09 = TYPE::Null_type, typename T10 = TYPE::Null_type,
typename T11 = TYPE::Null_type, typename T12 = TYPE::Null_type, typename T13 = TYPE::Null_type, typename T14 = TYPE::Null_type, typename T15 = TYPE::Null_type,
typename T16 = TYPE::Null_type, typename T17 = TYPE::Null_type, typename T18 = TYPE::Null_type, typename T19 = TYPE::Null_type, typename T20 = TYPE::Null_type,
typename T21 = TYPE::Null_type, typename T22 = TYPE::Null_type, typename T23 = TYPE::Null_type, typename T24 = TYPE::Null_type, typename T25 = TYPE::Null_type,
typename T26 = TYPE::Null_type, typename T27 = TYPE::Null_type, typename T28 = TYPE::Null_type, typename T29 = TYPE::Null_type, typename T30 = TYPE::Null_type,
typename T31 = TYPE::Null_type, typename T32 = TYPE::Null_type, typename T33 = TYPE::Null_type, typename T34 = TYPE::Null_type, typename T35 = TYPE::Null_type,
typename T36 = TYPE::Null_type, typename T37 = TYPE::Null_type, typename T38 = TYPE::Null_type, typename T39 = TYPE::Null_type, typename T40 = TYPE::Null_type,
typename T41 = TYPE::Null_type, typename T42 = TYPE::Null_type, typename T43 = TYPE::Null_type, typename T44 = TYPE::Null_type, typename T45 = TYPE::Null_type,
typename T46 = TYPE::Null_type, typename T47 = TYPE::Null_type, typename T48 = TYPE::Null_type, typename T49 = TYPE::Null_type, typename T50 = TYPE::Null_type
>
struct Type_list
{
private:
	typedef typename Type_list
		<
			 T02, T03, T04, T05, T06, T07, T08, T09, T10,
		T11, T12, T13, T14, T15, T16, T17, T18, T19, T20,
		T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
		T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
		T41, T42, T43, T44, T45, T46, T47, T48, T49, T50
		>
		::type TailResult;

public:
	typedef Type_node<T01, TailResult> type;
};

template<>
struct Type_list<>
{
	typedef TYPE::Null_type type;
};

/**\endcond*/

#endif//TYPELIST_STRUCTS_H_
/**
	\file type_list.h
	\brief Loki Type_list from Andrei Alexandrescu's book Modern C++ Design
	\details
	\copyright
	The Loki Library \n
	Copyright (c) 2001 by Andrei Alexandrescu \n
	This code accompanies the book: \n
	Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
	Patterns Applied". Copyright (c) 2001. Addison-Wesley. \n
	Permission to use, copy, modify, distribute and sell this software for any
	purpose is hereby granted without fee, provided that the above copyright
	notice appear in all copies and that both that copyright notice and this
	permission notice appear in supporting documentation.
	The author or Addison-Wesley Longman make no representations about the
	suitability of this software for any purpose. It is provided "as is"
	without express or implied warranty. \n
*/


#ifndef TYPE_LIST_H_
#	define TYPE_LIST_H_


/** \cond INTERNAL*/

namespace TYPELIST
{
	///typelist algorithms

	///length////////////////////////////////////////////////////////////
	template <typename Type_list> struct Length;//forward declare

	///end of list stop recursive search
	template <> struct Length<TYPE::Null_type>
	{
		enum { value = 0 };
	};

	///recursively search the list counting until we reach null
	template <typename This, typename Next>
	struct Length< Type_node<This, Next> >//node in the list
	{
		enum { value = 1 + Length<Next>::value };
	};
	///length////////////////////////////////////////////////////////////


	///at////////////////////////////////////////////////////////////////
	///forward declare
	template <typename Type_list, unsigned int index> struct At;

	///specialise the index zero
	///when called the This type is the type of interest
	template <typename This, typename Next>
	struct At<Type_node<This, Next>, 0>
	{
		typedef This Result;
	};
	///recursive at finds the type at the index or throws a compile error
	///because it has gone out of bounds
	template <typename This, typename Next, unsigned int i>
	struct At<Type_node<This, Next>, i>
	{
		typedef typename At<Next, i - 1>::Result Result;
	};
	///at////////////////////////////////////////////////////////////////

	///forgiving at//////////////////////////////////////////////////////
	///at returns a compile time error when out of bounds where as this
	///just set the type to the default if out of bounds

	//end of list, so prevent out of bounds and use default
	template <typename Type_list, unsigned int index, typename Default = TYPE::Null_type>
	struct At_default
	{
		typedef Default Result;
	};

	///at the index of interest typedef the result
	template <typename This, typename Next, typename Default>
	struct At_default<Type_node<This, Next>, 0, Default>
	{
		typedef This Result;
	};

	///recursivly search the tree until we get the index of interest,
	//this maybe out of bounds and the default will be stored
	template <typename This, typename Next, unsigned int i, typename Default>
	struct At_default<Type_node<This, Next>, i, Default>
	{
		typedef typename At_default<Next, i - 1, Default>::Result Result;
	};
	///forgiving at//////////////////////////////////////////////////////

	///index/////////////////////////////////////////////////////////////

	///first of search.???

	template <typename Type_list, typename Type> struct IndexOf;

	///not found in list
	template <typename Type>
	struct IndexOf<TYPE::Null_type, Type>
	{
		enum { value = -1 };
	};

	///This is the type we are looking for
	template <typename T, typename Next>
	struct IndexOf<Type_node<T, Next>, T>
	{
		enum { value = 0 };
	};

	template <typename This, typename Next, typename Type>
	struct IndexOf<Type_node<This, Next>, Type>
	{
	private:
		enum { temp = IndexOf<Next, Type>::value };
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };
	};

	///index/////////////////////////////////////////////////////////////



	///append////////////////////////////////////////////////////////////
	template <typename Type_list, typename T> struct Append;

	///list is empty and type is empty
	template <> struct Append<TYPE::Null_type, TYPE::Null_type>
	{
		typedef TYPE::Null_type Result;
	};

	///if the list is empty then this is its only entry
	template <typename T> struct Append<TYPE::Null_type, T>
	{
		//typedef typename type1<T>::type Result;
		typedef Type_node<T, TYPE::Null_type> Result;
	};

	///tree is empty but what we are appending to it is a node
	template <typename This, typename Next>
	struct Append<TYPE::Null_type, Type_node<This, Next> >
	{
		typedef Type_node<This, Next> Result;
	};


	template <typename Head, typename Tail, typename T>
	struct Append<Type_node<Head, Tail>, T>
	{
		typedef Type_node<Head, typename Append<Tail, T>::Result> Result;
	};

	///append////////////////////////////////////////////////////////////


	///erase/////////////////////////////////////////////////////////////
	///erase the first instance of type Type
	template <typename Type_list, typename Type> struct Erase;

	template <typename Type>                         /// Specialization 1
	struct Erase<TYPE::Null_type, Type>
	{
		typedef TYPE::Null_type Result;
	};

	template <typename Type, typename Next>             /// Specialization 2
	struct Erase<Type_node<Type, Next>, Type>
	{
		typedef Next Result;
	};

	template <typename This, typename Next, typename Type> /// Specialization 3
	struct Erase<Type_node<This, Next>, Type>
	{
		typedef Type_node<This, typename Erase<Next, Type>::Result> Result;
	};

	///erase/////////////////////////////////////////////////////////////


	///erase all/////////////////////////////////////////////////////////
	///erase all instances of Type
	template <typename Type_list, typename Type> struct EraseAll;

	template <typename Type>
	struct EraseAll<TYPE::Null_type, Type>
	{
		typedef TYPE::Null_type Result;
	};

	template <typename Type, typename Next>
	struct EraseAll<Type_node<Type, Next>, Type>
	{
		/// Go all the way down the list removing the type
		typedef typename EraseAll<Next, Type>::Result Result;
	};

	template <typename This, typename Next, typename Type>
	struct EraseAll<Type_node<This, Next>, Type>
	{
		/// Go all the way down the list removing the type
		typedef Type_node<This, typename EraseAll<Next, Type>::Result> Result;
	};
	///erase all/////////////////////////////////////////////////////////

}//namespace TYPELIST

/**\endcond*/

#endif//TYPE_LIST_H_

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

#ifndef OOLUA_DSL_VA_ARGS_H_
#	define OOLUA_DSL_VA_ARGS_H_

#	if defined __GNUC__
#		pragma GCC system_header
#	endif

/** \file dsl_va_args.h
	\brief Provides a lot of the DSL procedures which make use of  \_\_VA_ARGS\_\_
*/

/** \cond INTERNAL
	The only difference between the code at the following URL from what is used below, is
	that the macro names got an OOLUA prefix as per all macros in the library.
	http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5
*/

/*No No, No No No No, No No No No, No No there's a limit! */
#	define OOLUA_INTERNAL_60_N \
		N, N, N, N, N, N, N, N, N, N \
		, N, N, N, N, N, N, N, N, N, N \
		, N, N, N, N, N, N, N, N, N, N \
		, N, N, N, N, N, N, N, N, N, N \
		, N, N, N, N, N, N, N, N, N, N \
		, N, N, N, N, N, N, N, N, N, N


#	define OOLUA_NARG(...)\
		OOLUA_NARG_DO(__VA_ARGS__, OOLUA_RSEQ_N)

#	define OOLUA_ARG_N(\
		_1, _2, _3, _4, _5, _6, _7, _8, _9, _10 \
		, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20 \
		, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30 \
		, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40 \
		, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50 \
		, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60 \
		, _61, _62, _63, N, ...) N

#	define OOLUA_RSEQ_N\
		63, 62, 61, 60 \
		, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50 \
		, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40 \
		, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30 \
		, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20 \
		, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10 \
		, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0


	/*====================================================
		For macros which require at least a specific amount of arguments.
		Translates to:
			0 if equal to amount
			N if more than the amount
		Compile time error if less than the required amount and greater than zero
	*/
#	define OOLUA_NARG_GREATER_THAN_ONE(...) \
		OOLUA_NARG_DO(__VA_ARGS__, OOLUA_INTERNAL_60_N, N, N, 0, ERROR_NOT_ENOUGH_PARAMETERS )

#	define OOLUA_NARG_GREATER_THAN_TWO(...) \
		OOLUA_NARG_DO(__VA_ARGS__, OOLUA_INTERNAL_60_N, N, 0, ERROR_NOT_ENOUGH_PARAMETERS, ERROR_NOT_ENOUGH_PARAMETERS)

#	define OOLUA_NARG_GREATER_THAN_THREE(...) \
		OOLUA_NARG_DO(__VA_ARGS__, OOLUA_INTERNAL_60_N, 0, ERROR_NOT_ENOUGH_PARAMETERS, ERROR_NOT_ENOUGH_PARAMETERS, ERROR_NOT_ENOUGH_PARAMETERS)

/*====================================================*/

/*	Concatenating normally only requires two macros to correctly expand yet
	when using OOLUA_NARG with Visual Studio it fails unless we go through
	a further macro to expand it.
*/
#	define DO_VA_CONCAT2(A, B)A##B
#	define DO_VA_CONCAT(A, B) DO_VA_CONCAT2(A, B)
#	define OOLUA_VA_CONCAT(A, B) DO_VA_CONCAT(A, B)


#	define OOLUA_PUBLIC_INHERIT_1(ClassType) \
			public Proxy_class<ClassType>

#	define OOLUA_PUBLIC_INHERIT_2(ClassType1, ClassType2) \
			OOLUA_PUBLIC_INHERIT_1(ClassType1) \
			, OOLUA_PUBLIC_INHERIT_1(ClassType2)

#	define OOLUA_PUBLIC_INHERIT_3(ClassType1, ClassType2, ClassType3) \
			OOLUA_PUBLIC_INHERIT_2(ClassType1, ClassType2) \
			, OOLUA_PUBLIC_INHERIT_1(ClassType3)

#	define OOLUA_PUBLIC_INHERIT_4(ClassType1, ClassType2, ClassType3, ClassType4) \
			OOLUA_PUBLIC_INHERIT_3(ClassType1, ClassType2, ClassType3) \
			, OOLUA_PUBLIC_INHERIT_1(ClassType4)

#	define OOLUA_PUBLIC_INHERIT_5(ClassType1, ClassType2, ClassType3, ClassType4, ClassType5) \
			OOLUA_PUBLIC_INHERIT_4(ClassType1, ClassType2, ClassType3, ClassType4)\
			, OOLUA_PUBLIC_INHERIT_1(ClassType4)

#	define OOLUA_PUBLIC_INHERIT_6(ClassType1, ClassType2, ClassType3, ClassType4, ClassType5, ClassType6) \
			OOLUA_PUBLIC_INHERIT_5(ClassType1, ClassType2, ClassType3, ClassType4, ClassType5) \
			, OOLUA_PUBLIC_INHERIT_1(ClassType6)


#	define OOLUA_PROXY_WITH_BASES_0(ClassType) \
			OOLUA_CLASS(ClassType) \
			OOLUA_BASIC \
			OOLUA_NO_BASES

#	define OOLUA_PROXY_WITH_BASES_N(ClassType, ...)\
			OOLUA_CLASS(ClassType) : OOLUA_PUBLIC_INHERIT(__VA_ARGS__) \
			OOLUA_BASIC \
			OOLUA_BASES_START __VA_ARGS__ OOLUA_BASES_END

/** \endcond */



//#if defined BROKEN_PREPROCESSOR
#	if defined _MSC_VER && _MSC_VER >= 1400 && _MSC_VER < 2000 && !defined __INTEL_COMPILER
	/** \cond INTERNAL
		vs8(2005), vs9(2008), vs10(2010), vs11(2012), vs12(2013) and vs14(2015) should all be fine with the work around of the __VA_ARGS__ bug
		which the compiler team will never admit to it being wrong. The fix was previously documented at the following
		URL yet the page is no longer reachable.
		https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details

		Taken from the above bug report URL and the proposed workaround

		For inline documentation see the none MSC version below
	*/

#		define OOLUA_LEFT_PAREN (
#		define OOLUA_RIGHT_PAREN )
#		define OOLUA_NARG_DO(...) \
			OOLUA_ARG_N OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

		/*Function generation helper macros*/
#		define OOLUA_PARAMS_CONCAT(StackIndex, ...)			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_PARAMS_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN StackIndex, __VA_ARGS__  OOLUA_RIGHT_PAREN
#		define OOLUA_PARAM_TYPE_CONCAT(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_FUNCTION_PARAMS_TYPES_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN
#		define OOLUA_TPARAMS_CONCAT(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_COMMA_PREFIXED_PARAM_TYPES_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN
#		define OOLUA_PPARAMS_CONCAT(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_CALL_PARAMS_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN
#		define OOLUA_BACK_CONCAT(...)			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_BACK_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN
#		define OOLUA_RETURNS_CONCAT(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_COMMA_PREFIXED_PARAM_TYPES_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN

		/*Public API*/
#		define OOLUA_PROXY(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_PROXY_WITH_BASES_, OOLUA_NARG_GREATER_THAN_ONE OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MEM_FUNC(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_, OOLUA_NARG_GREATER_THAN_TWO OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN  OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MEM_FUNC_RENAME(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_RENAME_, OOLUA_NARG_GREATER_THAN_THREE OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MEM_FUNC_CONST(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_CONST_, OOLUA_NARG_GREATER_THAN_TWO OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MEM_FUNC_CONST_RENAME(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_CONST_RENAME_, OOLUA_NARG_GREATER_THAN_THREE OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_C_FUNCTION(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_C_FUNCTION_, OOLUA_NARG_GREATER_THAN_TWO OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MFUNC(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MFUNC_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN  OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MFUNC_CONST(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MFUNC_CONST_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_CFUNC(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_CFUNC_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN  OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_SFUNC(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_STATIC_FUNC_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN  OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MGET(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MGET_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MSET(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MSET_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_MGET_MSET(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_MGET_MSET_INTERNAL_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_EXPORT_FUNCTIONS(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG_GREATER_THAN_ONE OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN OOLUA_NON_CONST, __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_EXPORT_FUNCTIONS_CONST(...)OOLUA_VA_CONCAT OOLUA_LEFT_PAREN EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG_GREATER_THAN_ONE OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN OOLUA_CONST, __VA_ARGS__ OOLUA_RIGHT_PAREN
		/*End Public API*/

#		define OOLUA_PUBLIC_INHERIT(...)		OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_PUBLIC_INHERIT_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define EXPORT_OOLUA_FUNCTIONS_0(mod, ClassType) \
			EXPORT_OOLUA_FUNCTIONS_0_(mod, ClassType)

#		define EXPORT_OOLUA_FUNCTIONS_N(mod, ClassType, ...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN OOLUA_VA_CONCAT OOLUA_LEFT_PAREN EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN , _ OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN mod, ClassType, __VA_ARGS__ OOLUA_RIGHT_PAREN

#		define OOLUA_VA_CONSTRUCTOR(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN INTERNAL::Constructor, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN

#		define VA_PARAM_TYPES(...) \
			OOLUA_VA_CONCAT OOLUA_LEFT_PAREN VA_, OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN

	/** \endcond */

#	else //Generic __VA_ARGS__

	/** \cond INTERNAL
		Assume the compiler supports __VA_ARGS__ and uses the standard implementation.
		The only difference between the code at the following URL from what is used below, is
		that the macro names got an OOLUA prefix as per all macros in the library.
		http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5
	*/
#		define OOLUA_NARG_DO(...) \
			OOLUA_ARG_N(__VA_ARGS__)

		/*Function generation helper macros*/
#		define OOLUA_PARAMS_CONCAT(StackIndex, ...)			OOLUA_VA_CONCAT(OOLUA_PARAMS_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (StackIndex, __VA_ARGS__  )
#		define OOLUA_PARAM_TYPE_CONCAT(...)		OOLUA_VA_CONCAT(OOLUA_FUNCTION_PARAMS_TYPES_, OOLUA_NARG(__VA_ARGS__))
#		define OOLUA_TPARAMS_CONCAT(...)		OOLUA_VA_CONCAT(OOLUA_COMMA_PREFIXED_PARAM_TYPES_, OOLUA_NARG(__VA_ARGS__))
#		define OOLUA_PPARAMS_CONCAT(...)		OOLUA_VA_CONCAT(OOLUA_CALL_PARAMS_, OOLUA_NARG(__VA_ARGS__))
#		define OOLUA_BACK_CONCAT(...)			OOLUA_VA_CONCAT(OOLUA_BACK_INTERNAL_, OOLUA_NARG(__VA_ARGS__))
#		define OOLUA_RETURNS_CONCAT(...)		OOLUA_VA_CONCAT(OOLUA_COMMA_PREFIXED_PARAM_TYPES_, OOLUA_NARG(__VA_ARGS__))

	/** \endcond*/

/*Public API macros using NARG or variants*/

/** \addtogroup OOLuaDSL DSL
@{
\brief The domain specific language(DSL) used for generating C++ bindings to Lua.
\details OOLua provides a DSL for defining C++ types which are to be made available to a
	Lua script. The intention of this DSL is to hide the implementation details whilst
	providing a simple and rememberable interface to perform the required actions. For
	the generation of function proxies, the DSL contains two sub categories named
	\ref OOLuaMinimalist and \ref OOLuaExpressive.

\note
	"Optional" here means that extra macro parameters are optional, up to the
	configuration \ref OOLuaConfigCppParams "max" for a specific operation.
*/

	/** \def OOLUA_PROXY
		\hideinitializer
		\brief Starts the generation a proxy class
		\details
		OOLUA_PROXY(ClassName, Optional)
		\param ClassName Class to be proxied
		\param Optional Comma seperated list of real base classes
		\pre Each class specified in Optional must be a real base class of ClassName
	*/
#		define OOLUA_PROXY(...) \
			OOLUA_VA_CONCAT(OOLUA_PROXY_WITH_BASES_, OOLUA_NARG_GREATER_THAN_ONE(__VA_ARGS__))(__VA_ARGS__)
		/**@{*/
	/** \def OOLUA_MGET
		\hideinitializer
		\brief Generates a getter, which is a constant function, to retrieve a public instance.
		\details
		OOLUA_MGET(PublicName, Optional)
		\param PublicName Name of the public variable to be proxied.
		\param Optional GetterName. Defaults to get_PublicName
		\note
		A generated getter for a pointer, or shared pointer, with a proxied pointee type,
		has an implicit \ref OOLUA::maybe_null trait applied.
	*/
#		define OOLUA_MGET(...) \
			OOLUA_VA_CONCAT(OOLUA_MGET_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)

	/** \def OOLUA_MSET
		\hideinitializer
		\brief Generates a setter, which is a none constant function, to set a public instance.
		\details
		OOLUA_MSET(PublicName, Optional)
		\param PublicName Name of the public variable to be proxied.
		\param Optional SetterName. Defaults to set_PublicName
	*/
#		define OOLUA_MSET(...) \
			OOLUA_VA_CONCAT(OOLUA_MSET_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)

	/** \def OOLUA_MGET_MSET
		\hideinitializer
		\brief Generates both a getter and a setter for a public instance.
		\details
		OOLUA_MGET_MSET(PublicName, Optional1, Optional2)
		\param PublicName Name of the public variable to be proxied.
		\param Optional1 GetterName. Defaults to get_PublicName
		\param Optional2 SetterName. Defaults to set_PublicName
		\see OOLUA_MGET and OOLUA_MSET
		\note If one optional parameter is supplied then both must be given and they must
		use different names.
	*/
#		define OOLUA_MGET_MSET(...) \
			OOLUA_VA_CONCAT(OOLUA_MGET_MSET_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)
		/**@}*/
	/** \addtogroup OOLuaExpressive Expressive
	@{
	\brief Generates a proxy function where a user has expressed all the details.
	\details
	Generates a function for which the user has expressed all the parameters and the return type
	for a function. These types may also have \ref OOLuaTraits applied to them which the
	\ref OOLuaMinimalist section of the DSL does not allow.
	*/
		/**@{*/
	/**	\def OOLUA_MEM_FUNC
		\hideinitializer
		\brief Generates a member function proxy which will also be the named FunctionName
		\details
		OOLUA_MEM_FUNC( FunctionReturnType, FunctionName, Optional)
		\param FunctionReturnType
		\param FunctionName
		\param Optional : Comma separated list of function parameter types
		\see \ref OOLuaConfigCppParams "cpp_params"
	*/
#		define OOLUA_MEM_FUNC(...) \
			OOLUA_VA_CONCAT(OOLUA_MEM_FUNC_, OOLUA_NARG_GREATER_THAN_TWO(__VA_ARGS__)) (__VA_ARGS__)

	/** \def OOLUA_MEM_FUNC_RENAME
		\hideinitializer
		\brief Generates a member function proxy which will be the named ProxyFunctionName
		\details
		OOLUA_MEM_FUNC_RENAME( ProxyFunctionName, FunctionReturnType,FunctionName, Optional)
		\param ProxyFunctionName
		\param FunctionReturnType
		\param FunctionName
		\param Optional : Comma separated list of function parameter types
		\see \ref OOLuaConfigCppParams "cpp_params"
	*/
#		define OOLUA_MEM_FUNC_RENAME(...) \
			OOLUA_VA_CONCAT(OOLUA_MEM_FUNC_RENAME_, OOLUA_NARG_GREATER_THAN_THREE(__VA_ARGS__))(__VA_ARGS__)

	/** \def OOLUA_MEM_FUNC_CONST
		\hideinitializer
		\brief Generates a constant member function proxy which will also be the named FunctionName
		\details
		OOLUA_MEM_FUNC_CONST( FunctionReturnType,FunctionName,Optional)
		\param FunctionReturnType
		\param FunctionName
		\param Optional Comma separated list of function parameter types
		\see \ref OOLuaConfigCppParams "cpp_params"
	*/
#		define OOLUA_MEM_FUNC_CONST(...) \
			OOLUA_VA_CONCAT(OOLUA_MEM_FUNC_CONST_, OOLUA_NARG_GREATER_THAN_TWO(__VA_ARGS__))(__VA_ARGS__)

	/** \def OOLUA_MEM_FUNC_CONST_RENAME
		\hideinitializer
		\brief Generates a constant member function which will be named ProxyFunctionName
		\details
		OOLUA_MEM_FUNC_CONST_RENAME( ProxyFunctionName, FunctionReturnType, FunctionName,Optional)
		\param ProxyFunctionName
		\param FunctionReturnType
		\param FunctionName
		\param Optional Comma separated list of function parameter types
		\see \ref OOLuaConfigCppParams "cpp_params"
	*/
#		define OOLUA_MEM_FUNC_CONST_RENAME(...) \
			OOLUA_VA_CONCAT(OOLUA_MEM_FUNC_CONST_RENAME_, OOLUA_NARG_GREATER_THAN_THREE(__VA_ARGS__))(__VA_ARGS__)
		/**@}*/

	/** \def OOLUA_C_FUNCTION
		\hideinitializer
		\brief Generates a block which will call the C function FunctionName
		\details
		OOLUA_C_FUNCTION(FunctionReturnType,FunctionName, Optional)
		\param FunctionReturnType
		\param FunctionName
		\param Optional Comma separated list of function parameter types
		\see \ref OOLuaConfigCppParams "cpp_params"
		\pre The function in which this macro is contained must declare a lua_State pointer
		which can be identified by the name "vm"
		\code{.cpp}
		extern void foo(int);
		int l_foo(lua_State* vm)
		{
			OOLUA_C_FUNCTION(void,foo,int)
		}
		\endcode
		\note
		This macro should ideally be used as the last operation of a function body as
		control will return to the caller. Notice there is no return statement in l_foo
	*/
#		define OOLUA_C_FUNCTION(...) \
			OOLUA_VA_CONCAT(OOLUA_C_FUNCTION_, OOLUA_NARG_GREATER_THAN_TWO(__VA_ARGS__))(__VA_ARGS__)
	/**	@}*/



	/** \addtogroup OOLuaMinimalist Minimalist
 	@{
	\brief Generates code using only the minimal amount of information.
	\details
	Generates a proxy function using the only the minimal amount of information which is generally
	the name of the thing being proxied and possibly a new name for the proxy. If a new name is supplied
	then the function will be made available to Lua using it and this name must be used when
	\ref OOLuaExporting the function.

	This part of the DSL attempts to automatically determine the parameter types and return type for
	the function in question. However, if the function is overloaded then the compiler will be unable to
	resolve the function, due to the ambiguity, and will produce a compile time error. To help the
	compiler resolve this ambiguity, the user should specify more information using the corresponding,
	yet longer named, \ref OOLuaExpressive DSL entry.\n
	The longer DSL name requires more information. \n
	\note No \ref OOLuaTraits can be expressed with this DSL group.
	*/
		/**@{*/
	/** \def OOLUA_MFUNC
		\hideinitializer
		\brief Deduce and generate a proxy for a member function
		\details
		OOLUA_MFUNC(FunctionName, Optional)
		\param FunctionName Name of the member function to be proxied
		\param Optional ProxyFunctionName. Defaults to FunctionName
		\see \ref OOLuaConfigCppParams "cpp_params" \n
		\ref OOLUA_MEM_FUNC \n
		\ref OOLUA_MEM_FUNC_RENAME
	*/
#		define OOLUA_MFUNC(...) \
			OOLUA_VA_CONCAT(OOLUA_MFUNC_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)

	/** \def OOLUA_MFUNC_CONST
		\hideinitializer
		\brief Deduce and generate a proxy for a constant member function
		\details
		OOLUA_MFUNC_CONST(FunctionName, Optional)
		\param FunctionName Name of the constant function to be proxied
		\param Optional ProxyFunctionName. Defaults to FunctionName
		\see \ref OOLuaConfigCppParams "cpp_params" \n
		\ref OOLUA_MEM_FUNC_CONST \n
		\ref OOLUA_MEM_FUNC_CONST_RENAME
	*/
#		define OOLUA_MFUNC_CONST(...) \
			OOLUA_VA_CONCAT(OOLUA_MFUNC_CONST_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)
		/**@}*/

	/** \def OOLUA_CFUNC
		\hideinitializer
		\brief Deduce and generate a proxy for a C function
		\details
		OOLUA_CFUNC(FunctionName, ProxyFunctionName)
		\param FunctionName Name of the C function to be proxied
		\param ProxyFunctionName Name of the function to generate which will proxy FunctionName
		\see \ref OOLuaConfigCppParams "cpp_params" \n
		\ref OOLUA_C_FUNCTION
	*/
#		define OOLUA_CFUNC(...) \
			OOLUA_VA_CONCAT(OOLUA_CFUNC_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)

	/** \def OOLUA_SFUNC
		\hideinitializer
		\brief Deduce and generate a proxy for a class static function
		\details
		OOLUA_SFUNC(FunctionName, Optional)
		\param FunctionName Name of the static function to be proxied
		\param Optional ProxyFunctionName. Defaults to FunctionName
		\note This function will not be exported and needs to be registered
		with OOLua see OOLUA::register_class_static
		\see \ref OOLuaConfigCppParams "cpp_params"
	 */
#		define OOLUA_SFUNC(...) \
			OOLUA_VA_CONCAT(OOLUA_STATIC_FUNC_INTERNAL_, OOLUA_NARG(__VA_ARGS__)) (__VA_ARGS__)

	/**	@}*/


	/** \addtogroup OOLuaExporting Exporting
	@{
		\brief Exports member functions
		\details Exporting defines which member functions will be registered with Lua when the
		class type is registered. Even when there are no member functions to be exported you still
		need to inform OOLua about this. Calling an \ref OOLuaExporting "OOLUA_EXPORT*"
		procedure in a header file is an error that will fail to compile.

		\see OOLUA_EXPORT_FUNCTIONS \n OOLUA_EXPORT_FUNCTIONS_CONST \n OOLUA_EXPORT_NO_FUNCTIONS
	 */


	/**	\def OOLUA_EXPORT_FUNCTIONS
		\hideinitializer
		\brief Exports zero or more member functions which will be registered with Lua
		\details
		OOLUA_EXPORT_FUNCTIONS(ClassName,Optional)
		\param ClassName Name of class to which the function belong to
		\param Optional Comma separated list of member function names
		\see \ref OOLuaConfigClassFunctions "class_functions"
	*/
#		define OOLUA_EXPORT_FUNCTIONS(...)		OOLUA_VA_CONCAT(EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG_GREATER_THAN_ONE(__VA_ARGS__))(OOLUA_NON_CONST, __VA_ARGS__)

	/** \def OOLUA_EXPORT_FUNCTIONS_CONST
		\hideinitializer
		\brief Exports zero or more const member functions which will be registered with Lua
		\details
		OOLUA_EXPORT_FUNCTIONS_CONST(ClassName,Optional)
		\param ClassName Name of class to which the function belong to
		\param Optional Comma separated list of constant member function names
		\see \ref OOLuaConfigClassFunctions "class_functions"
	*/
#		define OOLUA_EXPORT_FUNCTIONS_CONST(...)OOLUA_VA_CONCAT(EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG_GREATER_THAN_ONE(__VA_ARGS__))(OOLUA_CONST, __VA_ARGS__)
	/**	@}*/

/**@}*/

/*End public API*/


	/** \cond INTERNAL*/
#		define OOLUA_PUBLIC_INHERIT(...)		OOLUA_VA_CONCAT(OOLUA_PUBLIC_INHERIT_, OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)

	/*This is here because EXPORT_OOLUA_FUNCTIONS_N uses OOLUA_NARG*/
#		define EXPORT_OOLUA_FUNCTIONS_0(mod, ClassType) \
			EXPORT_OOLUA_FUNCTIONS_0_(mod, ClassType)

#		define EXPORT_OOLUA_FUNCTIONS_N(mod, ClassType, ...) \
			OOLUA_VA_CONCAT(OOLUA_VA_CONCAT(EXPORT_OOLUA_FUNCTIONS_, OOLUA_NARG(__VA_ARGS__)), _)(mod, ClassType, __VA_ARGS__)

#		define OOLUA_VA_CONSTRUCTOR(...) \
			OOLUA_VA_CONCAT(INTERNAL::Constructor, OOLUA_NARG(__VA_ARGS__))

#		define VA_PARAM_TYPES(...) \
			OOLUA_VA_CONCAT(VA_, OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)

/** \endcond*/

#	endif
/*
		\details Tags specify more information about a class that is being exposed.
		An example of the details that are expressed with them is:
		\li \ref OperatorTags "Operators" to expose
		\li Overriding default \ref SharedTags "shared" settings
		\li Marking a class as \ref OOLUA::Abstract "abstract"
		\li Registering class \ref OOLUA::Register_class_enums "enumerations"
*/
/** \addtogroup OOLuaDSL DSL
@{
		\def OOLUA_TAGS
		\hideinitializer
		\brief Allows more information to be specified about the proxy class.
		\details Tags provide a method to inform the library that the type :
		\li has relationship and/or mathematical operators
		\li is an abstract class
		\li doesn't have a default constructor or any public constructors
		\li has enumerations

		<p>For an exhaustive list of the possible tags see \ref OOLuaTags.
		<p>
		OOLUA_TAGS(TagList)
		\param TagList Comma separated list of \ref OOLuaTags

		\note An OOLUA_TAGS list without any \ref OOLuaTags entries is invalid.
	 */
#		define OOLUA_TAGS(...) OOLUA_TAGS_START __VA_ARGS__ OOLUA_TAGS_END
/*@}*/


#endif //OOLUA_DSL_VA_ARGS_H_
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

#ifndef LVD_TYPE_TRAITS_H_
#	define LVD_TYPE_TRAITS_H_

/**
	\file lvd_type_traits.h
	\brief Template struct which report if the type has qualifiers and also
	removes some of the possible qualifiers
*/
namespace LVD
{
	struct is_true{};
	struct is_false{};

	template<typename T, typename T1>
	struct is_same
	{
		enum {value = 0};
	};

	template<typename T>
	struct is_same<T, T>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const
	{
		enum {value = 0};
	};

	template<typename T>struct is_const<T const>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T const&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T const*>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T * const>
	{
		enum {value = 0};
	};

	template<typename T>struct is_const<T const * const>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T const * const&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T * const&>
	{
		enum {value = 0};
	};

	template<typename T>struct is_const<T const *&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const<T * const *&>
	{
		enum {value = 0};
	};

	template<typename T>struct is_const<T const * const *&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_void
	{
  		enum {value = 0};
	};

	template<>struct is_void<void>
	{
		enum {value = 1};
	};

	template<typename T>struct is_ref
	{
		enum {value = 0};
	};

	template<typename T>struct is_ref<T&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_ref_to_const
	{
		enum {value = 0};
	};

	template<typename T>struct is_ref_to_const<T const&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_ref_to_pointer
	{
		enum {value = 0};
	};

	template<typename T>struct is_ref_to_pointer<T*&>
	{
		enum {value = 1};
	};

	template<typename T>struct is_ptr
	{
		enum {value = 0};
	};

	template<typename T>struct is_ptr<T*>
	{
		enum {value = 1};
	};

	template<typename T>struct is_ptr_to_const
	{
		enum {value = 0};
	};

	template<typename T>struct is_ptr_to_const<T const*>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const_ptr_to
	{
		enum {value = 0};
	};

	template<typename T>struct is_const_ptr_to<T *const>
	{
		enum {value = 1};
	};

	template<typename T>struct is_const_ptr_to_const
	{
		enum {value = 0};
	};

	template<typename T>struct is_const_ptr_to_const<T const * const>
	{
		enum {value = 1};
	};

	template<typename T>struct has_qualifiers
	{
		enum { value = (
			is_ref<T>::value
			+ is_ref_to_const<T>::value
			+ is_ref_to_pointer<T>::value
			+ is_ptr<T>::value
			+ is_ptr_to_const<T>::value
			+ is_const_ptr_to<T>::value
			+ is_const_ptr_to_const<T>::value
			+ is_const<T>::value )
		? 1 : 0 };
	};

	template<typename T>struct by_reference
	{
		enum { value = (
			is_ref<T>::value
			+ is_ref_to_const<T>::value
			+ is_ref_to_pointer<T>::value
			+ is_ptr<T>::value
			+ is_ptr_to_const<T>::value
			+ is_const_ptr_to<T>::value
			+ is_const_ptr_to_const<T>::value )
		? 1 : 0 };
	};

	template<typename T>struct by_value
	{
		enum { value = !by_reference<T>::value };
	};

	template<typename T>struct constant_remover
	{
		typedef T  type;
	};

	template<typename T>struct constant_remover<T const>
	{
		typedef T  type;
	};

	template<typename T>struct constant_remover<T const&>
	{
		typedef T&  type;
	};

	template<typename T>struct constant_remover<T const*>
	{
		typedef T*  type;
	};

	template<typename T>struct constant_remover<T const * const>
	{
		typedef T* const  type;
	};

	template<typename T>struct constant_remover<T* const>
	{
		typedef T* const  type;
	};

	template<typename T>struct remove_const
	{
		typedef typename constant_remover<T>::type type;
	};

/////////////////////////////////////////////////////////////////////////////////////


	template<typename T>struct all_constant_remover
	{
		typedef T  type;
	};

	template<typename T>struct all_constant_remover<T const>
	{
		typedef T  type;
	};

	template<typename T>struct all_constant_remover<T const&>
	{
		typedef T&  type;
	};

	template<typename T>struct all_constant_remover<T const*>
	{
		typedef T*  type;
	};

	template<typename T>struct all_constant_remover<T const * const>
	{
		typedef T*  type;
	};

	template<typename T>struct all_constant_remover<T* const>
	{
		typedef T*  type;
	};

	template<typename T>struct remove_all_const
	{
		typedef typename all_constant_remover<T>::type type;
	};

	template<typename T>struct remove_ref
	{
		typedef T type;
	};

	template<typename T>struct remove_ref<T&>
	{
		typedef T type;
	};

	template<typename T>struct ptr_remover
	{
		typedef T type;
	};

	template<typename T>struct ptr_remover<T*>
	{
		typedef T type;
	};

	template<typename T>struct remove_ptr
	{
		typedef typename ptr_remover<T>::type type;
	};

	namespace
	{
		template<typename Input, template <typename> class Do,
					template <typename> class Test, int result>
		struct do_while;


		template<typename Input, template <typename> class Do,
					template <typename> class Test, int result>
		struct do_while
		{
			typedef typename do_while<typename Do<Input>::type
									, Do
									, Test
									, Test<typename Do<Input>::type>::value >::type type;
		};

		template<typename Input, template <typename>class Do,
					template <typename> class Test >
		struct do_while<Input, Do, Test, 0>
		{
			typedef Input type;
		};
	} // namespace

	template<typename T>struct remove_all_ptrs
	{
		typedef typename do_while<T //input
									, remove_ptr //do
									, is_ptr //test
									, is_ptr<T>::value //result
								>::type type;
	};

	template<typename T>
	struct raw_type
	{
		typedef typename remove_ref<T>::type no_ref;
		typedef typename remove_all_const<no_ref>::type no_ref_or_const;
		typedef typename remove_all_ptrs<no_ref_or_const>::type raw;
		typedef raw type;
	};

	template <typename From>
	class can_convert_to_int
	{
		typedef char (&yes)[1];
		typedef char (&no)[2];
		struct Convertor
		{
			template <typename T>
			Convertor(T&);
		};
		static no test(Convertor);
		static no test(float&);
		static no test(double&);
#ifdef _MSC_VER
		static yes test(::size_t); // NOLINT
#else
		static yes test(int); // NOLINT
#endif
		static From& make_from();
	public:
		enum { value = sizeof test(make_from()) == sizeof(yes) ? 1 : 0 };
	};

	template<typename T>
	struct is_class_type
	{
		typedef char (&yes)[1];
		typedef char (&no)[2];
		template<typename C>
		static no test(...);
		template<typename C>
		static yes test(char C::*); // NOLINT
	public:
		enum { value = sizeof test<typename raw_type<T>::type >(0) == sizeof(yes) ? 1 : 0 };
	};

} // namespace LVD // NOLINT

#endif //LVD_TYPE_TRAITS_H_
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
///  @file lvd_types.h
///  \brief Cross platform integral sized types.
///////////////////////////////////////////////////////////////////////////////

#ifndef BASIC_TYPES_H_
#	define BASIC_TYPES_H_


/** \cond INTERNAL*/

#	if ( defined (WINDOWS_BUILD) )
#		ifdef __GNUC__
    #		include <stdint.h>
namespace LVD
{
			typedef int8_t				int8;
			typedef uint8_t				uint8;
			typedef int16_t				int16;
			typedef uint16_t			uint16;
			typedef int32_t				int32;
			typedef uint32_t			uint32;
			//gcc does define these types yet you need to use the
			// -Wno-long-long flag
			__extension__ typedef long long             int64;
			__extension__ typedef unsigned long long    uint64;
} // namespace LVD
#		elif defined _MSC_VER
namespace LVD
{
			typedef signed	__int8		int8;
			typedef unsigned __int8		uint8;
			typedef signed	__int16		int16;
			typedef unsigned __int16	uint16;
			typedef signed	__int32		int32;
			typedef unsigned __int32	uint32;
			typedef	signed	__int64		int64;
			typedef unsigned __int64	uint64;
} // namespace LVD
#		else
#			error please inform me what compiler are you using and set the correct types
#		endif
#	elif(defined(UNIX_BUILD) || defined(MAC_BUILD))
#		include <stdint.h>
namespace LVD
{
		typedef int8_t				int8;
		typedef uint8_t				uint8;
		typedef int16_t				int16;
		typedef uint16_t			uint16;
		typedef int32_t				int32;
		typedef uint32_t			uint32;
#		ifdef __CYGWIN__
			//gcc does define these types yet you need to use the
			// the extension keyword to prevent warnings when using a high warning level
			//The -Wno-long-long flag could suppress this but lets not interfere
			//with what settings a user wants.
			__extension__ typedef	long long			int64;
			__extension__ typedef unsigned long long	uint64;
#		else
			typedef int64_t				int64;
			typedef uint64_t			uint64;
#		endif
} // namespace LVD

#	endif

namespace LVD
{
	//typedef uint8 byte;
	typedef unsigned char byte;
	typedef uint32 size_t;

	template<typename T>
	struct is_integral_type
	{
		typedef Type_list<
				bool
				, char, unsigned char, signed char
				, short, unsigned short, signed short
				, int, unsigned int, signed int
				, long, unsigned long, signed long, int64, uint64
				, float
				, double, long double>::type Integral;
		enum {value = TYPELIST::IndexOf<Integral, T>::value == -1 ? 0 : 1};
	};


	template< bool Test>
	struct if_
	{
		enum {RESULT = 1};
	};

	template< >
	struct if_<false>
	{
		enum {RESULT = 0};
	};

	template<int T, int T1>
	struct if_or
	{
		enum {value =1};
	};
	template<>
	struct if_or<0, 0>
	{
		enum {value =0};
	};

	template< bool B, typename Then = void, typename Else = void >
	struct if_else
	{
		typedef Then type;
	};

	template< typename Then, typename Else >
	struct if_else< false, Then, Else >
	{
		typedef Else type;
	};

	struct Pointer_size
	{
		enum Size{size_value = sizeof(void*)};
		typedef if_else< sizeof(uint8) == size_value, uint8
					, if_else< sizeof(uint16) == size_value, uint16
					, if_else< sizeof(uint32) == size_value, uint32
					, if_else< sizeof(uint64) == size_value, uint64
				>::type >::type >::type >::type type;
	};
//
//	///unsigned int type for pointer manipulation
//	//it is here because it is not part of the C++ standard :(
//	typedef Pointer_size::type uintptr_t;
	typedef Pointer_size::type uintptr_t_lvd;

	///  Int2type
	///  Converts a int to a constant.
	template<int T>
	struct Int2type
	{
		enum {value = T};
	};

	///  Type2type
	///  typedefs a type.
	///  @remarks Useful for compile time choices.
	template<typename T>
	struct Type2type
	{
		typedef T type;
	};

	///  Type2bytes
	///  Convert a integral type into an array of bytes.
	template<typename T>
	struct Type2bytes
	{
		Type2bytes(T const &value):whole(value){}
		Type2bytes():whole(T()/*0*/){}
		union
		{
			T whole;
			byte bytes[sizeof(T)];
		};
	};

} // namespace LVD

/** \endcond*/

#endif//BASIC_TYPES_H_
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

#ifndef OOLUA_PROXY_TEST_H_
#	define OOLUA_PROXY_TEST_H_
namespace OOLUA
{
	template<typename T>
	class Proxy_class;
	/** \cond INTERNAL */
	namespace INTERNAL
	{
		template<typename Type>
		struct has_a_proxy_type
		{
			typedef OOLUA::Proxy_class<Type> proxy_type;
			template <typename U>
			static char (& has_none_proxy_typedef(typename U::OoluaNoneProxy*))[1];

			template <typename U>
			static char (& has_none_proxy_typedef(...))[2];

			enum {value = sizeof(has_none_proxy_typedef<proxy_type>(0)) == 1 ? 0 : 1};
		};
	} // namespace INTERNAL //NOLINT(readability/namespace)
	/** \endcond*/
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

/**
	\file oolua_string.h
	\brief Provides a method of not including the string header in DSL header
	files and allows other string types to be easily integrated.
*/
#ifndef OOLUA_STRING_H_
#	define OOLUA_STRING_H_


struct lua_State;

namespace OOLUA
{
	/**
	\addtogroup OOLuaStringConfig
	@{
		\brief Enables a string type to be treated as an integral.
		\details String configuration enables a type to be treated as an alias and
		integral type for a Lua string, LUA_TSTRING. When a type is considered an
		integral it means that a heap allocation, for the object itself, does not occur
		and the instance is a value rather than a reference. The alternative to this,
		is for the string type to be proxied using the library's DSL.

		Identification of the type is tested using the compile time value contained in
		\ref OOLUA::STRING::is_integral_string_class "is_integral_string_class".
		A provided macro, \ref OOLUA_CLASS_OR_BASE_CONTAINS_METHOD, helps to create a
		structure that identifies the type and can be used in is_integral_string_class.
		The library file oolua_string.h contains examples of using this macro to
		identify a number of string types; such as std::string, C++03 and C++11
		strings(std::string, std::wstring, std::u16string and std::u32string), wxString
		and QString.

		Once a type can be identified in
		\ref OOLUA::STRING::is_integral_string_class "is_integral_string_class" as an
		integral string alias, then a user should provide implementations for the three
		specific templated functions, (OOLUA::STRING::push, OOLUA::STRING::pull and
		OOLUA::STRING::get) in oolua_string.cpp.

		\namespace OOLUA::STRING
		\brief Defines which type of string classes can be pulled and pushed from
		the stack with the public API and the DSL.
		\details
		I would really like to be able to forward declare string types in a cross
		platform way. For example when using GCC we could, but really shouldn't,
		use bits/stringfwd.h. However this is just not possible. Instead this file and
		its accompanying source file, oolua_string.cpp, provide a way to not include the
		string header through out the library DSL headers, yet still be able to use a
		string type when needed. It also facilitates the addition, and therefore
		interaction, of other string types with Lua.
		To allow a string type to be compatible with OOLua requires that three functions
		are defined for the type(push, pull and get) and is_integral_string_class::value
		must be a compile time value that returns one for the type.
	@}
	*/
	namespace STRING
	{
		/**
		\addtogroup  OOLuaStringConfig
		@{*/
		/**
		\brief Function to which public API calls resolve to.
		*/
		template<typename StringType>
		bool push(lua_State* const vm, StringType const& value);

		/**
		\brief Function to which public API calls resolve to.
		*/
		template<typename StringType>
		bool pull(lua_State* const vm, StringType& value);

		/**
		\brief Internal function used by the DSL to retrieve a string from the stack.
		\details The are a couple of differences between this function and
		\ref OOLUA::STRING::pull "pull". Firstly, pull retrieves the stack's top entry and
		pops it where as this function uses a stack index to identify the stack slot
		and the function does not pop the entry. Secondly, there is a difference in how
		errors are reported. Pull will either store and error or throw an exception,
		where as this function will eventually call lua_error.
		*/
		template<typename StringType>
		void get(lua_State* const vm, int idx, StringType &  value);
		/**@}*/
	} // namespace STRING //NOLINT(readability/namespace)
} // namespace OOLUA


namespace OOLUA
{
	namespace STRING
	{
/**
	\addtogroup  OOLuaStringConfig
	@{
	\def OOLUA_CLASS_OR_BASE_CONTAINS_METHOD
	\brief Creates a structure that enables checking a class type for a specific
	function signature that has a specific name.
	\hideinitializer
	\param StructName The name of the structure this macro will create.
	\param MethodSignature The signature the checker will look for.
	\param MethodName The function's name which has the MethodSignature
	@}
*/
#define OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(StructName, MethodSignature, MethodName) \
		template<typename Type> \
		struct StructName \
		{ \
			typedef char yes[1]; \
			typedef char no [2]; \
			template<typename FuncT, FuncT> struct checker; \
			template <typename U> \
			static yes &check(checker<MethodSignature, &U::MethodName>*); \
			template <typename U> \
			static no &check(...); \
			enum {value = sizeof(check<Type>(0)) == sizeof(yes)}; \
		};

/**
	\addtogroup  OOLuaStringConfig
	@{
	\struct OOLUA::STRING::only_std_string_conforming_with_c_str_method
	\brief
	Defines the structure which checks for the method "c_str" which conforms to
	the std::string signature.
	@}
*/
OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(only_std_string_conforming_with_c_str_method
								, char const* (U::*)()const
								, c_str)

/*this will pass for all std:: string types (string, wstring, u16string and u32string)*/
/*
OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(std_conforming_with_c_str_method
								, typename U::const_pointer (U::*)()const
								, c_str)
*/

/*this will pass for all std:: string types (string wstring u16string u32string) and wxString*/
/*
OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(std_conforming_with_substr_method
								, U(U::*)(typename U::size_type,typename U::size_type)const
								, substr)
*/

/*
	wxString
	bool ToCULong (unsigned long *val, int base=10) const
*/
/*
OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(is_wxstring
								, (bool(U::*)(unsigned long*,int)const)
								, ToCULong)
*/

/*
	QString
	QString toCaseFolded () const
*/
/*
OOLUA_CLASS_OR_BASE_CONTAINS_METHOD(is_qstring
								, U(U::*)()const
								, toCaseFolded);
*/

		/**
		\addtogroup  OOLuaStringConfig
		@{
			\struct OOLUA::STRING::is_integral_string_class
			\brief Preforms the check on the type without including the string header
			\details To add a different string class type, see the commented out macros
			in oolua_string.h.
			\see \ref OOLUA_STD_STRING_IS_INTEGRAL
		@}
		*/
		template<typename T>
		struct is_integral_string_class
		{
			typedef typename LVD::raw_type<T>::type raw_type;
			enum { value =
#if OOLUA_STD_STRING_IS_INTEGRAL == 1
						INTERNAL::has_a_proxy_type<raw_type>::value == 0
						&& only_std_string_conforming_with_c_str_method<raw_type>::value == 1
#else
						0
#endif
				};
		};
	} // namespace STRING //NOLINT(readability/namespace)
} // namespace OOLUA

#endif //OOLUA_STRING_H_
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
	\file oolua_traits_fwd.h
	\brief Forward declarations of \ref OOLuaTraits
*/

#ifndef OOLUA_TRAITS_FWD_H_
#	define OOLUA_TRAITS_FWD_H_

namespace OOLUA
{
	template<typename T>
	struct in_p;

	template<typename T>
	struct out_p;

	template<typename T>
	struct in_out_p;

	template<typename T>
	struct lua_out_p;

	template<typename T>
	struct light_p;

	struct calling_lua_state;

	template<typename T>
	struct light_return;

	template<typename T>
	struct lua_return;

	template<typename T>
	struct shared_return;

	template<typename T>
	struct maybe_null;

	template<typename T>
	struct cpp_acquire_ptr;

	template<typename T>
	struct lua_acquire_ptr;

	enum Owner
	{	No_change	/*!< No change of ownership*/
		, Cpp		/*!< Change in ownership, C++ will now own the instance*/
		, Lua		/*!< Change in ownership, Lua will now own the instance*/
	};

	/** \cond INTERNAL */
	namespace INTERNAL
	{
		template<typename T>
		struct Type_enum_defaults;

		template<typename T>
		struct function_return;

		template<typename T>
		struct param_type;

		template<typename T>
		struct return_type_traits;

		template<typename T>
		struct lua_return_count;

		template<typename EnumType>
		struct is_scoped_enum;
	} //namespace INTERNAL //NOLINT(readability/namespace)
	/** \endcond */
} // namespace OOLUA

#endif //OOLUA_TRAITS_FWD_H_
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
	\file oolua_traits.h
	Traits for the DSL and public API functions.
	\remarks
	For the DSL if parameter traits are not supplied then it defaults to OOLUA::in_p.
	For function return values OOLUA::function_return is used (inside the generating
	function), this template is specialised for void types.
*/

#ifndef OOLUA_TRAITS_H_
#	define OOLUA_TRAITS_H_


struct lua_State;
namespace OOLUA
{

// TODO :
/*
	pull_type is really an incorrect name for return types
	yet it has this name to be the same as input parameters.
	Consider changing the name of both to something more suitable.
*/

/** \addtogroup OOLuaTraits Traits
@{
\brief Provides direction and/or ownership information.
\details
The general naming conventions for traits are :\n
\li \ref OOLuaFunctionParamTraits : end in "_p"
\li \ref OOLuaFunctionReturnTraits : end in "_return" or "_null"
\li \ref OOLuaStackTraits : end in "_ptr".
*/

	/** \addtogroup OOLuaFunctionParamTraits Parameter Traits
	@{
		\brief DSL Traits for function parameter types.
		\details Traits which allow control of ownership include in their name either
		"lua" or "cpp"; directional traits contain "in", "out" or a combination.
	*/
	/** \struct in_p
		\brief Input parameter trait
		\details
		The calling Lua procedure supplies the parameter to the proxied function.
		No change of ownership occurs.
		\note
		This is the default trait used for function parameters when no trait
		is supplied.
	*/
	template<typename T>struct in_p;

	/** \struct out_p
		\brief Output parameter trait
		\details
		The calling Lua procedure does not pass the parameter to the proxied
		function, instead one is created using the default constructor and
		passed to the proxied function. The result after the proxied call with
		be returned to the calling procedure. If this is a type which has a
		proxy then it will cause a heap allocation of the type, which Lua will
		own.
	*/
	template<typename T>struct out_p;

	/** \struct in_out_p
		\brief Input and output parameter trait
		\details
		The calling Lua procedure supplies the parameter to the proxied
		function, the value of the parameter after the proxied call will be
		passed back to the calling procedure as a return value.
		No change of ownership occurs.
	*/
	template<typename T>struct in_out_p;

	/** \struct cpp_in_p
		\brief Input parameter trait which will be owned by C++
		\details Parameter supplied via Lua changes ownership to C++.
	*/
	template<typename T>struct cpp_in_p;


	/** \struct lua_out_p
		\brief Output parameter trait which will be owned by Lua
		\details
		Lua code does not pass an instance to the C++ function, yet the pushed back
		value after the function call will be owned by Lua. This is meaningful only
		if called with a type which has a proxy and it is by reference, otherwise
		undefined.
	*/
	template<typename T>struct lua_out_p;

	/** \struct light_p
		\brief Input parameter trait
		\details
		The calling Lua procedure supplies a LUA_TLIGHTUSERDATA which will be cast to the
		requested T type. If T is not the correct type for the light userdata then
		the casting is undefined.
		A light userdata is never owned by Lua
	 */
	template<typename T>struct light_p;

	/** \struct OOLUA::calling_lua_state
		\brief Special parameter type
		\details This is different from all other traits as it does not take a type, yet
		is a type. It informs OOLua that the calling state is a parameter for a function
	*/
	struct calling_lua_state;
	/**@}*/

	/** \addtogroup OOLuaFunctionReturnTraits Function Return Traits
	@{
		\brief DSL traits for function return types.
		\details Some of the these traits allow for NULL pointers to be returned
		from functions, which was something commonly requested for the library.
		When such a trait is used and the runtime value is NULL, Lua's value of
		nil will be pushed to the stack.
	*/

	/** \struct light_return
		\brief Return trait for a light userdata type
		\details
		The type returned from the function is  either a void pointer or a pointer to another
		type. When the function returns, it will push a LUA_TLIGHTUSERDATA to the stack even
		when the pointer is NULL; therefore a NULL pointer using this traits is never converted
		to a Lua nil value. A light userdata is also never owned by Lua and OOLua does not
		store any type information for the it; light_return is a black box which when used
		incorrectly will invoke undefined behaviour.\n
		This is only valid for function return types.
	*/
	template<typename T>struct light_return;

	/** \struct lua_return
		\brief Return trait for a type which will be owned by Lua
		\details
		The type returned from the function is a heap allocated instance whose
		ownership will be controlled by Lua. This is only valid for function
		return types.
	*/
	template<typename T>struct lua_return;

	/** \struct maybe_null
		\brief Return trait for a pointer which at runtime maybe NULL.
		\details
		The type returned from the function is a pointer instance whose
		runtime value maybe NULL. If it is NULL then lua_pushnil will be called
		else the pointer will be pushed as normal. No change of ownership will
		occur for the type. This is only valid for function return types.
		\note To be consistent in naming this should really be called
		maybe_null_return, however I feel this would be too long a name for the
		trait so "return" has been dropped.
	*/
	template<typename T>struct maybe_null;

	/** \struct shared_return
		\brief Converts a raw pointer return type to the supported shared pointer type
		\details
		A shared_return does not define that a function returns a shared_ptr
		instead it informs the proxy to create a new shared object for the returned
		pointer. This trait therefore requires that there is not a reference to the
		pointer already known to the library.
	*/
	template<typename T>struct shared_return;

	/**@}*/

	/** \addtogroup OOLuaStackTraits Stack Traits
	@{
		\brief Public API traits which control a change of ownership
		\details Valid to usage for the \ref OOLUA::INTERNAL "Public API" which interact
		with the Lua stack.
	*/
	/** \struct cpp_acquire_ptr
		\brief Change of ownership to C++
		\details
		Informs the library that C++ will take control of the pointer being used
		and call delete on it when appropriate. This is only valid for public API
		functions which \ref OOLUA::pull from the stack.
	*/
	template<typename T>struct cpp_acquire_ptr;

	/** \struct lua_acquire_ptr
		\brief Change of ownership to Lua
		\details
		Informs the library that Lua will take control of the pointer being used
		and call delete on it when appropriate. This is only valid for public API
		functions which \ref OOLUA::push to the stack.
	*/
	template<typename T>struct lua_acquire_ptr;
	/**@}*/

/**@}*/


	/** \cond INTERNAL*/
	template<typename T>
	class Proxy_class;

	class Table;
	template<int ID>struct Lua_ref;

	namespace INTERNAL
	{
		template<typename T>
		struct Type_enum_defaults
		{
			enum { is_by_value = !LVD::by_reference<typename LVD::remove_all_const<T>::type >::value };
			enum { is_constant =  LVD::is_const<T>::value };
			enum
			{
				is_integral = LVD::is_integral_type< typename LVD::raw_type<T>::raw >::value
					|| /*enum*/(!has_a_proxy_type<typename LVD::raw_type<T>::raw>::value
								&& LVD::can_convert_to_int<typename LVD::raw_type<T>::raw>::value)
			};
		};

		template<typename T, int is_integral>
		struct Pull_type;

		template<typename T>
		struct Pull_type<T, 0>
		{
			typedef T* type;
		};

		template<typename T>
		struct Pull_type<T, 1>
		{
			typedef T type;
		};

		template<typename T, typename Original_Type, int is_integral>struct Pull_type_;

		template<typename Original_Type, typename T>
		struct pull_type_maybe_const
		{
			typedef typename LVD::if_else<
											LVD::is_const<Original_Type>::value
											|| INTERNAL::Type_enum_defaults<Original_Type>::is_by_value
											, T const*
											, T*
										>::type type;
		};

		/*specialisation to prevent Visual Studio warnings, that const applied to a function is ignored*/
		template<typename Original_Type>
		struct pull_type_maybe_const<Original_Type, int (lua_State*)> // NOLINT
		{
			typedef int(*type)(lua_State*); // NOLINT
		};

		/* should rename Pull_maybe_const */
		template<typename T, typename Original_Type>
		struct Pull_type_<T, Original_Type, 0>
		{
			typedef typename pull_type_maybe_const<Original_Type, T>::type type;
		};

		template<typename T, typename Original_Type>
		struct Pull_type_<T, Original_Type, 1>
		{
			typedef T type;
		};

		template<typename T>
		struct is_lua_ref
		{
			enum{value = 0};
		};
		template<int LuaTypeId>
		struct is_lua_ref< OOLUA::Lua_ref<LuaTypeId> >
		{
			enum{value = 1};
		};

		template<typename T>
		struct is_shared_type
		{
			enum {value = 0};
			typedef void underlying_type;
		};

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T, template <typename> class shared_type>
		struct is_shared_type<shared_type<T> >
		{
			//container class does not have a proxy yet the contained class does.
			enum {value = has_a_proxy_type<shared_type<T> >::value == 0
					&& has_a_proxy_type<typename LVD::raw_type<T>::raw>::value == 1};
			typedef T underlying_type;
		};
#endif
		template<typename T>
		struct is_shared_const
		{
			typedef typename LVD::raw_type<T>::type raw;
			typedef is_shared_type<raw> is_shared;

			enum {value = is_shared::value
					&& LVD::is_const<typename is_shared::underlying_type>::value };
		};

		template<typename EnumType>
		struct is_scoped_enum
		{
			typedef typename LVD::raw_type<EnumType>::type raw;
			enum {value = LVD::is_class_type<raw>::value == 0
						&& LVD::can_convert_to_int<raw>::value == 0
						&& LVD::is_integral_type<raw>::value == 0
						&& LVD::is_same<int(lua_State*), raw>::value == 0 //NOLINT(readability/casting)
						? 1 : 0
				};
		};

		template<>
		struct is_scoped_enum<void>
		{
			enum {value = 0};
		};

		template<typename T>
		struct is_false_integral
		{
			typedef typename LVD::raw_type<T>::type raw;
			enum {value = STRING::is_integral_string_class<raw>::value
						|| INTERNAL::is_lua_ref<raw>::value
						|| LVD::is_same<OOLUA::Table, raw>::value
						|| INTERNAL::is_shared_type<raw>::value
						|| INTERNAL::is_scoped_enum<raw>::value
					};
		};
	} // namespace INTERNAL // NOLINT
	/** \endcond */

	template<typename T>
	struct in_p
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T
								, INTERNAL::Type_enum_defaults<type>::is_integral
								|| INTERNAL::is_false_integral<type>::value>::type pull_type;
		enum {in = 1};
		enum {out = 0};
		enum {owner = No_change};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant
							|| INTERNAL::is_shared_const<type>::value };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral
							|| INTERNAL::is_false_integral<type>::value };
	};

	template<typename T>
	struct in_out_p
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type<raw
									, LVD::is_integral_type<raw>::value
									|| INTERNAL::is_false_integral<type>::value>::type pull_type;
		enum { in = 1};
		enum { out = 1};
		enum { owner = No_change};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral
								|| INTERNAL::is_false_integral<type>::value };
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
	};


	template<>
	struct out_p<void>;

	template<typename T>
	struct out_p
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef raw pull_type;
		enum { in = 0};
		enum { out = 1};
		enum { owner = INTERNAL::Type_enum_defaults<raw>::is_integral
						|| INTERNAL::is_false_integral<type>::value ? No_change : Lua};
		enum { is_by_value = 1};//yes OOLua creates on the stack
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral
							|| INTERNAL::is_false_integral<type>::value };
		typedef char type_has_to_be_by_reference [INTERNAL::Type_enum_defaults<type>::is_by_value ? -1 : 1 ];
	};


	//cpp takes ownership
	template<typename T>
	struct cpp_in_p
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type<raw, LVD::is_integral_type<raw>::value >::type pull_type;
		enum { in = 1};
		enum { out = 0};
		enum { owner = Cpp};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral  };
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_integral [is_integral ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type [	LVD::is_same<raw&, type>::value ? -1 : 1];
		typedef char type_can_not_be_just_a_reference_to_const_type [	LVD::is_same<raw const&, type>::value ? -1 : 1];
	};

	template<typename T>
	struct light_p
	{
		typedef T type;
		typedef void* raw;
		typedef void* pull_type;
		enum { in = 1 };
		enum { out = 0 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = 0 };
		enum { is_integral = 1 };
	};

	template<typename T>
	struct ref_to_const_ptr
	{
		enum{value = 0};
	};
	template<typename T>
	struct ref_to_const_ptr<T*const&>
	{
		enum{value = 1};
	};
	template<typename T>
	struct ref_to_ptr_const
	{
		enum{value = 0};
	};
	template<typename T>
	struct ref_to_ptr_const<T const*&>
	{
		enum{value = 1};
	};

	template<typename T>
	struct lua_out_p
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T, LVD::is_integral_type<raw>::value >::type pull_type;
		enum { in = 0};
		enum { out = 1};
		enum { owner = Lua};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral  };
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_integral [is_integral ? -1 : 1 ];
		typedef char must_be_assignable [ (is_constant && !ref_to_ptr_const<type>::value)
										 || (ref_to_const_ptr<type>::value)
											? -1 : 1];
		typedef char type_can_not_be_just_a_reference_to_type [	LVD::is_same<raw&, type>::value ? -1 : 1];
		typedef char type_can_not_be_just_a_pointer_to_type [LVD::is_same<raw*, type>::value ? -1 : 1];
	};

	template<typename T>
	struct lua_return
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T, LVD::is_integral_type<raw>::value >::type pull_type;
		enum { in = 0};
		enum { out = 1};
		enum { owner = Lua};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral  };
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_integral [is_integral ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type [	LVD::is_same<raw&, type>::value ? -1 : 1];
		typedef char type_can_not_be_just_a_const_reference_to_type [ LVD::is_same<raw const&, type>::value ? -1 : 1];
	};


	template<typename T>
	struct light_return
	{
		typedef T type;
		typedef void* raw;
		typedef void* pull_type;
		enum { in = 0 };
		enum { out = 1 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = 0 };
		enum { is_integral = 1 };
	};

	template<typename T>
	struct shared_return
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef void pull_type;//It is a return trait, therefore we are not interested in the pull type
		enum { in = 0 };
		enum { out = 1 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = 1 };
		typedef char type_can_not_be_integral [INTERNAL::Type_enum_defaults<type>::is_integral ? -1 : 1 ];
		typedef char type_has_to_be_by_reference [INTERNAL::Type_enum_defaults<type>::is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type [LVD::is_same<raw&, type>::value ? -1 : 1];
		typedef char type_can_not_be_just_a_reference_const_to_type [LVD::is_same<raw const&, type>::value ? -1 : 1];
		typedef char type_has_to_have_a_proxy[ INTERNAL::has_a_proxy_type<raw>::value ? 1 : -1];
	};

	template<typename T>
	struct maybe_null
	{
		typedef INTERNAL::function_return<T> return_trait;
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T
												, LVD::is_integral_type<raw>::value
												|| INTERNAL::is_shared_type<type>::value
											>::type pull_type;
		enum { in = 0};
		enum { out = 1};
		enum { owner = No_change};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant
										|| INTERNAL::is_shared_const<type>::value };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral
										|| INTERNAL::is_shared_type<type>::value };
		typedef char type_can_not_be_normal_integral [INTERNAL::Type_enum_defaults<type>::is_integral ? -1 : 1 ];
		typedef char type_has_to_be_by_reference_if_not_shared [!INTERNAL::is_shared_type<type>::value && is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type_if_not_shared [!INTERNAL::is_shared_type<type>::value && LVD::is_same<raw&, type>::value ? -1 : 1];
		typedef char type_can_not_be_just_a_const_reference_to_type_if_not_shared [!INTERNAL::is_shared_type<type>::value && LVD::is_same<raw const&, type>::value ? -1 : 1];
		/*Reference to pointer:
		this could be valid in some situations, until such a time as it is required
		or requested disable it*/
		typedef char type_can_not_be_a_reference_to_ptr [ LVD::is_same<raw *&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr [ LVD::is_same<raw *const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr_const [ LVD::is_same<raw const*const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_ptr_const [ LVD::is_same<raw const*&, type>::value ? -1 : 1];
	};

	template<typename T>
	struct maybe_null<lua_return<T> >
	{
		typedef lua_return<T> return_trait;
		typedef typename return_trait::type type;
		typedef typename return_trait::raw raw;
		typedef typename return_trait::pull_type pull_type;
		enum { in = return_trait::in};
		enum { out = return_trait::out};
		enum { owner = return_trait::owner};
		enum { is_by_value = return_trait::is_by_value  };
		enum { is_constant = return_trait::is_constant };
		enum { is_integral = return_trait::is_integral };
		/*Reference to pointer:
		this could be valid in some situations, until such a time as it is required
		or requested disable it*/
		typedef char type_can_not_be_a_reference_to_ptr [ LVD::is_same<raw *&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr [ LVD::is_same<raw *const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr_const [ LVD::is_same<raw const*const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_ptr_const [ LVD::is_same<raw const*&, type>::value ? -1 : 1];
	};

	template<typename T>
	struct maybe_null<shared_return<T> >
	{
		typedef shared_return<T> return_trait;
		typedef typename return_trait::type type;
		typedef typename return_trait::raw raw;
		typedef typename return_trait::pull_type pull_type;
		enum { in = return_trait::in};
		enum { out = return_trait::out};
		enum { owner = return_trait::owner};
		enum { is_by_value = return_trait::is_by_value  };
		enum { is_constant = return_trait::is_constant };
		enum { is_integral = return_trait::is_integral };
		/*Reference to pointer:
		this could be valid in some situations, until such a time as it is required
		or requested disable it*/
		typedef char type_can_not_be_a_reference_to_ptr [ LVD::is_same<raw *&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr [ LVD::is_same<raw *const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_const_ptr_const [ LVD::is_same<raw const*const&, type>::value ? -1 : 1];
		typedef char type_can_not_be_a_reference_to_ptr_const [ LVD::is_same<raw const*&, type>::value ? -1 : 1];
	};

	template<typename T>
	struct cpp_acquire_ptr
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T, LVD::is_integral_type<raw>::value>::type pull_type;
		enum { in = 1 };
		enum { out = 0 };
		enum { owner = Cpp };
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral  };

		cpp_acquire_ptr():m_ptr(0){}

		raw* m_ptr;
		typedef char type_can_not_be_integral [is_integral ? -1 : 1 ];
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type [	LVD::is_same<raw&, type>::value ? -1 : 1];
	};


	template<typename T>
	struct lua_acquire_ptr
	{
		typedef T type;
		typedef typename LVD::raw_type<T>::type raw;
		typedef typename INTERNAL::Pull_type_<raw, T, LVD::is_integral_type<raw>::value >::type pull_type;
		enum { in = 0};
		enum { out = 1};
		enum { owner = Lua};
		enum { is_by_value = INTERNAL::Type_enum_defaults<type>::is_by_value  };
		enum { is_constant = INTERNAL::Type_enum_defaults<type>::is_constant  };
		enum { is_integral = INTERNAL::Type_enum_defaults<type>::is_integral  };

		lua_acquire_ptr(pull_type ptr):m_ptr(ptr){}
		lua_acquire_ptr():m_ptr(0){}
		pull_type m_ptr;
		typedef char type_can_not_be_integral [is_integral ? -1 : 1 ];
		typedef char type_has_to_be_by_reference [is_by_value ? -1 : 1 ];
		typedef char type_can_not_be_just_a_reference_to_type [	LVD::is_same<raw&, type>::value ? -1 : 1];
	};

	/** \cond INTERNAL*/
	namespace INTERNAL
	{

		///////////////////////////////////////////////////////////////////////////////
		///  @struct lua_return_count
		///  Adds together the out values of the traits in the typelist
		///  which is an enum in the type
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>struct lua_return_count;

		template <>
		struct lua_return_count<TYPE::Null_type>
		{
			enum { out = 0 };
		};

		template<typename T, typename T1>
		struct lua_return_count< Type_node<T, T1> >
		{
			enum { out = T::out + lua_return_count<T1>::out };
		};

		///////////////////////////////////////////////////////////////////////////////
		///  @struct has_param_traits
		///  Checks if the type is a trait type or not.
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>struct has_param_traits;

		template<typename T>
		struct has_param_traits
		{
			enum {value = 0};
		};

		template<typename T>
		struct has_param_traits< in_p<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_param_traits< out_p<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_param_traits< in_out_p<T> >
		{
			enum {value = 1};
		};
		template<typename T>
		struct has_param_traits< lua_out_p<T> >
		{
			enum {value = 1};
		};
		template<typename T>
		struct has_param_traits< cpp_in_p<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_param_traits< light_p<T> >
		{
			enum {value = 1};
		};

		///////////////////////////////////////////////////////////////////////////////
		///  @struct param_type_typedef
		///  Typedefs the raw underlying type weather it is already a raw type or
		///  a type wrapped in a trait.
		///////////////////////////////////////////////////////////////////////////////
		template<typename T, bool True>
		struct param_type_typedef
		{
			typedef T traits;
		};

		template<typename T>
		struct param_type_typedef<T, false>
		{
			typedef in_p<T> traits;
		};

		///////////////////////////////////////////////////////////////////////////////
		///  @struct param_type
		///  Uses param_type_typedef and has_param_traits to define the type and its
		///  in_p in_out_p or out_p traits.
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>
		struct param_type
		{
			typedef typename param_type_typedef<T, has_param_traits<T>::value>::traits traits;
			typedef typename traits::type  type;
			typedef typename traits::pull_type pull_type;
			typedef typename traits::raw raw;

			enum { in = traits::in };
			enum { out = traits::out };
			enum { owner = traits::owner };
			enum { is_by_value = traits::is_by_value };
			enum { is_constant = traits::is_constant };
			enum { is_integral = traits::is_integral };
		};

		/**
			\brief Function return trait
			\details Default traits for function return types when none are provied
		*/
		template<typename T>
		struct function_return
		{
			typedef T type;//real type
			typedef typename LVD::raw_type<T>::type raw;//all modifiers removed
			typedef typename Pull_type<raw
								, LVD::is_integral_type<raw>::value
								|| INTERNAL::is_false_integral<type>::value >::type pull_type;
			enum { in = 0};
			enum { out = 1};
			enum { owner = No_change};
			enum { is_by_value = Type_enum_defaults<type>::is_by_value  };
			enum { is_constant = Type_enum_defaults<type>::is_constant  };
			enum { is_integral = Type_enum_defaults<type>::is_integral
									|| INTERNAL::is_false_integral<type>::value  };
		};

		template<>
		struct function_return<void>
		{
			typedef void type;
			typedef void pull_type;
			typedef void raw;
			enum { in = 0};
			enum { out = 0};
			enum { owner = No_change};
			enum { is_by_value = 1 };
			enum { is_constant = 0 };
			enum { is_integral = 1 };
		};

		template<typename T, bool True>
		struct return_type_typedef
		{
			typedef T traits;
		};

		//uses default traits
		template<typename T>
		struct return_type_typedef<T, false>
		{
			typedef function_return<T> traits;
		};


		template<typename T>
		struct has_return_traits
		{
			enum{value = 0};
		};

		template<typename T>
		struct has_return_traits< lua_return<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_return_traits< light_return<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_return_traits< maybe_null<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct has_return_traits< shared_return<T> >
		{
			enum {value = 1};
		};

		template<typename T>
		struct return_type_traits
		{
			typedef typename return_type_typedef<T, has_return_traits<T>::value>::traits traits;
			typedef typename traits::type  type;
			typedef typename traits::pull_type pull_type;
			typedef typename traits::raw raw;

			enum { in = traits::in };
			enum { out = traits::out };
			enum { owner = traits::owner };
			enum { is_by_value = traits::is_by_value  };
			enum { is_constant = traits::is_constant  };
			enum { is_integral = traits::is_integral  };
		};

	} // namespace INTERNAL // NOLINT
	/** \endcond */

	///////////////////////////////////////////////////////////////////////////////
	///  Specialisation for the calling lua_State
	///////////////////////////////////////////////////////////////////////////////

	//so this must be a coroutine on the stack
	template struct in_p<lua_State*>;//disable it

	struct calling_lua_state {};

	template<>
	struct in_p<calling_lua_state>
	{
		typedef lua_State* type;
		typedef lua_State* raw;
		typedef lua_State* pull_type;
		enum {in = 1};
		enum {out = 0};
		enum {owner = No_change};
		enum { is_by_value = 0 };
		enum { is_constant = 0 };
		enum { is_integral = 1 };
	};

	///////////////////////////////////////////////////////////////////////////////
	///  Specialisation for C style strings
	///////////////////////////////////////////////////////////////////////////////
	template<>
	struct in_p<char*>
	{
		typedef char* type;
		typedef char* raw;//we are an integral types but very different from the char type
		typedef char const* pull_type;//we pull as the correct type, as cast will occur
		enum { in = 1 };
		enum { out = 0 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = 0 };
		enum { is_integral = 1 };
	};

	template<>
	struct in_p<char*&>;//disabled

	template<>
	struct in_p<char const*>
	{
		typedef char const* type;
		typedef char* raw;//integral yet very different to char
		typedef char const* pull_type;
		enum { in = 1 };
		enum { out = 0 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = 1 };
		enum { is_integral = 1 };
	};

	template<>
	struct in_p<char const*&>
	{
		typedef char const*& type;
		typedef char* raw;//integral yet very different to char
		typedef char const* pull_type;
		enum { in = 1 };
		enum { out = 0 };
		enum { owner = No_change };
		enum { is_by_value = 0 };
		enum { is_constant = 1 };
		enum { is_integral = 1 };
	};

} // namespace OOLUA

#endif //OOLUA_TRAITS_H_
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

#ifndef OOLUA_CHAR_ARRAYS_H_
#	define OOLUA_CHAR_ARRAYS_H_

/** \cond INTERNAL*/
/**
	\file char_arrays.h
	\brief This file is to do away with magic string literals whilst also not
	paying the cost of a strlen
*/

namespace OOLUA
{
	namespace INTERNAL
	{
		static const char change_mt_to_none_const_field[] = "__change_mt_to_none_const";
		static const char set_owner_str[] = "set_owner";
		static const char lua_owns_str[] = "Lua_owns";
		static const char cpp_owns_str[] = "Cpp_owns";
		static const char weak_lookup_name [] = "__weak_lookup";
		static const char collision_mt_lookup_name [] = "__weak_collision_mt_lookup";
		static const char new_str [] = "new";
		static const char oolua_str [] = "OOLua";
		static const char lua_new_table [] = "new_table";
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA // NOLINT

#define OOLUA_PUSH_CARRAY(lua, carray) lua_pushlstring(lua, carray, sizeof(carray)-1)

/** \endcond */
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

/**
	\file proxy_userdata.h
	\brief Contains the internal userdata type used by OOLua to represent C++ class types,
	also contains inlined functions for checking and setting flags in the userdata.
*/
#ifndef OOLUA_PROXY_USERDATA_H_
#	define OOLUA_PROXY_USERDATA_H_


#if OOLUA_USE_SHARED_PTR == 1
#	include OOLUA_SHARED_HEADER
#endif

struct lua_State;
namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		struct Lua_ud;
		typedef void (*oolua_function_check_base)(INTERNAL::Lua_ud* __restrict, INTERNAL::Lua_ud const* __restrict);
		typedef void (*oolua_type_check_function)(lua_State * vm);
		typedef void (*oolua_release_shared_ptr)(INTERNAL::Lua_ud*);
		/**
			\brief The internal type which is used by the library to represent C++ classes.
		*/
		struct Lua_ud
		{
#if OOLUA_USE_SHARED_PTR == 1
			union
			{
				void* void_class_ptr;
				char shared_object[sizeof(OOLUA_SHARED_TYPE<int>)];
			};
#else
			void* void_class_ptr;
#endif
			oolua_function_check_base base_checker;
			oolua_type_check_function type_check;
#if OOLUA_USE_SHARED_PTR == 1
			oolua_release_shared_ptr shared_ptr_release;
#endif
			LVD::uint32 flags;
		};

#if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 1 && OOLUA_USERDATA_OPTIMISATION == 1
	/*lowest nibble is reserved for flags*/
#	define OOLUA_MAGIC_COOKIE	0xfC105Ef0
#	define OOLUA_CHECK_COOKIE(flags)(((flags) & 0xfffffff0) == OOLUA_MAGIC_COOKIE)
#	define OOLUA_SET_COOKIE(flags)	( (flags) = (OOLUA_MAGIC_COOKIE | ((flags) & 0xf)) )
#endif

		void userdata_const_value(Lua_ud* ud, bool value);
		bool userdata_is_constant(Lua_ud const* ud);
		bool userdata_is_to_be_gced(Lua_ud const * ud);
		void userdata_gc_value(Lua_ud* ud, bool value);
		void userdata_shared_ptr(Lua_ud* ud);
		bool userdata_is_shared_ptr(Lua_ud* ud);

		enum UD_FLAGS {CONST_FLAG = 0x01, GC_FLAG = 0x02, SHARED_FLAG = 0x4, COLLISION_FLAG = 0x08};

		inline void userdata_const_value(Lua_ud* ud, bool value)
		{
			if(value)ud->flags |= CONST_FLAG;
			else ud->flags &= (~CONST_FLAG);
		}
		inline bool userdata_is_constant(Lua_ud const* ud)
		{
			return (ud->flags & CONST_FLAG) != 0;
		}
		inline bool userdata_is_to_be_gced(Lua_ud const* ud)
		{
			return (ud->flags & GC_FLAG ) !=0;
		}
		inline void userdata_gc_value(Lua_ud* ud, bool value)
		{
			if(value) ud->flags |= GC_FLAG;
			else ud->flags &= (~GC_FLAG);
		}
		inline void userdata_ptr_collision(Lua_ud* ud)
		{
			ud->flags |= COLLISION_FLAG;
		}
		inline bool userdata_is_ptr_collision(Lua_ud* ud)
		{
			return (ud->flags & COLLISION_FLAG) != 0;
		}
		inline void userdata_shared_ptr(Lua_ud* ud)
		{
			ud->flags |= SHARED_FLAG;
		}

		inline bool userdata_is_shared_ptr(Lua_ud* ud)
		{
			return (ud->flags & SHARED_FLAG) != 0;
		}
	} // namespace INTERNAL //NOLINT
	/**\endcond */

} // namespace OOLUA

#endif //OOLUA_PROXY_USERDATA_H_
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
	\file proxy_class.h
	\brief Defines \ref OOLUA::Proxy_class, it's bases in the hierarchical tree and internal details.
	\details Defines the class, its bases in the hierarchical tree. The classes name
	an array used to hold the functions its make available to the script and
	C++ special member functions
*/

#ifndef CPP_PROXY_CLASS
#	define CPP_PROXY_CLASS



namespace OOLUA
{
	/** \class OOLUA::Proxy_class
		\brief A template wrapper for class objects of type T used by the script binding.
		\tparam T Type that is being proxied
		\see OOLuaDSL for the macros which are used to define a proxy class.
	 */
	template<typename T>class Proxy_class;

	/** \cond INTERNAL */

	namespace INTERNAL
	{
		template<typename TL, typename T>
		struct AddBase;

		template<typename TL, typename T>
		struct AddBase
		{
			typedef typename TYPELIST::Append<TL, T>::Result Result;
		};

		template<typename TL>
		struct AddBase<TL, TYPE::Null_type>
		{
			typedef TL Result;
		};

		template<int Index, typename AddToTL, typename BasesTL, typename BaseType>
		struct ForEachBaseAddAllBases
		{
			typedef typename AddBase<AddToTL, typename OOLUA::Proxy_class<BaseType>::AllBases>::Result InternalResult;
			typedef typename ForEachBaseAddAllBases<
								Index+1
								, InternalResult//adding to this type list
								, BasesTL//each of the entries in this types list
									, typename TYPELIST::At_default<BasesTL
									, Index+1
									, TYPE::Null_type>::Result//next type in the base type list
				>::Result Result;
		};

		template<int Index, typename AddToTL, typename BasesTL>
		struct ForEachBaseAddAllBases<Index, AddToTL, BasesTL, TYPE::Null_type>
		{
			typedef AddToTL Result;
		};

		template<typename T>
		struct FindAllBases
		{
			typedef typename ForEachBaseAddAllBases<
								0
								, typename OOLUA::Proxy_class<T>::Bases//adding to this type list
								, typename OOLUA::Proxy_class<T>::Bases//each of the entry in this types list
									, typename TYPELIST::At_default<typename OOLUA::Proxy_class<T>::Bases
									, 0
									, TYPE::Null_type>::Result//starting with this type
				>::Result Result;
		};

		template<typename AddTo, typename BaseType, typename NullIfRoot>
		struct AddIfRoot
		{
			typedef AddTo Result;
		};

		template<typename AddTo, typename BaseType>
		struct AddIfRoot<AddTo, BaseType, TYPE::Null_type>
		{
			typedef typename AddBase<AddTo, BaseType>::Result Result;
		};

		template<int Index, typename AddTo, typename AllTypesBases, typename T>
		struct ForEachOfAllBasesAddRoots
		{
			typedef typename AddIfRoot<AddTo, T, typename OOLUA::Proxy_class<T>::Bases>::Result InternalResult;
			typedef typename ForEachOfAllBasesAddRoots<
								Index+1//look at this index
								, InternalResult//add to this type list
								, AllTypesBases//looking at each entry in this list
									, typename TYPELIST::At_default<AllTypesBases
									, Index+1
									, TYPE::Null_type>::Result//next entry to check
				>::Result Result;
		};

		template<int Index, typename AddTo, typename AllTypesBases>
		struct ForEachOfAllBasesAddRoots<Index, AddTo, AllTypesBases, TYPE::Null_type>
		{
			typedef AddTo Result;
		};

		template<typename T>
		struct FindRootBases
		{
			typedef Type_list<>::type DummyTL;
			typedef typename ForEachOfAllBasesAddRoots<
								0//starting at the beginning
								, DummyTL//add to this type list
								, typename OOLUA::Proxy_class<T>::AllBases//looking at each entry in this list
									, typename TYPELIST::At_default<typename OOLUA::Proxy_class<T>::AllBases
									, 0
									, TYPE::Null_type>::Result//starting with this entry
				>::Result Result;
		};

		/////////////////////////////////////////////////////////////////////////////////
		/////  @struct OOLUA::Set_this_ptr
		/////  For each base set the this pointer
		/////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename TypeList, int TypeIndex, typename BaseType>
		struct Set_this_ptr
		{
			void operator()(T* proxy_this, typename T::class_* this_)
			{
				//base is valid add the this pointer to the base
				OOLUA::Proxy_class<BaseType>* base(proxy_this);
				//and set the m_this pointer
				base->m_this = this_;
				//move to the next class in the base list
				Set_this_ptr<
						T
						, TypeList
						, TypeIndex + 1, typename TYPELIST::At_default< TypeList, TypeIndex + 1, TYPE::Null_type >::Result
					> nextBase;
				nextBase(proxy_this, this_);
			}
		};
		template<typename T, typename TL, int TypeIndex>
		struct  Set_this_ptr<T, TL, TypeIndex, TYPE::Null_type>
		{
			//no valid base class at the index
			void operator()(T* /*proxy_this*/, typename T::class_* /*this_*/)const{}//no op
		};

		template<typename T>struct Proxy_type;

		template<typename T>
		struct Proxy_type<OOLUA::Proxy_class<T> >
		{
			typedef T Type;
		};
	} // namespace INTERNAL // NOLINT
	/** \endcond*/
} // namespace OOLUA

/*Doxygen does not seem to like crossing namespaces*/
/** \cond INTERNAL */

///  \def OOLUA_FORWARD_DECLARE
///  forward declare in the OOLUA namespace
///	 @note
///	 This must be called at the global namespace and not be nested.
#define OOLUA_FORWARD_DECLARE(name) \
namespace OOLUA \
{ \
	class OOLUA::Proxy_class<name>; \
} // namespace OOLUA

namespace OOLUA
{
	template<typename NoneProxyType>
	class Proxy_class
	{
	public:
		typedef NoneProxyType OoluaNoneProxy;
	};
} // namespace OOLUA

///	 \def OOLUA_CLASS
///	Class which may have base classes
#define OOLUA_CLASS(name___) \
	namespace OOLUA \
	{ \
		template<> \
		class Proxy_class<name___>

///  \def  OOLUA_BASIC
///  C++ special member functions and lua binding details
#define OOLUA_BASIC \
		{ \
		public: \
			typedef INTERNAL::Proxy_type<Proxy_class>::Type class_; \
			typedef Proxy_class<class_> this_type; \
			typedef int (Proxy_class::*mfp)(lua_State *  const  ); \
			typedef int (Proxy_class::*mfp_const)(lua_State *  const  )const; \
			struct Reg_type{ const char *name; mfp mfunc; }; \
			struct Reg_type_const{ const char *name; mfp_const mfunc; }; \
			static char const class_name[]; \
			static char const class_name_const[]; \
			static Reg_type class_methods[]; \
			static Reg_type_const class_methods_const[]; \
			class_ * m_this; \
			Proxy_class():m_this(0){} \
			Proxy_class(class_* p):m_this(p) \
			{ \
				set_this_ptr(); \
			} \
			Proxy_class& operator = (Proxy_class const &); \
			Proxy_class(Proxy_class const &); \
			virtual ~Proxy_class(){} \
		private: \
			void set_this_ptr() \
			{ \
				INTERNAL::Set_this_ptr< \
							this_type \
							, AllBases \
							, 0 \
							, TYPELIST::At_default< AllBases, 0, TYPE::Null_type >::Result \
					> ptr; \
				ptr(this, m_this); \
			} \
		public:
// NOLINT

/** \endcond*/

/** \addtogroup OOLuaDSL
 @{
		\def OOLUA_PROXY_END
		\hideinitializer
		\brief Ends the generation of the proxy class
	 */
#		define OOLUA_PROXY_END };} /*end the class and namespace*/ /*NOLINT*/
/**@}*/

/** \cond INTERNAL */

#define OOLUA_ALLBASES \
	typedef INTERNAL::FindAllBases<class_>::Result AllBases;

///  \def OOLUA_NO_BASES
///  define the class to have no base classes
#define OOLUA_NO_BASES \
	typedef TYPE::Null_type Bases;\
	OOLUA_ALLBASES

///  \def OOLUA_BASES_START
///  define the class to have numerical amount (equal to NUM) of base classes
#define OOLUA_BASES_START \
	typedef Type_list<

///  \def OOLUA_BASES_END
///  end of base class declaring
#define OOLUA_BASES_END \
	>::type Bases; \
	OOLUA_ALLBASES


///	\def  OOLUA_CLASS_NO_BASES
///	uses OOLUA_CLASS, OOLUA_BASIC and OOLUA_NO_BASES
/// Defines a Proxy_class which has no base which you want to
/// inform the script binding about.
/// \note The real class may have base classes.
#define OOLUA_CLASS_NO_BASES(name___) \
	OOLUA_CLASS(name___) \
	OOLUA_BASIC \
	OOLUA_NO_BASES

///	\def  OOLUA_TAGS_START
///	Starts the tags list
///	\see oolua_tags.h
#define OOLUA_TAGS_START \
	typedef Type_list<

///	\def  OOLUA_TAGS_END
///	Closes the tags list
///	\see oolua_tags.h
#define OOLUA_TAGS_END \
	>::type Tags; typedef class_ tag_block_check;

#define OOLUA_ENUMS_START \
static void oolua_enums(lua_State * vm) \
{ \
	/*Table meth(vm, Proxy_class<class_>::class_name);*/ \
	/*meth.push_on_stack(vm);*/ \
	lua_getglobal(vm, Proxy_class<class_>::class_name); \
	int const top = lua_gettop(vm);

#define OOLUA_ENUMS_END \
	lua_pop(vm, 1); \
}
/** \endcond*/

/** \addtogroup OOLuaDSL
@{
		\def OOLUA_SCOPED_ENUM
		\hideinitializer
		\brief Creates a entry into a \ref OOLUA_ENUMS block for a C++11 scoped enum
		\details OOLUA_SCOPED_ENUM(EnumName, Entry)
		\param Name The class enumeration name which will be used to access it from Lua
		\param Entry The class enumeration scoped qualified name (minus the class type)
		\see \ref OOLUA_ENUM
	*/
#	define OOLUA_SCOPED_ENUM(Name, Entry) \
		lua_pushliteral(vm, #Name); \
		lua_pushinteger(vm, (lua_Integer)class_::Entry); \
		lua_settable(vm, top);

	/**
		\def OOLUA_ENUM
		\hideinitializer
		\brief Creates a entry into a \ref OOLUA_ENUMS block
		\details OOLUA_ENUM(EnumName)
		\param EnumName The class enumeration name
	*/
#	define OOLUA_ENUM(EnumName) \
		OOLUA_SCOPED_ENUM(EnumName, EnumName)

	/**	\def OOLUA_ENUMS
		\hideinitializer
		\brief Creates a block into which enumerators can be defined with \ref OOLUA_ENUM
		or \ref OOLUA_SCOPED_ENUM
		\details OOLUA_ENUMS(EnumEntriesList)
		\param EnumEntriesList List which contains \ref OOLUA_ENUM and/or \ref OOLUA_SCOPED_ENUM entries.
		<p>
		\note
		An OOLUA_ENUMS block without any \ref OOLUA_ENUM or \ref OOLUA_SCOPED_ENUM entries is invalid.
	*/
#	define OOLUA_ENUMS(EnumEntriesList) OOLUA_ENUMS_START EnumEntriesList OOLUA_ENUMS_END

/** @}*/

#endif //CPP_PROXY_CLASS_H_
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
	@file proxy_base_checker.h
	\brief Checks the hierarchical bases to ensure a cast is defined
	\details Walks a list of bases class defined in a OOLUA::Proxy_class
	to find if a type can be converted to the requested type, if it is valid
	then the procedures will preform the cast.
*/
#ifndef OOLUA_PROXY_BASE_CHECKER_H_
#	define OOLUA_PROXY_BASE_CHECKER_H_


#if OOLUA_USE_SHARED_PTR == 1
#	include OOLUA_SHARED_HEADER
#endif

struct lua_State;

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		/*forward declare*/
		template<typename T>
		void register_class_imp(lua_State* vm);

		/**\addtogroup OOLuaClassTypeChecking
		@{*/
		/**
			\brief Start function which sets up the recursive base checking
			\tparam T The type whose bases will be checked
			\param[in,out] requested_ud The OOLua userdata type wanted
			\param[in] stack_ud The stack userdata type
			\pre requested_ud->void_class_pointer is NULL
			\post If the request type was a base then requested_ud->void_class_pointer is none NULL
			\details
			Starts the recursive iteration checks over the bases of T
			\note
			Neither this function or the recursive functions it calls set
			requested_ud->void_class_pointer to NULL, this happens in in
			OOLUA::INTERNAL::valid_base_ptr_or_null
		*/
		template<typename T>
		void requested_ud_is_a_base(Lua_ud* requested_ud, Lua_ud const* stack_ud);

		/**
			\brief Checks if the ud has the same type as tparam
			\tparam T The type to check the ud against
			\param[in] ud The OOLua userdata instance to check
			\result boolean indicating if the comparison is equal
		*/
		template<typename T>
		bool ud_is_type(Lua_ud const* ud);

		/**
			\struct CastToRequestedProxyType
			\brief Casts the stack type to the requested types
			\tparam ProxyStackType Correct type of the stack userdata before it was cast to void pointer
			\tparam BaseType The requested base type of the stack userdata
			\details Correctly casts the stack type to the requested type, taking into
			consideration class offsets.
		*/
		template<typename ProxyStackType, typename BaseType, int DoWork>
		struct CastToRequestedProxyType;

		/**
			\struct Is_a_base
			\brief Recurrsive base checker.
			\tparam ProxyStackType Correct type of the stack ud before it was cast to a void pointer.
			\tparam Bases Type list of base clases
			\tparam BaseIndex Index into the base class type list
			\tparam BaseType Current index type for the type list
			\details Iterates over the base classes and exits when it has either found the correct
			base type or has exhausted the base class types.

		*/
		template<typename ProxyStackType, typename Bases, int BaseIndex, typename BaseType>
		struct Is_a_base;

		template<typename ProxyStackType, typename BaseType, int DoWork = 1>
		struct CastToRequestedProxyType
		{
#if OOLUA_USE_SHARED_PTR == 1
			/*
				If the type in the stack_ud is a shared pointer you can request a shared pointer
				or a normal pointer from it which will be stored in requested_ud.

				If the type in the stack_ud is not a shared pointer it is undefined to
				request a shared pointer from it.
			*/
			static void cast(INTERNAL::Lua_ud * requested_ud, INTERNAL::Lua_ud const* stack_ud)
			{
				stack_ud->flags & SHARED_FLAG ?
						do_shared_cast(requested_ud, const_cast<Lua_ud*>(stack_ud))
						: do_ptr_cast(requested_ud, stack_ud);
			}

			static void do_ptr_cast(INTERNAL::Lua_ud * requested_ud, INTERNAL::Lua_ud const* stack_ud)
			{
				//cast the class void ptr from the stack to the stacktype
				//then to base type to get correct offset
				requested_ud->void_class_ptr = static_cast<BaseType*>(static_cast<typename ProxyStackType::class_* >(stack_ud->void_class_ptr));
			}

			static void do_shared_cast(INTERNAL::Lua_ud * requested_ud, INTERNAL::Lua_ud * stack_ud)
			{
				//cast the generic shared ptr to the the stacktype shared_ptr
				OOLUA_SHARED_TYPE<typename ProxyStackType::class_>* stack_shared_ptr = reinterpret_cast<OOLUA_SHARED_TYPE<typename ProxyStackType::class_>* >(stack_ud->shared_object);

				//the type wanted is a shared pointer
				if(requested_ud->flags & SHARED_FLAG)
				{
					//worried that this may get optimised away by clang, I recall something like this
					//in an old mailing list thread!
					//construct a base class shared ptr using placement new
					new(requested_ud->shared_object) OOLUA_SHARED_TYPE<BaseType>(*stack_shared_ptr);
				}
				else //the type wanted is a normal pointer
				{
					//cast from stack type to base type and store in requested_ud
					requested_ud->void_class_ptr = static_cast<BaseType*>(stack_shared_ptr->get());
				}
			}
#else
			static void cast(INTERNAL::Lua_ud * requested_ud, INTERNAL::Lua_ud const* stack_ud)
			{
				//cast the class void ptr from the stack to the stacktype
				//then to base type to get correct offset
				requested_ud->void_class_ptr = static_cast<BaseType*>(static_cast<typename ProxyStackType::class_* >(stack_ud->void_class_ptr));
			}
#endif
		};

		template<typename ProxyStackType, typename Bases, int BaseIndex, typename BaseType>
		struct Is_a_base
		{
			void operator()(Lua_ud* __restrict requested_ud, INTERNAL::Lua_ud const* __restrict stack_ud)
			{
				//is this a base
				if( ud_is_type<BaseType>(requested_ud) )
				{
					CastToRequestedProxyType<ProxyStackType, BaseType, 1>::cast(requested_ud, stack_ud);
					return;
				}
				//check the next in the type list
				Is_a_base<
					ProxyStackType
					, Bases
					, BaseIndex + 1
					, typename TYPELIST::At_default< Bases, BaseIndex + 1, TYPE::Null_type >::Result
				> nextIsBase;
				nextIsBase(requested_ud, stack_ud);
			}
		};

		template<typename ProxyStackType, typename Bases, int BaseIndex>
		struct Is_a_base<ProxyStackType, Bases, BaseIndex, TYPE::Null_type>
		{
			void operator()(INTERNAL::Lua_ud* __restrict/*requested_ud*/
							, INTERNAL::Lua_ud const* __restrict/*stack_ud*/)
			{}//noop
		};

		template<typename T>
		inline void requested_ud_is_a_base(Lua_ud* __restrict requested_ud, Lua_ud const* __restrict stack_ud)
		{
			INTERNAL::Is_a_base<OOLUA::Proxy_class<T>
					, typename OOLUA::Proxy_class<T>::AllBases
					, 0
					, typename TYPELIST::At_default< typename OOLUA::Proxy_class<T>::AllBases, 0, TYPE::Null_type >::Result
				> checkBases;
			checkBases(requested_ud, stack_ud);
		}

		template<typename T>
		inline bool ud_is_type(Lua_ud const* ud)
		{
			//some compilers need a hand it also enforces that the typedef in oolua_userdata is correct
			return ud->type_check ==  static_cast<oolua_type_check_function>(&register_class_imp<T>);
		}
		/**@}*/
	} // namespace INTERNAL // NOLINT
	/** \endcond  INTERNAL */
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

/** \cond INTERNAL*/
/**
	@file class_from_stack.h
	\brief Retrieves a typed pointer from a potential userdata on the stack.
	\details Preforms configuration dependent checks in a attempt to return a
	typed pointer from a userdata which resides on the stack.
*/
/** \endcond */

#ifndef OOLUA_CLASS_FROM_STACK_H_
#	define OOLUA_CLASS_FROM_STACK_H_



#if OOLUA_DEBUG_CHECKS == 1
#	include <cassert>
#endif

//forward declare
struct lua_State;

namespace OOLUA
{

	/** \cond INTERNAL*/

	namespace INTERNAL
	{
		/**
			\brief Uses a config dependent check to verify "index" is a library created userdata
			\tparam T Requested type wanted from the stack
			\param[in] vm Lua virtual machine on which to operate
			\param[in] index Stack index at which the potential userdata is located
			\return T* Either a pointer of the requested type or NULL
		*/
		template<typename T>
		T* check_index(lua_State * vm, int index);

		/**
			\brief Uses config dependent checks to verify "index" is a library created userdata
			\details Preforms an extra check that the stack type is not constant, throws a Lua
			error if the type is.
			\tparam T Requested type wanted from the stack
			\param[in] vm Lua virtual machine on which to operate
			\param[in] index
			\return T* Either a pointer of the requested type or NULL
		*/
		template<typename T>
		T* check_index_no_const(lua_State * vm, int index);

		/**
			\brief Uses config dependent checks to verify "index" is a library created userdata
			\param[in] vm Lua virtual machine on which to operate
			\param[in] index Stack index to check
			\param[out] ud If verification is successful then it points to the userdata on the stack
			\return Boolean indicting if verification was successful
		*/
		bool index_is_userdata(lua_State* vm, int index, Lua_ud*& ud);
		/**
			\brief Generates a Lua error that the stack type was constant when a none constant was wanted
			\param[in] vm Lua virtual machine on which to operate
			\param[in] pulling_class_type
 		*/
		void report_error_userdata_is_constant(lua_State* const vm, char const* pulling_class_type);

		/**
			\brief blah
			\tparam T Requested base class wanted from the stack type
			\param[in] stack_ud
			\return T* Either a valid base pointer or NULL
			\pre T is not the same type as the type stack_ud represents
		*/
		template<typename T>
		T* valid_base_ptr_or_null(Lua_ud const* stack_ud);

#if OOLUA_CHECK_EVERY_USERDATA_IS_CREATED_BY_OOLUA == 0
		inline bool index_is_userdata(lua_State* vm, int index, Lua_ud*& ud)
		{
			ud = static_cast<Lua_ud *>(lua_touserdata(vm, index));
			return ud != 0;
		}
#endif

		/**
			\brief Checks the stack top is a valid index before calling check_index
			\param[in] vm Lua virtual machine on which to operate
			\return NULL when top is not a valid stack index else the result of check_index
		*/
		template<typename T>
		inline T* class_from_stack_top(lua_State * vm)
		{
			const int top = lua_gettop(vm);
			return top ? check_index<T>(vm, top) : NULL;
		}

		/**
			\brief Checks that the stack top is a valid index before calling check_index_no_const
			\param[in] vm Lua virtual machine on which to operate
			\return NULL when top is not a valid stack index else the result of check_index_no_const
		*/
		template<typename T>
		inline T* none_const_class_from_stack_top(lua_State * vm)
		{
			const int top = lua_gettop(vm);
			return top ? check_index_no_const<T>(vm, top) : NULL;
		}

		template<typename T>
		T* valid_base_ptr_or_null(Lua_ud const* stack_ud)
		{
#if OOLUA_USE_SHARED_PTR == 1
			Lua_ud requested_ud = {{0}, 0, &register_class_imp<T>, 0, 0};
#else
			Lua_ud requested_ud = {0, 0, &register_class_imp<T>, 0};
#endif
			stack_ud->base_checker(&requested_ud, stack_ud);
			return static_cast<T* >(requested_ud.void_class_ptr);
		}

		template<typename T>
		T* check_index(lua_State *  vm, int index)
		{
			Lua_ud * ud;
			if( !index_is_userdata(vm, index, ud))return 0;
			if( !ud_is_type<T>(ud))
			{
				return valid_base_ptr_or_null<T>(ud);
			}
			return static_cast<T* >(ud->void_class_ptr);
		}
#if OOLUA_USE_SHARED_PTR == 1

		namespace
		{
			template<typename T>
			struct pointer_type
			{
				typedef T* ptr;
				typedef T raw;
				enum {ud_flag = 0};
			};

			template<typename T>
			struct pointer_type<OOLUA_SHARED_TYPE<T> >
			{
				typedef OOLUA_SHARED_TYPE<T> ptr;
				typedef T raw;
				enum {ud_flag = SHARED_FLAG};
				typedef char never_call_with_const_type_always_raw_type[LVD::is_const<T>::value ? -1 : 1];
			};

			template<typename T>
			inline T** ud_member_cast(Lua_ud* ud, T*&)
			{
				return reinterpret_cast<T**>(&ud->void_class_ptr);
			}

			template<typename T, template <typename> class Shared_pointer_class>
			inline Shared_pointer_class<T>* ud_member_cast(Lua_ud* ud, Shared_pointer_class<T>&)
			{
				return reinterpret_cast<Shared_pointer_class<T>*>(ud->shared_object);
			}

			template<typename T>
			inline T* ptr_null(T**) // NOLINT(readability/casting)
			{
				return NULL;
			}

			template<typename T, template <typename> class Shared_pointer_class>
			inline Shared_pointer_class<T> ptr_null(Shared_pointer_class<T>*)
			{
				return Shared_pointer_class<T>();
			}
			template<typename T>
			inline void destroy_ud_ptr(T** /*ud_ptr*/) // NOLINT(readability/casting)
			{}

			template<typename T, template <typename> class Shared_pointer_class>
			inline void destroy_ud_ptr(Shared_pointer_class<T>* ud_ptr)
			{
				ud_ptr->~Shared_pointer_class<T>();
			}
		} // namespace //NOLINT(readability/namespace)

		template<typename T>
		struct stack_checker
		{
			typedef pointer_type<T> type;
			typedef typename type::ptr ptr_type;
			typedef typename type::raw raw_type;

			static ptr_type& valid_base_ptr_or_null(Lua_ud const* stack_ud, ptr_type& ptr )
			{
#if OOLUA_USE_SHARED_PTR == 1
				Lua_ud requested_ud = {{0}, 0, &register_class_imp<raw_type>, 0, type::ud_flag};
#else
				Lua_ud requested_ud = {0, 0, &register_class_imp<raw_type>, 0};
#endif
				stack_ud->base_checker(&requested_ud, stack_ud);

				//this may not be a void class pointer but if found it will have some
				//value other than NULL. C99 TR3 allows this type casting
				if (requested_ud.void_class_ptr)
				{
					ptr_type* result = ud_member_cast(&requested_ud, ptr);
					ptr = *result;
					destroy_ud_ptr(result);
				}
				return ptr;
			}
			static ptr_type check_index(lua_State * vm, int index)
			{
				Lua_ud * ud;
				ptr_type ptr(ptr_null(static_cast<ptr_type*>(NULL)));
				if( !index_is_userdata(vm, index, ud))return ptr;
				if( !ud_is_type<raw_type>(ud))
				{
					return valid_base_ptr_or_null(ud, ptr);
				}
				return *ud_member_cast(ud, ptr);
			}
			static ptr_type check_index_no_const(lua_State * vm, int index)
			{
				Lua_ud * ud;
				ptr_type ptr(ptr_null(static_cast<ptr_type*>(NULL)));
				if( !index_is_userdata(vm, index, ud))return ptr;
				if( userdata_is_constant(ud) )
				{
					report_error_userdata_is_constant(vm, OOLUA::Proxy_class<raw_type>::class_name);
					//does not return
				}
				if( !ud_is_type<raw_type>(ud))
				{
					return valid_base_ptr_or_null(ud, ptr);
				}
				return *ud_member_cast(ud, ptr);
			}
		};

#endif

		template<typename T>
		T* check_index_no_const(lua_State * vm, int index)
		{
			Lua_ud * ud;
			if( !index_is_userdata(vm, index, ud))return 0;
			if( userdata_is_constant(ud) )
			{
				report_error_userdata_is_constant(vm, OOLUA::Proxy_class<T>::class_name);
				//does not return
			}
			if( !ud_is_type<T>(ud))
			{
				return valid_base_ptr_or_null<T>(ud);
			}
			return static_cast<T* >(ud->void_class_ptr);
		}

	} // namespace INTERNAL // NOLINT
	/** \endcond */
} // namespace OOLUA

#endif //OOLUA_CLASS_FROM_STACK_H_
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
	\file oolua_error.h
	\brief Generic header to be included when handling errors.
	\details When the library is compiled with \ref OOLUA_USE_EXCEPTIONS == 1
	it will include the \ref oolua_exception.h header and provide dummy
	implementations for OOLUA::get_last_error and OOLUA::reset_error_value.
	When compiled with \ref OOLUA_STORE_LAST_ERROR == 1 it provides implementations
	for \ref OOLUA::get_last_error and \ref OOLUA::reset_error_value.
	\see \ref OOLuaConfig
*/
#ifndef OOLUA_ERROR_H_
#	define OOLUA_ERROR_H_


#if OOLUA_USE_EXCEPTIONS == 1
#endif

#if OOLUA_DEBUG_CHECKS == 1
#   include <cassert>
#endif

#	include <string>

struct lua_State;
namespace OOLUA
{
	/** \addtogroup OOLuaErrorReporting
	@{*/

	/** \brief Reset the error state such that a call to OOLUA::get_last_error
		will return an empty string.
		\see OOLuaErrorReporting
		\note This function is a nop when \ref OOLUA_STORE_LAST_ERROR is not enabled
	*/
	void reset_error_value(lua_State* vm);
	/** \brief Returns the last stored error
		\return empty string if there is not an error else the error message
		\see OOLuaErrorReporting
		\note This function is a nop when \ref OOLUA_STORE_LAST_ERROR is not enabled
	*/
	std::string get_last_error(lua_State* vm);
	/**@}*/

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		void set_error_from_top_of_stack_and_pop_the_error(lua_State* vm);
	} // namespace INTERNAL
	/** \endcond */

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

/**
	\file oolua_exception.h
	\brief Declares the exceptions which are used by OOLua when \ref OOLUA_USE_EXCEPTIONS
	is set to one.
	\see \ref OOLuaConfig
	\see \ref OOLuaExceptionClasses
*/
#ifndef OOLUA_EXCEPTION_H_
#	define OOLUA_EXCEPTION_H_



/** \addtogroup OOLuaErrorReporting
@{*/
	/** \addtogroup OOLuaExceptionClasses Exception classes
		@{
	*/
	/** \struct std::exception */

	/** \struct OOLUA::Exception
		\brief Base class for OOLua exceptions
		\extends std::exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Syntax_error
		\brief Reports LUA_ERRSYNTAX
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Runtime_error
		\brief Reports LUA_ERRRUN
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Memory_error
		\brief Reports LUA_ERRMEM
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::File_error
		\brief Reports LUA_ERRFILE
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
	 */

	/** \struct OOLUA::Type_error
		\brief Reports that a type pulled from the stack was not the type that was asked for
		\extends OOLUA::Exception
		\see OOLuaErrorReporting
		\note Implicit casts such as a derived class to a base class are not type errors
	 */
		/**@}*/

/**@}*/

#	if OOLUA_USE_EXCEPTIONS == 1

#	include <exception>
#	include <cstddef>

	struct lua_State;

	namespace OOLUA
	{
		namespace ERROR
		{
			struct PopTheStack{};
			enum exception_buffer {size = 512};
		} // namespace ERROR

		struct Exception : std::exception
		{
			Exception(lua_State* vm);
			Exception(lua_State* vm, ERROR::PopTheStack*);
			Exception(char const* msg);
			Exception(Exception const& rhs);
			Exception& operator = (Exception const& rhs) throw();
			char const* what() const throw();

			size_t m_len;
			char m_buffer[ERROR::size];
		};

		struct Syntax_error : Exception
		{
			Syntax_error(lua_State* vm, ERROR::PopTheStack* specialisation);
		};

		struct Runtime_error : Exception
		{
			Runtime_error(lua_State* vm, ERROR::PopTheStack* specialisation);
			Runtime_error(char const* msg);
		};

		struct Memory_error : Exception // LCOV_EXCL_LINE
		{
			Memory_error(lua_State* vm, ERROR::PopTheStack* specialisation);
		};

		struct File_error : Exception
		{
			File_error(lua_State* vm, ERROR::PopTheStack* specialisation);
		};

		struct Type_error : Exception
		{
			Type_error(lua_State* vm, ERROR::PopTheStack* specialisation);
		};

	} // namespace OOLUA // NOLINT

#	endif

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
/**
	\file oolua_boilerplate.h
	\date Thu Apr 10 18:41:11 2014
	\details
	Configurable values as set when generating this file
	\li constructor_params 5 - Maximum amount of parameters for a constructor of a proxied type	(Default 5)
	\li lua_params 10 - Maximum amount of parameters for a call to a Lua function	(Default 10)
	\li cpp_params 8 - Maximum number of parameters a C++ function can have	(Default 8)
	\note Warning this file was generated, edits to the file will not persist if it is regenerated.
*/

#ifndef OOLUA_BOILERPLATE_H_
#	define OOLUA_BOILERPLATE_H_
/** \cond INTERNAL */

#if defined __GNUC__ && defined __STRICT_ANSI__
/*shhhh about va args and c99*/
#	pragma GCC system_header
#endif

/*
 Functions which are proxied when parameters have traits allow for a direction
 for the type such that it needs pushing back to the lua stack
 param return macros
*/
#define OOLUA_BACK_INTERNAL_NUM(NUM) \
MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
	if( P ## NUM ## _::out ) \
		OOLUA::INTERNAL::Proxy_stack_helper<P ## NUM ##_::traits, P ## NUM ##_::owner>::push(vm, p ## NUM); \
MSC_POP_COMPILER_WARNING_OOLUA
#define OOLUA_BACK_INTERNAL_0
#define OOLUA_BACK_INTERNAL_1 OOLUA_BACK_INTERNAL_NUM(1)
#define OOLUA_BACK_INTERNAL_2 OOLUA_BACK_INTERNAL_1  OOLUA_BACK_INTERNAL_NUM(2)
#define OOLUA_BACK_INTERNAL_3 OOLUA_BACK_INTERNAL_2  OOLUA_BACK_INTERNAL_NUM(3)
#define OOLUA_BACK_INTERNAL_4 OOLUA_BACK_INTERNAL_3  OOLUA_BACK_INTERNAL_NUM(4)
#define OOLUA_BACK_INTERNAL_5 OOLUA_BACK_INTERNAL_4  OOLUA_BACK_INTERNAL_NUM(5)
#define OOLUA_BACK_INTERNAL_6 OOLUA_BACK_INTERNAL_5  OOLUA_BACK_INTERNAL_NUM(6)
#define OOLUA_BACK_INTERNAL_7 OOLUA_BACK_INTERNAL_6  OOLUA_BACK_INTERNAL_NUM(7)
#define OOLUA_BACK_INTERNAL_8 OOLUA_BACK_INTERNAL_7  OOLUA_BACK_INTERNAL_NUM(8)

/*
Functions proxied using the following macro may have traits
 and therefore the types have the possiblity of not being on the stack
 it therefore uses a rolling parameter index to index the stack.
*/
#define OOLUA_INTERNAL_PARAM(NUM, PARAM) \
	typedef OOLUA::INTERNAL::param_type<PARAM > P ## NUM ##_; \
	P ## NUM ##_::pull_type p ## NUM; \
	MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
	if( P ## NUM ##_::in ) \
		OOLUA::INTERNAL::Proxy_stack_helper<P ## NUM ##_::traits, P ## NUM ##_::owner>::get(rolling_param_index, vm, p ## NUM); \
	MSC_POP_COMPILER_WARNING_OOLUA

#define OOLUA_PARAMS_INTERNAL_0(StackIndex)
#define OOLUA_PARAMS_INTERNAL_1(StackIndex, PARAM1) int rolling_param_index = StackIndex; OOLUA_INTERNAL_PARAM(1, PARAM1)
#define OOLUA_PARAMS_INTERNAL_2(StackIndex, PARAM1, PARAM2) OOLUA_PARAMS_INTERNAL_1(StackIndex, PARAM1)  OOLUA_INTERNAL_PARAM(2, PARAM2)
#define OOLUA_PARAMS_INTERNAL_3(StackIndex, PARAM1, PARAM2, PARAM3) OOLUA_PARAMS_INTERNAL_2(StackIndex, PARAM1, PARAM2)  OOLUA_INTERNAL_PARAM(3, PARAM3)
#define OOLUA_PARAMS_INTERNAL_4(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4) OOLUA_PARAMS_INTERNAL_3(StackIndex, PARAM1, PARAM2, PARAM3)  OOLUA_INTERNAL_PARAM(4, PARAM4)
#define OOLUA_PARAMS_INTERNAL_5(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5) OOLUA_PARAMS_INTERNAL_4(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4)  OOLUA_INTERNAL_PARAM(5, PARAM5)
#define OOLUA_PARAMS_INTERNAL_6(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6) OOLUA_PARAMS_INTERNAL_5(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5)  OOLUA_INTERNAL_PARAM(6, PARAM6)
#define OOLUA_PARAMS_INTERNAL_7(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6, PARAM7) OOLUA_PARAMS_INTERNAL_6(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6)  OOLUA_INTERNAL_PARAM(7, PARAM7)
#define OOLUA_PARAMS_INTERNAL_8(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6, PARAM7, PARAM8) OOLUA_PARAMS_INTERNAL_7(StackIndex, PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6, PARAM7)  OOLUA_INTERNAL_PARAM(8, PARAM8)

/*
macros for when using default traits and deducing the function signature
for these type of proxied functions the parameters can not use traits and
therefore are all on the stack, these then only need an offset for the first
parameters.
*/
#define OOLUA_INTERNAL_DEFAULT_PARAM(NUM, OFFSET) \
	typedef OOLUA::INTERNAL::param_type<P ## NUM > P ## NUM ##_; \
	typename P ## NUM ##_::pull_type p ## NUM; \
	OOLUA::INTERNAL::Proxy_stack_helper<P ## NUM ##_, P ## NUM ##_::owner>::get(vm, NUM + OFFSET, p ## NUM);

#define OOLUA_PARAMS_DEFAULT_INTERNAL_0(OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_1(OFFSET) OOLUA_INTERNAL_DEFAULT_PARAM(1, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_2(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_1(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(2, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_3(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_2(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(3, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_4(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_3(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(4, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_5(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_4(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(5, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_6(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_5(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(6, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_7(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_6(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(7, OFFSET)
#define OOLUA_PARAMS_DEFAULT_INTERNAL_8(OFFSET) OOLUA_PARAMS_DEFAULT_INTERNAL_7(OFFSET)  OOLUA_INTERNAL_DEFAULT_PARAM(8, OFFSET)

#define OOLUA_FUNCTION_PARAMS_TYPES_NUM(NUM) P##NUM##_::type
#define OOLUA_FUNCTION_PARAMS_TYPES_0
#define OOLUA_FUNCTION_PARAMS_TYPES_1 OOLUA_FUNCTION_PARAMS_TYPES_NUM(1)
#define OOLUA_FUNCTION_PARAMS_TYPES_2 OOLUA_FUNCTION_PARAMS_TYPES_1 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(2)
#define OOLUA_FUNCTION_PARAMS_TYPES_3 OOLUA_FUNCTION_PARAMS_TYPES_2 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(3)
#define OOLUA_FUNCTION_PARAMS_TYPES_4 OOLUA_FUNCTION_PARAMS_TYPES_3 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(4)
#define OOLUA_FUNCTION_PARAMS_TYPES_5 OOLUA_FUNCTION_PARAMS_TYPES_4 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(5)
#define OOLUA_FUNCTION_PARAMS_TYPES_6 OOLUA_FUNCTION_PARAMS_TYPES_5 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(6)
#define OOLUA_FUNCTION_PARAMS_TYPES_7 OOLUA_FUNCTION_PARAMS_TYPES_6 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(7)
#define OOLUA_FUNCTION_PARAMS_TYPES_8 OOLUA_FUNCTION_PARAMS_TYPES_7 , OOLUA_FUNCTION_PARAMS_TYPES_NUM(8)

#define OOLUA_COMMA_SEPERATED_TYPES_NUM(NUM) P##NUM
#define OOLUA_COMMA_SEPERATED_TYPES_0
#define OOLUA_COMMA_SEPERATED_TYPES_1 OOLUA_COMMA_SEPERATED_TYPES_NUM(1)
#define OOLUA_COMMA_SEPERATED_TYPES_2 OOLUA_COMMA_SEPERATED_TYPES_1 , OOLUA_COMMA_SEPERATED_TYPES_NUM(2)
#define OOLUA_COMMA_SEPERATED_TYPES_3 OOLUA_COMMA_SEPERATED_TYPES_2 , OOLUA_COMMA_SEPERATED_TYPES_NUM(3)
#define OOLUA_COMMA_SEPERATED_TYPES_4 OOLUA_COMMA_SEPERATED_TYPES_3 , OOLUA_COMMA_SEPERATED_TYPES_NUM(4)
#define OOLUA_COMMA_SEPERATED_TYPES_5 OOLUA_COMMA_SEPERATED_TYPES_4 , OOLUA_COMMA_SEPERATED_TYPES_NUM(5)
#define OOLUA_COMMA_SEPERATED_TYPES_6 OOLUA_COMMA_SEPERATED_TYPES_5 , OOLUA_COMMA_SEPERATED_TYPES_NUM(6)
#define OOLUA_COMMA_SEPERATED_TYPES_7 OOLUA_COMMA_SEPERATED_TYPES_6 , OOLUA_COMMA_SEPERATED_TYPES_NUM(7)
#define OOLUA_COMMA_SEPERATED_TYPES_8 OOLUA_COMMA_SEPERATED_TYPES_7 , OOLUA_COMMA_SEPERATED_TYPES_NUM(8)

#define OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(NUM), typename P##NUM
#define OOLUA_COMMA_PREFIXED_TYPENAMES_0
#define OOLUA_COMMA_PREFIXED_TYPENAMES_1 OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(1)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_2 OOLUA_COMMA_PREFIXED_TYPENAMES_1  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(2)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_3 OOLUA_COMMA_PREFIXED_TYPENAMES_2  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(3)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_4 OOLUA_COMMA_PREFIXED_TYPENAMES_3  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(4)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_5 OOLUA_COMMA_PREFIXED_TYPENAMES_4  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(5)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_6 OOLUA_COMMA_PREFIXED_TYPENAMES_5  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(6)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_7 OOLUA_COMMA_PREFIXED_TYPENAMES_6  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(7)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_8 OOLUA_COMMA_PREFIXED_TYPENAMES_7  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(8)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_9 OOLUA_COMMA_PREFIXED_TYPENAMES_8  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(9)
#define OOLUA_COMMA_PREFIXED_TYPENAMES_10 OOLUA_COMMA_PREFIXED_TYPENAMES_9  OOLUA_COMMA_PREFIXED_TYPENAMES_NUM(10)

#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(NUM), P##NUM##_
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_0
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_1 OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(1)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_2 OOLUA_COMMA_PREFIXED_PARAM_TYPES_1  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(2)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_3 OOLUA_COMMA_PREFIXED_PARAM_TYPES_2  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(3)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_4 OOLUA_COMMA_PREFIXED_PARAM_TYPES_3  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(4)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_5 OOLUA_COMMA_PREFIXED_PARAM_TYPES_4  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(5)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_6 OOLUA_COMMA_PREFIXED_PARAM_TYPES_5  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(6)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_7 OOLUA_COMMA_PREFIXED_PARAM_TYPES_6  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(7)
#define OOLUA_COMMA_PREFIXED_PARAM_TYPES_8 OOLUA_COMMA_PREFIXED_PARAM_TYPES_7  OOLUA_COMMA_PREFIXED_PARAM_TYPES_NUM(8)

#define OOLUA_CALL_PARAMS_NUM(NUM) , p##NUM
#define OOLUA_CALL_PARAMS_0
#define OOLUA_CALL_PARAMS_1 OOLUA_CALL_PARAMS_NUM(1)
#define OOLUA_CALL_PARAMS_2 OOLUA_CALL_PARAMS_1  OOLUA_CALL_PARAMS_NUM(2)
#define OOLUA_CALL_PARAMS_3 OOLUA_CALL_PARAMS_2  OOLUA_CALL_PARAMS_NUM(3)
#define OOLUA_CALL_PARAMS_4 OOLUA_CALL_PARAMS_3  OOLUA_CALL_PARAMS_NUM(4)
#define OOLUA_CALL_PARAMS_5 OOLUA_CALL_PARAMS_4  OOLUA_CALL_PARAMS_NUM(5)
#define OOLUA_CALL_PARAMS_6 OOLUA_CALL_PARAMS_5  OOLUA_CALL_PARAMS_NUM(6)
#define OOLUA_CALL_PARAMS_7 OOLUA_CALL_PARAMS_6  OOLUA_CALL_PARAMS_NUM(7)
#define OOLUA_CALL_PARAMS_8 OOLUA_CALL_PARAMS_7  OOLUA_CALL_PARAMS_NUM(8)

#define OOLUA_CONVERTER_NUM(NUM) OOLUA::INTERNAL::Converter<typename P##NUM::pull_type, typename P##NUM::type> p##NUM##_(p##NUM);
#define OOLUA_CONVERTER_0
#define OOLUA_CONVERTER_1 OOLUA_CONVERTER_NUM(1)
#define OOLUA_CONVERTER_2 OOLUA_CONVERTER_1  OOLUA_CONVERTER_NUM(2)
#define OOLUA_CONVERTER_3 OOLUA_CONVERTER_2  OOLUA_CONVERTER_NUM(3)
#define OOLUA_CONVERTER_4 OOLUA_CONVERTER_3  OOLUA_CONVERTER_NUM(4)
#define OOLUA_CONVERTER_5 OOLUA_CONVERTER_4  OOLUA_CONVERTER_NUM(5)
#define OOLUA_CONVERTER_6 OOLUA_CONVERTER_5  OOLUA_CONVERTER_NUM(6)
#define OOLUA_CONVERTER_7 OOLUA_CONVERTER_6  OOLUA_CONVERTER_NUM(7)
#define OOLUA_CONVERTER_8 OOLUA_CONVERTER_7  OOLUA_CONVERTER_NUM(8)

#define OOLUA_CONVERTER_PARAMS_NUM(NUM) p##NUM##_
#define OOLUA_CONVERTER_PARAMS_0
#define OOLUA_CONVERTER_PARAMS_1 OOLUA_CONVERTER_PARAMS_NUM(1)
#define OOLUA_CONVERTER_PARAMS_2 OOLUA_CONVERTER_PARAMS_1 , OOLUA_CONVERTER_PARAMS_NUM(2)
#define OOLUA_CONVERTER_PARAMS_3 OOLUA_CONVERTER_PARAMS_2 , OOLUA_CONVERTER_PARAMS_NUM(3)
#define OOLUA_CONVERTER_PARAMS_4 OOLUA_CONVERTER_PARAMS_3 , OOLUA_CONVERTER_PARAMS_NUM(4)
#define OOLUA_CONVERTER_PARAMS_5 OOLUA_CONVERTER_PARAMS_4 , OOLUA_CONVERTER_PARAMS_NUM(5)
#define OOLUA_CONVERTER_PARAMS_6 OOLUA_CONVERTER_PARAMS_5 , OOLUA_CONVERTER_PARAMS_NUM(6)
#define OOLUA_CONVERTER_PARAMS_7 OOLUA_CONVERTER_PARAMS_6 , OOLUA_CONVERTER_PARAMS_NUM(7)
#define OOLUA_CONVERTER_PARAMS_8 OOLUA_CONVERTER_PARAMS_7 , OOLUA_CONVERTER_PARAMS_NUM(8)

#define OOLUA_PULL_TYPE_PARAMS_NUM(NUM) , typename P##NUM ::pull_type& p##NUM
#define OOLUA_PULL_TYPE_PARAMS_0
#define OOLUA_PULL_TYPE_PARAMS_1 OOLUA_PULL_TYPE_PARAMS_NUM(1)
#define OOLUA_PULL_TYPE_PARAMS_2 OOLUA_PULL_TYPE_PARAMS_1  OOLUA_PULL_TYPE_PARAMS_NUM(2)
#define OOLUA_PULL_TYPE_PARAMS_3 OOLUA_PULL_TYPE_PARAMS_2  OOLUA_PULL_TYPE_PARAMS_NUM(3)
#define OOLUA_PULL_TYPE_PARAMS_4 OOLUA_PULL_TYPE_PARAMS_3  OOLUA_PULL_TYPE_PARAMS_NUM(4)
#define OOLUA_PULL_TYPE_PARAMS_5 OOLUA_PULL_TYPE_PARAMS_4  OOLUA_PULL_TYPE_PARAMS_NUM(5)
#define OOLUA_PULL_TYPE_PARAMS_6 OOLUA_PULL_TYPE_PARAMS_5  OOLUA_PULL_TYPE_PARAMS_NUM(6)
#define OOLUA_PULL_TYPE_PARAMS_7 OOLUA_PULL_TYPE_PARAMS_6  OOLUA_PULL_TYPE_PARAMS_NUM(7)
#define OOLUA_PULL_TYPE_PARAMS_8 OOLUA_PULL_TYPE_PARAMS_7  OOLUA_PULL_TYPE_PARAMS_NUM(8)

#define OOLUA_CONSTRUCTOR_PARAM_NUM(NUM) \
	typename P##NUM::pull_type p##NUM; \
	Proxy_stack_helper<typename P##NUM::traits, P##NUM::owner>::get(index, vm, p##NUM); \
	Converter<typename P##NUM::pull_type, typename P##NUM::type> p##NUM##_(p##NUM);
#define OOLUA_CONSTRUCTOR_PARAM_1 OOLUA_CONSTRUCTOR_PARAM_NUM(1)
#define OOLUA_CONSTRUCTOR_PARAM_2 OOLUA_CONSTRUCTOR_PARAM_1  OOLUA_CONSTRUCTOR_PARAM_NUM(2)
#define OOLUA_CONSTRUCTOR_PARAM_3 OOLUA_CONSTRUCTOR_PARAM_2  OOLUA_CONSTRUCTOR_PARAM_NUM(3)
#define OOLUA_CONSTRUCTOR_PARAM_4 OOLUA_CONSTRUCTOR_PARAM_3  OOLUA_CONSTRUCTOR_PARAM_NUM(4)
#define OOLUA_CONSTRUCTOR_PARAM_5 OOLUA_CONSTRUCTOR_PARAM_4  OOLUA_CONSTRUCTOR_PARAM_NUM(5)

#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(NUM) Param_helper<P##NUM >::param_is_of_type(vm, index)
#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_1 OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(1)
#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_2 OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_1 && OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(2)
#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_3 OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_2 && OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(3)
#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_4 OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_3 && OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(4)
#define OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_5 OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_4 && OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_NUM(5)

#define VA_PARAM_TYPES_NUM(NUM, ...) , INTERNAL::param_type< TYPELIST::At_default< Type_list<__VA_ARGS__ >::type, NUM-1>::Result  >
#define VA_1(...) VA_PARAM_TYPES_NUM(1, __VA_ARGS__)
#define VA_2(...) VA_1(__VA_ARGS__) VA_PARAM_TYPES_NUM(2, __VA_ARGS__)
#define VA_3(...) VA_2(__VA_ARGS__) VA_PARAM_TYPES_NUM(3, __VA_ARGS__)
#define VA_4(...) VA_3(__VA_ARGS__) VA_PARAM_TYPES_NUM(4, __VA_ARGS__)
#define VA_5(...) VA_4(__VA_ARGS__) VA_PARAM_TYPES_NUM(5, __VA_ARGS__)

#define OOLUA_FCALL_PARAM_NUM(NUM) , P##NUM p##NUM
#define OOLUA_FCALL_PARAM_0
#define OOLUA_FCALL_PARAM_1 OOLUA_FCALL_PARAM_NUM(1)
#define OOLUA_FCALL_PARAM_2 OOLUA_FCALL_PARAM_1  OOLUA_FCALL_PARAM_NUM(2)
#define OOLUA_FCALL_PARAM_3 OOLUA_FCALL_PARAM_2  OOLUA_FCALL_PARAM_NUM(3)
#define OOLUA_FCALL_PARAM_4 OOLUA_FCALL_PARAM_3  OOLUA_FCALL_PARAM_NUM(4)
#define OOLUA_FCALL_PARAM_5 OOLUA_FCALL_PARAM_4  OOLUA_FCALL_PARAM_NUM(5)
#define OOLUA_FCALL_PARAM_6 OOLUA_FCALL_PARAM_5  OOLUA_FCALL_PARAM_NUM(6)
#define OOLUA_FCALL_PARAM_7 OOLUA_FCALL_PARAM_6  OOLUA_FCALL_PARAM_NUM(7)
#define OOLUA_FCALL_PARAM_8 OOLUA_FCALL_PARAM_7  OOLUA_FCALL_PARAM_NUM(8)
#define OOLUA_FCALL_PARAM_9 OOLUA_FCALL_PARAM_8  OOLUA_FCALL_PARAM_NUM(9)
#define OOLUA_FCALL_PARAM_10 OOLUA_FCALL_PARAM_9  OOLUA_FCALL_PARAM_NUM(10)

#define OOLUA_FCALL_PUSH_NUM(NUM) && push(m_lua, p##NUM)
#define OOLUA_FCALL_PUSH_0
#define OOLUA_FCALL_PUSH_1 OOLUA_FCALL_PUSH_NUM(1)
#define OOLUA_FCALL_PUSH_2 OOLUA_FCALL_PUSH_1  OOLUA_FCALL_PUSH_NUM(2)
#define OOLUA_FCALL_PUSH_3 OOLUA_FCALL_PUSH_2  OOLUA_FCALL_PUSH_NUM(3)
#define OOLUA_FCALL_PUSH_4 OOLUA_FCALL_PUSH_3  OOLUA_FCALL_PUSH_NUM(4)
#define OOLUA_FCALL_PUSH_5 OOLUA_FCALL_PUSH_4  OOLUA_FCALL_PUSH_NUM(5)
#define OOLUA_FCALL_PUSH_6 OOLUA_FCALL_PUSH_5  OOLUA_FCALL_PUSH_NUM(6)
#define OOLUA_FCALL_PUSH_7 OOLUA_FCALL_PUSH_6  OOLUA_FCALL_PUSH_NUM(7)
#define OOLUA_FCALL_PUSH_8 OOLUA_FCALL_PUSH_7  OOLUA_FCALL_PUSH_NUM(8)
#define OOLUA_FCALL_PUSH_9 OOLUA_FCALL_PUSH_8  OOLUA_FCALL_PUSH_NUM(9)
#define OOLUA_FCALL_PUSH_10 OOLUA_FCALL_PUSH_9  OOLUA_FCALL_PUSH_NUM(10)

#define OOLUA_INTERNAL_CONSTRUCTORS_GEN OOLUA_CONSTRUCTOR_GENERATE_NUM(1) OOLUA_CONSTRUCTOR_GENERATE_NUM(2) \
	OOLUA_CONSTRUCTOR_GENERATE_NUM(3) OOLUA_CONSTRUCTOR_GENERATE_NUM(4) OOLUA_CONSTRUCTOR_GENERATE_NUM(5)
#define OOLUA_INTERNAL_FUNC_OPERATORS\
	OOLUA_INTERNAL_FUNC_OPERATOR(0) OOLUA_INTERNAL_FUNC_OPERATOR(1) OOLUA_INTERNAL_FUNC_OPERATOR(2) \
	OOLUA_INTERNAL_FUNC_OPERATOR(3) OOLUA_INTERNAL_FUNC_OPERATOR(4) OOLUA_INTERNAL_FUNC_OPERATOR(5) \
	OOLUA_INTERNAL_FUNC_OPERATOR(6) OOLUA_INTERNAL_FUNC_OPERATOR(7) OOLUA_INTERNAL_FUNC_OPERATOR(8) \
	OOLUA_INTERNAL_FUNC_OPERATOR(9) OOLUA_INTERNAL_FUNC_OPERATOR(10)
#define OOLUA_INTERNAL_C_CALLER_NO_RETURN_FUNCS\
	OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(0) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(1) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(2) \
	OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(3) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(4) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(5) \
	OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(6) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(7) OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(8)
#define OOLUA_INTERNAL_C_CALLER_FUNCS\
	OOLUA_INTERNAL_C_CALLER_NUM(0) OOLUA_INTERNAL_C_CALLER_NUM(1) OOLUA_INTERNAL_C_CALLER_NUM(2) \
	OOLUA_INTERNAL_C_CALLER_NUM(3) OOLUA_INTERNAL_C_CALLER_NUM(4) OOLUA_INTERNAL_C_CALLER_NUM(5) \
	OOLUA_INTERNAL_C_CALLER_NUM(6) OOLUA_INTERNAL_C_CALLER_NUM(7) OOLUA_INTERNAL_C_CALLER_NUM(8)
#define OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_FUNCS\
	OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(0) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(1) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(2) \
	OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(3) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(4) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(5) \
	OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(6) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(7) OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(8)
#define OOLUA_INTERNAL_MEMBER_CALLER_FUNCS\
	OOLUA_INTERNAL_MEMBER_CALLER_NUM(0) OOLUA_INTERNAL_MEMBER_CALLER_NUM(1) OOLUA_INTERNAL_MEMBER_CALLER_NUM(2) \
	OOLUA_INTERNAL_MEMBER_CALLER_NUM(3) OOLUA_INTERNAL_MEMBER_CALLER_NUM(4) OOLUA_INTERNAL_MEMBER_CALLER_NUM(5) \
	OOLUA_INTERNAL_MEMBER_CALLER_NUM(6) OOLUA_INTERNAL_MEMBER_CALLER_NUM(7) OOLUA_INTERNAL_MEMBER_CALLER_NUM(8)
#define OOLUA_GENERATE_DEFAULT_TRAIT_CALLERS\
	OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(0) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(1) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(2) \
	OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(3) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(4) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(5) \
	OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(6) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(7) OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(8)
/** \endcond */
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

#ifndef OOLUA_TYPE_CONVERTERS_H_
#	define OOLUA_TYPE_CONVERTERS_H_

/** \cond INTERNAL*/

namespace LVD
{
	template<typename T>struct by_reference;
} // namespace LVD

namespace OOLUA
{
	namespace INTERNAL
	{
		template<typename Pull_type, typename Real_type>struct Converter;

		template<typename T>
		struct Converter<T*, T&>
		{
			Converter(T*& t):m_t(t){}
			operator T& () const
			{
				return *m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T>
		{
			Converter(T* t):m_t(t){}
			operator T& () const
			{
				return *m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T const*, T>
		{
			typedef char T_has_to_be_by_value[ LVD::by_reference<T>::value ? -1 : 1];
			Converter(T const* t):m_t(const_cast<T*>(t)){}
			operator T& () const
			{
				return *m_t;
			}
			Converter& operator = (Converter const&);
			Converter(Converter const&);
			T* m_t;
		};

		template<typename T>
		struct Converter<T, T*>
		{
			Converter(T& t):m_t(t){}
			operator T* () const
			{
				return &m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T& m_t;
		};

		template<typename T>
		struct Converter<T*, T*&>
		{
			Converter(T*& t):m_t(t){}//added reference
			operator T*& () //const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T*& m_t;//added reference
		};

		template<typename T>
		struct Converter<T*, T const&>
		{
			Converter(T* t):m_t(t){}
			operator T const&() const
			{
				return *m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T const*&>
		{
			Converter(T* t):m_t(t){}
			operator T const*&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T const* m_t;
		};

		template<typename T>
		struct Converter<T*, T const*>
		{
			Converter(T* t):m_t(t){}
			operator T const*() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T, T*const&>
		{
			Converter(T & t):m_t(t){}
			operator T* /*const*/  () const
			{
				return &m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T & m_t;
		};

		template<typename T>
		struct Converter<T, T const*&>
		{
			Converter(T & t):m_t(&t){}
			operator T const*&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T const* m_t;
		};

		template<typename T>
		struct Converter<T, T const *const &>
		{
			Converter(T& t):m_t(&t){}
			operator T*const &() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T *const&>
		{
			Converter(T* t):m_t(t){}
			operator T *const&() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T const*const&>
		{
			Converter(T* t):m_t(t){}
			operator T const * /*const*/() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T const*const>
		{
			Converter(T* t):m_t(t){}
			operator T const * /*const*/() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T*, T*>
		{
			Converter(T* t):m_t(t){}
			operator T* () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T, T>
		{
			Converter(T& t):m_t(t){}
			operator T& () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T& m_t;
		};

		template<typename T>
		struct Converter<T, T&>
		{
			Converter(T& t):m_t(t){}
			operator T& () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T& m_t;
		};

		template<typename T>
		struct Converter<T, T*&>
		{
			Converter(T& t):m_t(&t){}
			operator T*& ()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T, T const&>
		{
			Converter(T& t):m_t(t){}
			operator T const& () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T& m_t;
		};

		template<typename T>
		struct Converter<T*, T *const>
		{
			Converter(T* t):m_t(t){}
			operator T * () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};

		template<typename T>
		struct Converter<T const*, T const*&>
		{
			Converter(T const*& t):m_t(t){}//added ref
			operator T const*&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T const*& m_t;//added ref
		};

		template<typename T>
		struct Converter<T, T const>
		{
			Converter(T& t):m_t(t){}
			operator T() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T const & m_t;
		};

		template<typename T>
		struct Converter<T, T const*>
		{
			Converter(T & t):m_t(&t){}
			operator T const*&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T const* m_t;
		};

		template<typename T>
		struct Converter<T, T const *const>
		{
			Converter(T& t):m_t(&t){}
			operator T*const &() const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			T* m_t;
		};


		///////////////////////////////////////////////////////////////////////////////
		/// Specialisation for C style strings
		///	This removes const.
		///	The cast has to happen somewhere if a function want to take a none
		///	modifiable string as char* tut tut but it happerns.
		///////////////////////////////////////////////////////////////////////////////
		template<>
		struct Converter<char const*, char *>
		{
			Converter(char const* & t):m_t(const_cast<char*>(t)){}
			operator char * () const
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			char * m_t;
		};

		///////////////////////////////////////////////////////////////////////////////
		/// Specialisation for light user data
		/// Casts from a void pointer to Real which is a pointer
		///	The cast has to happen somewhere if a light user data type is not a void
		/// pointer.
		///////////////////////////////////////////////////////////////////////////////
		template<typename Real>
		struct Converter<void*, Real>
		{
			Converter(void* t)
				: m_t(static_cast<Real>(t))
			{}
			operator Real&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			Real m_t;
		};

		///////////////////////////////////////////////////////////////////////////////
		/// Specialisation for light user data
		///	This specialisation is required because otherwise there would be
		/// ambiguity over which instance to use,
		///////////////////////////////////////////////////////////////////////////////
		template<>
		struct Converter<void*, void*>
		{
			Converter(void*& t)
				: m_t(t)
			{}
			operator void*&()
			{
				return m_t;
			}
			Converter& operator =(Converter const &);
			Converter(Converter const &);
			void*& m_t;
		};

	} // namespace INTERNAL //NOLINT
} // namespace OOLUA
/** \endcond */

#endif //OOLUA_TYPE_CONVERTERS_H_
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
	\file oolua_stack_fwd.h
 	\brief Forward declarations of the push and pull methods, which provide simple
 	interaction with the Lua stack.
*/


#ifndef OOLUA_STACK_FWD_H_
#	define OOLUA_STACK_FWD_H_
 //required for OOLUA::Owner

struct lua_State;

namespace OOLUA
{

	template<int ID>
	struct Lua_ref;

	class Table;

	//this does not take into account calling convention!!
	typedef int(*oolua_CFunction)(lua_State* vm); //NOLINT(readability/casting)

	/**@{*/
	/**
		\brief Pushes an instance to top of the Lua stack
		\return
		If \ref OOLUA_STORE_LAST_ERROR is set to one then the the return value will
		indicate success or failure, if \ref OOLUA_USE_EXCEPTIONS is set to one then
		failure will always be reported by the throwing of an exception.
		\note Although all push methods return a boolean, most simply return true.
		The only versions which can return false are functions which operate on
		full userdata and values which are associated with a Lua universe.
		\see \ref OOLUA::can_xmove
		\see OOLuaErrorReporting
		\see OOLuaExceptionClasses
	*/
	bool push(lua_State* const vm, void* lightud);
	bool push(lua_State* const vm, bool const& value);
	bool push(lua_State* const vm, char * const& value);
	bool push(lua_State* const vm, char const * const& value);
	bool push(lua_State* const vm, double const& value);
	bool push(lua_State* const vm, float const&  value);
	bool push(lua_State* const vm, oolua_CFunction const &  value);
	bool push(lua_State* const vm, Table const &  value);

	template<typename T>
	bool push(lua_State* const vm, T * const &  value);
	template<typename T>
	bool push(lua_State* const vm, lua_acquire_ptr<T> const&  value);
	template<typename T>
	bool push(lua_State* const vm, T const &  value);
	/**@}*/

	/** \cond INTERNAL */
	template<typename T>
	bool push(lua_State* const vm, T * const &  value, OOLUA::Owner);
	/** \endcond */

	/**
		@{
		\brief Pulls the top element off the stack and pops it.
		\details In stack terms this is a top followed by pop.
		\return
		If \ref OOLUA_STORE_LAST_ERROR is set to one then the the return value will
		indicate success or failure, if \ref OOLUA_USE_EXCEPTIONS is set to one then
		failure will always be reported by throwing an exception.
		\see OOLuaErrorReporting
		\see OOLuaExceptionClasses
	*/
	bool pull(lua_State* const vm, void*& lightud);
	bool pull(lua_State* const vm, bool& value);
	bool pull(lua_State* const vm, double& value);
	bool pull(lua_State* const vm, float& value);
	bool pull(lua_State* const vm, oolua_CFunction& value);
	bool pull(lua_State* const vm, Table&  value);

	template<typename T>
	bool pull(lua_State* const vm, T *&  value);
	template<typename T>
	bool pull(lua_State* const vm, T&  value);
	template<typename T>
	bool pull(lua_State* const vm, cpp_acquire_ptr<T> const&  value);
	/**	@}*/

	/** \cond INTERNAL */
	namespace INTERNAL
	{
		namespace LUA_CALLED
		{
			/**
				@{
				\brief Internal function used to get a value from the stack
				\details These functions differ from the public API pull methods by:
					\li Using a stack index on which to operate and by not popping the value
					\li Reporting errors differently.
				<p>
				By treating the stack differently, it ensures that the value is not garbage collected
				whilst in the process of a C++ proxied function call.
			*/
			void get(lua_State* const vm, int idx, void*& value);
			void get(lua_State* const vm, int idx, bool& value);
			void get(lua_State* const vm, int idx, char const*& value);
			void get(lua_State* const vm, int idx, double& value);
			void get(lua_State* const vm, int idx, float& value);
			void get(lua_State* const vm, int idx, oolua_CFunction& value);
			void get(lua_State* const vm, int idx, Table&  value);

			template<typename T>
			void get(lua_State* const vm, int idx, T& value);

			template<typename T>
			void get(lua_State* const vm, int idx, T *&  value);

			template<typename T>
			void get(lua_State* const vm, int idx, OOLUA::cpp_acquire_ptr<T>&  value);
			/**	@}*/

		} // namespace LUA_CALLED // NOLINT

	} // namespace INTERNAL // NOLINT
	/** \endcond */
} // namespace OOLUA

#endif //OOLUA_STACK_FWD_H_
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

#ifndef OOLUA_PROXY_TAG_INFO_H_
#	define OOLUA_PROXY_TAG_INFO_H_


namespace OOLUA
{
	namespace INTERNAL
	{
		/** \cond INTERNAL */
		/**
			\addtogroup OOLuaDeveloperDocs
		@{*/

			/**  \addtogroup OOLuaTagChecking Tag Checking
			@{
				\brief Provides a way to check for a \ref OOLuaTags "tag" in a specific Proxy_class
				\details Allows for the checking of a tag in a Proxy_class. There is no requirement
				for a Proxy_class to contain a tag block; it therefore first determines if the class
				, and not one of it's bases, contains such a block and then check for the presence
				of the tag.
			*/

		/**
			\brief Checks if a type of a base of the type has a tag block
			\details If a Proxy_class does not contain a tag block yet one of it's bases does,
			then this is the one which will be identified. We use the result from this template
			in a further test to determine if it is a base tag or the correct type tag.
			\see tag_block_is_same
		*/
		template<typename ClassType>
		struct class_or_base_has_tag_block
		{
			template <typename U>
			static char (&check_for_tag_block(typename OOLUA::Proxy_class<U>::tag_block_check*))[1];//NOLINT
			template <typename U>
			static char (&check_for_tag_block(...))[2];//NOLINT
			enum {value = sizeof(check_for_tag_block<ClassType >(0)) == 1 ? 1 : 0};
		};

		/**
			\brief Checks a potential tag block against the requested type
			\details As a tag block is a typedef for the class type, we can use the result of
			class_or_base_has_tag_block to check if the type is the same as the wanted type
			\tparam ClassType The class type which must be the same of the tag block if it is
				contained in Proxy_class<ClassType>
			\tparam TagBlockMaybeInClass_or_MaybeInABase specialisation which is the result of
			class_or_base_has_tag_block, which when is zero uses SFINAE to store a result
				which indicates it has no tag block.
		*/
		template< typename ClassType, int TagBlockMaybeInClass_or_MaybeInABase>
		struct tag_block_is_same
		{
			enum {value = LVD::is_same< typename Proxy_class<ClassType>::tag_block_check
					, ClassType >::value };
		};
		template< typename ClassType>
		struct tag_block_is_same<ClassType, 0>
		{
			enum {value = 0};
		};

		/**
			\brief Either typedefs the the tags typelist or an empty typelist which can
			be checked for the presence of a type, without producing a compile time failure.
			\tparam ClassType the Proxy_class<ClassType> which information is wanted from
			\tparam has_proxy_tags Allows specialisation and SFINAE
		*/
		template<typename ClassType, int has_proxy_tags>
		struct proxy_tag_type
		{
			typedef typename Proxy_class<ClassType>::Tags type;
		};

		template<typename ClassType>
		struct proxy_tag_type<ClassType, 0>
		{
			typedef TYPE::Null_type type;
		};

		/**
			\brief Uses the other templates in \ref OOLuaTagChecking to typedef a typelist
			which can then be checked safely.
			\tparam ClassType The Proxy_class<ClassType> from which tag information is wanted
		*/
		template<typename ClassType>
		struct tag_type
		{
			enum { has_proxy_tags = tag_block_is_same<ClassType, class_or_base_has_tag_block<ClassType>::value >::value };
			typedef typename proxy_tag_type<ClassType, has_proxy_tags>::type type;
		};

		/**
			\brief A compile time safe method of determining if a Proxy_class tag list contains a tag
			\tparam ProxyType The proxy_class to check
			\tparam Tag The specific tag which will be checked for in ProxyType
		*/
		template<typename ProxyType, typename Tag>
		struct has_tag
		{
			enum {Result = TYPELIST::IndexOf<typename tag_type<typename ProxyType::class_>::type, Tag>::value == -1 ? 0 : 1};
		};

			/**@}*/
		/**@}*/
#if OOLUA_USE_SHARED_PTR == 1
#	if OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE == 0
		template<typename RawClassType>
		struct new_pointer
		{
			typedef typename LVD::if_else<has_tag<Proxy_class<RawClassType>, Shared>::Result
										, OOLUA_SHARED_TYPE<RawClassType>
										, RawClassType*
									>::type type;
		};
#	else
		template<typename RawClassType>
		struct new_pointer
		{
			typedef typename LVD::if_else<has_tag<Proxy_class<RawClassType>, No_shared>::Result
										, RawClassType*
										, OOLUA_SHARED_TYPE<RawClassType>
									>::type type;
		};

#	endif
#else
		template<typename RawClassType>
		struct new_pointer
		{
			typedef RawClassType* type;
		};
#endif


		/** \endcond */
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA

#endif //OOLUA_PROXY_TAG_INFO_H_
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

#ifndef OOLUA_PROXY_STORAGE_H_
#	define OOLUA_PROXY_STORAGE_H_




namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		typedef bool (*is_const_func_sig)(Lua_ud const* ud);
		template<int NotTheSameSize>
		struct VoidPointerSameSizeAsFunctionPointer;

		template<int NotTheSameSize>
		struct VoidPointerSameSizeAsFunctionPointer
		{
			static void getWeakTable(lua_State* vm)
			{
				lua_getfield(vm, LUA_REGISTRYINDEX, OOLUA::INTERNAL::weak_lookup_name);
			}
			static void setWeakTable(lua_State* vm, int value_index)
			{
				OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::weak_lookup_name);
				lua_pushvalue(vm, value_index);
				lua_rawset(vm, LUA_REGISTRYINDEX);
			}
			static void getCollisionMetatable(lua_State* vm)
			{
				lua_getfield(vm, LUA_REGISTRYINDEX, OOLUA::INTERNAL::collision_mt_lookup_name);
			}
			static void setCollisionMetatable(lua_State* vm, int value_index)
			{
				OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::collision_mt_lookup_name);
				lua_pushvalue(vm, value_index);
				lua_rawset(vm, LUA_REGISTRYINDEX);
			}
		};


		template<>
		struct VoidPointerSameSizeAsFunctionPointer< sizeof(is_const_func_sig) >
		{
			static void getWeakTable(lua_State* vm)
			{
				//it is safe as the pointers are the same size
				//yet we need to stop warnings
				//NOTE: in 5.2 we can push a light c function here
				is_const_func_sig func = OOLUA::INTERNAL::userdata_is_constant;
				void** stopwarnings = reinterpret_cast<void**>(&func);
				lua_pushlightuserdata(vm, *stopwarnings);
				lua_rawget(vm, LUA_REGISTRYINDEX);
			}
			static void setWeakTable(lua_State* vm, int value_index)
			{
				//it is safe as the pointers are the same size
				//yet we need to stop warnings
				//NOTE: in 5.2 we can push a light c function here
				is_const_func_sig func = OOLUA::INTERNAL::userdata_is_constant;
				void** stopwarnings = reinterpret_cast<void**>(&func);
				lua_pushlightuserdata(vm, *stopwarnings);
				lua_pushvalue(vm, value_index);
				lua_rawset(vm, LUA_REGISTRYINDEX);
			}
			static void getCollisionMetatable(lua_State* vm)
			{
				//it is safe as the pointers are the same size
				//yet we need to stop warnings
				//NOTE: in 5.2 we can push a light c function here
				is_const_func_sig func = OOLUA::INTERNAL::userdata_is_to_be_gced;
				void** stopwarnings = reinterpret_cast<void**>(&func);
				lua_pushlightuserdata(vm, *stopwarnings);
				lua_rawget(vm, LUA_REGISTRYINDEX);
			}
			static void setCollisionMetatable(lua_State* vm, int value_index)
			{
				is_const_func_sig func = OOLUA::INTERNAL::userdata_is_to_be_gced;
				void** stopwarnings = reinterpret_cast<void**>(&func);
				lua_pushlightuserdata(vm, *stopwarnings);
				lua_pushvalue(vm, value_index);
				lua_rawset(vm, LUA_REGISTRYINDEX);
			}
		};

		typedef VoidPointerSameSizeAsFunctionPointer<sizeof(void*)> Weak_table; // NOLINT

		//pushes the weak top and returns its index
		int push_weak_table(lua_State* vm);
		template<typename T>Lua_ud* add_ptr(lua_State* vm, T* const ptr, bool is_const, Owner owner);

		template<typename PossiblySharedPtrType, typename ClassType>
		Lua_ud* find_ud(lua_State* vm, PossiblySharedPtrType const * shared_ptr, ClassType* ptr, bool is_const);

		bool is_there_an_entry_for_this_void_pointer(lua_State* vm, void* ptr);
		bool is_there_an_entry_for_this_void_pointer(lua_State* vm, void* ptr, int tableIndex);

		template<typename PossiblySharedType, typename ClassType>
		Lua_ud* reset_metatable(lua_State* vm, PossiblySharedType const* shared_ptr
										, ClassType* ptr, bool is_const);

		void add_ptr_if_required(lua_State* const vm, void* ptr, int udIndex, int weakIndex);


		Lua_ud* new_userdata(lua_State* vm, void* ptr, bool is_const
							 , oolua_function_check_base base_checker
							 , oolua_type_check_function type_check
							 , oolua_release_shared_ptr shared_release);
		void reset_userdata(Lua_ud* ud, void* ptr, bool is_const
							, oolua_function_check_base base_checker
							, oolua_type_check_function type_check
							, oolua_release_shared_ptr shared_release);

		template<typename Type, typename Bases, int BaseIndex, typename BaseType>
		struct Add_ptr;

		template<typename Type, typename Bases, int BaseIndex, typename BaseType>
		struct Has_a_root_entry;

		template<typename T>
		int lua_set_owner(lua_State* vm);

		bool ud_at_index_is_const(lua_State* vm, int index);

		//TODO: can not change gc on shared_ptrs
		template<typename T>
		int lua_set_owner(lua_State*  vm)
		{
			T* p = check_index<T>(vm, 1);
			if(!p) return luaL_error(vm, "The self/this instance to '%s' is not of type '%s'"
									 , OOLUA::INTERNAL::set_owner_str
									 , OOLUA::Proxy_class<T>::class_name);

			Owner own(No_change);
			OOLUA::INTERNAL::LUA_CALLED::get(vm, 2, own);
			if(own != No_change) INTERNAL::userdata_gc_value(static_cast<INTERNAL::Lua_ud*>(lua_touserdata(vm, 1)), own == Cpp? false : true);
			return 0;
		}

		template<typename T>
		inline bool is_derived_ptr(oolua_type_check_function base_type_checker, T* ptr)
		{
#if OOLUA_USE_SHARED_PTR == 1
			Lua_ud fake_stack_ud = {{ptr}, 0 , register_class_imp<T>, 0, 0};
			Lua_ud fake_requested_ud = {{0}, 0, base_type_checker, 0, 0};
#else
			Lua_ud fake_stack_ud = {ptr, 0 , register_class_imp<T>, 0};
			Lua_ud fake_requested_ud = {0, 0, base_type_checker, 0};
#endif
			requested_ud_is_a_base<T>(&fake_requested_ud, &fake_stack_ud);
			return fake_requested_ud.void_class_ptr != NULL;
		}

		template<typename PossiblySharedPtrType, typename ClassType>
		inline Lua_ud* is_correct_ud(lua_State* vm, Lua_ud* ud, PossiblySharedPtrType const* shared_ptr, ClassType* ptr, bool const is_const)
		{
			bool const was_const = OOLUA::INTERNAL::userdata_is_constant(ud);
			if (ud_is_type<ClassType>(ud) || valid_base_ptr_or_null<ClassType>(ud))
			{
				ud->flags &= ((!is_const && was_const) ? (~CONST_FLAG) : ud->flags);
				return ud;
			}
			else if (is_derived_ptr(ud->type_check, ptr))
				return reset_metatable(vm, shared_ptr, ptr, was_const && is_const);

			return NULL;
		}

		template<typename PossiblySharedPtrType, typename ClassType>
		inline Lua_ud* check_roots(lua_State* vm, PossiblySharedPtrType const* shared_ptr
								, ClassType * ptr, bool const is_const, int cache_table_index)
		{
			/*
				possibilities:
				a base class is stored.
				none of the hierarchy is stored
			*/
			Lua_ud* ud(0);
			bool base_is_stored(false);
			Has_a_root_entry<
					ClassType
					, typename FindRootBases<ClassType>::Result
					, 0
					, typename TYPELIST::At_default< typename FindRootBases<ClassType>::Result, 0, TYPE::Null_type >::Result
				> checkRoots;
			checkRoots(vm, ptr, cache_table_index, base_is_stored);
			if(base_is_stored)
			{
				bool was_const = ud_at_index_is_const(vm, -1);
				ud = reset_metatable(vm, shared_ptr, ptr, was_const && is_const);
			}
			return ud;
		}


		//if found it is left on the top of the stack and returns the Lua_ud ptr
		//else the stack is same as on entrance to the function and null is returned
		template<typename PossiblySharedPtrType, typename ClassType>
		inline Lua_ud* find_ud(lua_State*  vm, PossiblySharedPtrType const* shared_ptr
								, ClassType* ptr, bool const is_const)
		{
			Lua_ud* ud(0);
			int cache_table_index = push_weak_table(vm);
			lua_pushlightuserdata(vm, ptr);
			lua_rawget(vm, cache_table_index);
			switch(lua_type(vm, -1))
			{
				case LUA_TNIL: //no cache entry
				{
					lua_pop(vm, 1); //pop the nil
					ud = check_roots(vm, shared_ptr, ptr, is_const, cache_table_index);
					lua_remove(vm, cache_table_index);
					break;
				}
				case LUA_TUSERDATA: //one cached entry
				{
					ud = static_cast<Lua_ud *>(lua_touserdata(vm, -1));
					if ((ud = is_correct_ud(vm, ud, shared_ptr, ptr, is_const)) == NULL)
					{
						lua_pop(vm, 1);//pop the found ud
						ud = check_roots(vm, shared_ptr, ptr, is_const, cache_table_index);
						lua_remove(vm, cache_table_index);
					}
					else
						lua_remove(vm, cache_table_index);

					break;
				}
				case LUA_TTABLE: //pointer collision
				{
					lua_pushnil(vm);
					while(lua_next(vm, -2) != 0)
					{
						ud = static_cast<Lua_ud *>(lua_touserdata(vm, -1));
						if ((ud = is_correct_ud(vm, ud, shared_ptr, ptr, is_const)) == NULL)
							lua_pop(vm, 1);//pop the ud value to continue iteration
						else
						{
							lua_replace(vm, cache_table_index);
							lua_settop(vm, cache_table_index);
							return ud;
						}
					}
					lua_pop(vm, 2); //remove cache_table and collision table
					break;
				}
			}

			return ud;
		}


		/*
			This is required because when we want to change the metatable to a more
			derived type, we do not actually know the type that is already stored in
			the userdata member. So the userdata has to pay for another function
			pointer to do the work.
		*/
		template<typename T>
		struct SharedHelper;

#if OOLUA_USE_SHARED_PTR == 1
		/*
			Handles shared<T const> and shared<T>
		*/
		template<typename Ptr_type>//, template <typename> class Shared_pointer_class>
		struct SharedHelper<OOLUA_SHARED_TYPE<Ptr_type> >
		{
			typedef OOLUA_SHARED_TYPE<typename LVD::remove_const<Ptr_type>::type> shared;
			static void release_pointer(Lua_ud* ud)
			{
				//this member is only defined when compiled with shared pointer support
				shared* shared_ptr = reinterpret_cast<shared*>(ud->shared_object);
				shared_ptr->~shared();
			}
		};
#endif

		/* raw pointer version does nothing*/
		template<typename T>
		struct SharedHelper
		{
			static void release_pointer(Lua_ud* /*ud*/){}//nop // LCOV_EXCL_LINE
		};

		/*
			The library always stores the most derived type known for the instance
			and the weakest type.
			If there are two types A and B, where B derives from A.
			shared<B const> is pushed
			then shared<A> is pushed
			The weakest and most derived type now is shared<B> yet the library does not
			know the type stored in the userdata at this point and therefore how to cast
			it to the new none constant derived type.

			The problem is not unique for shared pointers but it adds another level of
			stupidity. Raw pointers B* and B const* are related types, which is not true
			for shared<B> and shared<B const>.
			Shared<B> b(new B);
			Shared<B const>* bb = &b; //BOOM unrelated types and undefined.
			You could try a C style function cast / reinterpret_cast to quieten the compiler
			but it is still undefined.
			However Shared<B const> bb(b) is defined, so we can always get a constant version
			from a none constant version. Therefore the library will use OOLUA_SHARED_CONST_CAST
			to remove constness and then use the const flag in the userdata. This way when
			constness changes the flag is switched off yet the type is still correct without
			knowing it at that point and later when the instance has it's destructor called.

		*/

#if OOLUA_USE_SHARED_PTR == 1
		/*
			These must be protected as they use OOLUA_SHARED_CONST_CAST and ud->shared_object
			which are only defined when using shared pointers.
		*/

		/*const version removes const*/
		template<typename Ptr_type>
		Ptr_type* fixup_pointer(Lua_ud* ud, OOLUA_SHARED_TYPE<Ptr_type const> const* shared)
		{
			typedef OOLUA_SHARED_TYPE<Ptr_type> none_const_sp;
			none_const_sp * sp = new(ud->shared_object) none_const_sp(OOLUA_SHARED_CONST_CAST<Ptr_type>(*shared));
			return sp->get();
		}

		/*none const version*/
		template<typename Ptr_type>
		Ptr_type* fixup_pointer(Lua_ud* ud, OOLUA_SHARED_TYPE<Ptr_type> const* shared)
		{
			typedef OOLUA_SHARED_TYPE<Ptr_type> none_const_sp;
			none_const_sp* sp = new(ud->shared_object) none_const_sp(*shared);
			return sp->get();
		}
#endif
		/* raw pointer version does nothing*/
		template<typename T>
		void fixup_pointer(Lua_ud* /*ud*/, T const* /*raw*/)//nop //NOLINT(readability/casting)
		{}


		template<typename PossiblySharedType, typename ClassType>
		inline Lua_ud* reset_metatable(lua_State* vm, PossiblySharedType const* shared_ptr
										, ClassType* ptr, bool is_const)
		{
			Lua_ud *ud = static_cast<Lua_ud *>(lua_touserdata(vm, -1));//ud
#if OOLUA_USE_SHARED_PTR == 1
			/*
				Member only defined when there is shared pointer support.
				If the type is not a shared pointer then translates to a nop.
			*/
			ud->shared_ptr_release(ud);
#endif
			reset_userdata(ud, ptr, is_const
							, &requested_ud_is_a_base<ClassType>
							, &register_class_imp<ClassType>
							, &SharedHelper<PossiblySharedType>::release_pointer);

			fixup_pointer(ud, shared_ptr);

			//change the metatable associated with the ud
			lua_getfield(vm, LUA_REGISTRYINDEX, OOLUA::Proxy_class<ClassType>::class_name);

			lua_setmetatable(vm, -2);//set ud's metatable to this

			int weak_index = push_weak_table(vm);//ud weakTable
			//then register all the bases that need it
			Add_ptr<ClassType
					, typename OOLUA::Proxy_class<ClassType>::AllBases
					, 0
					, typename TYPELIST::At_default< typename OOLUA::Proxy_class<ClassType>::AllBases, 0, TYPE::Null_type >::Result
				> addThisTypesBases;
			addThisTypesBases(vm, ptr, weak_index-1, weak_index);
			lua_pop(vm, 1);//ud
			return ud;
		}

		template<typename T>
		inline void add_ptr_imp(lua_State* const vm, T* const ptr)
		{
			lua_getfield(vm, LUA_REGISTRYINDEX, OOLUA::Proxy_class<T>::class_name);

#if	OOLUA_DEBUG_CHECKS == 1
			assert(lua_isnoneornil(vm, -1) == 0 && "no metatable of this name found in registry"); // LCOV_EXCL_LINE
#endif
			////Pops a table from the stack and sets it as the new metatable for the value at the given acceptable index
			lua_setmetatable(vm, -2);

			int weakIndex = push_weak_table(vm);//ud,weakTable
			int udIndex = weakIndex -1;

			add_ptr_if_required(vm, ptr, udIndex, weakIndex);//it is required

			Add_ptr<T
					, typename OOLUA::Proxy_class<T>::AllBases
					, 0
					, typename TYPELIST::At_default< typename OOLUA::Proxy_class<T>::AllBases, 0, TYPE::Null_type >::Result
				> addThisTypesBases;
			addThisTypesBases(vm, ptr, udIndex, weakIndex);

			lua_pop(vm, 1);//ud
		}

		template<typename T>
		inline Lua_ud* add_ptr(lua_State* const vm, T* const ptr, bool is_const, Owner owner)
		{
			Lua_ud* ud = new_userdata(vm, ptr, is_const
										, &requested_ud_is_a_base<T>
										, &register_class_imp<T>
										, &SharedHelper<T>::release_pointer);
			if(owner != No_change)userdata_gc_value(ud, owner == Lua);

			add_ptr_imp(vm, ptr);
			return ud;
		}

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T>
		inline Lua_ud* add_ptr(lua_State* const vm, OOLUA_SHARED_TYPE<T> const&  shared_ptr, bool is_const, Owner /*owner*/)
		{
			typedef typename LVD::remove_const<T>::type raw;
			typedef  OOLUA_SHARED_TYPE<raw> shared;

			Lua_ud* ud = new_userdata(vm, NULL, is_const
									, &requested_ud_is_a_base<raw>
									, &register_class_imp<raw>
									, &SharedHelper<shared>::release_pointer);

			raw* p = fixup_pointer(ud, &shared_ptr);

			userdata_gc_value(ud, true);//yes it always needs destructing
			userdata_shared_ptr(ud);//add the shared flag
			add_ptr_imp(vm, p);

			return ud;
		}
#endif

		template<typename Type, typename Bases, int BaseIndex, typename BaseType>
		struct Add_ptr
		{
			void operator()(lua_State * const vm, Type* ptr, int udIndex, int weakIndex)
			{
				//add this type if needed
				add_ptr_if_required(vm, static_cast<BaseType*>(ptr), udIndex, weakIndex);
				//add the next in the type list if needed
				Add_ptr<
						Type
						, Bases
						, BaseIndex + 1
						, typename TYPELIST::At_default< Bases, BaseIndex + 1, TYPE::Null_type >::Result
					> addBaseNextPtr;
				addBaseNextPtr(vm, ptr, udIndex, weakIndex);
			}
		};

		template<typename Type, typename Bases, int BaseIndex>
		struct Add_ptr<Type, Bases, BaseIndex, TYPE::Null_type>
		{
			void operator()(lua_State * const /*vm*/, Type* /*ptr*/, int /*udIndex*/, int /*weakIndex*/)const
			{}
		};

		template<typename Type, typename Bases, int BaseIndex, typename BaseType>
		struct Has_a_root_entry
		{
			void operator()(lua_State * const vm, Type* ptr, int weakIndex, bool& result)
			{
				if(result)return;

				void* void_base_ptr = static_cast<void*>(static_cast<BaseType*>(ptr));
				if(static_cast<void*>(ptr) != void_base_ptr
				   && is_there_an_entry_for_this_void_pointer(vm, void_base_ptr, weakIndex))
				{
					switch(lua_type(vm, -1))
					{
						case LUA_TUSERDATA:
						{
							Lua_ud* ud = static_cast<Lua_ud*>(lua_touserdata(vm, -1));
							if( is_derived_ptr(ud->type_check, ptr))
							{
								result = true;
								return;
							}
							else
								lua_pop(vm, 1);//remove the incorrect ud

							break;
						}
						case LUA_TTABLE:
						{
							lua_pushnil(vm);//collisionTable, nil
							while(lua_next(vm, -2) != 0)
							{
								//collisionTable, ud, ud
								Lua_ud* ud = static_cast<Lua_ud *>(lua_touserdata(vm, -1));
								if( is_derived_ptr(ud->type_check, ptr))
								{
									result = true;
									lua_replace(vm, -3);
									lua_pop(vm, 1);
									return;
								}
								//keep the ud(key) for the next iteration
								lua_pop(vm, 1);//collisionTable, ud
							}
							lua_pop(vm, 1);//remove the collision table
							break;
						}
					}
				}
				Has_a_root_entry<
						Type
						, Bases
						, BaseIndex + 1
						, typename TYPELIST::At_default< Bases, BaseIndex + 1, TYPE::Null_type >::Result
					> checkNextBase;
				checkNextBase(vm, ptr, weakIndex, result);
			}
		};

		template<typename Type, typename Bases, int BaseIndex>
		struct Has_a_root_entry<Type, Bases, BaseIndex, TYPE::Null_type>
		{
			void operator()(lua_State * const /*vm*/, Type* /*ptr*/, int /*weakIndex*/, bool& /*result*/)const
			{}
		};


	} // namespace INTERNAL // NOLINT
	/**\endcond*/


} // namespace OOLUA

#endif //OOLUA_PROXY_STORAGE_H_
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

#ifndef PUSH_POINTER_INTERAL_H_
#	define PUSH_POINTER_INTERAL_H_


struct lua_State;

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<typename Raw, typename TypeMaybeConst>
		void push_pointer_which_has_a_proxy_class(lua_State * vm, TypeMaybeConst * const ptr, Owner owner);

		void if_check_enabled_check_type_is_registered(lua_State* vm, char const* name);
		void set_owner_if_change(Owner owner, Lua_ud* ud);

		template<typename Raw, typename TypeMaybeConst>
		inline void push_pointer_which_has_a_proxy_class(lua_State * vm, TypeMaybeConst * const ptr, Owner owner)
		{
			if_check_enabled_check_type_is_registered(vm, Proxy_class<Raw>::class_name);
			Lua_ud* ud(find_ud<Raw,Raw>(vm, (Raw*)ptr,(Raw*)ptr, !!LVD::is_const<TypeMaybeConst>::value));//NOLINT
			if(!ud) ud = add_ptr(vm, (Raw*)ptr, !!(LVD::is_const<TypeMaybeConst>::value), owner);//NOLINT
			else set_owner_if_change(owner, ud);
		}

		template<typename Underlying_pointer_type, template <typename> class Shared_pointer_class>
		inline void push_shared_pointer(lua_State* vm, Shared_pointer_class<Underlying_pointer_type> const& instance)
		{
			typedef Shared_pointer_class<Underlying_pointer_type> shared_type;
			typedef typename LVD::remove_const<Underlying_pointer_type>::type raw_type;
			if_check_enabled_check_type_is_registered(vm, Proxy_class<raw_type>::class_name);
			Lua_ud* ud(find_ud<shared_type,raw_type>(vm, &instance, (raw_type*)(instance.get()), !!LVD::is_const<Underlying_pointer_type>::value));//NOLINT
			if(!ud) ud = add_ptr(vm, instance, !!(LVD::is_const<Underlying_pointer_type>::value), Lua/*ignored parameter*/);//NOLINT
		}

	} // namespace INTERNAL // NOLINT
	/**\endcond*/
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

/**
	\file proxy_stack_helper.h
	\brief Helpers for the DSL which are allowed to do things the Public API
	is not.
*/
#ifndef OOLUA_PROXY_STACK_HELPER_H_
#	define OOLUA_PROXY_STACK_HELPER_H_


#	include <cassert>

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace
	{
		/*
			Member functions are allowed to do things which are not allowed when using
			the public API function OOLUA::push:
				\li Pushing a instance which has a Proxy_class using a value or reference
					instead of a pointer.
				\li Pushing an integral type by pointer
		*/
		template<typename Raw, typename T, int is_by_value = 0 >
		struct proxy_maybe_by_ref
		{
			static void push(lua_State* const vm, T& value, Owner owner)
			{
				OOLUA::INTERNAL::push_pointer_which_has_a_proxy_class<Raw>(vm, &value, owner);
			}
		};

		template<typename Raw, typename T>
		struct proxy_maybe_by_ref<Raw, T, 1>
		{
			static void push(lua_State* const vm, T& value, Owner /*owner*/)
			{
				typename OOLUA::INTERNAL::new_pointer<Raw>::type ptr(new Raw(value));
				OOLUA::INTERNAL::add_ptr(vm, ptr, false, Lua);
			}
		};


		template<typename T, typename WT, int is_integral = 1>
		struct maybe_integral
		{
			static void push(lua_State* const vm, T& value)
			{
				OOLUA::push(vm, value);
			}
		};

		//user defined type
		template<typename T, typename WT>
		struct maybe_integral<T, WT, 0>
		{
			static void push(lua_State* const vm, T& value)
			{
				proxy_maybe_by_ref<typename WT::raw, T, WT::is_by_value>::push(vm, value, (Owner)WT::owner);
			}
		};

		template<typename T>
		struct add_ref
		{
			typedef T& type;
		};

		template<typename T>
		struct add_ref<T&>
		{
			typedef T& type;
		};
	} // namespace //NOLINT
	/** \endcond */

	/** \cond INTERNAL */
	namespace INTERNAL
	{

		/**
			\brief Handles the pushing and pulling of types for member functions
			\tparam TypeWithTraits The wanted which is being exchanged with the stack. with
			traits applied to it.
			\tparam owner One of OOLUA::Owner entries which indicate which language owns the type
		*/
		template<typename TypeWithTraits, int owner>
		struct Proxy_stack_helper;

		/*
		Specialisation for the light_return type.
		*/
		template<typename LightUdType>
		struct Proxy_stack_helper<light_return<LightUdType>, No_change>
		{
			static void push(lua_State* vm, LightUdType ptr)
			{
				OOLUA::push(vm, static_cast<void*>(ptr));
			}
		};

		/*
		Specialisation for the light_p parameter type.
		*/
		template<typename LightUdType>
		struct Proxy_stack_helper<light_p<LightUdType>, No_change>
		{
			static void get(lua_State* const vm, int idx, void*& value)
			{
				OOLUA::INTERNAL::LUA_CALLED::get(vm, idx, value);
			}
			static void get(int& idx, lua_State* const vm, void*& value)
			{
				get(vm, idx, value);
				++idx;
			}
			static void push(lua_State* /*vm*/, void* /*ptr*/) // NOLINT(readability/casting)
			{
				assert(0 && "this function should not be called");
			}
		};

		/*
		Specialisation for the maybe_null type.
		If NULL it pushes nil to the stack else calls the normal helper static function.
		*/
		template<typename MaybeNullType>
		struct Proxy_stack_helper<maybe_null<MaybeNullType>, No_change>
		{
			static void push(lua_State* vm, typename add_ref<typename maybe_null<MaybeNullType>::type>::type ptr)
			{
				if (ptr)
					Proxy_stack_helper<typename maybe_null<MaybeNullType>::return_trait, No_change>::push(vm, ptr);
				else
					lua_pushnil(vm);
			}
		};

		/*
		Specialisation for the maybe_null<lua_return<T> > type.
		If NULL it pushes nil to the stack else calls the normal helper static function.
		*/
		template<typename MaybeNullType>
		struct Proxy_stack_helper<maybe_null<lua_return<MaybeNullType> >, Lua>
		{
			static void push(lua_State* vm, MaybeNullType ptr)
			{
				if (ptr)
					Proxy_stack_helper<lua_return<MaybeNullType>, Lua>::push(vm, ptr);
				else
					lua_pushnil(vm);
			}
		};


		template<typename PtrType>
		struct Proxy_stack_helper<shared_return<PtrType>, No_change>
		{
			static void push(lua_State* vm, PtrType ptr)
			{
#if OOLUA_USE_SHARED_PTR == 1
				OOLUA_SHARED_TYPE<typename LVD::remove_ptr<PtrType>::type > shared(ptr);
				OOLUA::push(vm, shared);
#else
				assert(0 && "this is only valid when the library is compiled with"
						"shared pointer support");
#endif
			}
		};

		template<typename TypeWithTraits>
		struct Proxy_stack_helper<TypeWithTraits, No_change>
		{
			template<typename T>
			static void get(lua_State* const vm, int idx, T& value)
			{
				OOLUA::INTERNAL::LUA_CALLED::get(vm, idx, value);
			}

			template<typename T>
			static void get(int& idx, lua_State* const vm, T& value)
			{
				get(vm, idx, value);
				++idx;
			}

			static void get(lua_State* const vm, int /*idx*/, lua_State*& vm1)
			{
				typedef char type_has_to_be_calling_lua_state[LVD::is_same<in_p<calling_lua_state>, TypeWithTraits>::value ? 1 : -1] OOLUA_UNUSED;
				vm1 = vm;
			}

			static void get(int& /*idx*/, lua_State* const vm, lua_State*& vm1)
			{
				typedef char type_has_to_be_calling_lua_state[LVD::is_same<in_p<calling_lua_state>, TypeWithTraits>::value ? 1 : -1] OOLUA_UNUSED;
				vm1 = vm;
			}

			template<typename T>
			static void push(lua_State* const vm, T& value)
			{
				maybe_integral<T, TypeWithTraits, TypeWithTraits::is_integral>::push(vm, value);
			}

			template<typename T>
			static void push(lua_State* const vm, T*& value)
			{
				OOLUA::push(vm, value, No_change);
			}

			///special case "T* const" and "T const * const"
			template<typename T>
			static void push(lua_State* const vm, T*const& value)
			{
				OOLUA::push(vm, value, No_change);
			}

			static void push(lua_State* const , lua_State *& )
			{
				assert(0 && "this function should not be called");
			}
		};

		template<typename TypeWithTraits>
		struct Proxy_stack_helper<TypeWithTraits, Cpp>
		{
			template<typename T>
			static void get(lua_State* const vm, int idx, T*& value)
			{
				OOLUA::cpp_acquire_ptr<typename TypeWithTraits::type > p;
				OOLUA::INTERNAL::LUA_CALLED::get(vm, idx, p);
				value = p.m_ptr;
			}

			template<typename T>
			static void get(int& idx, lua_State* const vm, T*& value)
			{
				get(vm, idx, value);
				++idx;
			}

			template<typename T>
			static void push(lua_State* const /*s*/, T*& /*value*/)//noop
			{
				assert(0 && "this function should never be called");
			}
		};

		template<typename TypeWithTraits>
		struct Proxy_stack_helper<TypeWithTraits, Lua>
		{
			template<typename T>
			static void push(lua_State* const vm, T*& value)
			{
				OOLUA::lua_acquire_ptr<typename TypeWithTraits::type> p(value);
				OOLUA::push(vm, p);
			}

			template<typename T>
			static void push(lua_State* const vm, T& value)
			{
				proxy_maybe_by_ref<typename TypeWithTraits::raw
								, T
								, TypeWithTraits::is_by_value>
							::push(vm, value, (Owner)TypeWithTraits::owner);
			}

			template<typename T>
			static void get(lua_State* const /*s*/, int /*idx*/, T*& /*value*/)//noop
			{
				assert(0 && "this function should never be called");
			}

			template<typename T>
			static void get(int& /*idx*/,lua_State* const /*s*/,  T& /*value*/)//noop
			{
				assert(0 && "this function should never be called");
			}
		};

	} // namespace INTERNAL //NOLINT
	/** \endcond */
} // namespace OOLUA

#endif //OOLUA_PROXY_STACK_HELPER_H_
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

#ifndef PROXY_CALLER_H_
#	define PROXY_CALLER_H_

/**
	\file proxy_caller.h
	\brief Provides implementations which actually call the member or stand
	alone function, it also pushes a function return to the stack if the
	fubction has one.
*/


#if	OOLUA_USE_EXCEPTIONS ==1

#	define OOLUA_NONE_MEMBER_CATCH_RESPONSE(exception_type, what_message) \
		luaL_error(vm, "Type of exception: %s.\n what(): %s.\n When calling function on C function\n" \
					, exception_type \
					, what_message);

#	define OOLUA_NONE_MEMBER_FUNCTION_TRY \
	try \
	{ /*start try block*/
// NOLINT

#	define OOLUA_NONE_MEMBER_FUNCTION_CATCH \
	} /*end try block */ \
	catch(std::exception const& e) \
	{ \
		OOLUA_NONE_MEMBER_CATCH_RESPONSE("std::exception", e.what()) \
	} \
	catch(...) \
	{ \
		OOLUA_NONE_MEMBER_CATCH_RESPONSE("Unknown type", " ") \
	}
#else
#	define OOLUA_NONE_MEMBER_FUNCTION_TRY
#	define OOLUA_NONE_MEMBER_FUNCTION_CATCH (void)vm;
#endif


/** \cond INTERNAL*/
/**	\addtogroup OOLuaGeneratorTemplates
@{*/

/**	\def OOLUA_INTERNAL_MEMBER_CALLER_NUM
	\hideinitializer
	\param NUM
*/
#	define OOLUA_INTERNAL_MEMBER_CALLER_NUM(NUM) \
	template<typename FuncType  OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
	static void call(lua_State* const vm, C* m_this, FuncType ptr2mem OOLUA_PULL_TYPE_PARAMS_##NUM) \
	{ \
		OOLUA_CONVERTER_##NUM \
		typename R::type r( (m_this->*ptr2mem)(OOLUA_CONVERTER_PARAMS_##NUM) ); \
		Proxy_stack_helper<typename R::traits, R::owner>::push(vm, r); \
	}

/**	\def OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM
	\hideinitializer
	\param NUM
*/
#	define OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM(NUM) \
	template<typename FuncType  OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
	static void call(lua_State* const /*vm*/, C* m_this, FuncType ptr2mem OOLUA_PULL_TYPE_PARAMS_##NUM) \
	{ \
		OOLUA_CONVERTER_##NUM \
		(m_this->*ptr2mem)(OOLUA_CONVERTER_PARAMS_##NUM); \
	}

/**	\def OOLUA_INTERNAL_C_CALLER_NUM
	\hideinitializer
	\param NUM
*/
#	define OOLUA_INTERNAL_C_CALLER_NUM(NUM) \
	template<typename FuncType  OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
	static void call(lua_State* const vm, FuncType ptr2func OOLUA_PULL_TYPE_PARAMS_##NUM) \
	{ \
		OOLUA_CONVERTER_##NUM \
		OOLUA_NONE_MEMBER_FUNCTION_TRY \
			typename R::type r( (*ptr2func)(OOLUA_CONVERTER_PARAMS_##NUM) ); \
			Proxy_stack_helper<typename R::traits, R::owner>::push(vm, r); \
		OOLUA_NONE_MEMBER_FUNCTION_CATCH \
	}

/**	\def OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM
	\hideinitializer
	\param NUM
*/
#	define OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM(NUM) \
	template<typename FuncType  OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
	static void call(lua_State* const vm, FuncType ptr2func OOLUA_PULL_TYPE_PARAMS_##NUM) \
	{ \
		OOLUA_CONVERTER_##NUM \
		OOLUA_NONE_MEMBER_FUNCTION_TRY \
			(*ptr2func)(OOLUA_CONVERTER_PARAMS_##NUM); \
		OOLUA_NONE_MEMBER_FUNCTION_CATCH \
	}

/** @}*/

namespace OOLUA
{
	namespace INTERNAL
	{

		/**
			\struct Proxy_caller
			\tparam Return
			\tparam Class
			\tparam ReturnIsVoid
		*/
		template <typename Return, typename Class, int ReturnIsVoid>
		struct Proxy_caller;

		/**
			\struct Proxy_none_member_caller
			\tparam Return
			\tparam ReturnIsVoid
		*/
		template <typename Return, int ReturnIsVoid>
		struct Proxy_none_member_caller;

		template <typename R, typename C>
		struct Proxy_caller<R, C, 0 >
		{
			OOLUA_INTERNAL_MEMBER_CALLER_FUNCS
		};

		template <typename R, typename C>
		struct Proxy_caller<R, C, 1 >
		{
			OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_FUNCS
		};

		template <typename R>
		struct Proxy_none_member_caller<R, 0 >
		{
			OOLUA_INTERNAL_C_CALLER_FUNCS
		};

		template <typename R >
		struct Proxy_none_member_caller<R, 1 >
		{
			OOLUA_INTERNAL_C_CALLER_NO_RETURN_FUNCS
		};

	} // namespace INTERNAL // NOLINT
} // namespace OOLUA

#undef OOLUA_INTERNAL_MEMBER_CALLER_NUM
#undef OOLUA_INTERNAL_MEMBER_CALLER_NO_RETURN_NUM
#undef OOLUA_INTERNAL_C_CALLER_NUM
#undef OOLUA_INTERNAL_C_CALLER_NO_RETURN_NUM
#undef OOLUA_NONE_MEMBER_FUNCTION_TRY
#undef OOLUA_NONE_MEMBER_FUNCTION_CATCH
#undef OOLUA_NONE_MEMBER_CATCH_RESPONSE

/**\endcond */
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

#ifndef DEFAULT_TRAIT_CALLER_H_
#	define DEFAULT_TRAIT_CALLER_H_

/** \cond INTERNAL*/

/**
	\file default_trait_caller.h
	\brief Default trait callers for member functions which are constant or non constant member, in
	addition to C functions.
*/

struct lua_State;

namespace OOLUA
{
	namespace INTERNAL
	{
		/*Two structures are used here instead of one and specialising so that compile
		 errors are forced instead of a runtime error when an incorrect macro is used */
		/**
			\struct default_traits_caller
			\brief Caller for non constant member function using default traits.
			\details Determines the function return type and parameters for
			\ref OOLuaMinimalist "Minimalist" DSL usage. No traits can be provided by a user
			and it will instead use default traits, which are OOLUA::in_p for parameters
			and OOLUA::INTERNAL::function_return for the return type.
			\tparam func_type Specialiased function pointer type
			\tparam type None type template argument
		*/
		template<typename func_type, typename type = func_type>
		struct default_traits_caller;

		/**
			\struct default_traits_const_caller
			\brief Determines the function return type and parameters for
			\ref OOLuaMinimalist "Minimalist"  DSL usage
			\tparam func_type Specialised constant member function pointer type
			\tparam type Non type template argument
		*/
		template<typename func_type, typename type = func_type>
		struct default_traits_const_caller;

		/**
			\struct default_c_traits_caller
			\brief Determines the function return type and parameters for
			\ref OOLuaMinimalist "Minimalist" DSL usage.
			\tparam func_type Specialised function pointer type
			\tparam type Non type template argument
		*/
		template<typename func_type, typename type = func_type>
		struct default_c_traits_caller;

		template<typename this_type, typename func_type>
		int proxy_member_function_with_default_traits(lua_State* vm, this_type* this_, func_type mfptr)
		{
			return default_traits_caller<func_type>::call(vm, this_, mfptr);
		}

		template<typename this_type, typename func_type>
		int constproxy_member_function_with_default_traits(lua_State* vm, this_type* this_, func_type mfptr)
		{
			return default_traits_const_caller<func_type>::call(vm, this_, mfptr);
		}

		template<typename func_type>
		int proxy_c_function_with_default_traits(lua_State* vm, func_type fptr)
		{
			return default_c_traits_caller<func_type>::call(vm, fptr);
		}
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA


/** \addtogroup OOLuaGeneratorTemplates
@{*/
/**
	\def OOLUA_GENERATE_DEFAULT_TRAIT_CALLER
	\hideinitializer
	\brief Generator template to produce default trait callers
	\details Template for OOLUA::INTERNAL::default_traits_caller which produces
	a static method call for class member and non member functions.
	\param NUM Number of parameters the macro will generate a default traits caller for.
*/
#define OOLUA_GENERATE_DEFAULT_TRAIT_CALLER(NUM) \
namespace OOLUA \
{ \
	namespace INTERNAL \
	{ \
		template <class class_type, typename return_type OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM , typename func_type> \
		struct default_traits_caller<return_type (class_type::*)(OOLUA_COMMA_SEPERATED_TYPES_##NUM), func_type> \
		{ \
			typedef OOLUA::INTERNAL::return_type_traits<return_type > R; \
			static int call(lua_State* vm, class_type* this_, func_type mfptr) \
			{ \
				OOLUA_PARAMS_DEFAULT_INTERNAL_##NUM(1) \
				OOLUA::INTERNAL::Proxy_caller<R, class_type, LVD::is_void<return_type > ::value >:: \
					template call<func_type OOLUA_COMMA_PREFIXED_PARAM_TYPES_##NUM > \
						(vm, this_, mfptr OOLUA_CALL_PARAMS_##NUM); \
				return R::out; \
			} \
		}; \
		template <class class_type, typename return_type OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM , typename func_type> \
		struct default_traits_const_caller<return_type (class_type::*)(OOLUA_COMMA_SEPERATED_TYPES_##NUM)const, func_type> \
		{ \
			typedef OOLUA::INTERNAL::return_type_traits<return_type > R; \
			static int call(lua_State* vm, class_type* this_, func_type mfptr) \
			{ \
				OOLUA_PARAMS_DEFAULT_INTERNAL_##NUM(1) \
				OOLUA::INTERNAL::Proxy_caller<R, class_type, LVD::is_void<return_type >::value >\
					:: template call<func_type OOLUA_COMMA_PREFIXED_PARAM_TYPES_##NUM > \
						(vm, this_, mfptr OOLUA_CALL_PARAMS_##NUM); \
				return R::out; \
			} \
		}; \
		template <typename return_type OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM , typename func_type> \
		struct default_c_traits_caller<return_type (*)(OOLUA_COMMA_SEPERATED_TYPES_##NUM), func_type> \
		{ \
			typedef OOLUA::INTERNAL::return_type_traits<return_type > R; \
			static int call(lua_State* vm, func_type fptr) \
			{ \
				OOLUA_PARAMS_DEFAULT_INTERNAL_##NUM(0) \
				OOLUA::INTERNAL::Proxy_none_member_caller< R, LVD::is_void<return_type >::value >:: \
					template call<func_type OOLUA_COMMA_PREFIXED_PARAM_TYPES_##NUM > \
						(vm, fptr OOLUA_CALL_PARAMS_##NUM); \
				return R::out; \
			} \
		};\
	}/* namespace INTERNAL*/ /*NOLINT*/ \
}/* namespace OOLUA*/
/**@}*/

OOLUA_GENERATE_DEFAULT_TRAIT_CALLERS

/** \endcond */

#endif
/**
	\file oolua.h
	\brief Kitchen sink header file for Object Oriented Lua. Which could be a good
	candidate for a PCH.
*/

/**
	\mainpage
	\section OOLuaIntroduction Introduction
	OOLua is cross platform, test driven, dependency free and Open Source library. It uses C++03
	template meta-programming and pre-processor magic internally, which can be used to generate
	non intrusive proxies that provide a fast bridge for the interaction of C++ classes and functions
	with Lua.
	<p>
	The library provides multiple inheritance C++ classes without using C++'s RTTI,
	can be compiled either with or without exception support and is easily configurable.
	OOLua also provides a thin and simple abstraction layer for interfacing with the Lua stack and
	types in a type safe manner, whilst also supporting a means to bypass the type safety using the Lua
	light userdata type. The library can be use in a pick and mix fashion or in its entirety, whilst
	still using the Lua C API.

	OOLua is developed by Liam Devine who has over ten years experience using the Lua programming
	language, having what he considers to be a deep understanding of both it and also C++.

	This is not a fully original work and was originally based on ideas from binding classes using
	the famous <a href="http://lua-users.org/wiki/CppBindingWithLunar" target="_blank">Lunar</a>
	and <a href="http://www.lua.org/notes/ltn005.html" target="_blank">Lua Technical Note 5</a>.

	\section OOLuaCompatibility Lua compatibility
	This version of the library is compatible with the following Lua implementations
		\li Rio Lua 5.1, 5.2 and 5.3 http://www.lua.org
		\li LuaJIT 1.1.8 and 2.0 http://www.luajit.org/

	\section OOLuaLinks Links
		\li Project Home  https://oolua.org
		\li Library documentation https://docs.oolua.org/2.0.1
		\li Issue tracker https://oolua.org/issues
		\li Mailing list https://oolua.org/mailinglist

	\section OOLuaLicence Licence
	OOLua:
	\copyright
	The MIT License\n
	Copyright (c) 2009 - 2015 Liam Devine\n
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:\n
 	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.\n\n
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.\n

	Loki Type lists:
	\copydetails type_list.h

	Luna :
	\copydetails oolua_registration.h
*/


#ifndef OOLUA_H_
#	define OOLUA_H_



/**
	\namespace OOLUA
	\brief This is the root namespace of the Library
	\details There are sub namespaces contained in OOLUA yet mostly these are not
	meant for general usage, instead this namespace contains all Public API functions,
	structures etc.
*/
namespace OOLUA
{
	/**
		\brief Helper function to set a Lua global variable.
		\tparam T Type for instance
		\param[in] vm lua_State
		\param[in] name Global name to set
		\param[in] instance Any variable which is valid to push to the stack
		\return Boolean indicating if the operation was successful \see OOLuaErrorReporting
	*/
	template<typename T>
	bool set_global(lua_State* vm, char const* name, T& instance)
	{
		if ( !OOLUA::push(vm, instance) ) return false;
		lua_setglobal(vm, name);
		return true;
	}

	/**
		\brief None template version
		\details Enables setting a global with a value of lua_CFunction without
		requiring you make a reference to the function.
		\param[in] vm The lua_State to work on
		\param[in] name String which is used for the global name
		\param[in] instance The lua_CFuntion which will be set at the global value for name
	*/
	bool set_global(lua_State* vm, char const* name, lua_CFunction instance);

	/**
		\brief Helper function to set a Lua global variable to nil.
		\param[in] vm lua_State
		\param[in] name Global name to set
	*/
	void set_global_to_nil(lua_State* vm, char const * name);

	/**
		\brief Helper function to set a Lua global variable.
		\tparam T Type for instance
		\param[in] vm lua_State
		\param[in] name Global name to query
		\param[out] instance Any variable which is valid to pull from the stack
		\return Boolean indicating if the operation was successful \see OOLuaErrorReporting
	*/
	template<typename T>
	bool get_global(lua_State* vm, char const* name, T& instance)
	{
		lua_getglobal(vm, name);
		return OOLUA::pull(vm, instance);
	}

} // namespace OOLUA

#endif //OOLUA_H_
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

#ifndef OOLUA_CHECK_RESULT_H_
#   define OOLUA_CHECK_RESULT_H_

struct lua_State;

namespace OOLUA
{
	namespace INTERNAL
	{
		bool protected_call_check_result(lua_State* vm, int pcall_result);
		bool load_buffer_check_result(lua_State* vm, int result);
	} // namespace INTERNAL
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

/**
	\file oolua_chunk.h
	\brief Provides methods for loading and running chunks.
*/
#ifndef OOLUA_CHUNK_H_
#	define OOLUA_CHUNK_H_

#	include <string>

struct lua_State;

namespace OOLUA
{
	/** \brief Loads a chunk leaving the resulting function on the stack
		\param[in] vm \copydoc lua_State
		\param[in] chunk
	*/
	bool load_chunk(lua_State* vm, std::string const& chunk);

	/** \brief Loads and runs a chunk of code
		\param[in] vm \copydoc lua_State
		\param[in] chunk
	*/
	bool run_chunk(lua_State* vm, std::string const& chunk);

	/** \brief Loads a file leaving the resulting function on the stack
		\param[in] vm \copydoc lua_State
		\param[in] filename
	 */
	bool load_file(lua_State* vm, std::string const & filename);

	/** \brief Loads and runs the file
		\param[in] vm \copydoc lua_State
		\param[in] filename
	*/
	bool run_file(lua_State* vm, std::string const & filename);

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

/**
	\file oolua_dsl.h
	\brief Header which provides only what is needed for a class to be proxied using
	the DSL.
*/
#ifndef OOLUA_DSL_H_
#	define OOLUA_DSL_H_




#endif //OOLUA_DSL_H_
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
	\file oolua_dsl_export.h
	\brief Header to be used in conjunction with oolua_dsl.h when exporting proxies
	using the DSL.
*/
#ifndef OOLUA_DSL_EXPORT_H_
#	define OOLUA_DSL_EXPORT_H_


#endif //OOLUA_EXPORTS_H_
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
	\@file oolua_ref.h
	\detailsA wrapper for a lua registry reference in a struct
	so that the type is different to an int. Typedefs two types Lua_table_ref & \n
	Lua_ref.
*/

#ifndef OOLUA_REF_H_
#	define OOLUA_REF_H_


#ifdef __GNUC__
#	define OOLUA_DEFAULT __attribute__ ((visibility("default")))
#else
#	define OOLUA_DEFAULT
#endif

namespace OOLUA
{
	class Table;

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		void pull_handle_invalid(lua_State* const vm, int id);
		bool push_reference_if_possible(int const ref, lua_State* const from, lua_State* const to);
	}//namespace INTERNAL //NOLINT
	/** \endcond */

	bool can_xmove(lua_State* vm0, lua_State* vm1);

//TODO consider renaming to OOLUA::Ref

	/**	\struct Lua_ref
		\brief A typed wrapper for a Lua reference
		\details
		The Lua_ref templated class stores a reference using Lua's reference system
		luaL_ref and luaL_unref, along with a lua_State. The reason this class stores
		the lua_State is to make it difficult to use the reference with another universe.
		A reference from the same Lua universe, even if it is from a different lua_State,
		is valid to be used in the universe.
		<p>
		The class takes ownership of any reference passed either to the
		\ref OOLUA::Lua_ref::Lua_ref(lua_State* const,int const&) "two argument constructor"
		or the \ref OOLUA::Lua_ref::set_ref "set_ref" function. On going out of scope
		a \ref OOLUA::Lua_ref::valid "valid" reference is guaranteed to be released,
		you may also force a release by passing an instance to \ref OOLUA::Lua_ref::swap
		"swap" for which \ref OOLUA::Lua_ref::valid "valid" returns false.
		<p>
		There are two special values for the reference which Lua provides,
		both of which OOLua will treat as an invalid reference:
			\li LUA_REFNIL luaL_ref return value to indicate it encountered a
				nil object at the location the ref was asked for
			\li LUA_NOREF guaranteed to be different from any reference return
				by luaL_ref
		\tparam ID Lua type as returned by lua_type
		\note
			\li Universe: A call to luaL_newstate or lua_newstate creates a
		Lua universe and a universe is completely independent of any other
		universe. lua_newthread and coroutine.create, create a lua_State
		in an already existing universe.\n
		Term first heard in a Lua mailing list post by Mark Hamburg.
	*/
	template<int ID>
	struct Lua_ref
	{
		/**
			\brief
			Initialises the instance so that a call to valid will return false.
		 */
		Lua_ref();

		/**
			\brief
			Sets the lua_State and reference for the instance
			\note This does not preform any validation on the parameters and it
			is perfectly acceptable to pass parameters such that a call to
			valid will return false.
			\param[in] vm lua_State for which the ref is coupled with.
			\param[in] ref Registry reference or registry special value for this instance.
		*/
		Lua_ref(lua_State* const vm, int const& ref);

		/**
			\brief
			Sets the lua_State for the instance and initialises the instance
			so that a call to valid will return false.
			\param[in] vm lua_State for which this instance is coupled with.
		*/
		explicit Lua_ref(lua_State* const vm);

		/**
			\brief
			Creates a copy of rhs
			\details
			If rhs is valid then creates a new Lua reference to the value which rhs
			refers to, otherwise it initialises this instance so that a \ref Lua_ref::valid
			call returns false.
			\param[in] rhs Reference for which this instance will initialise its internal state from.
		 */
		Lua_ref(Lua_ref const& rhs) OOLUA_DEFAULT;

		/**
			\brief
			Destructor which releases a valid reference, removing the value from the registry
		*/
		~Lua_ref()OOLUA_DEFAULT;

		/**@{*/
		/**
			\brief
			Compares this instance reference with the right hand side operand using lua_rawequal.
			\param[in] rhs Right hand side operand for the operator.
			\details An invalid reference compares equal with any other invalid reference
			regardless of the lua_State members. This operator can produce different results for
			Lua versions 5.1 and 5.2. In the latter pushing the same C function twice to the
			stack using lua_pushcclosure and then comparing them will return true, yet in 5.1
			this will return false.
			\return bool Result of the comparison.
		*/
		bool operator == (Lua_ref const& rhs) const;

		/**
			\brief
			Makes this instance a copy of rhs.
			\param[in] rhs The instance to make a copy of
			\note Even self assignment makes a copy, yet it will refer to the same
			actual Lua instance. It doesn't seem correct for every assignment to pay for
			a branch just to keep the internal reference id the same.
		*/
		Lua_ref& operator = (Lua_ref const& rhs);

		/**
			\brief
			Swaps the Lua instance and the registry reference with rhs.
			\details
			Swaps the lua_State and reference with rhs, this is a
			simple swap and does not call luaL_ref therefore it will not
			create any new references.
			\param[inout] rhs Reference which will re-initialise this instance's state and which
				will receive the internal state of this instance as it was before the swap.
		*/
		void swap(Lua_ref& rhs);
		/**@}*/

		/**
			\brief
			Returns true if both the Lua instance is not NULL and the registry reference
			is not invalid.
		*/
		bool valid()const;

		/**
			\brief
			Returns the lua_State associated with the Lua reference.
		*/
		lua_State* state() const { return m_lua; }

		/**
			\brief
			Returns the integer Lua registry reference value.
		*/
		int const& ref()const;

		/**
			\brief
			Sets the stored reference and state.
			\details
			Releases any currently stored reference and takes ownership of the passed
			reference.
			\param[in] vm lua_State to associated the reference with.
			\param[in] ref Registry reference id for which the instance takes ownership of.
		*/
		void set_ref(lua_State* const vm, int const& ref)OOLUA_DEFAULT;


		/** \cond INTERNAL*/
		bool push(lua_State* const vm)const;
		bool pull(lua_State* const vm) OOLUA_DEFAULT;
		bool lua_push(lua_State* const vm)const;
		bool lua_get(lua_State* const vm, int idx);
		/** \endcond*/
	private:
		/** \cond INTERNAL Yes I know this is bad \endcond*/
		friend class Table;
		bool pull_if_valid(lua_State* vm);
		void release();
		lua_State* m_lua;
		int m_ref;
	};

	/** \cond INTERNAL*/
	template<int ID>
	Lua_ref<ID>::Lua_ref(lua_State* const vm, int const& ref)
		: m_lua(vm)
		, m_ref(ref)
	{}

	template<int ID>
	Lua_ref<ID>::Lua_ref(lua_State* const vm)
		: m_lua(vm)
		, m_ref(LUA_NOREF)
	{}

	template<int ID>
	Lua_ref<ID>::Lua_ref()
		: m_lua(0)
		, m_ref(LUA_NOREF)
	{}

	template<int ID>
	Lua_ref<ID>::Lua_ref(Lua_ref<ID> const& rhs)
		: m_lua(0)
		, m_ref(LUA_NOREF)
	{
		if (rhs.valid())
		{
			m_lua = rhs.m_lua;
			lua_rawgeti(m_lua, LUA_REGISTRYINDEX, rhs.m_ref);
			m_ref = luaL_ref(m_lua, LUA_REGISTRYINDEX);
		}
	}

	template<int ID>
	Lua_ref<ID>::~Lua_ref()
	{
		release();
	}

	template<int ID>
	Lua_ref<ID>& Lua_ref<ID>::operator = (Lua_ref<ID> const& rhs)
	{
		Lua_ref<ID> temp(rhs);
		temp.swap(*this);
		return *this;
	}

	template<int ID>
	inline bool Lua_ref<ID>::operator == (Lua_ref<ID> const& rhs) const
	{
		if (!valid() || !rhs.valid()) return valid() == rhs.valid();
		else if (m_lua == rhs.state() || can_xmove(m_lua, rhs.state()))
		{
			lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_ref);
			lua_rawgeti(m_lua, LUA_REGISTRYINDEX, rhs.m_ref);
			bool const result = !!lua_rawequal(m_lua, -1, -2);
			lua_pop(m_lua, 2);
			return result;
		}
		return false;
	}


	template<int ID>
	bool Lua_ref<ID>::valid()const
	{
		return m_lua && m_ref != LUA_REFNIL && m_ref != LUA_NOREF;
	}

	template<int ID>
	int const& Lua_ref<ID>::ref()const
	{
		return m_ref;
	}

	template<int ID>
	inline void Lua_ref<ID>::set_ref(lua_State* const vm, int const& ref)
	{
		release();
		m_ref = ref;
		m_lua = vm;
	}

	template<int ID>
	void Lua_ref<ID>::release()
	{
		if( valid() )
		{
			luaL_unref(m_lua, LUA_REGISTRYINDEX, m_ref);
		}
		m_ref = LUA_NOREF;
	}

	template<int ID>
	void Lua_ref<ID>::swap(Lua_ref & rhs)
	{
		lua_State* tl(rhs.m_lua);
		int tr(rhs.m_ref);
		rhs.m_lua = m_lua;
		rhs.m_ref = m_ref;
		m_lua = tl;
		m_ref = tr;
	}

	template<int ID>
	bool Lua_ref<ID>::push(lua_State* const vm)const
	{
		if( !valid() )
		{
			lua_pushnil(vm);
			return true;
		}
		return  INTERNAL::push_reference_if_possible(m_ref, m_lua, vm)
					&& lua_type(vm, -1) == ID;
	}

	template<int ID>
	bool Lua_ref<ID>::lua_push(lua_State* const vm)const
	{
		if ( !valid() )
		{
			lua_pushnil(vm);
			return true;
		}
		else if ( vm != m_lua )
		{
			luaL_error(vm, "The reference is not valid for this Lua State");
			return false;
		}
		lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_ref);
		return  lua_type(m_lua, -1) == ID;
	}

	template<int ID>
	bool Lua_ref<ID>::pull_if_valid(lua_State* const vm)
	{
		if (lua_gettop(vm) == 0)  return false;
		const int type = lua_type(vm, -1);
		if( type == ID )
		{
			set_ref(vm, luaL_ref(vm, LUA_REGISTRYINDEX) );
			return true;
		}
		else if ( type == LUA_TNIL )
		{
			release();
			return true;
		}
		return false;
	}

	template<int ID>
	bool Lua_ref<ID>::pull(lua_State* const vm)
	{
		if( !pull_if_valid(vm) )
		{
			INTERNAL::pull_handle_invalid(vm, ID);
			return false;
		}
		return true;
	}

	template<int ID>
	bool Lua_ref<ID>::lua_get(lua_State* const vm, int idx)
	{
#define oolua_err_get() \
		luaL_error(vm \
			, "pulling incorrect type from stack. This is a ref to id %d, stack contains %s" \
			, ID \
			, lua_typename(vm, lua_type(vm, idx)) \
		); /*NOLINT*/ \
		return false/*never gets here*/


		if (lua_gettop(vm) < idx) { oolua_err_get(); }
		const int type = lua_type(vm, idx);
		if( type == ID )
		{
			lua_pushvalue(vm, idx);
			set_ref(vm, luaL_ref(vm, LUA_REGISTRYINDEX));
			return true;
		}
		else if ( type == LUA_TNIL )
		{
			release();
			return true;
		}
		oolua_err_get();
#undef oolua_err_get
	}
	/** \endcond*/

	/** \typedef Lua_table_ref
		\brief Typedef helper for a LUA_TTABLE registry reference
	 */
	typedef Lua_ref<LUA_TTABLE> Lua_table_ref;
	/** \typedef Lua_func_ref
		\brief Typedef helper for a LUA_TFUNCTION registry reference
	*/
	typedef Lua_ref<LUA_TFUNCTION> Lua_func_ref;

} // namespace OOLUA

#endif //OOLUA_REF_H_
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
	\file oolua_function.h
	\brief Provides the class OOLUA::Lua_function which is a helper for calling
	Lua functions.
*/

#ifndef OOLUA_FUNCTION_H_
#	define OOLUA_FUNCTION_H_

#	include <string>

namespace OOLUA
{

/** \cond INTERNAL */
#if OOLUA_USE_EXCEPTIONS == 1
#	define OOLUA_CALLER_TRY \
	try \
	{
#	define OOLUA_CALLER_HANDLE_FAIL \
	} \
	catch(...) \
	{ \
		lua_settop(m_lua, top); \
		throw; \
	} \
	return false; /*Shhhhhhhhhh*/
#else
#	define OOLUA_CALLER_TRY
#	define OOLUA_CALLER_HANDLE_FAIL \
	lua_settop(m_lua, top); \
	return false;
#endif

/**
	\addtogroup OOLuaGeneratorTemplates
	@{
*/
/**
	\brief Generates an OOLUA::Lua_function call operator
	\hideinitializer
	\param NUM Number of parameters for which it the template will generate the operator for
*/
#define OOLUA_INTERNAL_FUNC_OPERATOR(NUM) \
	template<typename FUNC_TYPE OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
	bool operator()(FUNC_TYPE const& func OOLUA_FCALL_PARAM_##NUM) \
	{ \
		int error_index(0); \
		const int top = get_top(); \
		OOLUA_CALLER_TRY \
		if( prep_function(func, NUM, error_index) \
				OOLUA_FCALL_PUSH_##NUM \
		) return call(NUM, error_index); \
		OOLUA_CALLER_HANDLE_FAIL \
	}
/**@}*/
/** \endcond */





/**
	\struct Lua_function
	\brief Structure which is used to call a Lua function.
	\details
	Calling a Lua function, from C++ code using OOLua's API, can be achieved using a
	\ref OOLUA::Lua_function "Lua_function" object. This is a state bound caller,
	and the state in which the callee will be invoked is specified either in the
	\ref OOLUA::Lua_function::Lua_function(lua_State*) "constructor" or via the
	\ref OOLUA::Lua_function::bind_script "bind_script" member function.

	To invoke a callee, the \ref OOLUA::Lua_function type uses a call operator. The operator's
	first parameter must be the callee and it can be specified using one of the following types:
		\li std::string A function in the bound state's global table
		\li \ref OOLUA::Lua_func_ref A reference to a function
		\li int A valid stack index
	If the callee is identified via a valid stack index, then this index will remain on
	the stack at same absolute location after the caller has returned.

 	The call operator is also overloaded to enable the passing of parameters to the callee;
 	the maximum number of parameters is defined by the configurable value
 	\ref OOLuaConfigLuaParams "\"lua_params\"".
*/
	struct Lua_function
	{
		/** \brief Default constructor initialises the object
			\post Any call to a function call operator will cause
			an error until a lua_State is bound via \ref bind_script
		*/
		Lua_function();
		/** \brief Binds the state vm to this instance */
		Lua_function(lua_State* vm); // NOLINT Let OOLUA::Script decay to pointer

		/**@{*/
		/**
			\brief Function call operator
			\return Result indicating success
			\tparam FUNC_TYPE
			\see \ref OOLuaErrorReporting
			*/
			OOLUA_INTERNAL_FUNC_OPERATORS
		/**@}*/

		/** \brief Sets the state in which functions will be called
			\param[in] vm The state to bind to the instance.
		*/
		void bind_script(lua_State* const vm);
	private:
		int get_top();
		bool call(int const nparams, int const error_index);
		bool prep_function(Lua_func_ref const& func, int const nparams, int& error_index);
		bool prep_function(std::string const& func, int const nparams, int& error_index);
		bool prep_function(int const func, int const nparams, int& error_index);
		lua_State* m_lua;
	};

} // namespace OOLUA

#undef OOLUA_CALLER_TRY
#undef OOLUA_CALLER_HANDLE_FAIL

#endif //OOLUA_FUNCTION_H_
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
	\file oolua_helpers.h
	\brief Provides an index equal function which is multi Lua version compatible
	and a Lua Universe checking function.
*/
#ifndef OOLUA_HELPERS_H_
#	define OOLUA_HELPERS_H_

struct lua_State;

namespace OOLUA
{
	/**
		Compares two valid indices on the stack of vm.
		\details Compares the two indicies which will take into consideration
		metamethods when present for the types.
		\param[in] vm The lua_State in which to preform the operation
		\param[in] idx0 Valid stack index
		\param[in] idx1 Valid stack index
		\return bool Result of the comparison
	*/
	bool idxs_equal(lua_State* vm, int idx0, int idx1);

	/** \brief Uses the Lua C API to check if it is valid to move data between the states
		\details
		lua_xmove returns without doing any work if the two pointers are the same
		and fails when using LUA_USE_APICHECK and the states do not share the same
		global_State.

		It may be fine to move numbers between different unrelated states when Lua
		was not compiled with LUA_USE_APICHECK but this function would still return
		false for that scenario.

		\param[in] vm0
		\param[in] vm1
		\returns true if vm0 and vm1 are different yet none NULL related states, else false
	*/
	bool can_xmove(lua_State* vm0, lua_State* vm1);
} //namespace OOLUA

#endif //OOLUA_HELPERS_H_
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
	\file oolua_open.h
	\brief Sets up the a Lua Universe to work with the library.
*/
#ifndef OOLUA_OPEN_H_
#	define OOLUA_OPEN_H_

struct lua_State;

namespace OOLUA
{
	/**
		\brief Sets up a lua_State to work with OOLua.
		\details If you want to use OOLua with a lua_State you already have active
		or supplied by some third party, then calling this function
		adds the necessary tables and globals for it to work with OOLua.
		\param[in] vm lua_State to be initialise by OOLua
	*/
	void setup_user_lua_state(lua_State* vm);

} // namespace OOLUA

#endif //OOLUA_OPEN_H_
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
	\file oolua_pull.h
	\brief Implements the Lua stack operation OOLUA::pull.
*/
#ifndef OOLUA_PULL_H_
#	define OOLUA_PULL_H_


#include <cassert>

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		typedef int (*compare_lua_type_func_sig)(lua_State*, int);
		bool cpp_runtime_type_check_of_top(lua_State* vm, int expected_lua_type, char const * expected_type);
		bool cpp_runtime_type_check_of_top(lua_State* vm, compare_lua_type_func_sig compareFunc, char const * expected_type);
		void handle_cpp_pull_fail(lua_State* vm, char const * expected_type);

		namespace PULL
		{
			void set_index_gc_value_to_false(lua_State* vm, int idx);
		}
	} // namespace INTERNAL //NOLINT(readability/namespace)
	/** \endcond */


	//fwd
	template<typename T>class Proxy_class;

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		//fwd
		template<typename T>
		T* class_from_stack_top(lua_State * vm);
		template<typename T>
		T* none_const_class_from_stack_top(lua_State * vm);

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T>
		struct stack_checker;
#endif
		//fwd

		template<typename T, int is_integral, int is_convertable_to_int>
		struct pull_basic_type;

		template<typename T>
		struct pull_basic_type<T, 0, 1>//enum
		{
			static bool pull(lua_State* const vm, T &  value)
			{
				//enumeration type so a static cast should be allowed else this
				//is being called with the wrong type
				typedef char dummy_can_convert [ LVD::can_convert_to_int<T>::value ? 1 : -1] OOLUA_UNUSED;
				//value = static_cast<T>( lua_tonumber( vm, -1) );
				if( !cpp_runtime_type_check_of_top(vm, lua_isnumber, "enum type") )
					return false;
				value = static_cast<T>(lua_tointeger(vm, -1));
				lua_pop(vm, 1);
				return true;
			}
		};

		template<int ID>
		struct pull_basic_type<Lua_ref<ID>, 0, 0>
		{
			static bool pull(lua_State* const vm, Lua_ref<ID> &  value)
			{
				return value.pull(vm);
			}
		};

		template<typename T>
		struct pull_basic_type<T, 1, 1>
		{
			static bool pull(lua_State* const vm, T &  value)
			{
				if( !cpp_runtime_type_check_of_top(vm, lua_isnumber, "integer compatible type") )
					return false;
				value = static_cast<T>(lua_tointeger(vm, -1));
				lua_pop(vm, 1);
				return true;
			}
		};

		//either a C++11 scoped enum or a string class
		template<typename T>
		struct pull_basic_type<T, 0, 0>
		{
			static bool pull(lua_State* const vm, T&  value)
			{
				return pull_imp(vm, value, LVD::Int2type<is_scoped_enum<T>::value>());
			}
			static bool pull_imp(lua_State* const vm, T& value, LVD::Int2type<1>)
			{
				//C++11 scoped enum
				return pull_basic_type<T, 1, 1>::pull(vm, value);
			}
			static bool pull_imp(lua_State* const vm, T& value, LVD::Int2type<0>)
			{
				return OOLUA::STRING::pull(vm, value);
			}
		};

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T, template <typename> class Shared_pointer_class>
		struct pull_basic_type<Shared_pointer_class<T>, 0, 0>
		{
			typedef typename LVD::remove_const<T>::type raw;
			static bool pull(lua_State* const vm, Shared_pointer_class<T> & value)
			{
				value = !LVD::is_const<T>::value
							? stack_checker<Shared_pointer_class<raw> >::check_index_no_const(vm, lua_gettop(vm))
							: stack_checker<Shared_pointer_class<raw> >::check_index(vm, lua_gettop(vm));

				if(!value)
				{
#	if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					INTERNAL::handle_cpp_pull_fail(vm, LVD::is_const<T>::value
														   ? Proxy_class<raw>::class_name_const
														   : Proxy_class<raw>::class_name);
#	elif OOLUA_DEBUG_CHECKS == 1
					assert(value);
#	endif
#	if OOLUA_USE_EXCEPTIONS == 0
					return false;
#	endif
				}
				lua_pop(vm, 1);
				return true;
			}
		};
#endif

		///////////////////////////////////////////////////////////////////////////////
		///  @struct pull_ptr
		///  Pulls a pointer to C++ depending on the second template parameter. If it
		///  is true then the type is an integral type and one of the normal overloaded
		///  OOLUA::pull functions are called. If on the other hand the type is not
		///  integral then pull_class_type is used.
		///////////////////////////////////////////////////////////////////////////////
		template<typename T, bool IsIntegral>
		struct pull_ptr;

		template<typename Raw_type>
		inline void pull_class_type(lua_State *const vm, int Is_const, Raw_type*& class_type)
		{
MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA
			if(Is_const) class_type = INTERNAL::class_from_stack_top< Raw_type >(vm);
			else class_type = INTERNAL::none_const_class_from_stack_top<Raw_type>(vm);
MSC_POP_COMPILER_WARNING_OOLUA
		}


		template<typename T>
		struct pull_ptr<T, false>
		{
			//this needs to return a bool as it was called from C++
			static bool pull(lua_State* const vm, T *&  value)
			{
				assert(vm);
				typename OOLUA::INTERNAL::param_type<T>::raw* class_ptr;
				pull_class_type<typename OOLUA::INTERNAL::param_type<T>::raw>
					(vm, OOLUA::INTERNAL::param_type<T*>::is_constant, class_ptr);

				if(!class_ptr)
				{
#	if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					INTERNAL::handle_cpp_pull_fail(vm, OOLUA::INTERNAL::param_type<T*>::is_constant
												   ? Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name_const
												   : Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name);
#	elif OOLUA_DEBUG_CHECKS == 1
					assert(class_ptr);
#	endif
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
					value = 0;
					return false;
#	endif
				}
				value = class_ptr;
				lua_pop(vm, 1);
				return true;
			}
		};
		template<typename T>
		struct pull_ptr<T, true>;//disable

	} // namespace INTERNAL // NOLINT
	/** \endcond*/


	template<typename T>
	inline bool pull(lua_State* const vm, T& value)
	{
		return INTERNAL::pull_basic_type<T
						, LVD::is_integral_type<T>::value
						, LVD::can_convert_to_int<T>::value>::pull(vm, value);
	}


	//pulls a pointer from the stack which Cpp will then own and call delete on
	template<typename T>
	inline bool pull(lua_State* const vm, OOLUA::cpp_acquire_ptr<T>&  value)
	{
		INTERNAL::pull_class_type<typename OOLUA::cpp_acquire_ptr<T>::raw>
			(vm, OOLUA::cpp_acquire_ptr<T>::is_constant, value.m_ptr);

		if(!value.m_ptr)
		{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
			INTERNAL::handle_cpp_pull_fail(vm, OOLUA::cpp_acquire_ptr<T>::is_constant
										   ? Proxy_class<typename cpp_acquire_ptr<T>::raw>::class_name_const
										   : Proxy_class<typename cpp_acquire_ptr<T>::raw>::class_name);
#elif OOLUA_DEBUG_CHECKS == 1
			assert(value.m_ptr);
#endif
#	if OOLUA_USE_EXCEPTIONS == 0//prevent vs warnings
			return false; // LCOV_EXCL_LINE
#	endif
		}
		INTERNAL::PULL::set_index_gc_value_to_false(vm, -1);
		lua_pop(vm, 1);
		return true;
	}


	//  Checks if it is an integral type( LVD::is_integral_type ) or a type
	//  that should be registered to OOLua with Proxy_class and calls the correct function.
	template<typename T>
	inline bool pull(lua_State* const vm, T *&  value)
	{
		return INTERNAL::pull_ptr<T, LVD::is_integral_type<T>::value>::pull(vm, value);
	}

} //namespace OOLUA

#endif //OOLUA_PULL_H_
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
	\file oolua_push.h
	\brief Implements the Lua stack operation OOLUA::pull.
*/
#ifndef OOLUA_PUSH_H
#	define OOLUA_PUSH_H


#include <cassert>

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		//fwd
		template<typename Raw, typename TypeMaybeConst>
		void push_pointer_which_has_a_proxy_class(lua_State * vm, TypeMaybeConst * const ptr, Owner owner);

		template<typename Underlying_pointer_type, template <typename> class Shared_pointer_class>
		void push_shared_pointer(lua_State* vm, Shared_pointer_class<Underlying_pointer_type> const & instance);
		//fwd

		template<typename T, int is_integral, int is_convertable_to_int>
		struct push_basic_type;

		template<typename T, bool is_integral>
		struct push_ptr;

		template<typename T>
		struct push_basic_type<T, 0, 1>
		{
			static bool push(lua_State* const  vm, T const&  value)
			{
				//enumeration type so a static cast must be allowed.
				//enums will be stronger in C++0x so this will need revisiting then
				typedef char dummy_can_convert [ LVD::can_convert_to_int<T>::value ? 1 : -1] OOLUA_UNUSED;
				lua_pushinteger(vm, static_cast<lua_Integer>(value) );
				return true;
			}
		};

		template<int ID>
		struct push_basic_type<Lua_ref<ID>, 0, 0>
		{
			static bool push(lua_State* const vm, Lua_ref<ID> const& value)
			{
				return value.push(vm);
			}
		};

		template<typename T>
		struct push_basic_type<T, 1, 1>
		{
			static bool push(lua_State* const vm, T const& value)
			{
				lua_pushinteger(vm, static_cast<lua_Integer>(value));
				return true;
			}
		};

		//either a C++11 scoped enum or a string class
		template<typename T>
		struct push_basic_type<T, 0, 0>
		{
			static bool push(lua_State* const vm, T const& value)
			{
				return push_imp(vm, value, LVD::Int2type<is_scoped_enum<T>::value>());
			}

			static bool push_imp(lua_State* const vm, T const& value, LVD::Int2type<1>)
			{
				//C++11 scoped enum
				lua_pushinteger(vm, static_cast<lua_Integer>(value));
				return true;
			}

			static bool push_imp(lua_State* const vm, T const& value, LVD::Int2type<0>)
			{
				return OOLUA::STRING::push(vm, value);
			}
		};

		template<typename Ptr_type, template <typename> class Shared_pointer_class>
		struct push_basic_type<Shared_pointer_class<Ptr_type>, 0, 0>
		{
			static bool push(lua_State* const vm, Shared_pointer_class<Ptr_type> const& value)
			{
				assert(vm && value);
				push_shared_pointer(vm, value);
				return true;
			}
		};


		template<typename T>
		struct push_ptr<T, false>
		{
			static bool push(lua_State* const vm, T * const &  value, Owner owner)
			{
				assert(vm && value);
				OOLUA::INTERNAL::push_pointer_which_has_a_proxy_class<typename LVD::raw_type<T>::type>(vm, value, owner);
				return true;
			}

			static bool push(lua_State* const vm, T * const &  value)
			{
				return push_ptr<T, false>::push(vm, value, No_change);
			}
		};

		template<typename T>
		struct push_ptr<T, true>
		{
			//owner is here as it can be supplied but is ignored as the type is integral
			static bool push(lua_State* const vm, T * const &  value, Owner/* owner*/)
			{
				return push_ptr<T, true>::push(vm, value);
			}
			static bool push(lua_State* const vm, T * const &  value)
			{
				assert(vm && value);
				return OOLUA::push(vm, *value);
			}
		};

		///////////////////////////////////////////////////////////////////////////////
		///  Specialisation for C style strings
		///////////////////////////////////////////////////////////////////////////////
		template<>
		struct push_ptr<char, true>
		{
			static bool push(lua_State* const vm, char * const &  value, Owner/* owner*/)
			{
				assert(vm && value);
				lua_pushstring(vm, value);
				return true;
			}

			static bool push(lua_State* const /*vm*/, char * const &  /*value*/)
			{
				assert(0 && "this function should not be called");
				return false;
			}
		};
		template<>
		struct push_ptr<char const, true>
		{
			static bool push(lua_State* const vm, char const * const &  value, Owner/* owner*/)
			{
				assert(vm && value);
				lua_pushstring(vm, value);
				return true;
			}

			static bool push(lua_State* const /*vm*/, char const * const &  /*value*/)
			{
				assert(0 && "this function should not be called");
				return false;
			}
		};

	} // namespace INTERNAL // NOLINT
	/** \endcond*/



	template<typename T>
	inline bool push(lua_State* const  vm, T const&  value)
	{
		return INTERNAL::push_basic_type<T
							, LVD::is_integral_type<T>::value
							, LVD::can_convert_to_int<T>::value >::push(vm, value);
	}

	template<typename T>
	inline bool push(lua_State* const vm, OOLUA::lua_acquire_ptr<T> const&  value)
	{
		assert(vm && value.m_ptr);
		INTERNAL::push_pointer_which_has_a_proxy_class<typename OOLUA::lua_acquire_ptr<T>::raw>(vm, value.m_ptr, Lua);
		return true;
	}

	template<typename T>
	inline bool push(lua_State* const vm, T * const &  value, Owner owner)
	{
		return INTERNAL::push_ptr<T, INTERNAL::Type_enum_defaults<T>::is_integral >::push(vm, value, owner);
	}
	template<typename T>
	inline bool push(lua_State* const vm, T * const &  value)
	{
		return INTERNAL::push_ptr<T, LVD::is_integral_type<T>::value>::push(vm, value);
	}

} // namespace OOLUA

#endif //OOLUA_PUSH_H
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
	\file oolua_registration_fwd.h
	\brief Forward declarations of public API functions used for registering a class
	or statics for a class type.
*/
#ifndef OOLUA_FWD_REGISTRATION_FWD_H_
#	define OOLUA_FWD_REGISTRATION_FWD_H_

struct lua_State;

namespace OOLUA
{
	template<typename T>
	void register_class(lua_State * vm);

	template<typename T, typename K, typename V>
	void register_class_static(lua_State * const vm, K const& k, V const& v);

} // namespace OOLUA

#endif // OOLUA_FWD_REGISTRATION_FWD_H_
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
	\file proxy_function_dispatch.h
	\brief Provides the templated functions which are bound to Lua matching the
	lua_CFunction signature, which dispatch control to the correct Proxy_class
	functions.
*/
#ifndef OOLUA_PROXY_FUNCTION_DISPATCH_H_
#	define OOLUA_PROXY_FUNCTION_DISPATCH_H_



/** \cond INTERNAL */

#if	OOLUA_USE_EXCEPTIONS ==1

#	define OOLUA_PROXY_CALL_CATCH_RESPONSE(exception_type, what_message) \
		luaL_error(vm, "Type of exception: %s.\n what(): %s.\n When calling function on proxy type: %s\n" \
					, exception_type \
					, what_message   \
					, Proxy_type::class_name);



#	define OOLUA_MEMBER_FUNCTION_TRY \
	try \
	{ /*start try block*/
// NOLINT


#	define OOLUA_MEMBER_FUNCTION_CATCH \
	} /*end try block */ \
	catch(OOLUA::Type_error const& e) \
	{ \
		OOLUA_PROXY_CALL_CATCH_RESPONSE("OOLUA::Type_error", e.what()) \
	} \
	catch(std::exception const& e) \
	{ \
		OOLUA_PROXY_CALL_CATCH_RESPONSE("std::exception", e.what()) \
	} \
	catch(...) \
	{ \
		OOLUA_PROXY_CALL_CATCH_RESPONSE("Unknown type", " ") \
	} \
	/*can not return here yet required for the function signature */ \
	/* as it would have either returned in the */ \
	/*try block or called luaL_error which never returns */ \
	return 0;

#endif

#if OOLUA_RUNTIME_CHECKS_ENABLED == 1
#	define OOLUA_SELF_CHECK(obj, mod, reg_type, which_name) \
			if(!obj) \
				luaL_error(vm, "%s \"%s::%s\"%s" \
										, "The self/this instance in the function" \
										, Proxy_type::which_name \
										, (static_cast<typename Proxy_class<Base_type >::reg_type*>(lua_touserdata(vm, lua_upvalueindex(1))))->name \
										, mod " is either NULL or the wrong type is on the stack." \
				); /*NOLINT*/
#else
#	define OOLUA_SELF_CHECK(obj, mod, reg_type, which_name)
#endif



namespace OOLUA
{
	namespace INTERNAL
	{

		template<typename Proxy_type, typename Base_type>int member_caller(lua_State* vm);
		template<typename Proxy_type, typename Base_type>int const_member_caller(lua_State* vm);


		///////////////////////////////////////////////////////////////////////////////
		///  \brief Member function dispatcher
		///	 \details This is the member function dispatcher which has the signature
		///  of a \ref lua_CFunction and will be bound to a \ref lua_State by
		///  OOLUA::register_class, to enable the calling of none constant member
		///  functions. It receives the member function which it will call as an upvalue,
		///  which is set a the time the function is bound.
		///  @param[in] vm The lua_State on which to operate
		///  @return int The number of returns from the function to Lua.
		///////////////////////////////////////////////////////////////////////////////
		template<typename Proxy_type, typename Base_type>
		inline int member_caller(lua_State * vm)
		{
#if	OOLUA_USE_EXCEPTIONS == 1
			OOLUA_MEMBER_FUNCTION_TRY
#endif
				typename Proxy_type::class_ *obj = INTERNAL::check_index_no_const<typename Proxy_type::class_>(vm, 1);
				OOLUA_SELF_CHECK(obj, " ", Reg_type, class_name)
				//get member function from upvalue
				typename Proxy_class<Base_type >::Reg_type* r =
						static_cast<typename Proxy_class<Base_type >::Reg_type*>(lua_touserdata(vm, lua_upvalueindex(1)));
				Proxy_type P(obj);
				return (P.*(r->mfunc))(vm); //call member function
#if	OOLUA_USE_EXCEPTIONS == 1
			OOLUA_MEMBER_FUNCTION_CATCH
#endif
		}

		/**
			\brief Dispatcher for constant member functions
		*/
		template<typename Proxy_type, typename Base_type>
		inline int const_member_caller(lua_State * vm)
		{
#if	OOLUA_USE_EXCEPTIONS == 1
			OOLUA_MEMBER_FUNCTION_TRY
#endif
				typename Proxy_type::class_ *obj = INTERNAL::check_index<typename Proxy_type::class_>(vm, 1);
				OOLUA_SELF_CHECK(obj, "const", Reg_type_const, class_name_const)
				//get member function from upvalue
				typename Proxy_class<Base_type >::Reg_type_const* r =
						static_cast<typename Proxy_class<Base_type >::Reg_type_const*>(lua_touserdata(vm, lua_upvalueindex(1)));
				Proxy_type P(obj);
				return (P.*(r->mfunc))(vm); //call member function
#if	OOLUA_USE_EXCEPTIONS == 1
			OOLUA_MEMBER_FUNCTION_CATCH
#endif
		}
	} // namespace INTERNAL //NOLINT

} // namespace OOLUA




#if	OOLUA_USE_EXCEPTIONS == 1
#	undef OOLUA_PROXY_CALL_CATCH_RESPONSE
#	undef OOLUA_MEMBER_FUNCTION_TRY
#	undef OOLUA_MEMBER_FUNCTION_CATCH
#endif

#	undef OOLUA_GET_NONE_CONST_SELF
#	undef OOLUA_GET_CONST_SELF
#	undef OOLUA_SELF_CHECK


/** \endcond */

#endif //OOLUA_PROXY_FUNCTION_DISPATCH_H_
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
	\file proxy_tags.h
	\brief Possible members for the Proxy_class \ref OOLUA_TAGS "Tag block"
*/

#ifndef OOLUA_PROXY_TAGS_H_
# define OOLUA_PROXY_TAGS_H_

/**  \addtogroup OOLuaTags Tags
@{
\brief
Possible members for \ref OOLUA_TAGS which help express more information about
a class which is to be proxied.

	\struct OOLUA::Abstract
	\brief The class being mirrored is an abstract class.
	\details
	When OOLua encounters the \ref OOLUA::Abstract "Abstract" tag it will not
	look for any constructors for the type and the type will not be constructable
	from Lua. Specifying an \ref OOLUA_CTORS block will have no effect and such a
	block will be ignored.

	\addtogroup OperatorTags Operator Tags
	@{
		\brief Informs that a class has an operator exposed
		\details \ref OperatorTags inform OOLua that a class exposes one or more of the
		operators supported:
			\li \ref OOLUA::Less_op "Less_op"
			\li \ref OOLUA::Equal_op "Equal_op"
			\li \ref OOLUA::Not_equal_op "Not_equal_op"
			\li \ref OOLUA::Less_equal_op "Less_equal_op"
			\li	\ref OOLUA::Div_op "Div_op"
			\li \ref OOLUA::Mul_op "Mul_op"
			\li \ref OOLUA::Sub_op "Sub_op"
			\li \ref OOLUA::Add_op "Add_op"



	\struct OOLUA::Less_op
	\brief Less than operator is defined for the type.

	\struct OOLUA::Equal_op
	\brief Equal operator is defined for the type.

	\struct OOLUA::Not_equal_op
	\brief Not equal operator is defined for the type.

	\struct OOLUA::Less_equal_op
	\brief Less than or equal operator is defined for the type.

	\struct OOLUA::Div_op
	\brief Division operator is defined for the type.

	\struct OOLUA::Mul_op
	\brief Multiplication operator is defined for the type.

	\struct OOLUA::Sub_op
	\brief Subtraction operator is defined for the type.

	\struct OOLUA::Add_op
	\brief Addition operator is defined for the type.
	@}

	\struct OOLUA::No_default_constructor
	\brief
	There is not a default constructor in the public interface yet there are other
	constructors.
	\details
	There is not a public default constructor or you do not wish to expose such a
	constructor, yet there are other constructors which will be specified by
	\ref OOLUA_CTOR entries inside a \ref OOLUA_CTOR block.

	\struct OOLUA::No_public_constructors
	\brief There are no constructors in the public interface.
	\details
	When OOLua encounters this tag it will not look for any constructors for the
	type and the type will not be constructable from Lua. Specifying an OOLUA_CTORS
	block will have no effect and such a block will be ignored.

	\struct OOLUA::No_public_destructor
	\brief
	There is not a destructor in the public interface and OOLua will not attempt to
	delete an instance of this type

	\struct OOLUA::Register_class_enums
	\brief The class has enums to register
	\details
	The class has enums which are specified inside the OOLUA_ENUMS block, these
	entries will be registered with a lua_State when the proxy type is.

	\addtogroup SharedTags Shared Tags
	@{
		\brief Tags to override the default behaviour the library was compiled with.

	\struct OOLUA::Shared
	\brief Overrides the configuration behaviour when creating proxied types
	\details
	When the library is compiled with \ref OOLUA_USE_SHARED_PTR "shared pointer support"
	and it is not configured to create shared pointers by
	\ref OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE "default", then this tag
	overrides that behaviour for the proxy type.
	\note If the library is configured to use the shared pointer type by default
	then this tag is ignored when present in a proxy \ref OOLUA_TAGS "tag block".
	\see OOLUA_USE_SHARED_PTR
	\see OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE

	\struct OOLUA::No_shared
	\brief Overrides the configuration behaviour when creating proxied types
	\details
	When the library is compiled with \ref OOLUA_USE_SHARED_PTR "shared pointer support"
	and it is also configured to create shared pointers by
	\ref OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE "default", then this tag
	overrides that behaviour for the proxy type.
	\note If the library is configured to not use the shared pointer type by default
	then this tag is ignored when present in a proxy \ref OOLUA_TAGS "tag block".
	\see OOLUA_USE_SHARED_PTR
	\see OOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE

	@}
*/

namespace OOLUA
{

	struct Abstract{};
	struct Less_op{};
	struct Equal_op{};
	struct Not_equal_op{};
	struct Less_equal_op{};
	struct Div_op{};
	struct Mul_op{};
	struct Sub_op{};
	struct Add_op{};
	struct No_default_constructor{};
	struct No_public_constructors{};
	struct No_public_destructor{};
	struct Register_class_enums{};
	struct Shared{};
	struct No_shared{};
} // namespace OOLUA
/**@}*/
#endif //OOLUA_PROXY_TAGS_H_
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
	\file oolua_table.h
	\brief Interface for the Lua unordered and ordered associative container.
*/

#ifndef OOLUA_TABLE_H_
#	define OOLUA_TABLE_H_

#	include <string>


namespace OOLUA
{
	/**	\class Table
		\brief Wrapper around a table in Lua which allows easy usage
		\details
		\ref OOLUA::Table "Table" provides a simple typed C++ interface for the
		Lua unordered and ordered associative container of the same name. Operations
		which use the Lua stack ensure that the stack is the same on exit
		as it was on entry, OOLua tries to force a clean stack(\ref OOLuaAndTheStack).

		Any value can be retrieved or set from the table via the use of the template
		member functions \ref OOLUA::Table::set "set", \ref OOLUA::Table::at "at" or
		\ref OOLUA::Table::safe_at "safe_at".
		If the value asked for is not the correct type located in the position an
		error can be reported, the type of which depends on \ref OOLuaErrorReporting
		and the function which was called. See individual member function documentation
		for details.

		\note
		The member function \ref OOLUA::Table::try_at "try_at" is only defined when exceptions
		are enabled for the library.
	*/
	class Table
	{
	public:
		/**@{**/

		/** \brief Default creates an object on which a call to valid returns false*/
		Table();

		/** \brief
			Initialises the reference to be an instance of the same registry
			reference or an invalid table if ref.valid() == false
		*/
		explicit Table(Lua_table_ref const& ref);

		/** \brief Sets the lua_State and calls Lua_table::set_table */
		Table(lua_State*  const vm, std::string const& name);
		Table(Table const& rhs);

		/** \brief Assigns a copy of rhs's internal state to this instance
			\details If this table is valid then the operator will release
			the registry reference before assigning a copy of rhs to this
			instance.
			\param[in] rhs Table from which to copy the table reference
			\returns This instance.
			\see OOLUA::Lua_ref assignment operator
		*/
		Table& operator = (Table const& rhs);

		/**@}*/

		~Table()OOLUA_DEFAULT;

		/**@{*/
		/**
			\brief Associates the instance with the lua_State vm
			\details Associates the instance with the lua_State vm.
			If the table already has a lua_State bound to it
				\li If the Current bound instance is not equal to vm and the
				table has a valid reference, it releases the currently set reference
				and sets vm as the bound instance.
		*/
		void bind_script(lua_State*  const vm);

		/** \brief
			Order of trying to initialise :
			\li name.empty() == true: Creates an invalid object.
			\li name found as a table in Lua global: Swaps the internal Lua_func_ref
				with an instance initialised to an id obtained from the Lua registry.
			\li name found as a table in Lua registry: Swaps the internal Lua_func_ref
				with an instance initialised to an id obtained from the Lua registry.
			\li else Swaps the internal Lua_func_ref with an uninitialised instance.
		*/
		void set_table(std::string const& name);

		/** \brief Initailises the internal Lua_func_ref to the id ref*/
		void set_ref(lua_State* const vm, int const& ref);

		/** \brief Swaps the internal Lua_func_ref and rhs.m_table_ref*/
		void swap(Table & rhs);

		/**@}*/

		/**@{*/
#if OOLUA_USE_EXCEPTIONS == 1 || OOLUA_DOXYGEN_IS_PROCESSING == 999
		/**
			\brief Function which throws on an error
			\note This function is only defined when exceptions are enable for the library
			\tparam T Key type
			\tparam T1 Value type
			\param[in] key
			\param[out] value
		*/
		template<typename T, typename T1>void try_at(T const& key, T1& value);
#endif
		/**
			\brief A safe version of \ref OOLUA::Table::at "at", which will always return
			a boolean indicating the success of the function call.
			\details This function will not throw an exception when exceptions are enabled
			for the library.
			\tparam T Key type
			\tparam T1 Value type
			\param[in] key
			\param[out] value
		*/
		template<typename T, typename T1>bool safe_at(T const& key, T1& value);

		/**
			\brief
			\tparam T Key type
			\tparam T1 Value type
			\param[in] key
			\param[out] value
			zreturn The same instance as value
			\note
			No error checking.\n
			It is undefined to call this function when:
			\li table or the key are invalid
			\li table does not contain the key
			\li value is not the correct type

			\see Lua_table::safe_at \see Lua_table::try_at
		 */
		template<typename T, typename T1>T1& at(T const& key, T1& value);
		/**@}*/

		/**@{*/
		/** \brief
			Inserts the key value pair into the table if key is not present
			else it updates the table's key entry
		*/
		template<typename T, typename T1>void set(T const& key, T1 const& value);
		/** \brief
			Removes the key from the table by setting it's value to nil
		*/
		template<typename T>void remove(T const& key);
		/**@}*/

		/** \brief
			Returns a boolean which is the result of checking the state of the internal Lua_func_ref.
		*/
		bool valid()const;

		typedef void(*traverse_do_function)(lua_State* );//NOLINT
		/** \brief Traverses the table using \ref oolua_pairs
			\see \ref oolua_pairs "oolua_pairs'" details for the correct procedure
			to follow.
		*/
		void traverse(traverse_do_function do_);

		/**
			\brief Provides access to the associated lua_State
		*/
		lua_State* state() const { return m_table_ref.m_lua; }


		/** \cond INTERNAL*/
		bool push_on_stack(lua_State* vm)const;
		bool pull_from_stack(lua_State* vm);
		void lua_get(lua_State* vm, int idx);
		/** \endcond*/
	private:
		bool get_table()const;
		void restore_stack(int const & init_stack_size)const;
		int initial_stack_size()const;
		Lua_table_ref m_table_ref;
	};

	inline Table::~Table(){}


	//no error checking
	//undefined if lua is null or (table or key is invalid) or value is not correct type
	template<typename T, typename T1>
	inline T1& Table::at(T const& key, T1& value)
	{
		get_table();//table
		push(m_table_ref.m_lua, key);//table key
		lua_gettable(m_table_ref.m_lua, -2);//table value
		pull(m_table_ref.m_lua, value);//table
		lua_pop(m_table_ref.m_lua, 1);
		return value;
	}

	template<typename T, typename T1>
	inline void Table::set(T const& key, T1 const& value)
	{
		//record the stack size as we want to put the stack into the
		//same state that it was before entering here
		int const init_stack_size = initial_stack_size();
		if(!get_table())return;
		push(m_table_ref.m_lua, key);
		//table is now at -2 (key is at -1)
		//push the new value onto the stack
		push(m_table_ref.m_lua, value);
		//table is not at -3 set the table
		lua_settable(m_table_ref.m_lua, -3);

		restore_stack(init_stack_size);
	}

	template<typename T>
	inline void Table::remove(T const& key)
	{
		//record the stack size as we want to put the stack into the
		//same state that it was before entering here
		int const init_stack_size = initial_stack_size();
		if(!get_table())return;
		push(m_table_ref.m_lua, key);
		//table is now at -2 (key is at -1)
		//push the new value onto the stack
		lua_pushnil(m_table_ref.m_lua);
		//table is not at -3 set the table
		lua_settable(m_table_ref.m_lua, -3);

		restore_stack(init_stack_size);
	}

#if OOLUA_USE_EXCEPTIONS == 1
	template<typename T, typename T1>
	inline void Table::try_at(T const& key, T1& value)
	{
		int const init_stack_size = initial_stack_size();
		try
		{
			if(!get_table())throw OOLUA::Runtime_error("Table is invalid");
			push(m_table_ref.m_lua, key);
			lua_gettable(m_table_ref.m_lua, -2);
			if(lua_type(m_table_ref.m_lua, -1) == LUA_TNIL )
			{
				throw OOLUA::Runtime_error("key is not present in table");
			}
			pull(m_table_ref.m_lua, value);
			restore_stack(init_stack_size);
		}
		catch(...)
		{
			restore_stack(init_stack_size);
			throw;
		}
	}

	template<typename T, typename T1>
	inline bool Table::safe_at(T const& key, T1& value)
	{
		try
		{
			try_at(key, value);
		}
		catch(...)
		{
			return false;
		}
		return true;
	}
#else

	template<typename T, typename T1>
	inline bool Table::safe_at(T const& key, T1& value)
	{
		//record the stack size as we want to put the stack into the
		//same state that it was before entering here
		int const init_stack_size = initial_stack_size();
		if( !get_table() )return false;
		if( !push(m_table_ref.m_lua, key))
		{
			restore_stack(init_stack_size);
			return false;
		}
		//table is now at -2 (key is at -1). lua_gettable now pops the key off
		//the stack and then puts the data found at the key location on the stack
		lua_gettable(m_table_ref.m_lua, -2);
		if(lua_type(m_table_ref.m_lua, -1) == LUA_TNIL )
		{
			restore_stack(init_stack_size);
			return false;
		}
		pull(m_table_ref.m_lua, value);
		restore_stack(init_stack_size);

		return true;
	}
#endif


	/**	\brief
		The table is at table_index which can be either absolute or pseudo in the stack
		table is left at the index.
	*/
	template<typename T, typename T1>
	inline void table_set_value(lua_State* vm, int table_index, T const& key, T1 const& value)
	{
		push(vm, key);
		push(vm, value);
		lua_settable(vm, table_index < 0 ? table_index-2 : table_index);
	}

	/**	\brief
	 The table is at table_index which can be either absolute or pseudo in the stack
	 table is left at the index.
	*/
    template<typename T, typename T1>
	inline bool table_at(lua_State* vm, int const table_index, T const& key, T1& value)
	{
		push(vm, key);//table key
		lua_gettable(vm, table_index < 0 ? table_index-1 : table_index);//table value
		return pull(vm, value);//table
	}

	/**
		\brief Creates a new valid \ref OOLUA::Table
		\param [in] vm The lua_State in which to create the table.
		\param [inout] t Table which will hold the newly created valid table.
		\post stack is the same on exit as entry and t will be an instance on which
		valid returns true.

	*/
	void new_table(lua_State* vm, OOLUA::Table& t);

	/**
		\brief Creates a new valid \ref OOLUA::Table "Table"
		\post stack is the same on exit as entry
		\param[in] vm The lua_State in which to create the table
		\return A newly constructed Table on which valid will return true.
	*/
	OOLUA::Table new_table(lua_State* vm);

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		int l_new_table(lua_State* vm);
	} //namespace INTERNAL
	/** \endcond */

	/**	\def oolua_ipairs (table)
		\hideinitializer
		\brief Helper for iterating over the sequence part of a table.
		\param table
		\details
		Declares:
		\li int  \_i_index\_ : Current index into the array
		\li int const \_oolua_array_index\_  : Stack index at which table is located
		\li lua_State* lvm : The vm associated with the table

		\note
		Returning from inside of the loop will not leave the stack clean
		unless you reset it.
		usage:
		\code{.cpp}
		oolua_ipairs(table)
		{
			if(_i_index_ == 99)
			{
				lua_settop(lvm,_oolua_array_index-1);
				return "red balloons";
			}
		}
		oolua_ipairs_end()
		return "Not enough balloons to go bang."
		\endcode
	 */
#	define oolua_ipairs(table) \
	if( table.valid() ) \
	{ \
		lua_State* lvm = table.state(); \
		lua_checkstack(lvm, 2);\
		OOLUA::push(lvm, table); \
		int const _oolua_array_index_ = lua_gettop(lvm); \
		int _i_index_ = 1; \
		lua_rawgeti(lvm, _oolua_array_index_, _i_index_); \
		while (lua_type(lvm, -1)  != LUA_TNIL) \
		{
// NOLINT

	/** \def oolua_ipairs_end()
		\hideinitializer
		\see oolua_ipairs
	*/
#	define oolua_ipairs_end()\
			lua_settop(lvm, _oolua_array_index_); \
			lua_rawgeti(lvm, _oolua_array_index_, ++_i_index_); \
		} \
		lua_settop(lvm, _oolua_array_index_-1); \
	}


	/** \def oolua_pairs(table)
		\hideinitializer
		\param table
		\brief Helper for iterating over a table.
		\details
		When iterating over a table, for the next iteration to work you must leave the key
		on the top of the stack. If you need to work with the key, it is a good idea to use
		lua_pushvalue to duplicate it on the stack. This is because if the type is not a
		string and you retrieve a string from the stack with lua_tostring, this will alter
		the vm's stack entry.\n
		Declares:
		\li int const \_oolua_table_index\_  : Stack index at which table is located
		\li lua_State* lvm : The vm associated with the table

		usage:
		\code{.cpp}
		oolua_pairs(table)
		{
			\\do what ever
			lua_pop(vm, 1);\\Pop the value, leaving the key at the top of stack
		}
		oolua_pairs_end()
		\endcode
	*/

#	define oolua_pairs(table) \
	if( table.valid() ) \
	{ \
		lua_State* lvm = table.state(); \
		OOLUA::push(lvm, table); \
		int	const _oolua_table_index_ = lua_gettop(lvm); \
		lua_pushnil(lvm); \
		while (lua_next(lvm, _oolua_table_index_) != 0)

	/** \def oolua_pairs_end()
		\hideinitializer
		\see oolua_pairs
	*/
#	define oolua_pairs_end() \
		lua_pop(lvm, 1); \
	}

	/*
		\brief Iterates over a table using oolua_pairs calling a member function for each iteration
		\param[in] table The OOLUA::Table over which you want to iterate
		\param[in] instance Class instance on which to call the callback
		\param[in] func Member function call back for each iteration.

		\details
		You must remove the value from the stack and leave the key
		do not call anything which may call tostring on the actual key
		duplicate it instead with lua_pushvalue then call the operation on the copy
	*/
	template<typename ClassType>
	inline void for_each_key_value(OOLUA::Table& table, ClassType* instance, void(ClassType::*func)(lua_State*) ) //NOLINT
	{
		oolua_pairs(table)
		{
			(instance->*(func))(lvm);
		}
		oolua_pairs_end()
	}
} // namespace OOLUA

#endif //OOLUA_TABLE_H_
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
	\file proxy_operators.h
	\brief Internal implemenations of Proxy_class operators.
	\details Defines operators which will be made available in scripts when a
	\ref OOLUA::Proxy_class contains \ref OperatorTags "operator tags"
*/

#ifndef OOLUA_PROXY_OPERATORS_H_
#	define OOLUA_PROXY_OPERATORS_H_


namespace OOLUA
{
	/** \cond INTERNAL */
	namespace INTERNAL
	{
		/*fwd*/
		template<typename RawClassType>
		struct new_pointer;
		/*fwd*/

		//rhs is top of stack lhs is below (lhs op rhs)
		template<typename T>
		int lua_equal(lua_State*  const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			bool result(*lhs == *rhs);
			OOLUA::push(vm, result);
			return 1;
		}

		template<typename T>
		int lua_less_than(lua_State* const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			bool result(*lhs < *rhs);
			OOLUA::push(vm, result);
			return 1;
		}

		template<typename T>
		int lua_less_than_or_equal(lua_State* const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			bool result(*lhs <= *rhs);
			OOLUA::push(vm, result);
			return 1;
		}

		//these following operator functions return a type that they are working on
		template<typename T>
		int lua_add(lua_State*  const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			typename new_pointer<T>::type result(new T(*lhs + *rhs));
			INTERNAL::add_ptr<T>(vm, result, false, OOLUA::Lua);
			return 1;
		}


		template<typename T>
		int lua_sub(lua_State*  const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			typename new_pointer<T>::type result(new T(*lhs - *rhs));
			INTERNAL::add_ptr<T>(vm, result, false, OOLUA::Lua);
			return 1;
		}

		template<typename T>
		int lua_mul(lua_State*  const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			typename new_pointer<T>::type result(new T(*lhs * *rhs));
			INTERNAL::add_ptr<T>(vm, result, false, OOLUA::Lua);
			return 1;
		}

		template<typename T>
		int lua_div(lua_State*  const vm)
		{
			T const* lhs(0);
			T const* rhs(0);
			INTERNAL::LUA_CALLED::get(vm, 1, lhs);
			INTERNAL::LUA_CALLED::get(vm, 2, rhs);
			typename new_pointer<T>::type result(new T(*lhs / *rhs));
			INTERNAL::add_ptr<T>(vm, result, false, OOLUA::Lua);
			return 1;
		}

#define DEFINE_OOLUA_OPERATOR_FUNCTION_(operation, lua_string_op)\
		template<typename T, bool hasOperator >\
		struct set_ ## operation ## _function\
		{\
			static void set(lua_State* const /*vm*/, int /*metatable*/){}\
		};\
		template<typename T>\
		struct set_ ## operation ## _function<T, true> \
		{\
			static void set(lua_State* const vm, int metatable)\
			{\
				lua_pushliteral(vm, lua_string_op);\
				lua_pushcfunction(vm, lua_## operation<T>);\
				lua_rawset(vm, metatable);\
			}\
		};


DEFINE_OOLUA_OPERATOR_FUNCTION_(equal, "__eq")
DEFINE_OOLUA_OPERATOR_FUNCTION_(less_than, "__lt")
DEFINE_OOLUA_OPERATOR_FUNCTION_(less_than_or_equal, "__le")
DEFINE_OOLUA_OPERATOR_FUNCTION_(add, "__add")
DEFINE_OOLUA_OPERATOR_FUNCTION_(sub, "__sub")
DEFINE_OOLUA_OPERATOR_FUNCTION_(mul, "__mul")
DEFINE_OOLUA_OPERATOR_FUNCTION_(div, "__div")

#undef DEFINE_OOLUA_OPERATOR_FUNCTION_

	} // namespace INTERNAL // NOLINT
	/** \endcond  */
} // namespace OOLUA

#endif //OOLUA_PROXY_OPERATORS_H_

/**
	\file oolua_registration.h
	\brief Implements the public API register functions and internal workers.
	\details
	\copyright
	The MIT License\n
	Copyright (c) 2005 Leonardo Palozzi \n
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
	Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:\n
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.\n
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

#ifndef OOLUA_REGISTRATION_H_
#	define OOLUA_REGISTRATION_H_



#if OOLUA_USE_SHARED_PTR == 1
#	include OOLUA_SHARED_HEADER
#endif


namespace OOLUA
{
	/**
		\brief Registers the class type T and it's bases with an instance of lua_State
		\tparam T Class type to register with OOLua
		\details Registers a class type T for which there is a Proxy_class and also
		registers it's bases, if it has any. The function preforms a check to see
		if the type has already been registered with the instance and is safe to be
		called multiple times with a Lua universe.
		\param[in] vm Universe to register the class with.
	*/
	template<typename T>void register_class(lua_State * vm);

	/**
		\brief
		Registers a key K and value V entry into class T
		\tparam T Class type to register the static for
		\tparam K Key
		\tparam V Value
		\param[in] vm lua_State
		\param[in] key Key to register in type T,
		\param[in] value The data to associate with key in the class type T.
	*/
	template<typename T, typename K, typename V>
	void register_class_static(lua_State * const vm, K const& key, V const& value);



	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<typename T>struct garbage_collect;

		/**
			\brief
			Implements the registering of a single class which is used by register_class
			\tparam T Class type to register
		 */
		template<typename T>void register_class_imp(lua_State * vm);

		template<typename T, typename B>struct Add_base_methods;
		template<typename T, typename TL, int index, typename B>struct Register_base_methods;

		template<typename T, int HasNoPublicDestructor>struct set_delete_function;
		template<typename T, bool HasNoPublicDestructor>struct set_owner_function;
		template<typename T, bool IsAbstractOrNoConstructors>struct set_create_function;

		//fwd not defined here
		template<typename T>
		int oolua_generic_default_constructor(lua_State* vm);
		//fwd not defined here

		void set_function_in_table_with_upvalue(lua_State* vm, char const * func_name, lua_CFunction func
														, int tableIndex, void* upvalue);
		void set_function_in_table(lua_State* vm, char const* func_name, lua_CFunction func, int tableIndex);
		void set_oolua_userdata_creation_key_value_in_table(lua_State* vm, int tableIndex);

		void set_key_value_in_table(lua_State* vm, char const* key_name, int valueIndex, int tableIndex);
		int check_for_key_in_stack_top(lua_State* vm);

		bool class_name_is_already_registered(lua_State* vm, char const* name);
		int info(lua_State* vm, int const index, int const id);
		template<typename T, int HasRegisterEnumsTag>struct set_class_enums;

		int get_oolua_module(lua_State* vm);
		void register_oolua_type(lua_State* vm, char const* name, int const stack_index);

		template<typename T>
		void sets_oolua_userdata_creation_key_value_in_table(lua_State* vm, int const table);
	} //namespace INTERNAL // NOLINT

	namespace INTERNAL
	{

		template<typename T>
		inline void shared_delete(T* p)
		{
			p->~T();
		}

		//userdata is at index 1
		//weak table is at index 2
		inline void gc_clean_table(lua_State* vm, void* ptr)
		{
			lua_pushlightuserdata(vm, ptr);
			lua_rawget(vm, 2);
			if (lua_type(vm, 3) == LUA_TTABLE)
			{
				lua_pushnil(vm);
				if (lua_next(vm, 3) == 0)
				{
					//then table is empty and needs cleaning up
					lua_pushlightuserdata(vm, ptr);
					lua_pushnil(vm);
					lua_rawset(vm, 2);

					lua_pushnil(vm);
					lua_rawset(vm, 2);
				}
			}
			lua_settop(vm, 2);
		}

		template<typename T, typename TL, int Index, typename Base>
		struct gc_table_cleaner;

		//usersdata is at index 1
		//weak table is at index 2
		template<typename T, typename TL, int Index, typename Base>
		struct gc_table_cleaner
		{
			static void clean(lua_State* vm, T* ptr)
			{
				//is there is an offset
				if (static_cast<void*>(ptr) != static_cast<void*>(static_cast<Base*>(ptr)))
				{
					//there is a separate caching of the base pointer
					gc_clean_table(vm, static_cast<Base*>(ptr));
				}
				//clean next base
				gc_table_cleaner<T
								, TL
								, Index + 1
								, typename TYPELIST::At_default<TL, Index + 1, TYPE::Null_type>::Result
								>::clean(vm, ptr);
				//move to the bases of base
				gc_table_cleaner<Base
								, typename Proxy_class<Base>::Bases
								, 0
								, typename TYPELIST::At_default<typename Proxy_class<Base>::Bases, 0, TYPE::Null_type>::Result
								>::clean(vm, ptr);
			}
		};

		template<typename T, typename Bases, int Index>
		struct gc_table_cleaner<T, Bases, Index, TYPE::Null_type>
		{
			static void clean(lua_State* /*vm*/, T* /*ptr*/){}
		};

		template<typename T>
		struct garbage_collect
		{
			static int gc(lua_State * vm)
			{
				Lua_ud *ud = static_cast<Lua_ud*>(lua_touserdata(vm, 1));
				cleanup_collision_tables(vm, ud);
#if OOLUA_USE_SHARED_PTR == 1
				if( ud->flags & SHARED_FLAG)
					shared_delete(reinterpret_cast<OOLUA_SHARED_TYPE<T>* >(ud->shared_object));
				else
#endif
					if( ud->flags & GC_FLAG )delete static_cast<T*>(ud->void_class_ptr);
				return 0;
			}
			static int gc_no_destructor(lua_State * vm)
			{
				cleanup_collision_tables(vm, static_cast<Lua_ud*>(lua_touserdata(vm, 1)));
				return 0;
			}
			static void cleanup_collision_tables(lua_State * vm, Lua_ud *ud)
			{
				if( ud->flags & COLLISION_FLAG )
				{
					Weak_table::getWeakTable(vm);
#if OOLUA_USE_SHARED_PTR == 1
					//let's not depend on how shared_ptr is implemented
					void* void_class_ptr = ud->flags & SHARED_FLAG ?
								static_cast<OOLUA_SHARED_TYPE<T>* >(ud->void_class_ptr)->get()
								: ud->void_class_ptr;
#else
					void* void_class_ptr = ud->void_class_ptr;
#endif
					gc_clean_table(vm, void_class_ptr);
					gc_table_cleaner<T
								, typename Proxy_class<T>::Bases
								, 0
								, typename TYPELIST::At_default<typename Proxy_class<T>::Bases, 0, TYPE::Null_type>::Result
								>::clean(vm, static_cast<T*>(void_class_ptr));
				}
			}
		};

		template<typename T, int HasRegisterEnumsTag>
		struct set_class_enums
		{
			static void set(lua_State* /*vm*/){}//nop
		};

		template<typename T>
		struct set_class_enums<T, 1>
		{
			static void set(lua_State* vm)
			{
				Proxy_class<T>::oolua_enums(vm);
			}
		};

		template<typename TL, int Index, typename T>
		struct info_getter;

		// LCOV_EXCL_START
		template<typename T>
		inline int top(lua_State* vm)
		{
			lua_checkstack(vm, 1);
			lua_pushstring(vm, Proxy_class<T>::class_name);
			return 1;
		}
		// LCOV_EXCL_STOP

		template<typename T, int HasNoPublicDestructor>
		struct set_delete_function
		{
			static void set(lua_State* vm, int methods)
			{
				set_function_in_table(vm, "__gc", &INTERNAL::garbage_collect<T>::gc, methods);
			}
		};

		template<typename T>
		struct set_delete_function<T, 1>
		{
			static void set(lua_State* vm, int methods)
			{
				set_function_in_table(vm, "__gc", &INTERNAL::garbage_collect<T>::gc_no_destructor, methods);
			}
		};


		template<typename Base>
		struct Base_looker
		{
			static int findInBase(lua_State* vm)
			{
				//table keyString
				lua_getglobal(vm, Proxy_class<Base>::class_name);//table keyString baseTable
				return check_for_key_in_stack_top(vm);
			}
		};

		template<typename T, typename Bases, int Index, typename BaseAtIndex>
		struct R_Base_looker
		{
			static int findInBase(lua_State* vm)
			{
				if (Base_looker<BaseAtIndex>::findInBase(vm) )return 1;
				return R_Base_looker<T, Bases, Index+1
								, typename TYPELIST::At_default<Bases, Index+1, TYPE::Null_type>::Result
								>::findInBase(vm);
			}
		};

		// LCOV_EXCL_START
		template<typename T>
		inline int middle(lua_State* vm)
		{
			top<T>(vm);
			info_getter< typename Proxy_class<T>::Bases
						, 0
						, typename TYPELIST::At_default<typename Proxy_class<T>::Bases, 0, TYPE::Null_type >::Result
						>::add(vm);
				return TYPELIST::Length<typename Proxy_class<T>::Bases>::value + 1;
		}
		// LCOV_EXCL_STOP

		template<typename T, typename Bases, int Index>
		struct R_Base_looker<T, Bases, Index, TYPE::Null_type>
		{
			static int findInBase(lua_State* /*vm*/) // NOLINT
			{
				return 0;
			}
		};

		template<typename T>
		int search_in_base_classes(lua_State* vm)
		{
			return R_Base_looker<T, typename Proxy_class<T>::Bases, 0
									, typename TYPELIST::At_default<typename Proxy_class<T>::Bases
									, 0
									, TYPE::Null_type>::Result >::findInBase(vm);
		}

		// LCOV_EXCL_START
		template<typename T>
		static int bottom(lua_State* vm)
		{
			top<T>(vm);
			info_getter< typename Proxy_class<T>::AllBases
						, 0
						, typename TYPELIST::At_default<typename Proxy_class<T>::AllBases, 0, TYPE::Null_type >::Result
						>::add(vm);
			return TYPELIST::Length<typename Proxy_class<T>::AllBases>::value + 1;
		}
		// LCOV_EXCL_STOP

		template<typename T>
		int search_in_base_classes_yet_prevent_new(lua_State* vm)
		{
			if( lua_type(vm, -1) == LUA_TSTRING )
			{
				OOLUA_PUSH_CARRAY(vm, OOLUA::INTERNAL::new_str);
				if( lua_rawequal(vm, -1, -2) )
				{
					/*
					The string key is the OOLua identifier for the constructor factory function,
					if the type had this identifier it would not enter this function to search
					the heirachy tree to find another.
					*/
					return 0;
				}
				else lua_pop(vm, 1);
			}
			return R_Base_looker<T, typename Proxy_class<T>::Bases, 0
									, typename TYPELIST::At_default<typename Proxy_class<T>::Bases
									, 0
									, TYPE::Null_type>::Result >::findInBase(vm);
		}


		template<typename T, int HasNoPublicConstructors>
		struct set_base_lookup_function
		{
			static void set(lua_State* vm, int methods)
			{
				set_function_in_table(vm, "__index", &search_in_base_classes<T>, methods);
			}
		};

		template<typename T>
		struct set_base_lookup_function<T, 1>
		{
			static void set(lua_State* vm, int methods)
			{
				set_function_in_table(vm, "__index", &search_in_base_classes_yet_prevent_new<T>, methods);
			}
		};

		template<typename T, typename B>
		struct Add_base_methods
		{
			void operator()(lua_State * const vm, int const methods)
			{
				for (typename Proxy_class<B >::Reg_type *r = Proxy_class<B >::class_methods; r->name; r++)
				{
					INTERNAL::set_function_in_table_with_upvalue(vm, r->name, &OOLUA::INTERNAL::member_caller<T, B >
																 , methods, reinterpret_cast<void*>(r));
				}

				for (typename Proxy_class<B >::Reg_type_const *r = Proxy_class<B >::class_methods_const; r->name; ++r)
				{
					INTERNAL::set_function_in_table_with_upvalue(vm, r->name, &OOLUA::INTERNAL::const_member_caller<T, B >
																 , methods, reinterpret_cast<void*>(r));
				}
				Register_base_methods<T
							, typename Proxy_class<B>::Bases
							, 0
							, typename TYPELIST::At_default< typename Proxy_class<B>::Bases, 0, TYPE::Null_type >::Result
				> b;
				b(vm, methods);
			}
		};

		template<typename T>
		struct Add_base_methods<T, TYPE::Null_type>
		{
			void operator()(lua_State *  const /*vm*/,int const/*methods*/){}///no-op
		};

		template<typename T, typename TL, int index, typename B>
		struct Register_base_methods
		{
			void operator()(lua_State * const vm, int const methods)
			{
				Add_base_methods<T, typename TYPELIST::At_default< TL, index, TYPE::Null_type >::Result> adder;
				adder(vm, methods);
				Register_base_methods<T, TL, index + 1, typename TYPELIST::At_default< TL, index + 1, TYPE::Null_type >::Result> base;
				base(vm, methods);
			}
		};

		template<typename T, typename TL, int index>
		struct Register_base_methods<T, TL, index, TYPE::Null_type>
		{
			void operator()(lua_State * const  /*vm*/, int const /*methods*/){}///no-op
		};

		template<typename T>
		void sets_oolua_userdata_creation_key_value_in_table(lua_State* vm, int const table)
		{
			lua_pushinteger(vm, 1);
			lua_pushcclosure(vm, top<T>, 0);
			lua_rawset(vm, table);
			lua_pushinteger(vm, 2);
			lua_pushcclosure(vm, middle<T>, 0);
			lua_rawset(vm, table);
			lua_pushinteger(vm, 3);
			lua_pushcclosure(vm, bottom<T>, 0);
			lua_rawset(vm, table);
			set_oolua_userdata_creation_key_value_in_table(vm, table);
		}

		template<typename T>
		struct class_or_base_has_ctor_block
		{
			template<typename U>
			static char(& check_for_ctor_block(typename OOLUA::Proxy_class<U>::ctor_block_check*))[1]; // NOLINT
			template<typename U>
			static char(& check_for_ctor_block(...))[2]; // NOLINT
			enum {value = sizeof(check_for_ctor_block<T >(0)) == 1 ? 1 : 0};
		};

		template< typename T, int CtorBlockMaybeInClass_or_MaybeInABase>
		struct ctor_block_is_same
		{
			enum {value = LVD::is_same< typename Proxy_class<T>::ctor_block_check, T >::value };
		};

		template< typename T>
		struct ctor_block_is_same<T, 0>
		{
			enum {value = 0};
		};

		template< typename T>
		struct proxy_class_has_correct_ctor_block
		{
			enum { value = ctor_block_is_same<T, class_or_base_has_ctor_block<T>::value >::value  };
		};

		// LCOV_EXCL_START
		template<typename TL, int Index, typename T>
		struct info_getter
		{
			static void add(lua_State* vm)
			{
				top<T>(vm);
				info_getter<TL
						, Index+1
						, typename TYPELIST::At_default<TL, Index+1, TYPE::Null_type>::Result
					>::add(vm);
			}
		};

		template<typename TL, int Index>
		struct info_getter<TL, Index, TYPE::Null_type>
		{
			static void add(lua_State* /*vm*/) //NOLINT(readability/casting)
			{}
		};
		// LCOV_EXCL_STOP

		template<typename T, bool IsAbstractOrNoConstructors>
		struct set_create_function
		{
			static void do_set(lua_State* const vm, int methods, LVD::Int2type<1> /*use factory function*/)
			{
				set_function_in_table(vm
									  , new_str
									  , &OOLUA::Proxy_class<T>::oolua_factory_function
									  , methods);
			}
			static void do_set(lua_State* const vm, int methods, LVD::Int2type<0> /*needs generic function*/)
			{
				set_function_in_table(vm
									  , new_str
									  , &oolua_generic_default_constructor<T>
									  , methods);
			}
			static void set(lua_State*  const vm, int methods)
			{
				do_set(vm, methods, LVD::Int2type<proxy_class_has_correct_ctor_block<T>::value>());
				// methods["new"] = some_method
			}
		};

		template<typename T>
		struct set_create_function<T, true>
		{
			static void set(lua_State*  const /*vm*/,int /*methods*/){}///no-op
		};


		template<typename T, bool HasNoDestructors>
		struct set_owner_function
		{
			static void set(lua_State*  const vm, int methods)
			{
				set_function_in_table(vm
									  , set_owner_str
									  , &INTERNAL::lua_set_owner<T>
									  , methods);
				//methods["set_owner"]=&lua_set_owner()
			}
		};

		template<typename T>
		struct set_owner_function<T, true>
		{
			static void set(lua_State*  const /*vm*/, int /*methods*/){}///no-op
		};


		template<typename T>
		inline void register_class_imp(lua_State * vm)
		{
			if(class_name_is_already_registered(vm, Proxy_class<T>::class_name))
				return;
			lua_newtable(vm);
			int methods = lua_gettop(vm);//methods

			luaL_newmetatable(vm, Proxy_class<T>::class_name);//methods mt
			//registry[name]= mt
			int mt = lua_gettop(vm);

			// store method table in globals so that scripts can add functions written in Lua.
			lua_pushvalue(vm, methods);
			lua_setglobal(vm, Proxy_class<T>::class_name);
			//global[name]=methods

			register_oolua_type(vm, Proxy_class<T>::class_name, methods);
			//OOLua[name] = methods

			sets_oolua_userdata_creation_key_value_in_table<T>(vm, mt);

			set_key_value_in_table(vm, "__index", methods, mt);
			//mt["__index"]= methods

			//allow statics and functions to be added to the userdatatype metatable
			set_key_value_in_table(vm, "__newindex", methods, mt);
			//mt["__newindex"]= methods

			set_base_lookup_function<T
					, LVD::if_or<has_tag<Proxy_class<T>, Abstract >::Result
						, has_tag<Proxy_class<T>, No_public_constructors >::Result
						>::value
				>::set(vm, methods);
			//methods["__index"] = function to search bases classes for the key

			set_delete_function<T, INTERNAL::has_tag<Proxy_class<T>, No_public_destructor >::Result>::set(vm, mt);

			set_create_function<T
					, LVD::if_or<has_tag<Proxy_class<T>, Abstract >::Result
						, has_tag<Proxy_class<T>, No_public_constructors >::Result
						>::value
				>::set(vm, methods);

			set_owner_function<T, has_tag<Proxy_class<T>, No_public_destructor >::Result>::set(vm, methods);

			set_equal_function<T, has_tag<Proxy_class<T>, Equal_op>::Result>::set(vm, mt);
			set_less_than_function<T, has_tag<Proxy_class<T>, Less_op>::Result>::set(vm, mt);
			set_less_than_or_equal_function<T, has_tag<Proxy_class<T>, Less_equal_op>::Result>::set(vm, mt);
			set_add_function<T, has_tag<Proxy_class<T>, Add_op>::Result>::set(vm, mt);
			set_sub_function<T, has_tag<Proxy_class<T>, Sub_op>::Result>::set(vm, mt);
			set_mul_function<T, has_tag<Proxy_class<T>, Mul_op>::Result>::set(vm, mt);
			set_div_function<T, has_tag<Proxy_class<T>, Div_op>::Result>::set(vm, mt);

			set_class_enums<T, INTERNAL::has_tag<Proxy_class<T>, Register_class_enums>::Result>::set(vm);

			// fill method table with methods from class Proxy_class<T>
			for (typename Proxy_class<T >::Reg_type *r = Proxy_class<T >::class_methods; r->name; r++)
			{
				set_function_in_table_with_upvalue(vm
												 , r->name
												 , &member_caller<Proxy_class<T>, T>
												 , methods
												 , reinterpret_cast<void*>(r));
			}

			// fill constant method table with methods from class Proxy_class<T>
			for (typename Proxy_class<T >::Reg_type_const *r = Proxy_class<T >::class_methods_const; r->name; ++r)
			{
				set_function_in_table_with_upvalue(vm
												 , r->name
												 , &const_member_caller<Proxy_class<T>, T>
												 , methods
												 , reinterpret_cast<void*>(r));
			}

			//recursively register any base class methods
			Register_base_methods<Proxy_class<T>
									, typename Proxy_class<T>::Bases
									, 0
									, typename TYPELIST::At_default<typename Proxy_class<T>::Bases, 0, TYPE::Null_type >::Result
								> recursive_worker;
			recursive_worker(vm, methods);

			lua_pushvalue(vm, methods);
			lua_setmetatable(vm, methods);//set methods as it's own metatable
			lua_pop(vm, 2);
		}
	} // namespace INTERNAL // NOLINT
	/**\endcond*/

	template<typename T, typename K, typename V>
	inline void register_class_static(lua_State * const vm, K const& k, V const& v)
	{
		Table meth(vm, Proxy_class<T>::class_name);
		meth.set(k, v);
	}

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<int Index, typename Bases, typename Type>
		struct Register_bases_with_lua;

		template<int Index, typename Bases, typename Type>
		struct Register_bases_with_lua
		{
			static void work(lua_State * vm)
			{
				register_class_imp<Type>(vm);
				Register_bases_with_lua<Index+1
								, Bases
								, typename TYPELIST::At_default<Bases, Index+1, TYPE::Null_type>::Result
						>::work(vm);
			}
		};
		template<int index, typename TL>
		struct Register_bases_with_lua<index, TL, TYPE::Null_type>
		{
			static void work(lua_State * /*vm*/) // NOLINT
			{}
		};
	} // namespace INTERNAL // NOLINT
	/** \endcond*/

	template<typename T>
	inline void register_class(lua_State * vm)
	{
		INTERNAL::register_class_imp<T>(vm);
		INTERNAL::Register_bases_with_lua<0
								, typename OOLUA::Proxy_class<T>::AllBases
								, typename TYPELIST::At_default<typename OOLUA::Proxy_class<T>::AllBases, 0, TYPE::Null_type>::Result
						>::work(vm);
	}

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
/**
	\file oolua_script.h
	\brief Provides the helper class OOLUA::Script
*/

#ifndef OOLUA_SCRIPT_H_
#	define OOLUA_SCRIPT_H_

#include <string>

namespace OOLUA
{

	/** \class Script
		\brief OOLua helper class
		\details
		OOLua is purposely designed not to be dependent on the \ref OOLUA::Script "Script" class
		and therefore passes around its dependency of a lua_State instance.
		The Script class is only a helper and anything you can do with it
		can be accomplished by using a \ref OOLUA::Lua_function "Lua_function" struct,
		calling OOLUA namespaced functions or using the Lua C API.

		Script provides :
		\li scoping of a lua_State pointer
		\li access to the lua_State pointer via a \ref OOLUA::Script::operator  "cast operator" and \ref OOLUA::Script::state "function"
		\li methods to \ref OOLUA::Script::register_class "register" types
		\li binding a \ref OOLUA::Lua_function "Lua_function" instance to \ref OOLUA::Script::call "call" functions
		\li member functions for a little state management
		\li \ref OOLUA::setup_user_lua_state "setting up" the state to work with OOLua

		\note
		This class is not copy constructible or assignable.
		To accomplish this a counted reference to the lua_State would need to be
		maintained.
		\note If you do not want to or can not use this class please see
		\ref OOLUA::setup_user_lua_state "setup_user_lua_state"
	*/
	class Script
	{
	public:
		/** Function object instance which can be used to call Lua functions*/
		Lua_function call;

		/**@{*/
		/**
			\brief Initialises the instance.
			\details
				\li Creates a new Lua universe
				\li Binds the public member call with the lua_State
				\li Sets the lua_State up so that it will work with OOLUA::Proxy_class.
		*/
		Script();
		/**
			\brief Releases the bound lua_State if it is not NULL
		*/
		~Script();
		/**@}*/

		/**@{*/
		/** \brief Returns the stack count from the lua_State */
		int stack_count(){ return lua_gettop(m_lua); }
		/** \brief Conversion operator so that a \ref OOLUA::Script "Script"
			instance can be passed in place of a lua_State pointer*/
		operator lua_State * () const {return m_lua;}
		/** \brief Sometimes you may want to be explicit \see Script::operator()  */
		lua_State * const & state() const {return m_lua;}
		/** \brief Performs a garbage collection on the state*/
		void gc();
		/**@}*/

		/**@{*/
		/** \brief Helper function \see OOLUA::register_class*/
		template<typename T>
		void register_class();
		/** \brief Helper function \see OOLUA::register_class*/
		template<typename T>
		void register_class(T* /*dummy*/); // NOLINT
		/** \brief Helper function \see OOLUA::register_class_static */
		template<typename T, typename K, typename V>
		void register_class_static(K const& k, V const& v);
		/**@}*/

		/**@{*/
		/** \brief Helper function \see OOLUA::run_file */
		bool run_file(std::string const & filename);
		/** \brief Helper function \see OOLUA::load_file */
		bool load_file(std::string const & filename);
		/** \brief Helper function \see OOLUA::load_chunk */
		bool load_chunk(std::string const& chunk);
		/** \brief Helper function \see OOLUA::run_chunk */
		bool run_chunk(std::string const& chunk);
		/**@}*/

		/**@{*/
		/** \brief Helper function \see OOLUA::pull */
		template<typename T>
		bool pull(T & t);
		/** \brief Helper function \see OOLUA::push */
		template<typename T>
		bool push(T const& t);
		/**@}*/

	protected:
		void close_down();
		Script(Script const&);
		Script& operator = (Script const&);
		lua_State* m_lua;
	};


	template<typename T>
	inline void Script::register_class()
	{
		OOLUA::register_class<T>(m_lua);
	}

	template<typename T>
	inline void Script::register_class(T* /*dummy*/) // NOLINT
	{
		register_class<T>();
	}

	template<typename T, typename K, typename V>
	inline void Script::register_class_static(K const& k, V const& v)
	{
			OOLUA::register_class_static<T>(m_lua, k, v);
	}

	template<typename T>
	inline bool Script::push(T const& value)
	{
		return OOLUA::push(*this, value);
	}

	template<typename T>
	inline bool Script::pull(T& value)
	{
		return OOLUA::pull(*this, value);
	}

} //namespace OOLUA

#endif //OOLUA_SCRIPT_H_
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
	\file oolua_stack.h
	\brief Makes available implementations for the stack operations OOLUA::push
	and OOLUA::pull, which have forward declarations in oolua_stack_fwd.h
*/
#ifndef OOLUA_STACK_H_
#	define OOLUA_STACK_H_


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

#ifndef OOLUA_STACK_DUMP_H_
#	define OOLUA_STACK_DUMP_H_

struct lua_State;

namespace OOLUA
{
	void lua_stack_dump(lua_State * const vm);
} // namespace OOLUA

#endif // OOLUA_STACK_DUMP_H_
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
	\file oolua_version.h
	\brief OOLua library version information for both the CPP and at run time
*/

#ifndef OOLUA_VERSION_H_
#	define OOLUA_VERSION_H_

#	define OOLUA_DO_STRINGISE(a) #a
#	define OOLUA_STRINGISE(a) OOLUA_DO_STRINGISE(a)

/**
	\def OOLUA_VERSION_MAJ
	\brief CPP major version number
*/
#	define OOLUA_VERSION_MAJ 2

/**
	\def OOLUA_VERSION_MIN
 	\brief CPP minor version number
 */
#	define OOLUA_VERSION_MIN 0

/**
	\def OOLUA_VERSION_PATCH
	\brief CPP patch version number
*/
#	define OOLUA_VERSION_PATCH 1

/**
	\def OOLUA_VERSION
	\showinitializer
	\brief CPP string detailing the library version
*/
#	define OOLUA_VERSION \
					OOLUA_STRINGISE(OOLUA_VERSION_MAJ) "." \
					OOLUA_STRINGISE(OOLUA_VERSION_MIN) "." \
					OOLUA_STRINGISE(OOLUA_VERSION_PATCH)


namespace OOLUA
{
	/**
		\var version_str
		\showinitializer
		\brief OOLua version string
	*/
	static const char version_str[] = OOLUA_VERSION;
	/**
		\var version_number
		\brief OOLua version int
	*/
	static const int version_number = OOLUA_VERSION_MAJ*10000+OOLUA_VERSION_MIN*1000+OOLUA_VERSION_PATCH;
} // namespace OOLUA

#	undef OOLUA_DO_STRINGISE
#	undef OOLUA_STRINGISE

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
/**
	\file proxy_constructor_param_tester.h
	\brief Helps test that a constructor parameter is of the requested type
	so that a matching constructor can be called
*/

#ifndef OOLUA_PROXY_CONSTRUCTOR_PARAM_TESTER_H_
#	define OOLUA_PROXY_CONSTRUCTOR_PARAM_TESTER_H_


namespace OOLUA
{
	/** \cond INTERNAL */
	//fwd declare
	template<int ID>
	struct Lua_ref;

	namespace INTERNAL
	{
		/*
		#define LUA_TNIL		0
		#define LUA_TBOOLEAN		1
		#define LUA_TLIGHTUSERDATA	2
		#define LUA_TNUMBER		3
		#define LUA_TSTRING		4
		#define LUA_TTABLE		5
		#define LUA_TFUNCTION		6
		#define LUA_TUSERDATA		7
		#define LUA_TTHREAD		8
		*/

		//Used for constructors to check parameters on the stack
		template<typename Cpp_type, int Lua_type>
		struct lua_type_is_cpp_type;

		/*
		Specialisation
		This is required as Type_enum_defaults will strip the pointer and then can_convert_to_int
		uses the resulting type with a reference applied. This means it will try to use
		void& which is illegal.
		*/
		template<>
		struct lua_type_is_cpp_type<void*, LUA_TNUMBER>
		{
			enum {value = 0 };
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TNUMBER>
		{
			enum {value = (Type_enum_defaults<Cpp_type>::is_integral
							|| is_scoped_enum<Cpp_type>::value)
					&& !LVD::is_same<bool, Cpp_type>::value };
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TSTRING>
		{
			enum { value = LVD::is_same<char*, Cpp_type>::value
					|| OOLUA::STRING::is_integral_string_class<Cpp_type>::value };
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TBOOLEAN>
		{
			enum {value = LVD::is_same<bool, Cpp_type>::value};
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TFUNCTION>
		{
			enum {value = LVD::is_same<Lua_ref<LUA_TFUNCTION>, Cpp_type>::value};
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TTABLE>
		{
			typedef Type_list<
			Lua_ref<LUA_TTABLE>, Table
			>::type Table_types;
			enum {value = TYPELIST::IndexOf<Table_types, Cpp_type>::value == -1 ? 0 : 1};
		};

		template<typename Cpp_type>
		struct lua_type_is_cpp_type<Cpp_type, LUA_TLIGHTUSERDATA>
		{
			enum {value = LVD::is_same<void*, Cpp_type>::value};
		};




		/**
			\struct index_can_convert_to_type
			\brief Implements the testing of a stack index type against a requested
			OOLUA::Proxy_class userdata type
			\details If Is_integral is none zero then translates to a nop, otherwise
			\ref OOLUA::INTERNAL::index_can_convert_to_type::valid tests the userdata
			taking into accont the constness of the types and if stack type is correct
			for the required type.
			\tparam TypeWithTraits
			\tparam Is_integral
		*/
		template<typename TypeWithTraits, int Is_integral>
		struct index_can_convert_to_type
		{
			static int valid(lua_State* /*vm*/,int const& /*index*/){return 0;}//noop
		};

		template<typename TypeWithTraits>
		struct index_can_convert_to_type<TypeWithTraits, 0>
		{
			static int valid(lua_State* vm, int index)
			{
MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA
				if( OOLUA::INTERNAL::check_index<typename TypeWithTraits::raw>(vm, index) )
				{
					return !( !TypeWithTraits::is_constant
									&& INTERNAL::userdata_is_constant(static_cast<INTERNAL::Lua_ud *>(lua_touserdata(vm, index))) );
				}
				return 0;
MSC_POP_COMPILER_WARNING_OOLUA
			}
		};

		/**
			\struct Param_helper
			\brief Tests a requested type against a stack index type.
			\details Constructors support overloading, therefore there is a need to
			test the type at a specific stack location against the required type for the
			constructor parameter; this structure with it's static method implements some
			of that checking.
			As it is possible for the type to not actually be on the stack
			(see OOLUA::calling_lua_state) it also needs to increment the stack index
			when the type is correct, this ensures that any following parameters use the
			correct stack index.
			\tparam ParamWithTraits The current requested parameter type, with traits applied,
			for the stack index.
		*/
		template<typename ParamWithTraits>
		struct Param_helper;

		/**
			\struct Param_helper<OOLUA::INTERNAL::param_type<OOLUA::calling_lua_state> >
			Specialisation for OOLUA::calling_lua_state which is never a type on the stack,
			it therefore never increments the stack index and valid always returns
			a valid result.
		*/
		template<>
		struct Param_helper<param_type<calling_lua_state> >
		{
			static int param_is_of_type(lua_State* /*vm*/, int& /*index*/) //NOLINT
			{
				return 1;
			}
		};

		template<typename ParamWithTraits>
		struct Param_helper
		{
			static int param_is_of_type(lua_State* vm, int & index)
			{
				switch ( lua_type(vm, index) )
				{
					case LUA_TBOOLEAN :
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TBOOLEAN>::value && ++index ? 1 : 0;
					case LUA_TNUMBER :
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TNUMBER>::value && ++index ? 1 : 0;
					case LUA_TSTRING :
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TSTRING>::value && ++index ? 1 : 0;
					case LUA_TFUNCTION :
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TFUNCTION>::value && ++index ? 1 : 0;
					case LUA_TTABLE :
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TTABLE>::value && ++index ? 1 : 0;
					case LUA_TUSERDATA:
						if( index_can_convert_to_type<ParamWithTraits, ParamWithTraits::is_integral>::valid(vm, index) )
						{
							++index;
							return 1;
						}
						return 0;
					case LUA_TLIGHTUSERDATA:
						return lua_type_is_cpp_type<typename ParamWithTraits::raw, LUA_TLIGHTUSERDATA>::value && ++index ? 1 : 0;
					default:
						return 0;
						break;
				}
			}
		};
	} // namespace INTERNAL // NOLINT
	/** \endcond */
} // namespace OOLUA

#endif //OOLUA_PROXY_CONSTRUCTOR_PARAM_TESTER_H_
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

#ifndef OOLUA_PROXY_CONSTRUCTOR_H_
#	define OOLUA_PROXY_CONSTRUCTOR_H_

/**
	\file proxy_constructor.h
	\brief Implements Proxy_class constructor handlers and the constructor block.
*/


#if defined __GNUC__ && defined __STRICT_ANSI__
/*shhhhh about va args and c99*/
#	pragma GCC system_header
#endif

/** \cond INTERNAL*/


#if	OOLUA_USE_EXCEPTIONS ==1

#	define OOLUA_CONSTRUCTOR_TRY \
	try {
// NOLINT

#	define OOLUA_CONSTRUCTOR_RESPONSE(ExceptionType, Class, ArgNums) \
	luaL_error(vm, "%s exception in %d argument %s constructor. what() : %s" \
			, ExceptionType \
			, ArgNums \
			, OOLUA::Proxy_class<Class>::class_name \
			, err.what());

#	define OOLUA_CONSTRUCTOR_CATCH(Class, Num) \
	} \
	catch(OOLUA::Runtime_error const& err) \
	{ \
		OOLUA_CONSTRUCTOR_RESPONSE("OOLUA::Runtime_error", Class, Num)\
	}\
	catch(std::exception const& err) \
	{ \
		OOLUA_CONSTRUCTOR_RESPONSE("std::exception", Class, Num)\
	}\
	catch(...) \
	{ \
		luaL_error(vm, "unknown exception in %s %d argument constructor", OOLUA::Proxy_class<Class>::class_name, Num); \
	}
#else
#	define OOLUA_CONSTRUCTOR_TRY
#	define OOLUA_CONSTRUCTOR_CATCH(Class, Num)
#endif


namespace OOLUA
{
	namespace INTERNAL
	{
		/**\addtogroup OOLuaDeveloperDocs
		@{*/

		/**
			\brief Default constructor for a type
			\tparam Type Type to construct
			\tparam HasNoDefaultTypedef None zero indicates the type does not have the
				\ref No_default_constructor tag
			\pre Will never be called on a type which has the \ref No_public_constructors tag
		*/
		template<typename Type, int HasNoDefaultTypedef>
		struct Constructor
		{
			static int construct(lua_State * vm)
			{
				OOLUA_CONSTRUCTOR_TRY
				typename new_pointer<Type>::type obj(new Type);
				add_ptr(vm, obj, false, Lua);
				OOLUA_CONSTRUCTOR_CATCH(Type, 0)
				return 1;
			}
		};

		/**
		 	\brief Specialisation which generates a Lua error
		 	\details The static function construct will only be called when
		 		\li The type does not have a default constructor
		 		\li and
		 		\li There were no parameters passed to the new call.
		*/
		template<typename Type>
		struct Constructor<Type, 1>
		{
			static int construct(lua_State * vm)
			{
				return luaL_error(vm, "%s %s %s", "No parameters passed to the constructor of the type"
						   , OOLUA::Proxy_class<Type>::class_name
						   , "which does not have a default constructor.");
			}
		};

		/**
			\brief Default constructor handler
		*/
		template<typename T>
		inline int oolua_generic_default_constructor(lua_State* vm)
		{
			int const stack_count = lua_gettop(vm);
			if(stack_count == 0 )
			{
				return Constructor<T, has_tag<OOLUA::Proxy_class<T>, OOLUA::No_default_constructor>::Result>::construct(vm);
			}
			return luaL_error(vm, "%s %d %s %s", "Could not match", stack_count, "parameter constructor for type", OOLUA::Proxy_class<T>::class_name);
		}
		/**@}*/
	} // namespace INTERNAL // NOLINT
} // namespace OOLUA

/** \addtogroup OOLuaGeneratorTemplates
@{
*/
/**
	\def OOLUA_CONSTRUCTOR_GENERATE_NUM
	\hideinitializer
	\brief Constructor generator template
	\details
	\param NUM Number of parameters this macro will generate a constructor handler for
*/
#define OOLUA_CONSTRUCTOR_GENERATE_NUM(NUM) \
namespace OOLUA \
{ \
	namespace INTERNAL \
	{ \
		template<typename Class OOLUA_COMMA_PREFIXED_TYPENAMES_##NUM > \
		struct Constructor##NUM \
		{ \
			static int construct(lua_State* vm) \
			{ \
				int index(1); \
				if(OOLUA_CONSTRUCTOR_PARAM_IS_OF_TYPE_##NUM) \
				{ \
					valid_construct(vm); \
					return 1; \
				} \
				return 0; \
			} \
			static void valid_construct(lua_State* vm) \
			{ \
				int index(1); \
				OOLUA_CONSTRUCTOR_PARAM_##NUM \
				OOLUA_CONSTRUCTOR_TRY \
				typename new_pointer<Class>::type obj(new Class(OOLUA_CONVERTER_PARAMS_##NUM)); \
				add_ptr(vm, obj, false, Lua); \
				OOLUA_CONSTRUCTOR_CATCH(Class, NUM) \
			} \
		}; \
	} /* namespace INTERNAL*/ /*NOLINT*/\
} /* namespace OOLUA*/
/*@}*/


OOLUA_INTERNAL_CONSTRUCTORS_GEN

/**
	\addtogroup OOLuaDeveloperDocs
@{*/

/**
	\def OOLUA_CONSTRUCTORS_BEGIN
	\hideinitializer
	\brief Starts the generation of the static factory function for an OOLUA::Proxy_class
*/
#define OOLUA_CONSTRUCTORS_BEGIN \
static int oolua_factory_function(lua_State* vm) \
{ \
	int const stack_count = lua_gettop(vm);
/**@}*/
/** \endcond*/

/** \addtogroup OOLuaDSL
 @{
	\def OOLUA_CTOR
	\hideinitializer
	\brief Generates a constructor in a constructor block \see OOLUA_CTORS
	\details
	OOLUA_CTOR( ConstructorParameterList)
	\param ConstructorParameterList Comma separated list of parameters
	\pre Size of ConstructorParameterList >0 and <= \ref OOLuaConfigConstructorParams "\"constructor_params\""
	\see \ref OOLuaConfigConstructorParams "constructor_params"
 */
#define OOLUA_CTOR(...) \
	MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
	if( (stack_count == OOLUA_NARG(__VA_ARGS__) && TYPELIST::IndexOf<Type_list< __VA_ARGS__ >::type, calling_lua_state>::value == -1) \
	|| (stack_count == OOLUA_NARG(__VA_ARGS__)-1 && TYPELIST::IndexOf<Type_list< __VA_ARGS__ >::type, calling_lua_state>::value != -1) ) \
	{ \
		if( OOLUA_VA_CONSTRUCTOR(__VA_ARGS__)<class_ VA_PARAM_TYPES(__VA_ARGS__) >::construct(vm) ) return 1; \
	} \
	MSC_POP_COMPILER_WARNING_OOLUA
/**@}*/

/** \cond INTERNAL*/
/**
	\addtogroup OOLuaDeveloperDocs
@{*/

/**
	\def OOLUA_CONSTRUCTORS_END
	\hideinitializer
	\brief Ends the generation of the static factory function for an OOLUA::Proxy_class
	\details This macro ends the factory function for an OOLUA::Proxy_class and also places
	into the type a typedef named ctor_block_check, which is an alias for the type being proxied.
	The presence of this alias can be checked for at a later point to determine if the type
	does indeed have a factory function. After trying all constructors for which the stack count
	is valid for, if it was unable to find a matching constructor then a Lua error is thrown.
*/
#define OOLUA_CONSTRUCTORS_END \
	if(stack_count == 0 ) \
	{ \
		return INTERNAL::Constructor<class_, INTERNAL::has_tag<this_type, No_default_constructor>::Result>::construct(vm); \
	} \
	return luaL_error(vm, "%s %d %s %s", "Could not match", stack_count, "parameter constructor for type", class_name); \
} \
	typedef class_ ctor_block_check;
/**@}*/
/** \endcond*/

/** \addtogroup OOLuaDSL
@{
	\def OOLUA_CTORS
	\hideinitializer
	\brief Creates a block into which none default constructors can be defined using \ref OOLUA_CTOR
	\details OOLUA_CTORS(ConstructorEntriesList)
	\param ConstructorEntriesList List of \ref OOLUA_CTOR
	<p>
	To enable the construction of an instance without using the default constructor, there must be
	a constructor block specified for the proxy type. The constructor block, \ref OOLUA_CTORS,
	is where non-default constructor entries can be specified using an \ref OOLUA_CTOR per entry.
	<p>
	Constructors are the only real type of overloading which is permitted by OOLua
	and there is an important point which should be noted. This being that OOLua will
	attempt to match the number and type of parameters on the stack with the amount
	and types specified for each OOLUA_CTOR entry. The order in which it will attempt
	the matching is the same order in which they were defined. When interacting with the Lua
	stack certain types can not be differentiated between, these include some integral
	types such as float, int, double etc and types which are of a proxy class type or
	derived from that type. OOLua implicitly converts between classes in a hierarchy
	even if a reference is required. This means for example that if there are constructors
	such as Foo::Foo(int) and Foo::Foo(float) it will depend on which was defined first
	in the OOLUA_CTORS block as to which will be invoked for a call such as Foo.new(1).

	\see \ref OOLUA::No_default_constructor "No_default_constructor"
	\note An OOLUA_CTORS block without any \ref OOLUA_CTOR entries is invalid.
*/
#	define OOLUA_CTORS(ConstructorEntriesList) OOLUA_CONSTRUCTORS_BEGIN ConstructorEntriesList OOLUA_CONSTRUCTORS_END
/**@}*/


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
/**
	\file proxy_member_function.h
	\brief Internal macros which generate proxy member functions
*/

#ifndef OOLUA_PROXY_MEMBER_FUNCTION_H_
#	define OOLUA_PROXY_MEMBER_FUNCTION_H_



#	include <cassert>

#if defined __GNUC__ && defined __STRICT_ANSI__
#	pragma GCC system_header
#endif

/** \cond INTERNAL*/

/**
	\def OOLUA_MEMBER_BODY_N
	\hideinitializer
	\brief Generates a member function with at least one parameter
	\param mod Optional either const of empty
	\param func_name Name to be used for the proxy function
	\param return_value Return type
	\param func Function name which will be proxied
	\param ... __VA_ARGS__ list of parameters
*/
#define OOLUA_MEMBER_BODY_N(mod, func_name, return_value, func , ...) \
int func_name(lua_State* const vm) mod \
{ \
	assert(m_this); \
	OOLUA_PARAMS_CONCAT(2, __VA_ARGS__) \
	typedef INTERNAL::return_type_traits<return_value > R; \
	typedef R::type (class_::*funcType )( OOLUA_PARAM_TYPE_CONCAT(__VA_ARGS__) ) mod ; \
	OOLUA::INTERNAL::Proxy_caller<R, class_, LVD::is_void< R::type >::value > \
		::call<funcType OOLUA_TPARAMS_CONCAT(__VA_ARGS__) > \
			(vm, m_this, &class_::func OOLUA_PPARAMS_CONCAT(__VA_ARGS__)); \
	OOLUA_BACK_CONCAT(__VA_ARGS__) \
	return INTERNAL::lua_return_count< Type_list<R OOLUA_RETURNS_CONCAT(__VA_ARGS__) > \
		::type> ::out; \
}

/**
	\def OOLUA_MEMBER_BODY_0
	\hideinitializer
	\brief Generates a member function with no parameters
	\param mod Optional either const or empty
	\param func_name Name to be used for the proxy function
	\param return_value Return type
	\param func Function name which will be proxied
*/
#define OOLUA_MEMBER_BODY_0(mod, func_name, return_value, func) \
int func_name(lua_State* const vm) mod\
{ \
	assert(m_this); \
	typedef INTERNAL::return_type_traits<return_value > R; \
	typedef R::type (class_::*funcType )() mod ; \
	OOLUA::INTERNAL::Proxy_caller<R, class_, LVD::is_void< R::type >::value > \
		::call< funcType>(vm, m_this, &class_::func); \
	return INTERNAL::lua_return_count< Type_list<R >::type> ::out; \
}
//	OOLUA_MEM_FUNC_N and OOLUA_MEM_FUNC_0

/**
	@{
	/details
	A member function defined using OOLUA_MEM_FUNC*  (*=  |_CONST | _RENAME | _CONST_RENAME )
	will translate into a corresponding macro below using either a suffix of _N if there are
	function parameters else _0
*/

/**
	\def OOLUA_MEM_FUNC_N
	\brief Generates a none constant proxy which will have the same name as the proxied function
	\pre The proxied function will have one or more function parameters
	\hideinitializer
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name to use for the proxied function and also the name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_N(return_value, func , ...) \
	OOLUA_MEMBER_BODY_N(      , func, return_value, func , __VA_ARGS__ ) /*NOLINT*/

/**
	\def OOLUA_MEM_FUNC_CONST_N
	\brief Generates a constant proxy which will have the same name as the proxied function
	\pre The proxied function will have one or more function parameters
	\hideinitializer
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name to use for the proxy function and also the name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_CONST_N(return_value, func , ...) \
	OOLUA_MEMBER_BODY_N(const , func, return_value, func , __VA_ARGS__ )

/**
	\def OOLUA_MEM_FUNC_RENAME_N
	\brief Generates a none constant proxy which will have a differnt name from the proxied function
	\pre The proxied function will have one or more function parameters
	\hideinitializer
	\param name Name to use for the proxy function
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_RENAME_N(name, return_value, func , ...) \
	OOLUA_MEMBER_BODY_N(      , name, return_value, func , __VA_ARGS__ ) /*NOLINT*/

/**
	\def OOLUA_MEM_FUNC_CONST_RENAME_N
	\brief Generates a constant proxy which will have a different name from the proxied function
	\pre The proxied function will have one or more function parameters
	\hideinitializer
	\param name Name to use for the proxy function
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_CONST_RENAME_N(name, return_value, func , ...) \
	OOLUA_MEMBER_BODY_N(const , name, return_value, func , __VA_ARGS__ )

/**
	\def OOLUA_MEM_FUNC_0
	\brief Generates a none constant proxy which will have the same name as the proxied function
	\pre The proxied function will have no function parameters
	\hideinitializer
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name to use for the proxy function and also the name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_0(return_value, func) \
	OOLUA_MEMBER_BODY_0(      , func, return_value, func) /*NOLINT*/

/**
	\def OOLUA_MEM_FUNC_CONST_0
	\brief Generates a constant proxy which will have the same name as the proxied function
	\pre The proxied function will have no function parameters
	\hideinitializer
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name to use for the proxy function and also the name of the proxied function
*/
#define OOLUA_MEM_FUNC_CONST_0(return_value, func) \
	OOLUA_MEMBER_BODY_0(const , func, return_value, func)

/**
	\def OOLUA_MEM_FUNC_RENAME_0
	\brief Generates a none constant proxy which will have a different name from the proxied function
	\pre The proxied function will have no function parameters
	\hideinitializer
	\param name Name to use for the proxy function
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name of the proxied function
*/
#define OOLUA_MEM_FUNC_RENAME_0(name, return_value, func) \
	OOLUA_MEMBER_BODY_0(      , name, return_value, func) /*NOLINT*/

/**
	\def OOLUA_MEM_FUNC_CONST_RENAME_0
	\brief Generates a constant proxy which will have a different name from the proxied function
	\pre The proxied function will have no function parameters
	\hideinitializer
	\param name Name to use for the proxy function
	\param return_value The return type of the proxied function possibily with \ref OOLuaTraits
	\param func Name of the proxied function
	\param ... __VA_ARGS__ of parameters which can also have traits
*/
#define OOLUA_MEM_FUNC_CONST_RENAME_0(name, return_value, func) \
	OOLUA_MEMBER_BODY_0(const , name, return_value, func)
/**	@}*/

/**
	\def OOLUA_MFUNC_GENERIC
	\hideinitializer
	\brief Generates a generic member function for OOLUA::Proxy_class
	\details Internal macro used by the Minimal DSL, it will generate either
	a constant or none constant member function for the Proxy_class depending
	on the mod parameter. As this proxy function is part of the Minimal DSL
	it does not allow specifiying traits from the function return value or
	parameters, insted it uses default traits for all.
	\param mod Optional parameter which is either const or empty
	\param ProxyName Name that will be given to the proxy member function
	\param FunctionName Name of the member function to be proxied
*/
#define OOLUA_MFUNC_GENERIC(mod, ProxyName, FunctionName) \
	int ProxyName(lua_State* vm) mod \
	{ \
		return OOLUA::INTERNAL::mod##proxy_member_function_with_default_traits(vm, m_this, &class_::FunctionName); \
	}

/**
	@{
 	\details
 	OOLUA_MFUNC(_CONST)_INTERNAL_2 and OOLUA_MFUNC(_CONST)_INTERNAL_1
 	A member function defined using OOLUA_MFUNC*  (*=  |_CONST )
 	will translate into a corresponding macro below using and then to OOLUA_MFUNC_GENERIC
 */
#define OOLUA_MFUNC_INTERNAL_2(FunctionName, ProxyName)		OOLUA_MFUNC_GENERIC( , ProxyName, FunctionName) /*NOLINT*/
#define OOLUA_MFUNC_INTERNAL_1(FunctionName)				OOLUA_MFUNC_INTERNAL_2(FunctionName, FunctionName)

#define OOLUA_MFUNC_CONST_INTERNAL_2(FunctionName, ProxyName)	OOLUA_MFUNC_GENERIC(const, ProxyName, FunctionName)
#define OOLUA_MFUNC_CONST_INTERNAL_1(FunctionName)				OOLUA_MFUNC_CONST_INTERNAL_2(FunctionName, FunctionName)
/**@}*/

/** \endcond*/

#endif //OOLUA_PROXY_MEMBER_FUNCTION_H_

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
///	\file proxy_none_member_function.h
/// \brief Contains internal macros for proxing none member functions.
///////////////////////////////////////////////////////////////////////////////

#ifndef OOLUA_PROXY_NONE_MEMBER_FUNCTION_H_
#	define OOLUA_PROXY_NONE_MEMBER_FUNCTION_H_


//* \cond INTERNAL*/

#if defined __GNUC__ && defined __STRICT_ANSI__
#	pragma GCC system_header
#endif

//proxy implementations
/**
	\def OOLUA_C_FUNCTION_N
	\brief Internal macro which generates the function body for a proxied C Function
	\hideinitializer
	\pre Function being proxied has at least one parameter
	\param return_value The type returned by the function or the type with traits
	\param func Function name which is to be proxied
	\param ... __VA_ARGS__ of function parameters which may have traits
*/
#define OOLUA_C_FUNCTION_N(return_value, func, ...) \
	OOLUA_PARAMS_CONCAT(1, __VA_ARGS__) \
	typedef OOLUA::INTERNAL::return_type_traits<return_value > R; \
	typedef R::type (funcType)( OOLUA_PARAM_TYPE_CONCAT(__VA_ARGS__) ) ; \
	OOLUA::INTERNAL::Proxy_none_member_caller<R, LVD::is_void< R::type >::value >:: \
		call<funcType OOLUA_TPARAMS_CONCAT(__VA_ARGS__)> \
			(vm, &func OOLUA_PPARAMS_CONCAT(__VA_ARGS__)); \
	OOLUA_BACK_CONCAT(__VA_ARGS__) \
	return OOLUA::INTERNAL::lua_return_count< Type_list<R OOLUA_RETURNS_CONCAT(__VA_ARGS__) >::type> ::out;

/**
	\def OOLUA_C_FUNCTION_0
	\brief Internal macro which generates the function body for a proxied C Function
	\hideinitializer
	\pre Function being proxied has no parameters
	\param return_value The type returned by the function or the type with traits
	\param func Function name which is to be proxied
*/
#define OOLUA_C_FUNCTION_0(return_value, func) \
	typedef OOLUA::INTERNAL::return_type_traits<return_value > R; \
	typedef R::type (funcType)() ; \
	OOLUA::INTERNAL::Proxy_none_member_caller<R, LVD::is_void< R::type >::value >:: \
		call<funcType>(vm, &func); \
	return R::out;

/**
	\def OOLUA_CFUNC_INTERNAL_2
	\brief Internal macro which creates a generic proxy function and body
	\hideinitializer
	\param FunctionName Name of the function to be proxied
	\param ProxyName Name that will be given to the proxy function
*/
#define OOLUA_CFUNC_INTERNAL_2(FunctionName, ProxyName) \
int ProxyName(lua_State* vm) \
{ \
	return OOLUA::INTERNAL::proxy_c_function_with_default_traits(vm, FunctionName); \
}

/**
	\def OOLUA_CFUNC_INTERNAL_1
	\brief Internal macro where only a function name has been suppplied
	\hideinitializer
	\param FunctionName Name used both for the proxied function and the proxy function.
*/
#define OOLUA_CFUNC_INTERNAL_1(FunctionName) \
	OOLUA_CFUNC_INTERNAL_2(FunctionName, FunctionName)

/**
	\def OOLUA_STATIC_FUNC_INTERNAL_2
	\brief Internal macro for class static function
	\hideinitializer
	\details Proxies a class static function which has the name FunctionName, using
	the ProxyName which is how it will be known in Lua
	\param FunctionName Name of the function to be proxied
	\param ProxyName Name of the proxy function
*/
#define OOLUA_STATIC_FUNC_INTERNAL_2(FunctionName, ProxyName) \
	static OOLUA_CFUNC_INTERNAL_2(class_::FunctionName, ProxyName)

/**
	\def OOLUA_STATIC_FUNC_INTERNAL_1
	\brief Internal macro for a class static function
	\hideinitializer
	\details Proxies a class static function using FunctionName for both the function
	that will be proxied and the proxy function's name.
	\param FunctionName Name of the static function to proxy and the name of the proxy function
*/
#define OOLUA_STATIC_FUNC_INTERNAL_1(FunctionName) \
	OOLUA_STATIC_FUNC_INTERNAL_2(FunctionName, FunctionName)

/** \endcond*/

#endif //OOLUA_PROXY_NONE_MEMBER_FUNCTION_H_
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
	\file proxy_public_member.h
	\brief Proxies a class public member variable
*/

#ifndef OOLUA_PROXY_PUBLIC_MEMBER_H_
#	define OOLUA_PROXY_PUBLIC_MEMBER_H_

/** \cond INTERNAL */


namespace OOLUA
{
	namespace INTERNAL
	{
		template<typename T, int byValue, int hasProxyType>
		struct shouldPushValueByReference
		{
			enum {value = 0};
			static void push(lua_State* vm, T* input)
			{
				OOLUA::push(vm, *input);
			}
		};

		/*Not by value and has a proxy type*/
		template<typename T>
		struct shouldPushValueByReference<T, 0, 1>
		{
			enum {value = 0};
			static void push(lua_State* vm, T* input)
			{
				if(*input) OOLUA::push(vm, *input); else lua_pushnil(vm);
			}
		};

		/*by value and has a proxy type*/
		template<typename T>
		struct shouldPushValueByReference<T, 1, 1>
		{
			enum {value = 1};
			static void push(lua_State* vm, T* input)
			{
				OOLUA::push(vm, input);
			}
		};

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T>
		struct shouldPushValueByReference<OOLUA_SHARED_TYPE<T>, 1, 0>
		{
			enum {value = 0};
			static void push(lua_State* vm, OOLUA_SHARED_TYPE<T>* input)
			{
				if(*input) OOLUA::push(vm, *input); else lua_pushnil(vm);
			}
		};
#endif

		struct PushPublicMember
		{
			template<typename T>
			static void push(lua_State* vm, T* input)
			{
				shouldPushValueByReference<T,
					//can not have a pointer to reference.
					//T will either be a pointer to type
					//or type
					LVD::by_value<T>::value
					, has_a_proxy_type<typename LVD::raw_type<T>::type >::value >
						::push(vm, input);
			}
		};

		struct GetPublicMember
		{
			template<typename T>
			static void get(lua_State* vm, T* output)
			{
				get_imp(vm, output
					, LVD::Int2type<
						LVD::by_value<T>::value
						&& has_a_proxy_type<typename LVD::raw_type<T>::type>::value
					>()
				); // NOLINT
			}
			template<typename T>
			static void get_imp(lua_State* vm, T* output, LVD::Int2type<0>)
			{
				OOLUA::INTERNAL::LUA_CALLED::get(vm, 2, *output);
			}
			template<typename T>
			static void get_imp(lua_State* vm, T* output, LVD::Int2type<1>)
			{
				T* temp(0);
				OOLUA::INTERNAL::LUA_CALLED::get(vm, 2, temp);
				*output = *temp;
			}
		};

	} // namespace INTERNAL // NOLINT
} // namespace OOLUA


#define OOLUA_MGET_INTERNAL_2(PublicInstance, GetterName) \
	int GetterName(lua_State* vm) const \
	{ \
		OOLUA::INTERNAL::PushPublicMember::push(vm, &m_this->PublicInstance); \
		return 1; \
	}

#define OOLUA_MGET_INTERNAL_1(PublicInstance) \
	OOLUA_MGET_INTERNAL_2(PublicInstance, get_##PublicInstance)


#define OOLUA_MSET_INTERNAL_2(PublicInstance, SetterName) \
	int SetterName(lua_State* vm) \
	{ \
		OOLUA::INTERNAL::GetPublicMember::get(vm, &m_this->PublicInstance); \
		return 0; \
	}

#define OOLUA_MSET_INTERNAL_1(PublicInstance) \
	OOLUA_MSET_INTERNAL_2(PublicInstance, set_##PublicInstance)


#define OOLUA_MGET_MSET_INTERNAL_3(PublicInstance, GetterName, SetterName) \
	OOLUA_MGET_INTERNAL_2(PublicInstance, GetterName) \
	OOLUA_MSET_INTERNAL_2(PublicInstance, SetterName)

#define OOLUA_MGET_MSET_INTERNAL_1(PublicInstance) \
	OOLUA_MGET_INTERNAL_1(PublicInstance) \
	OOLUA_MSET_INTERNAL_1(PublicInstance)

	/** \endcond */

#endif //OOLUA_PROXY_PUBLIC_MEMBER_H_

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

#ifndef OOLUA_STACK_GET_H_
#define OOLUA_STACK_GET_H_


namespace OOLUA
{
	//fwd
	template<typename T>class Proxy_class;
	//fwd

	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		//fwd
		template<typename T>
		T* check_index(lua_State * vm, int index);

		template<typename T>
		T* check_index_no_const(lua_State * vm, int index);

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T>
		struct stack_checker;
#endif


		namespace PULL
		{
			void set_index_gc_value_to_false(lua_State* vm, int idx);
		}
		//fwd

		namespace LUA_CALLED
		{
			void get_class_type_error(lua_State* const vm, char const* expected_type);
			void get_error(lua_State* vm, int idx, char const* expected_type);

			template<typename Raw_type, int is_const>
			struct stack_class_type
			{
				static void get(lua_State* const vm, int idx, Raw_type*& class_type)
				{
					class_type = check_index<Raw_type>(vm, idx);
				}
			};

			template<typename Raw_type>
			struct stack_class_type<Raw_type, 0>
			{
				static void get(lua_State* const vm, int idx, Raw_type*& class_type)
				{
					class_type = check_index_no_const<Raw_type>(vm, idx);
				}
			};

			template<typename T, int is_integral, int is_convertable_to_int>
			struct get_basic_type;

			template<typename T>
			struct get_basic_type<T, 0, 1>//enum
			{
				static void get(lua_State* const vm, int idx, T &  value)
				{
					//enumeration type so a static cast should be allowed else this
					//is being called with the wrong type
					typedef char dummy_can_convert [ LVD::can_convert_to_int<T>::value ? 1 : -1] OOLUA_UNUSED;
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if( !lua_isnumber(vm, idx) ) get_error(vm, idx, "enum type");
#endif
					value = static_cast<T>(lua_tointeger(vm, idx));
				}
			};

			template<int ID>
			struct get_basic_type<Lua_ref<ID>, 0, 0>
			{
				static void get(lua_State* const vm, int idx, Lua_ref<ID> &  value)
				{
					value.lua_get(vm, idx);
				}
			};
			template<typename T>
			struct get_basic_type<T, 1, 1>
			{
				static void get(lua_State* const vm, int idx, T &  value)
				{
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if( !lua_isnumber(vm, idx) ) get_error(vm, idx, "integer compatible type");
#endif
					value = static_cast<T>(lua_tointeger(vm, idx));
				}
			};

			//either a C++11 scoped enum or a string class
			template<typename T>
			struct get_basic_type<T, 0, 0>
			{
				static void get(lua_State* const vm, int idx, T &  value)
				{
					return get_imp(vm, idx, value, LVD::Int2type<STRING::is_integral_string_class<T>::value>());
				}
				static void get_imp(lua_State* const vm, int idx, T& value, LVD::Int2type<0>)
				{
					//C++11 scoped enum
					get_basic_type<T, 1, 1>::get(vm, idx, value);
				}
				static void get_imp(lua_State* const vm, int idx, T& value, LVD::Int2type<1>)
				{
					OOLUA::STRING::get(vm, idx, value);
				}
			};

#if OOLUA_USE_SHARED_PTR == 1
		template<typename T, template <typename> class Shared_pointer_class>
		struct get_basic_type<Shared_pointer_class<T>, 0, 0>
		{
			typedef typename LVD::remove_const<T>::type raw;
			static void get(lua_State* const vm, int idx, Shared_pointer_class<T> & value)
			{
				value = !LVD::is_const<T>::value
							? stack_checker<Shared_pointer_class<raw> >::check_index_no_const(vm, idx)
							: stack_checker<Shared_pointer_class<raw> >::check_index(vm, idx);
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if (!value)
				{
					get_class_type_error(vm, LVD::is_const<T>::value
											  ? Proxy_class<raw>::class_name_const
											  : Proxy_class<raw>::class_name);
				}
#endif
			}
		};
#endif
			template<typename T, int is_integral>
			struct get_ptr;

			template<typename T>
			struct get_ptr<T, false>
			{
				static void get(lua_State* const vm, int idx, T *&  value)
				{
					typename OOLUA::INTERNAL::param_type<T>::raw* class_ptr;
					stack_class_type<typename OOLUA::INTERNAL::param_type<T>::raw
													, OOLUA::INTERNAL::param_type<T*>::is_constant
												>::get(vm, idx, class_ptr);
#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
					if(!class_ptr)
					{
						get_class_type_error(vm, OOLUA::INTERNAL::param_type<T*>::is_constant
											  ? Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name_const
											  : Proxy_class<typename OOLUA::INTERNAL::param_type<T>::raw>::class_name);
					}
#endif
					value = class_ptr;
				}
			};
			template<typename T>
			struct get_ptr<T, true>
			{
				static void get(lua_State* const vm, int idx, T *&  value)
				{
#if OOLUA_DEBUG_CHECKS == 1
					if(!value)
					{
						get_error(vm, idx, "pulling pointer to integral type and was passed NULL. OOLua can not dereference it"); // LCOV_EXCL_LINE
					}
#endif
					LUA_CALLED::get(vm, idx, *value);
				}
			};



			template<typename T>
			inline void get(lua_State* const vm, int idx, T& value)
			{
				get_basic_type<T
							, LVD::is_integral_type<T>::value
							, LVD::can_convert_to_int<T>::value >::get(vm, idx, value);
			}


			template<typename T>
			inline void get(lua_State* const vm, int idx, T *&  value)
			{
				get_ptr<T, LVD::is_integral_type<T>::value>::get(vm, idx, value);
			}


			//pulls a pointer from the stack which Cpp will then own and call delete on
			template<typename T>
			inline void get(lua_State* const vm, int idx, OOLUA::cpp_acquire_ptr<T>&  value)
			{
				typedef cpp_acquire_ptr<T> Type;
				typedef typename Type::raw raw;
				stack_class_type<raw, Type::is_constant>::get(vm, idx, value.m_ptr);

#if OOLUA_RUNTIME_CHECKS_ENABLED  == 1
				if(!value.m_ptr)
				{
					get_class_type_error(vm, Type::is_constant
										  ? Proxy_class<raw>::class_name_const
										  : Proxy_class<raw>::class_name);
				}
#endif
				INTERNAL::PULL::set_index_gc_value_to_false(vm, idx);
			}

		} // namespace LUA_CALLED // NOLINT
	} // namespace INTERNAL // NOLINT
	/**\endcond*/


} // namespace OOLUA

#endif //OOLUA_STACK_GET_H_
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
	\file proxy_function_exports.h
	\date Thu Apr 10 18:41:11 2014
	\details
	Configurable values as set when generating this file
	\li class_functions 15 - Maximum amount of class functions that can be registered for each proxied type	(Default 15)
	\note Warning this file was generated, edits to the file will not persist if it is regenerated.
*/

#ifndef PROXY_FUNCTION_EXPORTS_H_
#	define PROXY_FUNCTION_EXPORTS_H_
/** \cond INTERNAL */

#define LUA_MEMBER_FUNC_1(Class, func1) {#func1, &Class::func1},
#define LUA_MEMBER_FUNC_2(Class, func1, func2) LUA_MEMBER_FUNC_1(Class, func1)  LUA_MEMBER_FUNC_1(Class, func2)
#define LUA_MEMBER_FUNC_3(Class, func1, func2, func3) LUA_MEMBER_FUNC_2(Class, func1, func2)  LUA_MEMBER_FUNC_1(Class, func3)
#define LUA_MEMBER_FUNC_4(Class, func1, func2, func3, func4) LUA_MEMBER_FUNC_3(Class, func1, func2, func3)  LUA_MEMBER_FUNC_1(Class, func4)
#define LUA_MEMBER_FUNC_5(Class, func1, func2, func3, func4, func5) LUA_MEMBER_FUNC_4(Class, func1, func2, func3, func4)  LUA_MEMBER_FUNC_1(Class, func5)
#define LUA_MEMBER_FUNC_6(Class, func1, func2, func3, func4, func5, func6) LUA_MEMBER_FUNC_5(Class, func1, func2, func3, func4, func5)  LUA_MEMBER_FUNC_1(Class, func6)
#define LUA_MEMBER_FUNC_7(Class, func1, func2, func3, func4, func5, func6, func7) LUA_MEMBER_FUNC_6(Class, func1, func2, func3, func4, func5, func6)  LUA_MEMBER_FUNC_1(Class, func7)
#define LUA_MEMBER_FUNC_8(Class, func1, func2, func3, func4, func5, func6, func7, func8) LUA_MEMBER_FUNC_7(Class, func1, func2, func3, func4, func5, func6, func7)  LUA_MEMBER_FUNC_1(Class, func8)
#define LUA_MEMBER_FUNC_9(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9) LUA_MEMBER_FUNC_8(Class, func1, func2, func3, func4, func5, func6, func7, func8)  LUA_MEMBER_FUNC_1(Class, func9)
#define LUA_MEMBER_FUNC_10(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10) LUA_MEMBER_FUNC_9(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9)  LUA_MEMBER_FUNC_1(Class, func10)
#define LUA_MEMBER_FUNC_11(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11) LUA_MEMBER_FUNC_10(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10)  LUA_MEMBER_FUNC_1(Class, func11)
#define LUA_MEMBER_FUNC_12(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12) LUA_MEMBER_FUNC_11(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11)  LUA_MEMBER_FUNC_1(Class, func12)
#define LUA_MEMBER_FUNC_13(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12, func13) LUA_MEMBER_FUNC_12(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12)  LUA_MEMBER_FUNC_1(Class, func13)
#define LUA_MEMBER_FUNC_14(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12, func13, func14) LUA_MEMBER_FUNC_13(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12, func13)  LUA_MEMBER_FUNC_1(Class, func14)
#define LUA_MEMBER_FUNC_15(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12, func13, func14, func15) LUA_MEMBER_FUNC_14(Class, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10, func11, func12, func13, func14)  LUA_MEMBER_FUNC_1(Class, func15)

/// @def end the assigning of functions to the array
#define CLASS_LIST_MEMBERS_END {0, 0}};}

/// @def define the constants in the class, which are the the class name and the member function array
#define CLASS_LIST_MEMBERS_START_OOLUA_NON_CONST(Class)\
namespace OOLUA { \
char const OOLUA::Proxy_class< Class >::class_name[] = #Class;\
OOLUA::Proxy_class< Class >::Reg_type OOLUA::Proxy_class< Class >::class_methods[]={
// NOLINT

#define CLASS_LIST_MEMBERS_START_OOLUA_CONST(Class)\
namespace OOLUA { \
char const OOLUA::Proxy_class< Class >::class_name_const[] = #Class "_const";\
OOLUA::Proxy_class< Class >::Reg_type_const OOLUA::Proxy_class< Class >::class_methods_const[]={
// NOLINT

#define EXPORT_OOLUA_FUNCTIONS_0_(mod, Class)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_1_(mod, Class, p0)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_1(OOLUA::Proxy_class< Class > , p0)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_2_(mod, Class, p0, p1)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_2(OOLUA::Proxy_class< Class > , p0, p1)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_3_(mod, Class, p0, p1, p2)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_3(OOLUA::Proxy_class< Class > , p0, p1, p2)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_4_(mod, Class, p0, p1, p2, p3)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_4(OOLUA::Proxy_class< Class > , p0, p1, p2, p3)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_5_(mod, Class, p0, p1, p2, p3, p4)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_5(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_6_(mod, Class, p0, p1, p2, p3, p4, p5)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_6(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_7_(mod, Class, p0, p1, p2, p3, p4, p5, p6)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_7(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_8_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_8(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_9_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_9(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_10_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_10(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_11_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_11(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_12_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_12(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_13_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_13(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_14_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_14(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)\
	CLASS_LIST_MEMBERS_END
#define EXPORT_OOLUA_FUNCTIONS_15_(mod, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)\
	CLASS_LIST_MEMBERS_START_ ##mod(Class)\
	LUA_MEMBER_FUNC_15(OOLUA::Proxy_class< Class > , p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)\
	CLASS_LIST_MEMBERS_END

#define EXPORT_OOLUA_FUNCTIONS_0_CONST(Class) \
	EXPORT_OOLUA_FUNCTIONS_0_(OOLUA_CONST, Class)
#define EXPORT_OOLUA_FUNCTIONS_0_NON_CONST(Class) \
	EXPORT_OOLUA_FUNCTIONS_0_(OOLUA_NON_CONST, Class)
#define EXPORT_OOLUA_FUNCTIONS_1_CONST(Class, p0) \
	EXPORT_OOLUA_FUNCTIONS_1_(OOLUA_CONST, Class, p0)
#define EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(Class, p0) \
	EXPORT_OOLUA_FUNCTIONS_1_(OOLUA_NON_CONST, Class, p0)
#define EXPORT_OOLUA_FUNCTIONS_2_CONST(Class, p0, p1) \
	EXPORT_OOLUA_FUNCTIONS_2_(OOLUA_CONST, Class, p0, p1)
#define EXPORT_OOLUA_FUNCTIONS_2_NON_CONST(Class, p0, p1) \
	EXPORT_OOLUA_FUNCTIONS_2_(OOLUA_NON_CONST, Class, p0, p1)
#define EXPORT_OOLUA_FUNCTIONS_3_CONST(Class, p0, p1, p2) \
	EXPORT_OOLUA_FUNCTIONS_3_(OOLUA_CONST, Class, p0, p1, p2)
#define EXPORT_OOLUA_FUNCTIONS_3_NON_CONST(Class, p0, p1, p2) \
	EXPORT_OOLUA_FUNCTIONS_3_(OOLUA_NON_CONST, Class, p0, p1, p2)
#define EXPORT_OOLUA_FUNCTIONS_4_CONST(Class, p0, p1, p2, p3) \
	EXPORT_OOLUA_FUNCTIONS_4_(OOLUA_CONST, Class, p0, p1, p2, p3)
#define EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(Class, p0, p1, p2, p3) \
	EXPORT_OOLUA_FUNCTIONS_4_(OOLUA_NON_CONST, Class, p0, p1, p2, p3)
#define EXPORT_OOLUA_FUNCTIONS_5_CONST(Class, p0, p1, p2, p3, p4) \
	EXPORT_OOLUA_FUNCTIONS_5_(OOLUA_CONST, Class, p0, p1, p2, p3, p4)
#define EXPORT_OOLUA_FUNCTIONS_5_NON_CONST(Class, p0, p1, p2, p3, p4) \
	EXPORT_OOLUA_FUNCTIONS_5_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4)
#define EXPORT_OOLUA_FUNCTIONS_6_CONST(Class, p0, p1, p2, p3, p4, p5) \
	EXPORT_OOLUA_FUNCTIONS_6_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5)
#define EXPORT_OOLUA_FUNCTIONS_6_NON_CONST(Class, p0, p1, p2, p3, p4, p5) \
	EXPORT_OOLUA_FUNCTIONS_6_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5)
#define EXPORT_OOLUA_FUNCTIONS_7_CONST(Class, p0, p1, p2, p3, p4, p5, p6) \
	EXPORT_OOLUA_FUNCTIONS_7_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6)
#define EXPORT_OOLUA_FUNCTIONS_7_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6) \
	EXPORT_OOLUA_FUNCTIONS_7_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6)
#define EXPORT_OOLUA_FUNCTIONS_8_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7) \
	EXPORT_OOLUA_FUNCTIONS_8_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7)
#define EXPORT_OOLUA_FUNCTIONS_8_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7) \
	EXPORT_OOLUA_FUNCTIONS_8_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7)
#define EXPORT_OOLUA_FUNCTIONS_9_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8) \
	EXPORT_OOLUA_FUNCTIONS_9_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8)
#define EXPORT_OOLUA_FUNCTIONS_9_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8) \
	EXPORT_OOLUA_FUNCTIONS_9_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8)
#define EXPORT_OOLUA_FUNCTIONS_10_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
	EXPORT_OOLUA_FUNCTIONS_10_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define EXPORT_OOLUA_FUNCTIONS_10_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
	EXPORT_OOLUA_FUNCTIONS_10_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define EXPORT_OOLUA_FUNCTIONS_11_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
	EXPORT_OOLUA_FUNCTIONS_11_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define EXPORT_OOLUA_FUNCTIONS_11_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
	EXPORT_OOLUA_FUNCTIONS_11_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define EXPORT_OOLUA_FUNCTIONS_12_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
	EXPORT_OOLUA_FUNCTIONS_12_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
#define EXPORT_OOLUA_FUNCTIONS_12_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
	EXPORT_OOLUA_FUNCTIONS_12_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
#define EXPORT_OOLUA_FUNCTIONS_13_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
	EXPORT_OOLUA_FUNCTIONS_13_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)
#define EXPORT_OOLUA_FUNCTIONS_13_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
	EXPORT_OOLUA_FUNCTIONS_13_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)
#define EXPORT_OOLUA_FUNCTIONS_14_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13) \
	EXPORT_OOLUA_FUNCTIONS_14_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)
#define EXPORT_OOLUA_FUNCTIONS_14_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13) \
	EXPORT_OOLUA_FUNCTIONS_14_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)
#define EXPORT_OOLUA_FUNCTIONS_15_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14) \
	EXPORT_OOLUA_FUNCTIONS_15_(OOLUA_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)
#define EXPORT_OOLUA_FUNCTIONS_15_NON_CONST(Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14) \
	EXPORT_OOLUA_FUNCTIONS_15_(OOLUA_NON_CONST, Class, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)
/** \endcond */

/** \addtogroup OOLuaExporting
@{
	\def OOLUA_EXPORT_NO_FUNCTIONS
	\hideinitializer
	\brief Inform that there are no functions of interest
	\param Class
*/
#define OOLUA_EXPORT_NO_FUNCTIONS(Class)\
	EXPORT_OOLUA_FUNCTIONS_0_NON_CONST(Class)\
	EXPORT_OOLUA_FUNCTIONS_0_CONST(Class)

/**@}*/

#endif

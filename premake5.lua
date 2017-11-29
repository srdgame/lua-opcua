-- A solution
workspace "lua-opcua"
	configurations { "Debug", "Release"}

project "opcua"
	kind "SharedLib"
	language "C++"
	location "build"
	targetprefix ""
	targetdir "bin/%{cfg.buildcfg}"

	includedirs { "/usr/include/lua5.3", "inc", "/home/cch/github/freeopcua/include" }
	files { "src/**.h", "src/**.cpp"}

	libdirs { "/home/cch/github/freeopcua/.libs" }
	links { "pthread", "xml2", "boost_filesystem", "boost_thread"}
	linkoptions { "-Wl,--whole-archive -lopcuacore -lopcuaprotocol -lopcuaclient -lopcuaserver -Wl,--no-whole-archive" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"


group(cfg_name.."/Tests")

project(cfg_name.."-Server-Test")
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/Sandbox/Server/src/test/"

	debugdir("%{wks.location}/bin/"..outdir.."/Server")
	targetdir("%{wks.location}/bin/"..outdir.."/Server")
	objdir("%{wks.location}/bin-int/"..outdir.."/Server")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Sandbox"]["Server"]
	}

	links {
		dependencies["Sandbox"]["Server"]
	}

	filter "configurations:Debug*"
		symbols "On"
		optimize "Off"
		defines { "GE_DEBUG" }
	filter "configurations:Release*"
		symbols "On"
		optimize "Debug"
		defines { "GE_RELEASE"}
	filter "configurations:Dist*"
		symbols "Off"
		optimize "Speed"
		defines { "GE_DIST" }

	filter "system:windows"
		defines { "GE_WINDOWS" }
	filter "system:macosx"
		defines { "GE_MACOSX", "GE_UNIX" }
	filter "system:linux"
		defines { "GE_LINUX", "GE_UNIX" }

group(cfg_name)
project(cfg_name.."-Server")
	kind "StaticLib"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/Sandbox/Server/src/main/"
	
	debugdir("%{wks.location}/bin/"..outdir.."/Server")
	targetdir("%{wks.location}/bin/"..outdir.."/Server")
	objdir("%{wks.location}/bin-int/"..outdir.."/Server")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Sandbox"]["Server"]
	}

	links {
		dependencies["Sandbox"]["Server"]
	}

	filter "configurations:Debug*"
		symbols "On"
		optimize "Off"
		defines { "GE_DEBUG" }
	filter "configurations:Release*"
		symbols "On"
		optimize "Debug"
		defines { "GE_RELEASE"}
	filter "configurations:Dist*"
		symbols "Off"
		optimize "Speed"
		defines { "GE_DIST" }

	filter "system:windows"
		defines { "GE_WINDOWS" }
	filter "system:macosx"
		defines { "GE_MACOSX", "GE_UNIX" }
	filter "system:linux"
		defines { "GE_LINUX", "GE_UNIX" }

project(cfg_name.."-ServerLauncher")
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/Sandbox/ServerLauncher/src/"
	
	debugdir("%{wks.location}/bin/"..outdir.."/ServerLauncher")
	targetdir("%{wks.location}/bin/"..outdir.."/ServerLauncher")
	objdir("%{wks.location}/bin-int/"..outdir.."/ServerLauncher")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Sandbox"]["ServerLauncher"]
	}

	links {
		dependencies["Sandbox"]["ServerLauncher"]
	}

	filter "configurations:Debug*"
		symbols "On"
		optimize "Off"
		defines { "GE_DEBUG" }
	filter "configurations:Release*"
		symbols "On"
		optimize "Debug"
		defines { "GE_RELEASE"}
	filter "configurations:Dist*"
		symbols "Off"
		optimize "Speed"
		defines { "GE_DIST" }

	filter "system:windows"
		defines { "GE_WINDOWS" }
	filter "system:macosx"
		defines { "GE_MACOSX", "GE_UNIX" }
	filter "system:linux"
		defines { "GE_LINUX", "GE_UNIX" }

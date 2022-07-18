group "GenesisEngine/Tests"

project("GenesisEngine-Core-Test")
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/GenesisEngine/Core/src/test/"

	debugdir("%{wks.location}/bin/"..outdir.."/Core")
	targetdir("%{wks.location}/bin/"..outdir.."/Core")
	objdir("%{wks.location}/bin-int/"..outdir.."/Core")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["GenesisEngine"]["Core"]
	}

	links {
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

group "GenesisEngine"
project("GenesisEngine-Core")
	kind "StaticLib"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/GenesisEngine/Core/src/main/"
	
	debugdir("%{wks.location}/bin/"..outdir.."/Core")
	targetdir("%{wks.location}/bin/"..outdir.."/Core")
	objdir("%{wks.location}/bin-int/"..outdir.."/Core")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["GenesisEngine"]["Core"]
	}

	links {
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
	

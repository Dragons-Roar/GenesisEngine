group "GenesisEngine/Tests"

project("GenesisEngine-Editor-Test")
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/GenesisEngine/Editor/src/test/"

	debugdir("%{wks.location}/bin/"..outdir.."/Editor")
	targetdir("%{wks.location}/bin/"..outdir.."/Editor")
	objdir("%{wks.location}/bin-int/"..outdir.."/Editor")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["GenesisEngine"]["Editor"]
	}

	links {
		dependencies["GenesisEngine"]["Editor"]
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
project("GenesisEngine-Editor")
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/GenesisEngine/Editor/src/main/"
	
	debugdir("%{wks.location}/bin/"..outdir.."/Editor")
	targetdir("%{wks.location}/bin/"..outdir.."/Editor")
	objdir("%{wks.location}/bin-int/"..outdir.."/Editor")

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["GenesisEngine"]["Editor"]
	}

	links {
		dependencies["GenesisEngine"]["Editor"]
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
	


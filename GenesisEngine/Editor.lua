group "Genesis"
project "Genesis-Editor"
	kind "ConsoleApp"
	systemversion "latest"
	language "C++"
	cppdialect(cfg_cxxStandard)
	location "%{wks.location}/GenesisEngine/src/GenesisEditor/"

	debugdir("%{wks.location}/bin/"..outdir)
	targetdir("%{wks.location}/bin/"..outdir)
	objdir("%{wks.location}/bin-int/"..outdir)

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Genesis-Editor"]
	}

	links {
		dependencies["Genesis-Editor"]
	}

	defines { globalDefines }

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

	filter { "system:windows", "configurations:dist" }
		linkoptions '/SUBSYSTEM:WINDOWS'

	filter "system:windows"
		postbuildcommands {
			--"robocopy %{wks.location}/GenesisEngine/assets/GenesisEditor/ bin/%{wks.system}/bin\windows\Debug-x64\GenesisEngine-Editor\assets\ /PURGE"
			"echo %{wks.location}/GenesisEngine/assets/GenesisEditor/"..outdir.."/assets/ /PURGE"
		}

outdir = "%{cfg.system}/%{cfg.longname}/%{prj.name}"
outputdir = outdir

include "defines.lua"
include "config.lua"
include "dependencies.lua"

workspace "GenesisEngine"
	configurations {
		"Debug-x64", "Release-x64", "Dist-x64",
		"Debug-x86", "Release-x86", "Dist-x86"
	}

	filter "configurations:*86"
		architecture "x86"
		defines { "GE_X86" }
	filter "configurations:*64"
		architecture "x86_64"
		defines { "GE_X64" }

	group "Libs"

	-- Engine
	include "GenesisEngine/Core.lua"
	include "GenesisEngine/Server.lua"
	include "GenesisEngine/Client.lua"
	include "GenesisEngine/Editor.lua"

	-- Sandbox
	include "Sandbox/Server.lua"
	include "Sandbox/Client.lua"

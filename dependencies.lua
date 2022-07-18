includes = {}

includeDirs = {}
includeDirs["Sandbox"] = {}
includeDirs["Sandbox"]["Server"] = {
	"%{prj.location}/include/",
	"%{wks.location}/GenesisEngine/Core/src/main/include/",
	"%{wks.location}/GenesisEngine/Server/src/main/include/"
}
includeDirs["Sandbox"]["Client"] = {
	"./",
	"%{wks.location}/GenesisEngine/Core/src/main/include/",
	"%{wks.location}/GenesisEngine/Server/src/main/include/",
	"%{wks.location}/GenesisEngine/Client/src/main/include/"
}
includeDirs["Sandbox"]["ServerLauncher"] = {
	"./",
	"%{wks.location}/Sandbox/Server/src/main/include/"
}

includeDirs["GenesisEngine"] = {}
includeDirs["GenesisEngine"]["Server"] = {
	"%{prj.location}/include/",
	"%{wks.location}/GenesisEngine/Core/src/main/include/"
}
includeDirs["GenesisEngine"]["Client"] = {
	"%{prj.location}/include/",
	"%{wks.location}/GenesisEngine/Core/src/main/include/",
	"%{wks.location}/GenesisEngine/Server/src/main/include/"
}
includeDirs["GenesisEngine"]["Editor"] = {
	"./",
	"%{wks.location}/GenesisEngine/Core/src/main/include/",
	"%{wks.location}/GenesisEngine/Client/src/main/include/",
	"%{wks.location}/GenesisEngine/Server/src/main/include/"
}
includeDirs["GenesisEngine"]["Core"] = {
	"%{prj.location}/include/"
}

dependencies = {}
dependencies["Sandbox"] = {}
dependencies["Sandbox"]["ServerLauncher"] = {
	"GenesisEngine-Core",
	"GenesisEngine-Server",
	"Sandbox-Server"
}
dependencies["Sandbox"]["Client"] = {
	"GenesisEngine-Core",
	"GenesisEngine-Server",
	"GenesisEngine-Client",
	"Sandbox-Server"
}
dependencies["GenesisEngine"] = {}
dependencies["GenesisEngine"]["Editor"] = {
	"GenesisEngine-Core",
	"GenesisEngine-Server",
	"GenesisEngine-Client"
}

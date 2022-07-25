includeDirs = {}
dependencies = {}
local libraries = {}
luaIncludes = {}
local projects = {}

local Json = require 'json'
local data = Json.decode(readFile('./dependencies.json'))

-- Read json data
local jDependencies = data["dependencies"]
local jLibRoot = data["libRoot"]
local jProjectRoot = data["projectRoot"]
local jLinks = data["links"]
local jProjects = data["projects"]

print("LibraryRoot: "..jLibRoot)
print("ProjectRoot: "..jProjectRoot)

-- Parse Dependency Packets
for _, v in pairs(jDependencies) do
	libraries[v["name"]] = {}
	local m = libraries[v["name"]]
	m["type"] = v["library"]["type"]
	m["script"] = v["library"]["script"] == "provided"
	m["includes"] = "%{wks.location}/"..jLibRoot..v["name"].."/"..v["library"]["includeDir"]
	table.insert(luaIncludes, jLibRoot..v["name"].."/premake5.lua")
end

-- Parse Project Dependencies
for _, v in pairs(jProjects) do
	projects[v["name"]] = {}
	local p = projects[v["name"]]
	p["location"] = jProjectRoot..v["location"]
	p["includes"] = jProjectRoot..v["includes"]
end

-- Loop through generated data and add it to dependencies and includeDirs
for prj, v in pairs(jLinks) do
	includeDirs[prj] = {}
	local iDir = includeDirs[prj]

	-- If Project exists in dependency projects, it cannot be an executable and needs no links
	local dep = nil
	if(projects[prj] == nil) then
		dependencies[prj] = {}
		dep = dependencies[prj]
	end

	for _, lib in pairs(v) do
		if(projects[lib] == nil) then
			if(libraries[lib] == nil) then
				error(lib.." could not be found in libs nor in projects!")
			else
				if(projects[prj] == nil) then
					table.insert(dep, lib)
				end
				table.insert(iDir, libraries[lib]["includes"])
			end
		else 
			if(projects[prj] == nil) then
				table.insert(dep, lib)
			end
			table.insert(iDir, projects[lib]["includes"])
		end
	end
end

print("Includes:")
for prj, v in pairs(includeDirs) do
	print("  "..prj..":")
	for _, dir in pairs(v) do
		print("  - "..dir)
	end
end

print("Links:")
for prj, v in pairs(dependencies) do
	print("  "..prj..":")
	for _, dir in pairs(v) do
		print("  - "..dir)
	end
end

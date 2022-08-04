includeDirs = {}
dependencies = {}
luaIncludes = {}
globalDefines = {}
local libraries = {}
local projects = {}
local singleFiles = {}
local headerOnlies = {}

local Json = require 'json'
local data = Json.decode(readFile('./dependencies.json'))

-- Read json data
local jDependencies = data["dependencies"]
local jLibRoot = data["libRoot"]
local jProjectRoot = data["projectRoot"]
local jLinks = data["links"]
local jProjects = data["projects"]
local jIncludes = data["includes"]

print("LibraryRoot: "..jLibRoot)
print("ProjectRoot: "..jProjectRoot)

globalDefines = data["defines"]

-- Parse Dependency Packets
for _, v in pairs(jDependencies) do
	if v["packet"]["type"] == "file" then
		-- These are header only single file dependencies
		singleFiles[v["name"]] = {}
		local s = singleFiles[v["name"]]
		s["path"] = "%{wks.location}/"..jLibRoot..v["group"].."/"..v["packet"]["path"]
		s["include"] = "%{wks.location}/"..jLibRoot..v["group"].."/"..v["library"]["includeDir"]
		s["url"] = v["packet"]["url"]
	elseif v["packet"]["type"] == "local" then
		-- These are local dependencies
		headerOnlies[v["name"]] = {}
		local h = headerOnlies[v["name"]]
		h["include"] = "%{wks.location}/"..jLibRoot..v["group"].."/"..v["library"]["includeDir"]
	else
		-- These are dependencies that are needed to build and included
		libraries[v["name"]] = {}
		local m = libraries[v["name"]]
		m["type"] = v["library"]["type"]
		m["script"] = v["library"]["script"]

		m["includes"] = "%{wks.location}/"..jLibRoot..v["name"].."/"..v["library"]["includeDir"]

		if m["type"] == "premake" then
			print("Adding "..v["name"].." as a premake library...")

			if m["script"] == "provided" then
				table.insert(luaIncludes, jLibRoot..v["name"].."/premake5.lua")
			else
				table.insert(luaIncludes, jLibRoot..m["script"])
			end
		elseif m["type"] == "header" then
			print("Adding "..v["name"].." as a header only library...")
		end
	end
end

-- Parse Project Dependencies
for _, v in pairs(jProjects) do
	projects[v["name"]] = {}
	local p = projects[v["name"]]
	p["location"] = jProjectRoot..v["location"]
	p["includes"] = jProjectRoot..v["includes"]
end

for prj, v in pairs(jIncludes) do
	includeDirs[prj] = {}

	for _, lib in pairs(v) do
		if libraries[lib]["includes"] ~= nil then
			table.insert(includeDirs[prj], libraries[lib]["includes"])
		end
	end
end

-- Loop through generated data and add it to dependencies and includeDirs
for prj, v in pairs(jLinks) do
	depCount = 0

	includeDirs[prj] = {}
	local iDir = includeDirs[prj]

	-- If Project exists in dependency projects, it cannot be an executable and needs no links
	local dep = nil
	if(projects[prj] == nil) then
		dependencies[prj] = {}
		dep = dependencies[prj]
	end

	for _, lib in pairs(v) do
		if(singleFiles[lib] ~= nil) then
			depCount = depCount + 1
			table.insert(iDir, singleFiles[lib]["include"])
		elseif(headerOnlies[lib] ~= nil) then
			depCount = depCount + 1
			table.insert(iDir, headerOnlies[lib]["include"])
		elseif(string.endswith(lib, ".lib")) then
			depCount = depCount + 1
			table.insert(dep, lib)
		else
			if(projects[lib] == nil) then
				if(libraries[lib] == nil) then
					error(lib.." could not be found in libs nor in projects!")
				else
					if(projects[prj] == nil and (libraries[lib] == nil or libraries[lib]["type"] == "premake")) then
						depCount = depCount + 1
						table.insert(dep, lib)
					end
					table.insert(iDir, libraries[lib]["includes"])
				end
			else
				if(projects[prj] == nil and (libraries[lib] == nil or libraries[lib] == "premake")) then
					depCount = depCount + 1
					table.insert(dep, lib)
				end
				table.insert(iDir, projects[lib]["includes"])
			end
		end
	end
end

-- Print Include Results
print("Includes:")
for prj, v in pairs(includeDirs) do
	print("  "..prj..":")
	for _, dir in pairs(v) do
		print("  - "..dir)
	end
end

-- Print Link Results
print("Links:")
for prj, v in pairs(dependencies) do
	print("  "..prj..":")
	for _, dir in pairs(v) do
		print("  - "..dir)
	end
end

-- Print Define Results
print("Defines:")
for _, def in pairs(globalDefines) do
	print("  "..def)
end

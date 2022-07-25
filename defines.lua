-- Checks if a file exits
function fileExists(file)
	local f = io.open(file, "rb")
	if f then f:close() end
	return f ~= nil
end

-- Reads lines from a file
function readFileLines(file)
	if not fileExists(file) then return {} end
	local lines = {}
	for line in io.lines(file) do 
		lines[#lines + 1] = line
	end
	return lines
end

-- Reads file as string
function readFile(file)
	if not fileExists(file) then return {} end
	local lines = {}
	local file = io.open(file, "rb")
	io.input(file)
	return io.read("*all")
end

-- Gets a line of a file
function readLine(file, line)
	local lines = readFile(file)
	if lines == nil then return nil end
	return lines[line]
end

-- Gets the amount of entries in a table
function tableLength(t)
	local count = 0
	for _ in pairs(t) do count = count + 1 end
	return count
end

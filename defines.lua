-- Checks if a file exits
function fileExists(file)
	local f = io.open(file, "rb")
	if f then f:close() end
	return f ~= nil
end

-- Reads lines from a file
function readFile(file)
	if not fileExists(file) then return {} end
		local lines = {}
	for line in io.lines(file) do 
		lines[#lines + 1] = line
	end
	return lines
end

-- Gets a line of a file
function readLine(file, line)
	local lines = readFile(file)
	if lines == nil then return nil end
	return lines[line]
end

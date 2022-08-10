newaction {
	trigger = "clean",
	description = "Remove all project files / make files",
	execute = function()
		print("Removing Visual Studio Project Files...")
		os.rmdir("./.vs")
		os.remove("**.sln")
		os.remove("**.vcxproj")
		os.remove("**.vcxproj.filters")
		os.remove("**.vcxproj.user")

		print("Removing CodeLite Project Files...")
		os.rmdir("./.vs")
		os.remove("**.workspace")
		os.remove("**.project")

		print("Removing compiled binaries...")
		os.remove("/bin/**.exe")
		os.remove("/bin/**.lib")

		print("Removing intermediates...")
		os.rmdir('./bin-int/')

		print("Removing program data bases...")
		os.remove('./bin/**.pdb')

		print("Removing makefiles...")
		os.remove('./**Makefile')

		print("Delete MSBuild logs...")
		os.remove('./GenesisEngine/**.log')
		os.remove('./Sandbox/**.log')

		print("Done!")
	end
}

# Genesis Engine
The goal of the Genesis Engine is to be a simple, (lightweight) and easy to use game engine  
The main goal of this engine is to make the production fo voxel games simple by adding default algorithms for performance  

The Scripting Language will be C++ at the beginning but may be expanded to C# or JS  

# Current Features
Currently there are no features as this project is still in development

# How to install
1. To Install the Engine you need [Node.js](https://nodejs.org/en/), [Git](https://git-scm.com) and [Premake5](https://premake.github.io)
2. Put the premake executable into one of your path folders or into the root of this project
3. The next step is to run the ``install.ps1`` script in a terminal, this will download the required JS libraries and git modules
4. If youre not on windows, just run
	>``npm install`` and ``node ./install.js``
5. Now execute premake using ``premake5 vs2022``
6. If you are not using Visual Studio 2022 enter your generator
7. If you are using Visual Studio, you can now open the Solution File
8. Inside of Visual Studio always make sure that the Configuration and Platforms are matching!  
   For example: 
   > `Debug-x86` with `Win32` and  
	 `Debug-x64` with `x64` but not  
	 `Debug-x64` with `Win32`
9. Now you can run your desired project!
10. Every Files you code for your game has to be in the Sandbox Projects

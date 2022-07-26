# Genesis Engine
The goal of the Genesis Engine is to be a simple, (lightweight) and easy to use game engine  
The main goal of this engine is to make the production fo voxel games simple by adding default algorithms for performance  

The Scripting Language will be C++ at the beginning but may be expanded to C# or JS  

## Current Features
Currently there are no features as this project is still in development

## How to install
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

## Project Structure
| Path | Description |
|------|-------------|
| GenesisEngine/ | Here are the sources for the Engine Modules |
| GenesisEngine/Client/ | Here are sources stored that are needed for the Client. Those sources range from Renderer, to Audio and so on |
| GenesisEngine/Server/ | This project stores sources for the Server. Those sources range from Networking, Server, Authentification and so on |
| GenesisEngine/Core/ | Here are sources stored that are needed for the entire engine. The project also holds sources for abstractions |
| GenesisEngine/Editor | This project stores the sources that are needed to run the Genesis Editor |
| Sandbox/ | Here are the sources of the game stored |
| Sandbox/Client | Here is the client code stored |
| Sandbox/Server | Here is special server code stored. In the most cases, no sources are needed in here because the engine already handles the most use cases |
| ThirdParty/ | Here are libraries stored |
| bin/ | Binaries are stored in this folder |
| bin-int/ | Here are the intermediate files stored |

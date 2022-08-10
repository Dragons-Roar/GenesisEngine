const MSBuild = require('msbuild')

const { exit, env } = require('process')
const argv = process.argv.slice(2)

const { exec, spawn } = require('child_process')
const dependencies = require('./dependencies.json')
const fs = require('fs')

const vsVersions = [ '2005', '2008', '2010', '2012', '2013', '2015', '2017', '2019', '2022' ]
const args = require('minimist')(process.argv.slice(2))

let system = ''
switch(process.platform) {
	case 'win32': system = 'windows'
		break
	case 'android': system = 'android'
		break
	case 'darwin': system = 'macosx'
		break
	case 'linux': system = 'linux'
}

let config = 'Debug-x64'
let platform = 'x64'

if(argv[0] == undefined) {
	console.log(args._[0])

	printHelp()
	exit()
} else {
	if(argv.length > 1) {

		if(args.system != undefined) {
			system = args.system
		}
		if(args.config != undefined) {
			config = args.config
		}
		if(args.platform != undefined) {
			platform = args.platform
		}

		if(args.exe != undefined) {
			if(dependencies.applications[args.exe] != undefined) {
				const app = dependencies.applications[args.exe]
					.replace('%{platform}', platform)
					.replace('%{config}', config)
					.replace('%{system}', system)
				
				const dir = app.split('/')
				let exe = changeDir = dir.pop()

				runApplication = exe
				changeDir = dir.join('/')
			}
		}
	}

	switch(argv[0]) {
		case "help":	printHelp()
			break
		case "compile":	compile()
			break
		default:		runPremake()
	}
}

function printHelp() {
	console.log('Genesis Build System')
	console.log('(C) Justin Jakob 2022')
	console.log()
	console.log('compile			Generates makefiles, then compiles using the makefiles')
	console.log('clean			Removes all project files')
	console.log('codelite		Generate Codelite rpoject files')
	console.log('gmake			Generate GNU makefiles for POSIX, MinGW, and Cygin')
	vsVersions.forEach((v) => {
		console.log(`vs${v}			Generate Visual Studio ${v} project files`)
	})
	console.log('xcode4			Generate Apple Xcode 4 project files')
}
function runPremake() {
	exec(`premake5.exe ${argv.join(' ')}`, (err, data) => {
		console.error(err)
		console.log(data.toString())
	})
}
function compile() {
	console.log('Compiling...')
	if(dependencies.visualStudioVersion == undefined) {
		console.error('Currently only Visual Studio is supported!')
		exit(-1)
	}

	if(!vsVersions.includes(dependencies.visualStudioVersion)) {
		console.error(`Visual Studio Version ${dependencies.visualStudioVersion} is not supported!`)
		console.error('Supported Visual Studio Versions: ', vsVersions.join(', '))
		exit(-2)
	}

	if(dependencies.solutionName == undefined) {
		console.error('Solution Name is not defined!')
		console.error('Add "solutionName": "YOUR_SOLUTION_NAME" to your dependencies.json!')
		exit(-3)
	}

	if(dependencies.msbuildPath == undefined) {
		dependencies.msbuildPath = `C:\\Program Files\\Microsoft Visual Studio\\${dependencies.visualStudioVersion}\\Community\\MSBuild\\Current\\Bin\\msbuild.exe`
		if(fs.existsSync(dependencies.msbuildPath)) {
			fs.writeFileSync('./dependencies.json', JSON.stringify(dependencies, null, 4), { encoding: 'utf-8' })
		} else {
			console.error('MSBuildPath not defined and the default path that matches your Visual Studio Version could not be resolved!')
			console.error('Add "msbuildPath": "YOUR_MS_BUILD_PATH" to your dependencies.json')
			exit(-4)
		}
	}

	const msbuild = new MSBuild()
	msbuild.msbuildPath = dependencies.msbuildPath
	msbuild.sourcePath = `./${dependencies.solutionName}.sln`
	msbuild.overrideParams.push(`/property:Configuration=${config}`)
	msbuild.overrideParams.push(`/property:Platform=${platform}`)
	msbuild.overrideParams.push('-verbosity:minimal')
	msbuild.on('error', e => {
		console.error(e)
	})

	msbuild.on('done', () => {
	})

	msbuild.build()
}

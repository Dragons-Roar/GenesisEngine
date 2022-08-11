// This file is used to generate vscode launch.json
// It will generate all launch configs that are specified in genesis.json

const config = require('./genesis.json')
const dependencies = require('./dependencies.json')
const FS = require('fs')

var launch = {
	version: '0.2.0',
	configurations: [
	]
}
var tasks = {
	version: '2.0.0',
	tasks: [
	]
}
var settings = {
	"files.associations": {
		algorithm: "cpp"
	},
	"C_Cpp.default.includePath": [
		"${workspaceFolder}/Genesis/src/"
	]
}

Object.keys(config.launchConfigs.projects).forEach(prj => {
	const prjName = config.launchConfigs.projects[prj].alias
	const args = config.launchConfigs.projects[prj].args

	config.launchConfigs.configs.forEach(cfg => {
		launch.configurations.push({
			name: `${prjName}-${cfg}`,
			type: 'cppvsdbg',
			request: 'launch',
			program: `\${workspaceFolder}/bin/windows/${cfg}/${prj}/${prj}.exe`,
			args,
			stopAtEntry: false,
			cwd: `\${workspaceFolder}/bin/windows/${cfg}/${prj}`,
			externalConsole: true,
			preLaunchTask: `build-${cfg.toLowerCase()}`
		})
	})
})

config.launchConfigs.configs.forEach(cfg => {
	const label = `build-${cfg.toLowerCase()}`

	tasks.tasks.push({
		label,
		type: 'shell',
		command: 'msbuild',
		args: [
			`/p:Configuration=${cfg}`,
			`/p:Platform=${cfg.substring(cfg.indexOf('-') + 1)}`,
			'-verbosity:minimal'
		],
		group: 'build',
		presentation: {
			reveal: 'silent'
		},
		problemMatcher: '$msCompile'
	})
})

config.includeDirs.forEach(inc => {
	settings['C_Cpp.default.includePath'].push(inc)
})

FS.writeFileSync('./.vscode/launch.json', JSON.stringify(launch, null, 4), { encoding: 'utf-8' })
FS.writeFileSync('./.vscode/tasks.json', JSON.stringify(tasks, null, 4), { encoding: 'utf-8' })
FS.writeFileSync('./.vscode/settings.json', JSON.stringify(settings, null, 4), { encoding: 'utf-8' })

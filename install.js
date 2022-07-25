const fs = require('fs')
const data = require('./dependencies.json')
const Git = require('simple-git').default()

const addSubmodule = async (link, path) => {
	if(fs.existsSync(path)) { console.log(`Submodule ${link} already exists in ${path}!`); return; }

	console.log(`Cloning from ${link} into ${path} and adding as submodule...`)
	await Git.submoduleAdd(link, path)
	console.log(`Finished cloning ${link}!`)
}

data.dependencies.forEach(d => {
	const name = d.name
	const packet = d.packet

	console.log(`Installing ${name}...`)

	if(packet.type == 'git') {
		addSubmodule(packet.repo, `.${data.libRoot}${d.name}`)
	}

	console.log('Finished installing!')
})

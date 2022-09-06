const fs = require('fs')
const data = require('./dependencies.json')

const Git = require('simple-git').default()
const https = require('https')
const Path = require('path')

const addSubmodule = async (link, path) => {
	if (fs.existsSync(path)) { console.log(`Submodule ${link} already exists in ${path}!`); return; }

	console.log(`Cloning from ${link} into ${path} and adding as submodule...`)
	await Git.submoduleAdd(link, path)
	console.log(`Finished cloning ${link}!`)
}
const addFile = async (url, path, name) => {
	console.log(`Cloning from ${url} into ${path} as ${name}...`)

	// Check if dir exists, if not, create one
	if (!fs.existsSync(path)) {
		console.log(`Creating ${path}...`)
		fs.mkdirSync(Path.join(__dirname, path), { recursive: true })
	}

	// Check if the file already exists, if it exists, delete it
	if (fs.existsSync(path + name)) {
		console.log(`File ${path}${name} already exists! Deleting...`)
		fs.rmSync(path + name)
	}

	// Download file
	console.log(`Downloaing ${name} from ${url} into ${path}`)
	https.get(url, (res) => {
		const file = fs.createWriteStream(path + name)
		res.pipe(file)
		file.on('finish', () => {
			file.close()
			console.log(`Successfully donwloaded ${name} into ${path} from ${url}!`)
		})
	}).on('error', e => {
		console.error("Error: ", e)
	})
}

data.dependencies.forEach(d => {
	const name = d.name
	const packet = d.packet

	console.log(`Installing ${name}...`)

	if (packet.type == 'git') {
		addSubmodule(packet.repo, `${data.libRoot}${d.name}`)
	} else if (packet.type == 'file') {
		addFile(packet.url, data.libRoot + d.group + "/" + packet.path, packet.name)
	}
})

#include <GenesisCore/ConfigFile.hpp>

namespace ge {
	namespace core {
		/* ---> ConfigFile <--- */
		ConfigFile::ConfigFile(String file): file(file), ConfigSection(nullptr) {
		}
		ConfigFile::~ConfigFile() {
		}

		void ConfigFile::load() { _load(); }
		void ConfigFile::load(String file) { this->file = file; _load(); }
		void ConfigFile::_load() {
			handle = toml::parse_file(file);
			this->ConfigSection::handle = &handle;
		}

		void ConfigFile::save() { _save(file); }
		void ConfigFile::save(String file) { _save(file); }
		void ConfigFile::_save(const String& file) {
			std::fstream fout(file, std::ios::out);
			fout << handle << std::endl;
			fout.close();
		}

		ConfigSection& ConfigFile::getSection(String key) {
			ConfigSection sec(handle[key].as_table());
			return sec;
		}

		/* ---> ConfigSection <--- */
		String ConfigSection::getString(String key) const {
			return handle->get(key)->as_string()->get();
		}
		int32 ConfigSection::getInt32(String key) const {
			return handle->get(key)->as_integer()->get();
		}
		uint32 ConfigSection::getUInt32(String key) const {
			return handle->get(key)->as_integer()->get();
		}
		float32 ConfigSection::getFloat32(String key) const {
			return handle->get(key)->as_floating_point()->get();
		}
		float64 ConfigSection::getFloat64(String key) const {
			return handle->get(key)->as_floating_point()->get();
		}
		bool ConfigSection::getBool(String key) const {
			return handle->get(key)->as_boolean()->get();
		}

		String ConfigSection::getDefaultString(String key, String def) {
			if(contains(key)) return getString(key);
			set<String>(key, def);
			return def;
		}
		int32 ConfigSection::getDefaultInt32(String key, int32 def) {
			if(contains(key)) return getInt32(key);
			set<int32>(key, def);
			return def;
		}
		uint32 ConfigSection::getDefaultUInt32(String key, uint32 def) {
			if(contains(key)) return getUInt32(key);
			set<uint32>(key, def);
			return def;
		}
		float32 ConfigSection::getDefaultFloat32(String key, float32 def) {
			if(contains(key)) return getFloat32(key);
			set<float32>(key, def);
			return def;
		}
		float64 ConfigSection::getDefaultFloat64(String key, float64 def) {
			if(contains(key)) return getFloat64(key);
			set<float64>(key, def);
			return def;
		}
		bool ConfigSection::getDefaultBool(String key, bool def) {
			if(contains(key)) return getBool(key);
			set<bool>(key, def);
			return def;
		}

		void ConfigSection::erase(String key) {
			if(handle->contains(key)) { handle->erase(key); }
		}

		bool ConfigSection::isString(String key) const {
			return handle->get(key)->is_string();
		}
		bool ConfigSection::isInt(String key) const {
			return handle->get(key)->is_integer();
		}
		bool ConfigSection::isFloat32(String key) const {
			return handle->get(key)->is_floating_point();
		}
		bool ConfigSection::isFloat64(String key) const {
			return handle->get(key)->is_floating_point();
		}
		bool ConfigSection::isBool(String key) const {
			return handle->get(key)->is_boolean();
		}
		bool ConfigSection::isNumber(String key) const {
			return handle->get(key)->is_number();
		}

		bool ConfigSection::contains(String key) const {
			return handle->contains(key);
		}
	}
}

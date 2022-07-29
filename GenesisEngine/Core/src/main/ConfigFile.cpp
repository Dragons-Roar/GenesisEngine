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
		void ConfigSection::setString(String key, String value) {
			handle->insert_or_assign(key, value);
		}
		void ConfigSection::setInt32(String key, int32 value) {
			handle->insert_or_assign(key, value);
		}
		void ConfigSection::setUInt32(String key, uint32 value) {
			handle->insert_or_assign(key, value);
		}
		void ConfigSection::setFloat32(String key, float32 value) {
			handle->insert_or_assign(key, value);
		}
		void ConfigSection::setFloat64(String key, float64 value) {
			handle->insert_or_assign(key, value);
		}
		void ConfigSection::setBool(String key, bool value) {
			handle->insert_or_assign(key, value);
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

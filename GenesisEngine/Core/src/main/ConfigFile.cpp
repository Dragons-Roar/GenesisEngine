#include <GenesisCore/ConfigFile.hpp>
#include <GenesisCore/Utils.hpp>

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

		/* ---> ConfigSection <--- */
		String ConfigSection::getString(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getString(handle, list);
			} else {
				if(!handle->contains(key)) { GE_ThrowException(exceptions::KeyNotFound(key)); return ""; }
				auto val = handle->get(key);
				switch(val->type()) {
					case toml::node_type::string:
						return val->as_string()->get();
						break;
					case toml::node_type::boolean:
						return val->as_boolean()->get() ? "true" : "false";
						break;
					case toml::node_type::integer:
						return std::to_string(val->as_integer()->get());
						break;
					case toml::node_type::floating_point:
						return std::to_string(val->as_floating_point()->get());
						break;
				}
				GE_ThrowException(exceptions::WrongValueType(key, "bool"));
			}
			return "";
		}
		String ConfigSection::_getString(toml::table* table, List<String>& keys) const {
			String key = keys.popLast();
			if(table->contains(key)) {
				auto val = table->get(key);
				if(keys.size() == 0) {
					switch(val->type()) {
						case toml::node_type::string:
							return val->as_string()->get();
							break;
						case toml::node_type::boolean:
							return val->as_boolean()->get() ? "true" : "false";
							break;
						case toml::node_type::integer:
							return std::to_string(val->as_integer()->get());
							break;
						case toml::node_type::floating_point:
							return std::to_string(val->as_floating_point()->get());
							break;
					}
					GE_ThrowException(exceptions::WrongValueType(key, "string"));
				}
				if(val->is_table()) {
					return _getString(val->as_table(), keys);
				}
			} else {
				GE_ThrowException(exceptions::KeyNotFound(key.c_str()));
			}
			return "";
		}

		int32 ConfigSection::getInt32(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getInt<int32>(handle, list);
			} else {
				return static_cast<int32>(handle->get(key)->as_integer()->get());
			}
		}
		uint32 ConfigSection::getUInt32(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getInt<uint32>(handle, list);
			} else {
				return static_cast<uint32>(handle->get(key)->as_integer()->get());
			}
		}
		float32 ConfigSection::getFloat32(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getFloat<float32>(handle, list);
			} else {
				return static_cast<float32>(handle->get(key)->as_floating_point()->get());
			}
		}
		float64 ConfigSection::getFloat64(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getFloat<float64>(handle, list);
			} else {
				return static_cast<float64>(handle->get(key)->as_floating_point()->get());
			}
		}
		bool ConfigSection::getBool(String key, bool deep) const {
			if(deep) {
				List<String> list;
				Utils::splitString(list, key, '.');
				list.reverse();
				return _getBool(handle, list);
			} else {
				if(!handle->contains(key)) { GE_ThrowException(exceptions::KeyNotFound(key)); return ""; }
				auto val = handle->get(key);
				switch(val->type()) {
					case toml::node_type::boolean: {
						return handle->get(key)->as_boolean()->get();
					}
					case toml::node_type::string: {
						String str = val->as_string()->get();
						std::transform(str.begin(), str.end(), str.begin(), ::tolower);
						if(str == "true" || str == "on") return true;
						if(str == "false" || str == "off") return false;
						break;
					}
					case toml::node_type::integer: {
						return val->as_integer()->get() != 0;
						break;
					}
				}
				GE_ThrowException(exceptions::WrongValueType(key, "bool"));
			}
		}
		bool ConfigSection::_getBool(toml::table* table, List<String>& keys) const {
			String key = keys.popLast();
			if(table->contains(key)) {
				auto val = table->get(key);
				if(keys.size() == 0) {
					switch(val->type()) {
						case toml::node_type::boolean: {
							return handle->get(key)->as_boolean()->get();
						}
						case toml::node_type::string: {
							String str = val->as_string()->get();
							std::transform(str.begin(), str.end(), str.begin(), ::tolower);
							if(str == "true" || str == "on") return true;
							if(str == "false" || str == "off") return false;
							break;
						}
						case toml::node_type::integer: {
							return val->as_integer()->get() != 0;
							break;
						}
					}
					GE_ThrowException(exceptions::WrongValueType(key, "bool"));
					return false;
				}

				if(val->is_table()) {
					return _getBool(val->as_table(), keys);
				}
			} else {
				GE_ThrowException(exceptions::KeyNotFound(key.c_str()));
				return false;
			}
			return false;
		}

		List<String> ConfigSection::keys(bool deep, bool sort) const {
			List<String> out;
			if(deep) {
				List<String> prefix;
				_keys(prefix, handle, out);
				if(sort) {
					out.sort([](const String& a, const String& b) {
						return Utils::countChars(a, '.') < Utils::countChars(b, '.');
					});
				}
			} else {
				for(auto it = handle->begin(); it != handle->end(); ++it) {
					out.add(String(it->first.str()));
				}
			}
			return out;
		}
		void ConfigSection::keys(bool deep, KeyParseFunction func) const {
			if(deep) {
				List<String> prefix;
				_keys(prefix, handle, func);
			} else {
				for(auto it = handle->begin(); it != handle->end(); ++it) {
					func(String(it->first.str()));
				}
			}
		}

		void ConfigSection::_keys(List<String>& prefix, toml::table* handle, List<String>& list) const {
			for(auto it = handle->begin(); it != handle->end(); ++it) {
				if(it->second.is_table()) {
					prefix.add(String(it->first.str()));
					_keys(prefix, it->second.as_table(), list);
				} else {
					if(prefix.size() > 0) {
						list.add(prefix.join(".") + "." + String(it->first.str()));
					} else {
						list.add(String(it->first.str()));
					}
				}
			}
			if(prefix.size() > 0) {
				prefix.popLast();
			}
		}
		void ConfigSection::_keys(List<String>& prefix, toml::table* handle, KeyParseFunction func) const {
			for(auto it = handle->begin(); it != handle->end(); ++it) {
				if(it->second.is_table()) {
					prefix.add(String(it->first.str()));
					_keys(prefix, it->second.as_table(), func);
				} else {
					if(prefix.size() > 0) {
						func(prefix.join(".") + "." + String(it->first.str()));
					} else {
						func(String(it->first.str()));
					}
				}
			}
			if(prefix.size() > 0) {
				prefix.popLast();
			}
		}

		ConfigSection ConfigSection::getSection(String key) {
			if(handle->contains(key)) {
				ConfigSection sec = (handle->get(key)->as_table());
				return sec;
			} else {
				std::cout << "Inserting table..." << std::endl;
				handle->insert(key, toml::table());
				ConfigSection sec = (handle->get(key)->as_table());
				return sec;
			}
		}

		String ConfigSection::getDefaultString(String key, String def) {
			if(contains(key)) return getString(key, false);
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
		bool ConfigSection::isFloat(String key) const {
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

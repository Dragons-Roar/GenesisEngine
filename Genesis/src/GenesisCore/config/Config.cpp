#include "Config.hpp"
#include "GenesisCore/Utils.hpp"

namespace ge {
	namespace core {
		/* ----- Config Section ----- */
		void ConfigFile::load(const String& file) {
			GE_ProfileFunction();

			std::fstream in(file, std::ios::in | std::ios::binary);
			if(!in.is_open()) {
				GE_Warn("File '{0}' has not been found!", file);
				return;
			}

			handle = nlohmann::json::parse(in);
			in.close();
		}

		void ConfigSection::getAsJSONObjects(nlohmann::json& json) {
			if(key != "") json[key] = handle;
			if(sections.size() < 1) return;
			for(auto it = sections.begin(); it != sections.end(); ++it) {
				it->second->getAsJSONObjects(json);
			}
		}

		void ConfigFile::save(const String& file, bool pretty) {
			GE_ProfileFunction();

			// Go into child sections and add their values recursively to this handle
			getAsJSONObjects(handle);

			std::fstream out(file, std::ios::out | std::ios::binary);
			if(pretty) {
				out << std::setw(4) << handle << std::endl;
			} else {
				out << handle << std::endl;
			}
			out.close();
		}

		void ConfigSection::keys(bool deep, KeyFunction func) {
			if(deep) {
				std::vector<String> v;
				_keys(v, func);
				return;
			}

			auto items = handle.items();
			for(auto it = items.begin(); it != items.end(); ++it) {
				func(it.key());
			}
		}
		void ConfigSection::_keys(std::vector<String>& prefix, KeyFunction func) {
			if(key != "") prefix.push_back(key);
			auto items = handle.items();
			String s = "";
			for(uint32 i = 0; i < prefix.size(); ++i) {
				s += prefix[i] + ".";
			}
			for(auto it = items.begin(); it != items.end(); ++it) {
				if(handle[it.key()].is_object()) continue;
				if(handle[it.key()].is_array()) {
					auto array = handle[it.key()];
					for(uint32 i = 0; i < array.size(); ++i) {
						func(s + it.key() + "." + std::to_string(i));
					}
					continue;
				}
				func(s + it.key());
			}
			for(auto it = sections.begin(); it != sections.end(); ++it) {
				it->second->_keys(prefix, func);
			}
			if(key != "") prefix.erase(prefix.end() - 1);
		}

		bool ConfigSection::isDefined(const String& key) const {
			return handle.contains(key);
		}
		bool ConfigSection::isNull(const String& key) const {
			return handle[key].is_null();
		}
		bool ConfigSection::isPrimitive(const String& key) const {
			return handle[key].is_primitive();
		}
		bool ConfigSection::isNumber(const String& key) const {
			return handle[key].is_number();
		}
		bool ConfigSection::isFloat(const String& key) const {
			return handle[key].is_number_float();
		}
		bool ConfigSection::isInteger(const String& key) const {
			return handle[key].is_number_integer();
		}
		bool ConfigSection::isUnsigned(const String& key) const {
			return handle[key].is_number_unsigned();
		}
		bool ConfigSection::isString(const String& key) const {
			return handle[key].is_string();
		}
		bool ConfigSection::isBool(const String& key) const {
			return handle[key].is_boolean();
		}
		bool ConfigSection::isSection(const String& key) const {
			return handle[key].is_object();
		}
		bool ConfigSection::isArray(const String& key) const {
			return handle[key].is_array();
		}
		ConfigSection::~ConfigSection() {
		}

		/* ------ Config File ------- */
		ConfigFile ConfigFile::fromSection(const String& file, ConfigSection& sec) {
			ConfigFile cf(file);
			cf.handle = sec.getHandle();
			cf.key = "";
			return cf;
		}
	}
}

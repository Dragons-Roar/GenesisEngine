#include "Config.hpp"
#include "GenesisCore/Utils.hpp"

namespace ge {
	namespace core {
		/* ----- Config Section ----- */
		void ConfigFile::load(const String& file) {
			GE_ProfileFunction();

			std::fstream in(file, std::ios::in | std::ios::binary);
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

		/* ------ Config File- ------ */
		ConfigSection::~ConfigSection() {
		}
	}
}

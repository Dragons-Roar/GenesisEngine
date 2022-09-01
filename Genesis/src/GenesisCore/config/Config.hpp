#pragma once
#include "GenesisCore/Color.hpp"
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/GenesisBase.hpp"
#include "GenesisCore/Logger.hpp"
#include "GenesisCore/Utils.hpp"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace ge {
	namespace core {
		namespace exceptions {
			struct WrongValueType: public ge::core::exceptions::GenesisRuntimeException {
				WrongValueType(const String& key, const String& got, const String& expected): ge::core::exceptions::GenesisRuntimeException("Got " + got + " at '" + key + "', but expected '" + expected + "'!") {}
			};
		}

		class ConfigSection {
		public:
			using KeyFunction = std::function<void(const String&)>;

			ConfigSection(): handle(nlohmann::json()), key("") {}
			ConfigSection(const nlohmann::json& obj, const String& key = ""): key(key), handle(obj) {}

			~ConfigSection();

			/**
			 * @brief Gets or creates a section object
			 * @param key The key where to get/create the section
			 * @return const ConfigSection&
			 */
			ConfigSection* getSection(const String& key) {
				if(handle.contains(key)) {
					ConfigSection* sec = new ConfigSection(handle[key].get<nlohmann::json>(), key);
					sections.insert(std::make_pair(key, sec));
					return sec;
				}

				ConfigSection* sec = new ConfigSection(nlohmann::json(), key);
				sections.insert(std::make_pair(key, sec));
				return sec;
			}

			inline void keys(KeyFunction func) { keys(false, func); }
			void keys(bool deep, KeyFunction func);

			/**
			 * @brief Gets a value at a key
			 * @tparam T the value type
			 * @param key the key
			 * @return T
			 */
			template <typename T>
			T get(const String& key) const {
				if(handle.contains(key)) {
				}

				return handle[key].get<T>();
			}
			/**
			 * @brief Like the get function, but allows for a deep key
			 * @tparam T the value type
			 * @param key the key
			 * @return T
			 */
			template <typename T>
			T getD(const String& key, char delim = '.') const {
				std::vector<String> keys;
				Utils::splitString(keys, key, delim);

				nlohmann::json sec = handle;
				uint32 i = 0;
				while(true) {
					if(i == keys.size() - 1) {
						return sec[keys[i]].get<T>();
						break;
					}
					sec = handle[keys[i]].get<nlohmann::json>();
					++i;
				}
			}

			template <typename T>
			void set(const String& key, const T value) {
				handle[key] = value;
			}

			inline void setColor(const String& key, const Color& color) {
				set<uint32>(key, color.getRGBA());
			}
			inline const Color& getColor(const String& key) {
				Color c(handle[key].get<uint32>());
				return c;
			}

			void setVec(const String& key, const glm::vec2& value) {
				nlohmann::json arr = nlohmann::json::array({value.x, value.y});
				handle[key] = arr;
			}
			void setVec(const String& key, const glm::vec3& value) {
				nlohmann::json arr = nlohmann::json::array({value.x, value.y, value.z});
				handle[key] = arr;
			}
			void setVec(const String& key, const glm::vec4& value) {
				nlohmann::json arr = nlohmann::json::array({value.x, value.y, value.z, value.w});
				handle[key] = arr;
			}

			glm::vec2 getVec2(const String& key) {
				nlohmann::json arr = handle[key].get<nlohmann::json>();
				if(arr.is_array()) {
					if(arr.size() > 2) {
						GE_Warn("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 2);
					}
					if(arr.size() < 2) {
						GE_Error("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 2);
						return glm::vec2(arr[0]);
					}
					return glm::vec2(arr[0], arr[1]);
				}
				GE_ThrowException(exceptions::WrongValueType(key, getJSONTypeAsString(arr.type()), "Array"));
			}
			glm::vec3 getVec3(const String& key) {
				nlohmann::json arr = handle[key].get<nlohmann::json>();
				if(arr.is_array()) {
					if(arr.size() > 3) {
						GE_Warn("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 3);
					}
					if(arr.size() < 3) {
						GE_Error("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 3);
						return glm::vec3(arr[0]);
					}
					return glm::vec3(arr[0], arr[1], arr[2]);
				}
				GE_ThrowException(exceptions::WrongValueType(key, getJSONTypeAsString(arr.type()), "Array"));
			}
			glm::vec4 getVec4(const String& key) {
				nlohmann::json arr = handle[key].get<nlohmann::json>();
				if(arr.is_array()) {
					if(arr.size() > 4) {
						GE_Warn("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 4);
					}
					if(arr.size() < 4) {
						GE_Error("Array at '{0}' has a size of {1}, 2 was expected!", key, arr.size(), 4);
						return glm::vec4(arr[0]);
					}
					return glm::vec4(arr[0], arr[1], arr[2], arr[3]);
				}
				GE_ThrowException(exceptions::WrongValueType(key, getJSONTypeAsString(arr.type()), "Array"));
			}

			/**
			 * @brief Checks if the object exists, if not it will be created and returned
			 * @tparam T the value type
			 * @param key the key
			 * @param def the value to insert and return if key is undefined
			 * @return T
			 */
			template <typename T>
			T getDefault(const String& key, T def) {
				if(!handle.contains(key)) {
					handle[key] = def;
					return def;
				}

				return handle[key].get<T>();
			}

			/**
			 * @brief Checks if the key is defined
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isDefined(const String& key) const;
			/**
			 * @brief Checks if the key is null
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isNull(const String& key) const;
			/**
			 * @brief Checks if the key has a primitive value type
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isPrimitive(const String& key) const;
			/**
			 * @brief Checks if the key has a numeric value
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isNumber(const String& key) const;
			/**
			 * @brief Checks if the key has a floating point number
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isFloat(const String& key) const;
			/**
			 * @brief Checks if the key has a integer number
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isInteger(const String& key) const;
			/**
			 * @brief Checks if the key has an unsigned number
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isUnsigned(const String& key) const;
			/**
			 * @brief Checks if the key has a string value
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isString(const String& key) const;
			/**
			 * @brief Checks if the key has a boolean value
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isBool(const String& key) const;
			/**
			 * @brief Checks if the key links to another section/object
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isSection(const String& key) const;
			/**
			 * @brief Checks if the key has an array value
			 *
			 * @param key
			 * @return true
			 * @return false
			 */
			inline bool isArray(const String& key) const;

			void getAsJSONObjects(nlohmann::json& json);

			inline const nlohmann::json& getHandle() const { return handle; }

		private:
			void _keys(std::vector<String>& prefix, KeyFunction func);

			static const String& getJSONTypeAsString(nlohmann::json::value_t type) {
				switch(type) {
					case nlohmann::json::value_t::array: return "Array";
					case nlohmann::json::value_t::binary: return "Binary";
					case nlohmann::json::value_t::boolean: return "Boolean";
					case nlohmann::json::value_t::discarded: return "Discord";
					case nlohmann::json::value_t::null: return "Null";
					case nlohmann::json::value_t::number_float: return "Float";
					case nlohmann::json::value_t::number_integer: return "Integer";
					case nlohmann::json::value_t::number_unsigned: return "Unsigned";
					case nlohmann::json::value_t::object: return "Object";
					case nlohmann::json::value_t::string: return "String";
				}
				GE_Assert(false, "Unknown / Unexpected JSON Value Type!");
			}

		protected:
			String key;
			nlohmann::json handle;
			std::unordered_map<String, ConfigSection*> sections;
		};

		class ConfigFile: public ConfigSection {
		public:
			ConfigFile(const String& file): file(file), ConfigSection(nlohmann::json(), "") {}

			static ConfigFile fromSection(const String& file, ConfigSection& sec);

			void load() { load(file); }
			void load(const String& file);

			void save(bool pretty = false) { save(file, pretty); }
			void save(const String& file, bool pretty = false);

		private:
			String file;
		};
	}
}

#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/GenesisBase.hpp"
#include "GenesisCore/Logger.hpp"
#include <nlohmann/json.hpp>

namespace ge {
	namespace core {
		class ConfigSection {
		public:
			ConfigSection(const String& key, const nlohmann::json& obj): key(key), handle(obj) {}

			~ConfigSection();

			/**
			 * @brief Gets or creates a section object
			 * @param key The key where to get/create the section
			 * @return const ConfigSection&
			 */
			ConfigSection& getSection(const String& key) {
				if(handle.contains(key)) {
					ConfigSection* sec = new ConfigSection(key, handle[key].get<nlohmann::json>());
					sections.insert(std::make_pair(key, sec));
					return *sec;
				}

				ConfigSection* sec = new ConfigSection(key, nlohmann::json());
				sections.insert(std::make_pair(key, sec));
				return *sec;
			}

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

		protected:
			String key;
			nlohmann::json handle;
			std::unordered_map<String, ConfigSection*> sections;
		};

		class ConfigFile: public ConfigSection {
		public:
			ConfigFile(const String& file): file(file), ConfigSection("", nlohmann::json()) {}

			void load() { load(file); }
			void load(const String& file);

			void save(bool pretty = false) { save(file, pretty); }
			void save(const String& file, bool pretty = false);

		private:
			String file;
		};
	}
}

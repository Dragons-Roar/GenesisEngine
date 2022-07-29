#pragma once
#include "./Defines.hpp"
#include "./List.hpp"
#include <toml++/toml.h>

namespace ge {
	namespace core {
		class ConfigSection {
		public:
			ConfigSection(toml::table* table): handle(table) { }

			String getString(String key) const;
			int32 getInt32(String key) const;
			uint32 getUInt32(String key) const;
			float32 getFloat32(String key) const;
			float64 getFloat64(String key) const;
			bool getBool(String key) const;

			/// <summary>
			/// Gets a int/uint list
			/// </summary>
			/// <typeparam name="T">The int type (e.g. uint32, int32, unsinged int, ...)</typeparam>
			/// <param name="key">The key</param>
			/// <returns>The list</returns>
			template <typename T>
			List<T> getIntList(String key) const {
				List<T> out;
				toml::array* arr = handle->get(key)->as_array();
				for(uint32 i = 0; i < arr->size(); ++i) {
					out.add(static_cast<T>(arr->get(i)->as_integer()->get()));
				}
				return out;
			}
			/// <summary>
			/// Gets a float/double list
			/// </summary>
			/// <typeparam name="T">The float typ (e.g float32, float64, ...)</typeparam>
			/// <param name="key">The key</param>
			/// <returns>The list</returns>
			template <typename T>
			List<T> getFloatingList(String key) const {
				List<T> out;
				toml::array* arr = handle->get(key)->as_array();
				for(uint32 i = 0; i < arr->size(); ++i) {
					out.add(static_cast<T>(arr->get(i)->as_floating_point()->get()));
				}
				return out;
			}
			/// <summary>
			/// Gets a string list
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>The list</returns>
			List<String> getStringList(String key) const {
				List<String> out;
				toml::array* arr = handle->get(key)->as_array();
				for(uint32 i = 0; i < arr->size(); ++i) {
					out.add(arr->get(i)->as_string()->get());
				}
				return out;
			}
			/// <summary>
			/// Gets a bool list
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>The list</returns>
			List<bool> getBoolList(String key) const {
				List<bool> out;
				toml::array* arr = handle->get(key)->as_array();
				for(uint32 i = 0; i < arr->size(); ++i) {
					out.add(arr->get(i)->as_boolean()->get());
				}
				return out;
			}

			void setString(String key, String value);
			void setInt32(String key, int32 value);
			void setUInt32(String key, uint32 value);
			void setFloat32(String key, float32 value);
			void setFloat64(String key, float64 value);
			void setBool(String key, bool value);

			void erase(String key);

			bool isString(String key) const;
			bool isInt(String key) const;
			bool isFloat32(String key) const;
			bool isFloat64(String key) const;
			bool isNumber(String key) const;
			bool isBool(String key) const;

			inline bool contains(String key) const;

		protected:
			toml::table* handle;
		};

		/// <summary>
		/// A simple Toml config file wrapper
		/// </summary>
		class ConfigFile: public ConfigSection {
		public:
			/// <summary>
			/// A simple config file
			/// </summary>
			/// <param name="file">The file which will be loaded/saved</param>
			ConfigFile(String file);
			~ConfigFile();

			/// <summary>
			/// Loads the file into memory
			/// </summary>
			void load();
			/// <summary>
			/// Loads a specific file into memory
			/// </summary>
			/// <param name="file">The file to load</param>
			void load(String file);
			/// <summary>
			/// Saves a file to the loaded file's path
			/// </summary>
			void save();
			/// <summary>
			/// Saves s file to a speicifc path
			/// </summary>
			/// <param name="">The file path</param>
			void save(String file);

			/// <summary>
			/// Gets a section from the file
			/// </summary>
			/// <param name="key">The section</param>
			/// <returns>The config file section</returns>
			ConfigSection& getSection(String key);

		private:
			void _load();
			void _save(const String& file);

			String file;
			toml::table handle;
		};
	}
}

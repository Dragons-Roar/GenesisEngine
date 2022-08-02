#pragma once
#include <toml++/toml.h>
#include <GenesisCore/Logger.hpp>
#include "./GenesisBase.hpp"
#include "./List.hpp"
#include "./Defines.hpp"

namespace ge {
	namespace core {
		namespace exceptions {
			/// Throws if a key in this section was requested but not found
			struct KeyNotFound: public ge::core::exceptions::GenesisRuntimeException {
				KeyNotFound(String key): GenesisRuntimeException("Key '" + key + "' could not be found!") {}
				const String name() const override { return "ge::core::exceptions::KeyNotFound"; }
			};
			/// Throws if a key in this section was found but had an unexpected value
			struct WrongValueType: public ge::core::exceptions::GenesisRuntimeException {
				WrongValueType(String key, String assumed): GenesisRuntimeException("Key '" + key + "' has the wrong value type, " + assumed + " assumed!") {}
				const String name() const override { return "ge::core::exceptions::WrongValueType"; }
			};
		}

		class ConfigSection: public GClass {
		public:
			typedef std::function<void(const String&)> KeyParseFunction;

			ConfigSection(toml::table* table): handle(table) { }

			/// <summary>
			/// Gets a string at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			String getString(String key, bool deep = true) const;
			/// <summary>
			/// Gets a int32 at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			int32 getInt32(String key, bool deep = true) const;
			/// <summary>
			/// Gets a uint32 at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			uint32 getUInt32(String key, bool deep = true) const;
			/// <summary>
			/// Gets a float32 at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			float32 getFloat32(String key, bool deep = true) const;
			/// <summary>
			/// Gets a float64 at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			float64 getFloat64(String key, bool deep = true) const;
			/// <summary>
			/// Gets a bool at a specific key
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="deep">If the key should searched deep</param>
			/// <returns>The value</returns>
			bool getBool(String key, bool deep = true) const;

			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			String getDefaultString(String key, String def);
			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			int32 getDefaultInt32(String key, int32 def);
			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			uint32 getDefaultUInt32(String key, uint32 def);
			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			float32 getDefaultFloat32(String key, float32 def);
			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			float64 getDefaultFloat64(String key, float64 def);
			/// <summary>
			/// Gets a value at this key, if the key does not exist, it returns and sets the key to the default parameter
			/// </summary>
			/// <param name="key">The key</param>
			/// <param name="def">The default value if nothing is found</param>
			/// <returns>The value at the key or the default value</returns>
			bool getDefaultBool(String key, bool def);

			/// <summary>
			/// Gets a section from the file
			/// </summary>
			/// <param name="key">The section</param>
			/// <returns>The config file section</returns>
			ConfigSection getSection(String key);

			/// <summary>
			/// Gets every key in a toml::table
			/// </summary>
			/// <param name="deep">toml::tables in toml::tables will be parsed too</param>
			/// <param name="sort">Sorts the list of keys by the key length</param>
			/// <returns>The list of keys</returns>
			List<String> keys(bool deep = false, bool sort = false) const;

			/// <summary>
			/// Gets every key in a toml::table and passes it to a function
			/// </summary>
			/// <param name="deep">toml::tables in toml::tables will be parsed too</param>
			/// <param name="func">The function where the keys will get passed to</param>
			void keys(bool deep, KeyParseFunction func) const;
			/// <summary>
			/// Gets every key in a toml::table and passes it to a function
			/// </summary>
			/// <param name="func">The function where the keys will get passed to</param>
			inline void keys(KeyParseFunction func) const { keys(false, func); }

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

			/// <summary>
			/// Gets a list, if the list is not found it will be set and returned
			/// </summary>
			/// <typeparam name="T">The type of the list</typeparam>
			/// <param name="key">The key where to find the lsit</param>
			/// <param name="list">The default list</param>
			/// <returns>The list</returns>
			template <typename T>
			List<T> getDefaultIntList(String key, List<T> list) {
				if(contains(key)) return getIntList<T>(key);
				toml::array arr;
				arr.resize(list.size(), 0);
				for(uint32 i = 0; i < list.size(); ++i) {
					arr.push_back(list[i]);
				}
				set<toml::array>(key, arr);
				return List<T>(list);
			}

			/// <summary>
			/// Sets a value at a key
			/// </summary>
			/// <typeparam name="T">The value type</typeparam>
			/// <param name="key">The key</param>
			/// <param name="value">The value</param>
			template <typename T>
			void set(String key, T value) {
				handle->insert_or_assign(key, value);
			}

			/// <summary>
			/// Clears a key out of the list
			/// </summary>
			/// <param name="key">The key</param>
			void erase(String key);

			/// <summary>
			/// Checks if the value at the key exists and is a string
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>True if it exists and is a string</returns>
			bool isString(String key) const;
			/// <summary>
			/// Checks if the value at the key exists and is a int / uint
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>True if it exists and is a int / uint</returns>
			bool isInt(String key) const;
			/// <summary>
			/// Checks if the value at the key exists and is a float32 / float64
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>True if it exists and is a float32 / float64</returns>
			bool isFloat(String key) const;
			/// <summary>
			/// Checks if the value at the key exists and is a number (int or float)
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>True if it exists and is a number (int or float)</returns>
			bool isNumber(String key) const;
			/// <summary>
			/// Checks if the value at the key exists and is a bool
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>True if it exists and is a bool</returns>
			bool isBool(String key) const;

			/// <summary>
			/// Checks if the key exists
			/// </summary>
			/// <param name="key"></param>
			/// <returns></returns>
			inline bool contains(String key) const;

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::ConfigSection" << std::endl;
				return ss.str();
			}

		protected:
			toml::table* handle;

		private:
			String _getString(toml::table* table, List<String>& keys) const;
			template <typename T>
			T _getInt(toml::table* table, List<String>& keys) const {
				String key = keys.popLast();
				if(table->contains(key)) {
					auto val = table->get(key);
					if(keys.size() == 0) return val->as_integer()->get();
					if(val->is_table()) {
						return _getInt<T>(val->as_table(), keys);
					}
				} else {
					GE_ThrowException(exceptions::KeyNotFound(key.c_str()));
					return 0;
				}
			}
			template <typename T>
			T _getFloating(toml::table* table, List<String>& keys) const {
				String key = keys.popLast();
				if(table->contains(key)) {
					auto val = table->get(key);
					if(keys.size() == 0) return val->as_floating_point()->get();
					if(val->is_table()) {
						return _getInt<T>(val->as_table(), keys);
					}
				} else {
					GE_ThrowException(exceptions::KeyNotFound(key.c_str()));
					return 0;
				}
			}
			bool _getBool(toml::table* table, List<String>& keys) const;

			void _keys(List<String>& prefix, toml::table* handle, List<String>& list) const;
			void _keys(List<String>& prefix, toml::table* handle, KeyParseFunction func) const;
		};

		/// <summary>
		/// A simple Toml config file wrapper
		/// </summary>
		class ConfigFile: public ConfigSection, public GClass {
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

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::ConfigSection{file:" << file << "}" << std::endl;
				return ss.str();
			}

		private:
			void _load();
			void _save(const String& file);

			String file;
			toml::table handle;
		};
	}
}

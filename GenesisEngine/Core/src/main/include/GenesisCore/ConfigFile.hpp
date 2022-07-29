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
			/// Loads the file into the ram
			/// </summary>
			void load();
			/// <summary>
			/// Loads a file into the ram
			/// </summary>
			/// <param name="file">The file to load</param>
			void load(String file);
			/// <summary>
			/// Saves a file at the file's path
			/// </summary>
			void save();

			/// <summary>
			/// Gets a section from the file
			/// </summary>
			/// <param name="key">The section</param>
			/// <returns>The config file section</returns>
			ConfigSection& getSection(String key);

		private:
			void _load();

			String file;
			toml::table handle;
		};
	}
}
